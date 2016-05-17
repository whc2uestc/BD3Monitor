/*
 * ioc.h
 * Date   : 11-14-2014
 * Author : HouBiao,WangHanCheng
*/

#ifndef IOC_H_
#define IOC_H_
#include<stdio.h>
#include"type.h"

#define FILENUM				66						// 总的输出文件数

#define DLL_DIS_OUT			0						// 文件相对编号： DLL环鉴相输出 
#define DLL_LPF_OUT			1						// 文件相对编号： DLL环滤波器输出
#define PLL_DIS_OUT			2						// 文件相对编号： PLL环鉴相输出
#define PLL_LPF_OUT			3						// 文件相对编号： PLL环滤波器输出
#define TRK_I_OUT			4						// 文件相对编号： 跟踪I路输出
#define TRK_Q_OUT			5						// 文件相对编号： 跟踪Q路输出
#define ACQ_OUT				6						// 文件相对编号： 捕获结果输出
#define PRN_PHS_SRC_OUT		7						// 文件相对编号： PRN码信号源相位输出
#define PRN_PHS_LCL_OUT		8						// 文件相对编号： PRN码本地码相位输出
#define CAR_PHS_SRC_OUT		9						// 文件相对编号： 载波信号源输出
#define CAR_PHS_LCL_OUT		10						// 文件相对编号： 载波本地相位输出

#define B1D_DLL_DIS_OUT			0					// B1D通道文件编号：DLL环鉴相输出
#define B1D_DLL_LPF_OUT			1					// B1D通道文件编号：DLL环滤波器输出
#define B1D_PLL_DIS_OUT			2					// B1D通道文件编号：PLL环鉴相输出
#define B1D_PLL_LPF_OUT			3					// B1D通道文件编号：PLL环滤波器输出
#define B1D_TRK_I_OUT			4					// B1D通道文件编号：跟踪I路输出
#define B1D_TRK_Q_OUT			5					// B1D通道文件编号：跟踪Q路输出
#define B1D_ACQ_OUT				6					// B1D通道文件编号：捕获结果输出
#define B1D_PRN_PHS_SRC_OUT		7					// B1D通道文件编号：PRN码信号源相位输出
#define B1D_PRN_PHS_LCL_OUT		8					// B1D通道文件编号：PRN码本地码相位输出
#define B1D_CAR_PHS_SRC_OUT		9					// B1D通道文件编号：载波信号源输出
#define B1D_CAR_PHS_LCL_OUT		10					// B1D通道文件编号：载波本地相位输出
				
#define B1P_DLL_DIS_OUT			11					// B1P通道文件编号：DLL环鉴相输出
#define B1P_DLL_LPF_OUT			12					// B1P通道文件编号：DLL环滤波器输出
#define B1P_PLL_DIS_OUT			13					// B1P通道文件编号：PLL环鉴相输出
#define B1P_PLL_LPF_OUT			14					// B1P通道文件编号：PLL环滤波器输出
#define B1P_TRK_I_OUT			15					// B1P通道文件编号：跟踪I路输出
#define B1P_TRK_Q_OUT			16					// B1P通道文件编号：跟踪Q路输出
#define B1P_ACQ_OUT				17					// B1P通道文件编号：捕获结果输出
#define B1P_PRN_PHS_SRC_OUT		18					// B1P通道文件编号：PRN码信号源相位输出
#define B1P_PRN_PHS_LCL_OUT		19					// B1P通道文件编号：PRN码本地码相位输出
#define B1P_CAR_PHS_SRC_OUT		20					// B1P通道文件编号：载波信号源输出
#define B1P_CAR_PHS_LCL_OUT		21					// B1P通道文件编号：载波本地相位输出
	
#define B2D_DLL_DIS_OUT			22					// B2D通道文件编号：DLL环鉴相输出
#define B2D_DLL_LPF_OUT			23					// B2D通道文件编号：DLL环滤波器输出
#define B2D_PLL_DIS_OUT			24					// B2D通道文件编号：PLL环鉴相输出
#define B2D_PLL_LPF_OUT			25					// B2D通道文件编号：PLL环滤波器输出
#define B2D_TRK_I_OUT			26					// B2D通道文件编号：跟踪I路输出
#define B2D_TRK_Q_OUT			27					// B2D通道文件编号：跟踪Q路输出
#define B2D_ACQ_OUT				28					// B2D通道文件编号：捕获结果输出
#define B2D_PRN_PHS_SRC_OUT		29					// B2D通道文件编号：PRN码信号源相位输出
#define B2D_PRN_PHS_LCL_OUT		30					// B2D通道文件编号：PRN码本地码相位输出
#define B2D_CAR_PHS_SRC_OUT		31					// B2D通道文件编号：载波信号源输出
#define B2D_CAR_PHS_LCL_OUT		32					// B2D通道文件编号：载波本地相位输出
	
