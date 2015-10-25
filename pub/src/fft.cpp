/*
 * fft.cpp
 * Date   : 11-13-2014
 * Author : HouBiao,WangHanCheng
*/
#include <math.h>
#include <stdio.h>

#include "../inc/type.h"
#include "../inc/cfg.h"
//复数乘法
complex complexMult (complex a,complex b)
{
	complex c;
	c.real = a.real * b.real - a.imag * b.imag;
	c.imag = a.real * b.imag + a.imag * b.real;
	return (c);
}

//复数共轭
void complexConj (complex * a,int length)
{
	int i;
	for (i = 0; i < length; i++)
	{
		a[i].imag =- a[i].imag;
	}
}

//对输入数据倒序排序，雷德算法
void reorder (complex *a, int length)
{
	int i, k, j;
	complex t;
	j = 0 ;
	for (i = 0; i < length-1; i++) {
		if (i < j) {
			t = a[j];
			a[j] = a[i];
			a[i] = t;
		}
		k = length >> 1;
		while (k <= j && i ) {
			j = j - k;
			k = k >> 1;
		}
		j = j + k;
	}
}
// FFT
void FFT (complex *a, int length)
{
	int lev, f, m, b, j, i, ip;
	complex u, w, t;
	reorder(a, length);
	f = length;
	for (lev = 1; (f >>= 1) != 1; lev++);
	for (m = 1; m <= lev; m++) {
		b = 1 << (m - 1);
		u.real = 1.0;
		u.imag = 0.0;
		w.real = cos(PI / b);
		w.imag = -sin(PI / b);
		for (j = 0; j <= b - 1; j++) {
			for (i = j; i <= length - 1; i = i + 2*b) {
				ip = i + b;
				t = complexMult(a[ip], u);
				a[ip].real = a[i].real - t.real;
				a[ip].imag = a[i].imag - t.imag;
				a[i].real = a[i].real + t.real;
				a[i].imag = a[i].imag + t.imag;
			}
			u = complexMult(u, w);
		}
	}
}

//IFFT
void IFFT(complex *a, int length)
{
	int i;
	complexConj(a, length);
	FFT(a, length);
	complexConj(a, length);
	for (i = 0; i < length; i++) {
		a[i].real /= length;
		a[i].imag /= length;
	}
}
