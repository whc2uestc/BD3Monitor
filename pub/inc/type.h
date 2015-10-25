/*
 * type.h
 * Date   : 11-14-2014
 * Author : HouBiao,WangHanCheng
*/
#ifndef TYPE_H_
#define TYPE_H_

typedef double FLOAT;								// 浮点类型
	
// 复数结构体
typedef struct
	{
		FLOAT real;									// 实部
		FLOAT imag;									// 虚部
	}complex;

// 跟踪阶段码相位
typedef struct
{
	FLOAT phsE;										// E支路码相位
	FLOAT phsP;										// P支路码相位
	FLOAT phsL;										// L支路码相位
}EPLPhs;
// NCO
typedef struct 
{
	FLOAT fo;										// 频率
	FLOAT fcw;										// 频率控制字
	FLOAT phs;										// 相位
}NCO;
// 跟踪码NCO
typedef struct 
{
	FLOAT fo;										// 频率
	FLOAT fcw;										// 频率控制字
	EPLPhs phs;										// 跟踪阶段码相位
}TrkNCO;

// 滤波器系数
typedef struct 
{
	FLOAT dll_a;									// DLL滤波器系数A
	FLOAT dll_b;									// DLL滤波器系数B
	FLOAT dll_reg;									// DLL滤波器寄存器
	FLOAT dll_gain;									// DLL滤波器增益
	

	FLOAT fll_a;									// FLL滤波器系数A
	FLOAT fll_b;									// FLL滤波器系数B
	FLOAT pll_a;									// PLL滤波器系数A
	FLOAT pll_b;									// PLL滤波器系数B
	FLOAT pll_c;									// PLL滤波器系数C
	FLOAT pll_reg0;									// PLL滤波器寄存器0
	FLOAT pll_reg1;									// PLL滤波器寄存器1
	FLOAT pll_gain;									// PLL滤波器增益
	FLOAT fll_gain;									// FLL滤波器增益
	
}LPF;

#endif