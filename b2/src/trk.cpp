/*
 * trk.cpp
 * Date   : 11-14-2014
 * Author : HouBiao
*/
#include <stdio.h>
#include <math.h>
#include "../inc/type.h"
#include "../inc/cfg.h"
#include "../../pub/inc/ioc.h"
#include "../../pub/inc/filter.h"
extern int outflag;


static void correlation(B2ChnlPrms *chnlInst,char dataIn)
{
	FLOAT icarrier,qcarrier;
	char codee,codep,codel;
	B2TrkPrms *trkInst = &(chnlInst->trkInst);
	icarrier = cos(2*PI*trkInst->car.phs/NCOTOTAL);
	qcarrier = sin(2*PI*trkInst->car.phs/NCOTOTAL);
	//码采样
	codee = chnlInst->code[trkInst->codeIndexEarly];
	codep = chnlInst->code[trkInst->codeIndexPrompt];
	codel = chnlInst->code[trkInst->codeIndexLate];

	//混频，解扩，积分
	trkInst->accumulatorEarly.real  += dataIn*icarrier*codee;
	trkInst->accumulatorPrompt.real += dataIn*icarrier*codep;
	trkInst->accumulatorLate.real   += dataIn*icarrier*codel;
	trkInst->accumulatorEarly.imag  -= dataIn*qcarrier*codee;
	trkInst->accumulatorPrompt.imag -= dataIn*qcarrier*codep;
	trkInst->accumulatorLate.imag   -= dataIn*qcarrier*codel;
	//载波相位累加
	trkInst->car.phs += trkInst->car.fcw;
	if (trkInst->car.phs >= NCOTOTAL)
		trkInst->car.phs -= NCOTOTAL;
	//码相位累加
	trkInst->prn.phs.phsE += trkInst->prn.fcw;
	if (trkInst->prn.phs.phsE >= NCOTOTAL)
	{
		trkInst->prn.phs.phsE -= NCOTOTAL;
		trkInst->codeIndexEarly += 1;
		if (trkInst->codeIndexEarly == B2PRNLEN)
			trkInst->codeIndexEarly = 0;
	}
	trkInst->prn.phs.phsP += trkInst->prn.fcw;
	if (trkInst->prn.phs.phsP >= NCOTOTAL)
	{
		trkInst->prn.phs.phsP -= NCOTOTAL;
		trkInst->codeIndexPrompt += 1;
		if (trkInst->codeIndexPrompt == B2PRNLEN)
		{
			trkInst->codeIndexPrompt = 0;
			trkInst->oneCircle = 1;
		}
	}
	trkInst->prn.phs.phsL += trkInst->prn.fcw;
	if (trkInst->prn.phs.phsL >= NCOTOTAL)
	{
		trkInst->prn.phs.phsL -= NCOTOTAL;
		trkInst->codeIndexLate += 1;
		if (trkInst->codeIndexLate == B2PRNLEN)
			trkInst->codeIndexLate = 0;
	}
}
static void updateTrk(B2ChnlPrms * chnlInst)
{
	B2TrkPrms *trkInst = &(chnlInst->trkInst);
	//调整频率控制
		trkInst->prn.fo = B2PRNFRQ + trkInst->flt_codeLoop;
		trkInst->prn.fcw = floor(trkInst->prn.fo/SMPFRQ*NCOTOTAL);
		FLOAT intermediateFrequency;
		if (chnlInst->chnlID == B2PID ||chnlInst->chnlID == B2DID)
		{
			intermediateFrequency = B2INTFRQ;
		}
		else
		{
			intermediateFrequency = B3INTFRQ;
		}
		trkInst->car.fo = intermediateFrequency+chnlInst->acqInst.dopplerAcq + trkInst->flt_carrierLoop;
		trkInst->car.fcw = floor(trkInst->car.fo/SMPFRQ*NCOTOTAL);

		writeToFile(trkInst->accumulatorPrompt.real,(chnlInst->chnlID-1)*11 +TRK_I_OUT);
		writeToFile(trkInst->accumulatorPrompt.imag,(chnlInst->chnlID-1)*11 +TRK_Q_OUT);
		
		writeToFile(trkInst->flt_codeLoop,(chnlInst->chnlID-1)*11 +DLL_LPF_OUT);
		writeToFile(trkInst->flt_carrierLoop,(chnlInst->chnlID-1)*11 +PLL_LPF_OUT);

		writeToFile(trkInst->dis_dll,(chnlInst->chnlID-1)*11 +DLL_DIS_OUT);
		writeToFile(trkInst->dis_pll,(chnlInst->chnlID-1)*11 +PLL_DIS_OUT);

		printf("Chnl %d: doppler = %f %f I = %f Q = %f\n",chnlInst->chnlID,trkInst->flt_carrierLoop,trkInst->flt_codeLoop,trkInst->accumulatorPrompt.real,trkInst->accumulatorPrompt.imag);
		//积分器清零
			trkInst->accumulatorEarly.real = 0;
			trkInst->accumulatorLate.real = 0;
			trkInst->accumulatorPrompt.real = 0;
			trkInst->accumulatorEarly.imag = 0;
			trkInst->accumulatorLate.imag = 0;
			trkInst->accumulatorPrompt.imag = 0;
		//标志清零
			trkInst->oneCircle = 0;
}
static void discriminator(B2TrkPrms * trkInst)
{
	FLOAT E ,L;
	//E
		E = trkInst->accumulatorEarly.real*trkInst->accumulatorEarly.real +\
			trkInst->accumulatorEarly.imag*trkInst->accumulatorEarly.imag;
	//L
		L = trkInst->accumulatorLate.real*trkInst->accumulatorLate.real +\
			trkInst->accumulatorLate.imag*trkInst->accumulatorLate.imag;
	//DLL鉴相
		trkInst->dis_dll = (sqrt(E)-sqrt(L))/(sqrt(E)+sqrt(L))/2;

	
		if (trkInst->fll_time<trkInst->fll_timemax)//FLL鉴相
		{
			FLOAT dot,cor;
			dot = trkInst->accumulatorPrompt.real*trkInst->accumulatorPromptOld.real+trkInst->accumulatorPrompt.imag*trkInst->accumulatorPromptOld.imag;
			cor = trkInst->accumulatorPromptOld.real*trkInst->accumulatorPrompt.imag-trkInst->accumulatorPromptOld.imag*trkInst->accumulatorPrompt.real;
			trkInst->dis_pll = 0.0;
			trkInst->dis_fll = atan2(cor,dot);
			trkInst->accumulatorPromptOld.real = trkInst->accumulatorPrompt.real;
			trkInst->accumulatorPromptOld.imag = trkInst->accumulatorPrompt.imag;
			trkInst->fll_time += 1;
		}
		else//PLL鉴相
		{
			trkInst->dis_pll = atan(trkInst->accumulatorPrompt.imag/trkInst->accumulatorPrompt.real);
			trkInst->dis_fll = 0.0;
		}
}
void B2Trk(B2ChnlPrms * chnlInst,char dataIn)
{	
	B2TrkPrms *trkInst = &(chnlInst->trkInst);

	// 相关运算
	correlation(chnlInst,dataIn);

	//如果是一个完整的码周期
	if (trkInst->oneCircle == 1)
	{
		// 鉴相
			discriminator(trkInst);	

		//一阶滤波
			trkInst->flt_codeLoop = codeLoopFilter(&(trkInst->lpf),trkInst->dis_dll);
				
		//二阶滤波
			trkInst->flt_carrierLoop = carrierLoopFilter(&(trkInst->lpf),trkInst->dis_pll,trkInst->dis_fll);
		
		// 更新跟踪参数
			updateTrk(chnlInst);
		

		//比特流处理
			//subFrameUpdate(chnl);

	}

	
	//↓↓↓↓↓↓ for test↓↓↓↓↓↓↓
	if (outflag == 1)
	{
		writeToFile(chnlInst->TCAR.phs,(chnlInst->chnlID-1)*11+CAR_PHS_SRC_OUT);
		writeToFile(chnlInst->TPRN.phs,(chnlInst->chnlID-1)*11+PRN_PHS_SRC_OUT);
		writeToFile(chnlInst->trkInst.car.phs,(chnlInst->chnlID-1)*11+CAR_PHS_LCL_OUT);
		writeToFile(chnlInst->trkInst.prn.phs.phsP,(chnlInst->chnlID-1)*11+PRN_PHS_LCL_OUT);
	}
	// ↑↑↑↑↑↑for test↑↑↑↑↑↑↑
	


}
