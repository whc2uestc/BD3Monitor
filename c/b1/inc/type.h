/*
 * struct.h
 * Date   : 11-14-2014
 * Author : WangHanCheng
*/
#ifndef B1TYPE_H_
#define B1TYPE_H_

#include "../../pub/inc/type.h"

#include "cfg.h"



typedef struct 
{
	NCO car;										//本地载波NCO
	NCO prn;										//本地码NCO
	NCO sub_1;										//本地BOC（1,1）NCO
	NCO sub_6;										//本地BOC（6,1）NCO
	NCO pkg;										//捕获打包NCO
	unsigned int pid;								//打包计数
	unsigned int PID;								//总打包数
	unsigned int cid;								//码片计数
	unsigned int did;								//多普勒仓计数
	int doppler[2*(DOPPLERRANGE/DOPPLERSTEP)+1];	//多普勒搜索列表
	unsigned int CID;								//码片总数
	unsigned int FID;								//FFT点数
	complex fft_prn[B1PKGLEN*2];					//本地码的FFT
	complex fft_boc[B1PKGLEN*2];					//本地BOC的FFT
	complex fft_src[B1PKGLEN*2];					//信号源的FFT
	FLOAT corr[B1PKGLEN*2];							//信号源与本地的相关值
	char rdy;										//1ms打包完成标志位
	char flg;										//搜索到峰值标志位
	char suc;										//捕获成功标志位
	char NH[B1NHLEN];								//NH码 导频通道
	FLOAT  pk_srh[2*(DOPPLERRANGE/DOPPLERSTEP)+1];	//多普勒搜索峰值
	int  phs_srh[2*(DOPPLERRANGE/DOPPLERSTEP)+1];	//多普勒搜索相位值
}B1AcqPrms;





typedef struct 
{
	NCO car;							//本地载波NCO
	TrkNCO prn;							//本地码NCO
	TrkNCO sub_1;						//本地BOC（1,1）NCO
	TrkNCO sub_6;						//本地BOC（6,1）NCO
	int doppler;						//捕获的多普勒值
	char suc;							//跟踪成功
	char rdy;							//1码片周期数据完成
	LPF  lpf;							//环路滤波参数
	unsigned int cidE;					//E路的码片计数
	unsigned int cidP;					//P路的码片计数
	unsigned int cidL;					//L路的码片计数
	FLOAT pkg_I0;						//FLL 超前I路
	FLOAT pkg_I1;						//FLL 当前I路
	FLOAT pkg_Q0;						//FLL 超前Q路
	FLOAT pkg_Q1;						//FLL 当前Q路
	complex corr_bbE;					//信号源与本地E路BOC相关值
	complex corr_bbP;					//信号源与本地P路BOC相关值
	complex corr_bbL;					//信号源与本地L路BOC相关值
	complex corr_bpE;					//信号源与本地E路伪码相关值
	complex corr_bpP;					//信号源与本地P路伪码相关值
	complex corr_bpL;					//信号源与本地L路伪码相关值
	FLOAT disD_out;						//DLL输出
	FLOAT disF_out;						//FLL输出
	FLOAT disP_out;						//PLL输出
	FLOAT prnE;							//E路本地伪码
	FLOAT bocE;							//E路本地BOC
	FLOAT prnP;							//P路本地伪码
	FLOAT bocP;							//P路本地BOC
	FLOAT prnL;							//L路本地伪码
	FLOAT bocL;							//L路本地BOC	
	FLOAT pll_out;						// PLL滤波器输出
	FLOAT dll_out;						// DLL滤波器输出
	complex src;						//信号源去载波
	unsigned int pid;					//采样点计数
	unsigned int tmr;					//跟踪时间ms

}B1TrkPrms;



typedef struct
{
	short satID;			// 卫星编号，也即PRN码编号
	B1AcqPrms acq;			// 捕获阶段参数
	B1TrkPrms trk;			// 跟踪阶段参数

	char code[B1PRNLEN];	// PRN扩频码
	char chnlPros;			// 通道进度，=1 捕获，=2 跟踪
	char chnlID;			// 通道ID 1~2
	int smp_cnt;			// 读取样本数，用于1ms输出相位
// for test down
	NCO TPRN;				// 信号源PRN NCO
	NCO TCAR;				// 信号源载波 NCO
	short prnIndex;			// 信号源PRN 码索引0~1022
// for test up
}B1ChnlPrms;

#endif