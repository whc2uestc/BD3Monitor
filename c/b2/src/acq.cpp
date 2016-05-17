/*
 * acq.cpp
 * Date   : 11-14-2014
 * Author : HouBiao
*/
#include <stdio.h>
#include <math.h>

#include "../inc/type.h"
#include "../inc/cfg.h"
#include "../../pub/inc/fft.h"
#include "../../pub/inc/ioc.h"

static void updateTrk(B2ChnlPrms * chnlInst)
{
	FLOAT intermediateFrequency;

	B2TrkPrms * trkInst = &(chnlInst->trkInst);

	if (chnlInst->chnlID == B2PID ||chnlInst->chnlID == B2DID)
	{
		intermediateFrequency = B2INTFRQ;		
	}
	else
	{
		intermediateFrequency = B3INTFRQ;	
	}
	//初始化载波相位
	trkInst->car.phs = 0;
	trkInst->car.fo = intermediateFrequency + chnlInst->acqInst.dopplerAcq;
	trkInst->car.fcw = floor(trkInst->car.fo/SMPFRQ*NCOTOTAL);
	//初始化码相位
	trkInst->prn.fo = B2PRNFRQ;
	trkInst->prn.fcw = floor(trkInst->prn.fo/SMPFRQ*NCOTOTAL);

	//P
	trkInst->codeIndexPrompt = (short)floor(chnlInst->acqInst.phaseAcq);
	trkInst->prn.phs.phsP = floor((chnlInst->acqInst.phaseAcq - trkInst->codeIndexPrompt)*NCOTOTAL);
	
	//E
	trkInst->codeIndexEarly = (short)floor((chnlInst->acqInst.phaseAcq+B2DELTA));
	if (trkInst->codeIndexEarly == B2PRNLEN)
		trkInst->codeIndexEarly = 0;
	trkInst->prn.phs.phsE = floor(((chnlInst->acqInst.phaseAcq+B2DELTA) - (short)floor((chnlInst->acqInst.phaseAcq+B2DELTA)))*NCOTOTAL);
	
	//L
	FLOAT temp = ((chnlInst->acqInst.phaseAcq-B2DELTA));
	if (temp<0)
		temp = temp+ (FLOAT)B2PRNLEN;
	trkInst->codeIndexLate = (short)floor(temp);
	trkInst->prn.phs.phsL = floor((temp-floor(temp)*NCOTOTAL));
	// 初始化P支路的相关值，这里本来应该是0，但是由于除数不能为0，所以初始化为1
	trkInst->accumulatorPromptOld.real = 1.0;
	trkInst->accumulatorPromptOld.imag = 1.0;
	// 累加器清零
	trkInst->accumulatorEarly.real = 0.0;
	trkInst->accumulatorEarly.imag = 0.0;
	trkInst->accumulatorPrompt.real = 0.0;
	trkInst->accumulatorPrompt.imag = 0.0;
	trkInst->accumulatorLate.real = 0.0;
	trkInst->accumulatorLate.imag = 0.0;

	// 完整扩频码周期标志清零
	trkInst->oneCircle = 0;

	
}
static void updateAcq(B2ChnlPrms *chnlInst)
{
	B2AcqPrms *acqInst = &(chnlInst->acqInst); 
	acqInst->packetIndex = 0;
	int i;
	for (i=0;i<B2PKGLEN;i++)
	{
		acqInst->packetReceive[i].real = 0.0;
		acqInst->packetReceive[i].imag = 0.0;
	}
	FLOAT intermediateFrequency;
	FLOAT ratioFrequency;
	if (chnlInst->chnlID == B2PID ||chnlInst->chnlID == B2DID)
	{
		intermediateFrequency = B2INTFRQ;
		ratioFrequency = B2CARFRQ;
	}
	else
	{
		intermediateFrequency = B3INTFRQ;
		ratioFrequency = B3CARFRQ;
	}
	acqInst->car.fo = intermediateFrequency + (acqInst->doppler[acqInst->dopplerIndex]);
	acqInst->car.fcw = floor(acqInst->car.fo/SMPFRQ*NCOTOTAL);

	acqInst->pkg.fo = B2PKGFRQ*(1+((acqInst->doppler[acqInst->dopplerIndex]))/ratioFrequency);
	acqInst->pkg.fcw = floor(acqInst->pkg.fo/SMPFRQ*NCOTOTAL);
	printf("Chnl %d: \tdoppler searching:%dHz\n",chnlInst->chnlID,acqInst->doppler[acqInst->dopplerIndex]);
}
static  void correlation(B2ChnlPrms *chnlInst)
{
	B2AcqPrms *acqInst = &(chnlInst->acqInst);
	int i,tempi;
	FLOAT max,value;
	complex temp[B2PKGLEN];
	//接收信号FFT运算
		FFT(acqInst->packetReceive,B2PKGLEN);
	//共轭
		complexConj(acqInst->packetReceive,B2PKGLEN);
	//点乘
		for (i=0;i<B2PKGLEN;i++)
		{
			temp[i] = complexMult(acqInst->packetReceive[i],acqInst->packetLocal[i]);
		}
	//IFFT

		IFFT(temp,B2PKGLEN);
		
	// 找最大相关值
		max = 0 ;
		for (i=0;i<B2PKGLEN;i++)
		{
			 value = temp[i].real*temp[i].real + temp[i].imag*temp[i].imag;
			 
			 writeToFile(value,(chnlInst->chnlID-1)*11 +ACQ_OUT);
			 if (value > max)
			 {
				 max = value ;
				 tempi = i;
			 }

		}
		acqInst->acqResultInst[acqInst->dopplerIndex].doppler = acqInst->doppler[acqInst->dopplerIndex];
		acqInst->acqResultInst[acqInst->dopplerIndex].phase = (tempi)/(B2PKGFRQ/B2PRNFRQ);
		acqInst->acqResultInst[acqInst->dopplerIndex].value = max;
}