#define B2P_DLL_DIS_OUT			33					// B2P通道文件编号：DLL环鉴相输出
#define B2P_DLL_LPF_OUT			34					// B2P通道文件编号：DLL环滤波器输出
#define B2P_PLL_DIS_OUT			35					// B2P通道文件编号：PLL环鉴相输出
#define B2P_PLL_LPF_OUT			36					// B2P通道文件编号：PLL环滤波器输出
#define B2P_TRK_I_OUT			37					// B2P通道文件编号：跟踪I路输出
#define B2P_TRK_Q_OUT			38					// B2P通道文件编号：跟踪Q路输出
#define B2P_ACQ_OUT				39					// B2P通道文件编号：捕获结果输出
#define B2P_PRN_PHS_SRC_OUT		40					// B2P通道文件编号：PRN码信号源相位输出
#define B2P_PRN_PHS_LCL_OUT		41					// B2P通道文件编号：PRN码本地码相位输出
#define B2P_CAR_PHS_SRC_OUT		42					// B2P通道文件编号：载波信号源输出
#define B2P_CAR_PHS_LCL_OUT		43					// B2P通道文件编号：载波本地相位输出
	
#define B3D_DLL_DIS_OUT			44					// B3D通道文件编号：DLL环鉴相输出
#define B3D_DLL_LPF_OUT			45					// B3D通道文件编号：DLL环滤波器输出
#define B3D_PLL_DIS_OUT			46					// B3D通道文件编号：PLL环鉴相输出
#define B3D_PLL_LPF_OUT			47					// B3D通道文件编号：PLL环滤波器输出
#define B3D_TRK_I_OUT			48					// B3D通道文件编号：跟踪I路输出
#define B3D_TRK_Q_OUT			49					// B3D通道文件编号：跟踪Q路输出
#define B3D_ACQ_OUT				50					// B3D通道文件编号：捕获结果输出
#define B3D_PRN_PHS_SRC_OUT		51					// B3D通道文件编号：PRN码信号源相位输出
#define B3D_PRN_PHS_LCL_OUT		52					// B3D通道文件编号：PRN码本地码相位输出
#define B3D_CAR_PHS_SRC_OUT		53					// B3D通道文件编号：载波信号源输出
#define B3D_CAR_PHS_LCL_OUT		54					// B3D通道文件编号：载波本地相位输出
		
#define B3P_DLL_DIS_OUT			55					// B3P通道文件编号：DLL环鉴相输出
#define B3P_DLL_LPF_OUT			56					// B3P通道文件编号：DLL环滤波器输出
#define B3P_PLL_DIS_OUT			57					// B3P通道文件编号：PLL环鉴相输出
#define B3P_PLL_LPF_OUT			58					// B3P通道文件编号：PLL环滤波器输出
#define B3P_TRK_I_OUT			59					// B3P通道文件编号：跟踪I路输出
#define B3P_TRK_Q_OUT			60					// B3P通道文件编号：跟踪Q路输出
#define B3P_ACQ_OUT				61					// B3P通道文件编号：捕获结果输出
#define B3P_PRN_PHS_SRC_OUT		62					// B3P通道文件编号：PRN码信号源相位输出
#define B3P_PRN_PHS_LCL_OUT		63					// B3P通道文件编号：PRN码本地码相位输出
#define B3P_CAR_PHS_SRC_OUT		64					// B3P通道文件编号：载波信号源输出
#define B3P_CAR_PHS_LCL_OUT		65					// B3P通道文件编号：载波本地相位输出

extern FILE *pFile;									// 数据源文件
extern FILE *FP[FILENUM];							// 输出文件
extern void openFile();								// 打开文件
extern void writeToFile(FLOAT data_src,int i);		// 写文件

extern void closeFile();							// 关闭文件
#endif