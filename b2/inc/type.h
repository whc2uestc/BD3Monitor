/*
 * struct.h
 * Date   : 11-14-2014
 * Author : HouBiao
*/
#ifndef B2TYPE_H_
#define B2TYPE_H_
#include <stdio.h>
#include "../../pub/inc/type.h"
#include "cfg.h"

// 一次多普勒搜索结果
typedef struct
	{
		FLOAT value;											// 一次多普勒搜索最大相关值
		FLOAT doppler;											// 一次多普勒搜索值
		FLOAT phase;											// 一次多普勒索索最大值对应相位值

	}acqResult;

// 捕获阶段的参数
typedef struct 
	{
		FLOAT dopplerAcq;										// 捕获多普勒
		FLOAT phaseAcq;											// 捕获相位	

		NCO car;												// 载波NCO
		NCO pkg;												// 打包NCO
		unsigned short packetIndex;								// 打包索引

		unsigned short dopplerIndex;							// 多普勒搜索索引
		int doppler[2*(DOPPLERRANGE/DOPPLERSTEP)+1];
		complex packetReceive[B2PKGLEN];						// 接收信号打包
		complex packetLocal[B2PKGLEN];							// 本地信号打包
		acqResult acqResultInst[2*DOPPLERRANGE/DOPPLERSTEP+1];  // 捕获结果

	}B2AcqPrms;

// 跟踪阶段参数
typedef struct
	{
		NCO car;												// 载波 NCO

		TrkNCO prn;												// 码 NCO
		short codeIndexEarly;									// 超前码索引
		short codeIndexPrompt;									// 及时码索引
		short codeIndexLate;									// 滞后码索引

		LPF lpf;												// 滤波器
		int fll_time;											// 锁频环时间,ms
		int fll_timemax;										// 锁频环最大时间,ms

		unsigned char oneCircle;								// 一个完整扩频码周期标志

		complex accumulatorEarly;								// 累加器E支路
		complex accumulatorPrompt;								// 累加器P支路
		complex accumulatorLate;								// 累加器L支路
		complex accumulatorPromptOld;							// 缓存累加器P支路的值，用于锁频环

		FLOAT dis_dll;											// 码环鉴相输出
		FLOAT dis_pll;											// 载波环锁相环鉴相输出
		FLOAT dis_fll;											// 载波环锁频环鉴相输出
		FLOAT flt_codeLoop;										// 码环滤波器输出
		FLOAT flt_carrierLoop;									// 载波环滤波器输出
	}B2TrkPrms;

// 通道参数
typedef struct 
	{		
		char chnlPros;											// 通道进度，=1 捕获，=2 跟踪
	    char chnlID;											// 通道ID 3~6
		char code[B2PRNLEN];									// 扩频码

		B2AcqPrms acqInst;										// 捕获过程参数
		B2TrkPrms trkInst;										// 跟踪过程参数
	// for test
		NCO TCAR;												// 信号源源载波 NCO
		NCO TPRN;												// 信号PRN NCO
		short prnIndex;											// 信号源PRN 码索引0~10229
	// for test
	}B2ChnlPrms;

#endif