static  void packet(B2AcqPrms *acqInst,char data)
{
	
	//混频及打包
	
	acqInst->packetReceive[acqInst->packetIndex].real += cos(acqInst->car.phs/NCOTOTAL*2*PI)*data;
	acqInst->packetReceive[acqInst->packetIndex].imag += sin(acqInst->car.phs/NCOTOTAL*2*PI)*data;
	//相位累加
	acqInst->pkg.phs += acqInst->pkg.fcw;

	if (acqInst->pkg.phs >= NCOTOTAL)
	{
		acqInst->pkg.phs -= NCOTOTAL;
		acqInst->packetIndex += 1;
	}
	//相位累加
	acqInst->car.phs += acqInst->car.fcw;

	if (acqInst->car.phs >= NCOTOTAL)
	{
		acqInst->car.phs -= NCOTOTAL;
	}
}
/*
 * void acq(channel *chnl,char data);
 * 实现捕获
 */
void B2Acq(B2ChnlPrms *chnlInst,char data)
{
	
	B2AcqPrms *acqInst = &(chnlInst->acqInst); 

	//接收信号打包
	packet(acqInst,data);

	if (acqInst->packetIndex == B2PKGLEN)//一个完整的扩频码周期
	{
		//相关运算
		correlation(chnlInst);

		//下一个多普勒
		acqInst->dopplerIndex += 1;	

		if (acqInst->dopplerIndex == 2*(DOPPLERRANGE/DOPPLERSTEP)+1)//多普勒搜索完
		{
			int i;
			int tempi;
			FLOAT max = 0;

			// 遍历捕获结果，找到最大值
			for (i=0;i<2*(DOPPLERRANGE/DOPPLERSTEP)+1;i++)
			{
				if (acqInst->acqResultInst[i].value > max)
				{	
					max = acqInst->acqResultInst[i].value ;
					tempi = i;
				}
			}
			acqInst->dopplerAcq = acqInst->acqResultInst[tempi].doppler;
			acqInst->phaseAcq = acqInst->acqResultInst[tempi].phase;

			// 更新跟踪阶段参数
			updateTrk(chnlInst);

			// 转入跟踪
			chnlInst->chnlPros = TRK_FLG;
		
			printf("Chnl %d: dopplerAcq=%f phaseAcq=%f\n",chnlInst->chnlID,acqInst->dopplerAcq,acqInst->phaseAcq);
		}	
		else// 更新捕获阶段参数
		{
			updateAcq(chnlInst);			
		}

	}
}
