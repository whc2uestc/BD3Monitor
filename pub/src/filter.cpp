/*
 * fft.cpp
 * Date   : 11-13-2014
 * Author : HouBiao,WangHanCheng
*/
#include <stdio.h>

#include "../inc/type.h"
#include "../inc/cfg.h"

FLOAT codeLoopFilter(LPF * lpfInst,FLOAT dis_dll)
 {
     FLOAT phaseError;
	 FLOAT temp0;
	 FLOAT filter;
	 phaseError=dis_dll*lpfInst->dll_gain;

	 temp0 = phaseError*lpfInst->dll_a*T + lpfInst->dll_reg;
	 filter = (temp0+lpfInst->dll_reg)/2 + phaseError*lpfInst->dll_b;
	 lpfInst->dll_reg = temp0;
	 return filter ;
 }
 //ÔØ²¨»·ÂË²¨Æ÷
 FLOAT carrierLoopFilter(LPF * lpfInst,FLOAT dis_pll,FLOAT dis_fll)
 {
	 FLOAT phaseError,frqError;
	 FLOAT temp0,temp1;
	 FLOAT filter ;
	 phaseError = dis_pll*lpfInst->pll_gain;
	 frqError = dis_fll*lpfInst->fll_gain;

	temp0 = frqError*lpfInst->fll_a*T + phaseError*lpfInst->pll_a*T + lpfInst->pll_reg0;
	temp1 = (phaseError*lpfInst->pll_b + (temp0+lpfInst->pll_reg0)/2+frqError*lpfInst->fll_b)*T + lpfInst->pll_reg1;
	filter = (temp1+lpfInst->pll_reg1)/2+phaseError*lpfInst->pll_c;

	lpfInst->pll_reg0 = temp0;
	lpfInst->pll_reg1 = temp1;
	return filter ;
 }
