/*
 * trk.cpp
 * Date   : 11-14-2014
 * Author : WangHanCheng
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../inc/type.h"
#include "../inc/cfg.h"
#include "../../pub/inc/ioc.h"
#include "../../pub/inc/filter.h"
extern int outflag;
static inline int sgn(double x){
	if(x >= 0)
		return 1;
	else
		return -1;
}
static inline unsigned int sgn_0(double x){
	if(x >= 0)
		return 1;
	else
		return 0;
}
static inline unsigned int  sgn_1(double x){
	if(x >= 0)
		return 0;
	else
		return 1;
}



static void get_EPL(B1TrkPrms *inst,char code[],char chnlID,char data_src){

	inst->src.real = data_src * cos(2*PI*inst->car.phs/NCOTOTAL);
	inst->src.imag = data_src * sin(2*PI*inst->car.phs/NCOTOTAL);
	inst->car.phs += inst->car.fcw;

	if(inst->car.phs >= NCOTOTAL){
		inst->car.phs -= NCOTOTAL;
	}

	if(chnlID == B1DID){
		inst->bocE = code[inst->cidE] * sgn(sin(2*PI*inst->sub_1.phs.phsE/NCOTOTAL));
		inst->bocP = code[inst->cidP] * sgn(sin(2*PI*inst->sub_1.phs.phsP/NCOTOTAL));
		inst->bocL = code[inst->cidL] * sgn(sin(2*PI*inst->sub_1.phs.phsL/NCOTOTAL));
	}
	else if(chnlID == B1PID){
		if(inst->cidE%33 == 0 || inst->cidE%33 == 4 || inst->cidE%33 == 6 || inst->cidE%33 == 29)
			inst->bocE = code[inst->cidE] * sgn(sin(2*PI*inst->sub_6.phs.phsE/NCOTOTAL));
		else
			inst->bocE = code[inst->cidE] * sgn(sin(2*PI*inst->sub_1.phs.phsE/NCOTOTAL));
		
		if(inst->cidP%33 == 0 || inst->cidP%33 == 4 || inst->cidP%33 == 6 || inst->cidP%33 == 29)
			inst->bocP = code[inst->cidP] * sgn(sin(2*PI*inst->sub_6.phs.phsP/NCOTOTAL));
		else
			inst->bocP = code[inst->cidP] * sgn(sin(2*PI*inst->sub_1.phs.phsP/NCOTOTAL));
		
		if(inst->cidL%33 == 0 || inst->cidL%33 == 4 || inst->cidL%33 == 6 || inst->cidL%33 == 29)
			inst->bocL = code[inst->cidL] * sgn(sin(2*PI*inst->sub_6.phs.phsL/NCOTOTAL));
		else
			inst->bocL = code[inst->cidL] * sgn(sin(2*PI*inst->sub_1.phs.phsL/NCOTOTAL));
		
		inst->sub_6.phs.phsE += inst->sub_6.fcw;
		inst->sub_6.phs.phsP += inst->sub_6.fcw;
		inst->sub_6.phs.phsL += inst->sub_6.fcw;
		if(inst->sub_6.phs.phsE >= NCOTOTAL) 
			inst->sub_6.phs.phsE -= NCOTOTAL;	

		if(inst->sub_6.phs.phsP >= NCOTOTAL) 
			inst->sub_6.phs.phsP -= NCOTOTAL;

		if(inst->sub_6.phs.phsL >= NCOTOTAL) 
			inst->sub_6.phs.phsL -= NCOTOTAL;

	}

	inst->prnE = code[inst->cidE];
	inst->prnP = code[inst->cidP];
	inst->prnL = code[inst->cidL];

	inst->corr_bpE.real += inst->prnE * inst->src.real;
	inst->corr_bpE.imag += inst->prnE * inst->src.imag;

	inst->corr_bbE.real += inst->bocE * inst->src.real;
	inst->corr_bbE.imag += inst->bocE * inst->src.imag;

	inst->corr_bpP.real += inst->prnP * inst->src.real;
	inst->corr_bpP.imag += inst->prnP * inst->src.imag;

	inst->corr_bbP.real += inst->bocP * inst->src.real;
	inst->corr_bbP.imag += inst->bocP * inst->src.imag;

	inst->corr_bpL.real += inst->prnL * inst->src.real;
	inst->corr_bpL.imag += inst->prnL * inst->src.imag;

	inst->corr_bbL.real += inst->bocL * inst->src.real;
	inst->corr_bbL.imag += inst->bocL * inst->src.imag;


	inst->sub_1.phs.phsE += inst->sub_1.fcw;
	inst->sub_1.phs.phsP += inst->sub_1.fcw;
	inst->sub_1.phs.phsL += inst->sub_1.fcw;
	if(inst->sub_1.phs.phsE >= NCOTOTAL) 
		inst->sub_1.phs.phsE -= NCOTOTAL;	

	if(inst->sub_1.phs.phsP >= NCOTOTAL) 
		inst->sub_1.phs.phsP -= NCOTOTAL;

	if(inst->sub_1.phs.phsL >= NCOTOTAL) 
		inst->sub_1.phs.phsL -= NCOTOTAL;


	inst->prn.phs.phsE += inst->prn.fcw;
	inst->prn.phs.phsP += inst->prn.fcw;
	inst->prn.phs.phsL += inst->prn.fcw;
	if(inst->prn.phs.phsE >= NCOTOTAL) {
		inst->prn.phs.phsE -= NCOTOTAL;	
		inst->cidE ++;
		if(inst->cidE >= B1PRNLEN)
			inst->cidE -= B1PRNLEN;
	}
	if(inst->prn.phs.phsP >= NCOTOTAL) {
		inst->prn.phs.phsP -= NCOTOTAL;
		inst->cidP ++;
		if(inst->cidP >= B1PRNLEN){
			inst->cidP -= B1PRNLEN;
			inst->rdy = 1;

		}
	}
	if(inst->prn.phs.phsL >= NCOTOTAL) {
		inst->prn.phs.phsL -= NCOTOTAL;
		inst->cidL ++;
		if(inst->cidL >= B1PRNLEN)
			inst->cidL -= B1PRNLEN;
	}


}

static void discri(B1TrkPrms *inst,char chnlID){
	FLOAT P_dot,P_cor;
	FLOAT temp1,temp2;
	if(chnlID == B1DID){
		temp1 = (inst->corr_bbE.real*inst->corr_bbE.real + inst->corr_bbE.imag*inst->corr_bbE.imag)	\
			 - (inst->corr_bbL.real*inst->corr_bbL.real + inst->corr_bbL.imag*inst->corr_bbL.imag)		\
			 - ((inst->corr_bpE.real*inst->corr_bpE.real + inst->corr_bpE.imag*inst->corr_bpE.imag)		\
			 - (inst->corr_bpL.real*inst->corr_bpL.real + inst->corr_bpL.imag*inst->corr_bpL.imag));	\
		temp2 = inst->corr_bbP.real*inst->corr_bbP.real + inst->corr_bbP.imag*inst->corr_bbP.imag;	
		inst->disD_out = temp1/(4*(3*(1-3*0.25)+0.25)*temp2);
	}
	else if(chnlID == B1PID){
		temp1 = (inst->corr_bbE.real*inst->corr_bbE.real + inst->corr_bbE.imag*inst->corr_bbE.imag)	\
			 - (inst->corr_bbL.real*inst->corr_bbL.real + inst->corr_bbL.imag*inst->corr_bbL.imag)		\
			 - 0.9*((inst->corr_bpE.real*inst->corr_bpE.real + inst->corr_bpE.imag*inst->corr_bpE.imag)		\
			 - (inst->corr_bpL.real*inst->corr_bpL.real + inst->corr_bpL.imag*inst->corr_bpL.imag));	\
		temp2 = inst->corr_bbP.real*inst->corr_bbP.real + inst->corr_bbP.imag*inst->corr_bbP.imag;	
		inst->disD_out = temp1/(4*(3*(1-3*0.25)+0.9*0.25)*temp2);
	}

	if(inst->tmr < 100){
		if(inst->tmr == 0){
			inst->pkg_I0 = inst->corr_bbP.real;
			inst->pkg_I1 = inst->corr_bbP.real;
			inst->pkg_Q0 = inst->corr_bbP.imag;
			inst->pkg_Q1 = inst->corr_bbP.imag;
			inst->disP_out = 0;
			inst->disF_out = 0;
		}
		else{
			inst->pkg_I0 = inst->pkg_I1;
			inst->pkg_I1 = inst->corr_bbP.real;
			inst->pkg_Q0 = inst->pkg_Q1;
			inst->pkg_Q1 = inst->corr_bbP.imag;
			P_dot = inst->pkg_I0*inst->pkg_I1 + inst->pkg_Q0*inst->pkg_Q1;
			P_cor = inst->pkg_I0*inst->pkg_Q1 - inst->pkg_Q0*inst->pkg_I1;
			if(chnlID == B1DID)
				inst->disF_out = atan2(P_cor,P_dot)/(2*PI);
			else if(chnlID == B1PID)
				inst->disF_out = -atan2(P_cor,P_dot)/(2*PI);
		}
	}
	else{
		inst->disF_out = 0;
		inst->disP_out = atan(inst->corr_bbP.imag/inst->corr_bbP.real)/(2*PI);
	}

}

static void filter(B1TrkPrms *inst){
	FLOAT reg,reg0,reg1;
	reg = inst->disD_out * inst->lpf.dll_a * 0.001 + inst->lpf.dll_reg;
	inst->dll_out = (reg + inst->lpf.dll_reg)*0.5 + inst->disD_out*inst->lpf.dll_b;

	inst->lpf.dll_reg = reg;

	reg0 = (inst->disP_out * inst->lpf.pll_a + inst->disF_out/0.001 * inst->lpf.fll_a) *0.001 + inst->lpf.pll_reg0;
	reg1 = (0.5 * (reg0 + inst->lpf.pll_reg0) + inst->disP_out * inst->lpf.pll_b + inst->disF_out/0.001 * inst->lpf.fll_b)\
		* 0.001 + inst->lpf.pll_reg1;
	inst->pll_out = 0.5 * (reg1 + inst->lpf.pll_reg1) + inst->disP_out * inst->lpf.pll_c;

	inst->lpf.pll_reg0 = reg0;
	inst->lpf.pll_reg1 = reg1;
}

static void fdback(B1TrkPrms *inst){
	inst->prn.fo = B1PRNFRQ + inst->doppler/AIDFCT + inst->dll_out;
	inst->prn.fcw = inst->prn.fo * NCOTOTAL/SMPFRQ;

	inst->sub_1.fo = B1PRNFRQ + inst->doppler/AIDFCT + inst->dll_out;
	inst->sub_1.fcw = inst->sub_1.fo * NCOTOTAL/SMPFRQ;

	inst->sub_6.fo = 6*B1PRNFRQ + 6*inst->doppler/AIDFCT + 6*inst->dll_out;
	inst->sub_6.fcw = inst->sub_6.fo * NCOTOTAL/SMPFRQ;

	inst->car.fo = B1INTFRQ + inst->doppler - inst->pll_out;
	inst->car.fcw = inst->car.fo * NCOTOTAL/SMPFRQ;
}

void B1TrkASPT(B1ChnlPrms *ChnlH,char data_src){
	
	
	
	B1TrkPrms *trkH = &ChnlH->trk;

	get_EPL(trkH,ChnlH->code,ChnlH->chnlID,data_src);
	if(trkH->rdy == 1)
	{
		trkH->rdy = 0;

		discri(trkH,ChnlH->chnlID);
		trkH->dll_out = codeLoopFilter(&(trkH->lpf),trkH->disD_out);
		trkH->pll_out = carrierLoopFilter(&(trkH->lpf),trkH->disP_out,trkH->disF_out);
		//filter(trkH);
		fdback(trkH);
		trkH->tmr ++;
	
		writeToFile(trkH->disD_out,(ChnlH->chnlID-1)*11+DLL_DIS_OUT);
		writeToFile(trkH->disP_out,(ChnlH->chnlID-1)*11+PLL_DIS_OUT);
		writeToFile(trkH->dll_out,(ChnlH->chnlID-1)*11+DLL_LPF_OUT);
		writeToFile(trkH->pll_out,(ChnlH->chnlID-1)*11+PLL_LPF_OUT);
		writeToFile(trkH->corr_bbP.real,(ChnlH->chnlID-1)*11+TRK_I_OUT);
		writeToFile(trkH->corr_bbP.imag,(ChnlH->chnlID-1)*11+TRK_Q_OUT);
		printf("Chnl %d: doppler = %f %f I = %f Q = %f\n",ChnlH->chnlID,trkH->pll_out,trkH->dll_out,trkH->corr_bbP.real,trkH->corr_bbP.imag);
		
		memset(&trkH->corr_bpE,0,sizeof(complex));
		memset(&trkH->corr_bbE,0,sizeof(complex));
		memset(&trkH->corr_bpP,0,sizeof(complex));
		memset(&trkH->corr_bbP,0,sizeof(complex));
		memset(&trkH->corr_bpL,0,sizeof(complex));
		memset(&trkH->corr_bbL,0,sizeof(complex));
	}
	// for test
	if (outflag == 1)
	{
		writeToFile(ChnlH->TCAR.phs,(ChnlH->chnlID-1)*11+CAR_PHS_SRC_OUT);
		writeToFile(ChnlH->TPRN.phs,(ChnlH->chnlID-1)*11+PRN_PHS_SRC_OUT);
		writeToFile(ChnlH->trk.car.phs,(ChnlH->chnlID-1)*11+CAR_PHS_LCL_OUT);
		writeToFile(ChnlH->trk.prn.phs.phsP,(ChnlH->chnlID-1)*11+PRN_PHS_LCL_OUT);
	}
	// for test

}