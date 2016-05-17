/*
 * trk.cpp
 * Date   : 11-14-2014
 * Author : HouBiao
*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../inc/cfg.h"
#include "../inc/type.h"
#include "../../pub/inc/fft.h"

/*
 * void initAcq(B2ChnlPrms *chnlInst)
 * 初始化一个通道捕获阶段变量
*/
static void initAcq(B2ChnlPrms *chnlInst)
{

	B2AcqPrms *acqInst = & (chnlInst->acqInst);				// 获取捕获阶段结构体指针
	
	
	//多普勒搜索值向量
	acqInst->dopplerIndex = 0;
	acqInst->doppler[0] = 0;
	int i;
	int j = 1;
	for (i=1;i<2*(DOPPLERRANGE/DOPPLERSTEP)+1;i=i+2)
	{
		acqInst->doppler[i] = DOPPLERSTEP*j;
		acqInst->doppler[i+1]= -DOPPLERSTEP*j;
		j++;
	}

	//本地载波变量
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
	acqInst->car.fo = intermediateFrequency+(acqInst->doppler[acqInst->dopplerIndex]);
	acqInst->car.phs = 0;
	acqInst->car.fcw = floor(acqInst->car.fo/SMPFRQ*NCOTOTAL);
	

	//打包变量
	acqInst->packetIndex = 0;
	acqInst->pkg.phs = 0;
	acqInst->pkg.fo = B2PKGFRQ*(1+(acqInst->doppler[acqInst->dopplerIndex])/ratioFrequency);
	acqInst->pkg.fcw = floor(acqInst->pkg.fo/SMPFRQ*NCOTOTAL);
	//清零打包
	for (i=0;i<B2PKGLEN;i++)
	{
		acqInst->packetReceive[i].real = 0.0;
		acqInst->packetReceive[i].imag = 0.0;
	}
	//由于使用FFT捕获，所以在进入捕获前完成本地码FFT的计算
	FLOAT phase;
	FLOAT fcw;
	unsigned short index;
	phase = 0;
	index = 0 ;
	fcw = floor(B2PRNFRQ/(B2PKGLEN*1000)*NCOTOTAL);
		for (i = 0; i < B2PKGLEN;i++)
		{

			acqInst->packetLocal[i].real = chnlInst->code[index];
			acqInst->packetLocal[i].imag = 0.0;
			phase = phase +fcw;
			if(phase >=NCOTOTAL)
			{
				phase = phase - NCOTOTAL;
				index = index +1;
				if (index == B2PRNLEN )
				{
					index = 0 ;
				}
			}
		}
		FFT(acqInst->packetLocal, B2PKGLEN);

	printf("Chnl %d: \tdoppler searching:%dHz\n",chnlInst->chnlID,acqInst->doppler[acqInst->dopplerIndex]);

}

/*
 * void initTrk(B2ChnlPrms * chnlInst)
 * 初始化跟踪阶段部分变量
 */
static void initTrk(B2ChnlPrms * chnlInst)
{
	

	FLOAT omegacode;												// 码环特征频率
	FLOAT omegafll;													// 锁频环特征频率
	FLOAT omegapll;													// 锁相环特征频率
	B2TrkPrms * trkInst = &(chnlInst->trkInst);						// 获取跟踪阶段参数结构体指针
	
	//码环滤波器系数
	omegacode = BANDWITHCODE/0.53;
	trkInst->lpf.dll_a = omegacode*omegacode;
	trkInst->lpf.dll_b = ALPHACODE*omegacode;
	trkInst->lpf.dll_gain = CODELOOPGAIN;
	trkInst->lpf.dll_reg = 0;
	//载波环滤波器参数
	omegafll = BANDWITHFLL/0.53;
	omegapll = BANDWITHPLL/0.7845;
	trkInst->lpf.fll_a = omegafll*omegafll;
	trkInst->lpf.fll_b = ALPHAFLL*omegafll;
	trkInst->lpf.pll_a = omegapll*omegapll*omegapll;
	trkInst->lpf.pll_b = ALPHAPLL*omegapll*omegapll;
	trkInst->lpf.pll_c = BETAPLL*omegapll;
	trkInst->lpf.pll_gain = CARRIERLOOPGAINPLL;
	trkInst->lpf.fll_gain = CARRIERLOOPGAINFLL;  
    trkInst->lpf.pll_reg0 = 0;
    trkInst->lpf.pll_reg1 = 0;

	trkInst->fll_time = 0;
	trkInst->fll_timemax = B2FLLMAXTIME;
	

	   
}

/*
 * void B2ChnlInit(B2ChnlPrms *chnlInst)
 * 初始化一个通道的参数
*/
void B2ChnlInit(B2ChnlPrms *chnlInst)

{	
	int i ;
	for (i=2;i<4;i++)
	{
		// 通道ID
		(chnlInst+i)->chnlID = i+3;
		//通道进度
		(chnlInst+i)->chnlPros = ACQ_FLG;
		//通道扩频码
		FILE *fp;
		switch(i+3)
		{
		case B2DID:
			fp = fopen(B2DCODEPATH,"rb");
			break;
		case B2PID:
			fp = fopen(B2PCODEPATH,"rb");
			break;
		case B3DID:
			fp = fopen(B3DCODEPATH,"rb");
			break;
		case B3PID:
			fp = fopen(B3PCODEPATH,"rb");
			break;
		default:
			break;
		}
		if (fp ==NULL)
		{
			printf("无法打开B2B3扩频码文件，请指定正确的文件路径！\n");
			exit(1);
		}
		fread((chnlInst+i)->code,sizeof(char),B2PRNLEN,fp);
		fclose(fp);

		// 捕获阶段初始化
		initAcq(chnlInst+i);
		// 跟踪阶段初始化
		initTrk(chnlInst+i);
		
		// ↓↓↓↓↓↓↓↓for test↓↓↓↓↓↓↓↓
		// 信号源NCO初始化
		(chnlInst+i)->TCAR.phs = 0.0;
		if (i==2||i==3)
		{
			(chnlInst+i)->TCAR.fcw = 260741328872.0;//B3
		}
		else
		{
			(chnlInst+i)->TCAR.fcw = 356984294732.0;//B2
		}
		(chnlInst+i)->TPRN.phs = 0.0;
		(chnlInst+i)->TPRN.fcw = 73038986702.0;
		(chnlInst+i)->prnIndex = 0;
		// ↑↑↑↑↑↑↑↑for test↑↑↑↑↑↑↑↑
	}

}

