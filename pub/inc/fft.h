/*
 * fft.h
 * Date   : 11-14-2014
 * Author : HouBiao,WangHanCheng
*/
#ifndef FFT_H_
#define FFT_H_
#include <stdio.h>
#include "type.h"
extern complex complexMult(complex , complex );				// 复数点乘
extern void complexConj(complex *,int );					// 复数共轭
extern void FFT(complex *, int);							// 快速傅里叶变换
extern void IFFT(complex *, int );							// 快速傅里叶反变换
#endif 