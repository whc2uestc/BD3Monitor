/*
 * trk.cpp
 * Date   : 11-14-2014
 * Author : WangHanCheng
*/
#include <stdio.h>
#include<string.h>
#include <math.h>

#include "../inc/cfg.h"
#include "../inc/type.h"
#include "../../pub/inc/fft.h"




static void codeGen(short sat,char code[1023]){
	short node[37][2] ={
		    { 1, 5 },{ 2, 6 },{ 3, 7 },{ 4, 8 },{ 0, 8 },
		    { 1, 9 },{ 0, 7 },{ 1, 8 },{ 2, 9 },{ 1, 2 },
		    { 2, 3 },{ 4, 5 },{ 5, 6 },{ 6, 7 },{ 7, 8 },
			{ 8, 9 },{ 0, 3 },{ 1, 4 },{ 2, 5 },{ 3, 6 },
			{ 4, 7 },{ 5, 8 },{ 0, 2 },{ 3, 5 },{ 4, 6 },
		    { 5, 7 },{ 6, 8 },{ 7, 9 },{ 0, 5 },{ 1, 6 },
			{ 2, 7 },{ 3, 8 },{ 4, 9 },{ 3, 9 },{ 0, 6 },
			{ 0, 7 },{ 3, 9 }
	};

	int j, k;
	char save1, save2;

	char reg1[10] ={ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	char reg2[10] ={ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };

	for (j = 0; j < 1023; j++) {
		code[j] = reg2[node[sat-1][0]] * reg2[node[sat-1][1]] * reg1[9];
        //update G1
		save1 = reg1[2] * reg1[9];
        for (k = 8; k >= 0; k--) {
			reg1[k + 1] = reg1[k];
		}
		reg1[0] = save1;
        //update G2
		save2 = reg2[1] * reg2[2] * reg2[5] * reg2[7] * reg2[8] * reg2[9];
		for (k = 8; k >= 0; k--) {
			reg2[k + 1] = reg2[k];
		}
		reg2[0] = save2;
	}
}

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
static void fftGen(B1AcqPrms *inst,char chnlID,char code[]){
	while(!inst->rdy ){
		inst->fft_prn[inst->pid].real += code[inst->cid];
		if(chnlID == B1DID)
			inst->fft_boc[inst->pid].real += code[inst->cid] * sgn(sin(2*PI*inst->sub_1.phs/NCOTOTAL));
		else if(chnlID == B1PID){
			if(inst->cid%33 == 0 || inst->cid%33 == 4 || inst->cid%33 == 6 || inst->cid%33 == 29)
				inst->fft_boc[inst->pid].real += code[inst->cid] * sgn(sin(2*PI*inst->sub_6.phs/NCOTOTAL));
			else
				inst->fft_boc[inst->pid].real += code[inst->cid] * sgn(sin(2*PI*inst->sub_1.phs/NCOTOTAL));

			inst->sub_6.phs += inst->sub_6.fcw;
			if(inst->sub_6.phs >= NCOTOTAL)
				inst->sub_6.phs -= NCOTOTAL;
		}

		
		
		inst->pkg.phs += inst->pkg.fcw;
		if(inst->pkg.phs >= NCOTOTAL){
			inst->pkg.phs -= NCOTOTAL;
			inst->pid ++;
			if(inst->pid >= inst->FID){
				inst->pid = 0;
				inst->cid = 0;
				inst->rdy = 1;
			}
		}
		inst->prn.phs += inst->prn.fcw;
		if(inst->prn.phs >= NCOTOTAL){
			inst->prn.phs -= NCOTOTAL;
			inst->cid ++;
			if(inst->cid >= inst->CID)
				inst->cid = 0;
		}
		inst->sub_1.phs += inst->sub_1.fcw;
		if(inst->sub_1.phs >= NCOTOTAL){
			inst->sub_1.phs -= NCOTOTAL;
		}
	}
	inst->rdy = 0;
	FFT(inst->fft_prn,inst->FID);
	FFT(inst->fft_boc,inst->FID);
	complexConj(inst->fft_prn,inst->FID);
	complexConj(inst->fft_boc,inst->FID);
}

static void acq_Init(B1AcqPrms *inst,char chnlID,char code[]){
	char NH_Code[B1NHLEN] = {-1, -1, -1, -1, -1, 1, -1, -1, 1, 1, -1, 1, -1, 1, -1, -1, 1, 1, 1, -1};
	//XXXXXX

	int dop_tab[2*(DOPPLERRANGE/DOPPLERSTEP)+1];
	int i ;
	int j = 1;
	dop_tab[0] = 0;
	for (i=1;i<2*(DOPPLERRANGE/DOPPLERSTEP)+1;i=i+2)
	{
		dop_tab[i] = DOPPLERSTEP*j;
		dop_tab[i+1]= -DOPPLERSTEP*j;
		j++;
	}
	inst->car.fo  = B1INTFRQ;
	inst->car.fcw = B1INTFRQ*NCOTOTAL/SMPFRQ;
	inst->car.phs = 0.0;

	inst->prn.fo  = B1PRNFRQ;
	inst->prn.fcw = B1PRNFRQ*NCOTOTAL/SMPFRQ;
	inst->prn.phs = 0.0;

	inst->sub_1.fo  = B1SUBFRQ;
	inst->sub_1.fcw = B1SUBFRQ*NCOTOTAL/SMPFRQ;
	inst->sub_1.phs = 0.0;

	inst->sub_6.fo  = 6*B1SUBFRQ;
	inst->sub_6.fcw = 6*B1SUBFRQ*NCOTOTAL/SMPFRQ;
	inst->sub_6.phs = 0.0;
	
	inst->cid = 0;
	inst->pid = 0;
	inst->CID = B1PRNLEN;
	inst->PID = B1PKGLEN;

	inst->pkg.fo = B1PKGFRQ;
	inst->pkg.fcw = B1PKGFRQ*NCOTOTAL/SMPFRQ;

	if(chnlID == B1DID)
		inst->FID = B1PKGLEN;
	else if(chnlID == B1PID)
		inst->FID = B1PKGLEN * 2;

	memcpy(inst->doppler,dop_tab,sizeof(dop_tab));
	strcpy(inst->NH,NH_Code);
	fftGen(inst,chnlID,code);
	printf("Chnl %d: \tdoppler=%d\n",chnlID,inst->doppler[0]);
}

static void trk_Init(B1TrkPrms *inst,char chnlID){
	inst->car.fo  = B1INTFRQ;
	inst->car.fcw = B1INTFRQ*NCOTOTAL/SMPFRQ;
	inst->car.phs = 0.0;

	inst->prn.fo  = B1PRNFRQ;
	inst->prn.fcw = B1PRNFRQ*NCOTOTAL/SMPFRQ;

	inst->sub_1.fo  = B1SUBFRQ;
	inst->sub_1.fcw = B1SUBFRQ*NCOTOTAL/SMPFRQ;

	inst->sub_6.fo  = 6*B1SUBFRQ;
	inst->sub_6.fcw = 6*B1SUBFRQ*NCOTOTAL/SMPFRQ;

	inst->lpf.dll_a = B1DLL_A;
	inst->lpf.dll_b = B1DLL_B;
	inst->lpf.fll_a = B1FLL_A;
	inst->lpf.fll_b = B1FLL_B;
	inst->lpf.pll_a = B1PLL_A;
	inst->lpf.pll_b = B1PLL_B;
	inst->lpf.pll_c = B1PLL_C;
	inst->prn.phs.phsE = NCOTOTAL * B1DELTA;
	inst->prn.phs.phsP = 0;
	inst->prn.phs.phsL = NCOTOTAL * (1 - B1DELTA);
	inst->sub_1.phs.phsE = NCOTOTAL * B1DELTA; 
	inst->sub_1.phs.phsP = 0;
	inst->sub_1.phs.phsL = NCOTOTAL * (1 - B1DELTA);
	inst->sub_6.phs.phsE = NCOTOTAL * B1DELTA; 
	inst->sub_6.phs.phsP = 0;
	inst->sub_6.phs.phsL = NCOTOTAL * (1 - B1DELTA);
	inst->cidE = 0;
	inst->cidP = 0;
	inst->cidL = B1PRNLEN - 1;
	inst->lpf.dll_gain = B1DLLGAIN;
	inst->lpf.pll_gain = B1PLLGAIN;
	inst->lpf.fll_gain = B1FLLGAIN;
}



void B1ChnlInit(B1ChnlPrms *inst){
	int i;
	for(i=0; i<2; i++,inst++)
	{

		B1AcqPrms *acqH = &inst->acq;
		B1TrkPrms *trkH = &inst->trk;
		

		memset(inst,0,sizeof(B1ChnlPrms));
		inst->chnlPros		= ACQ_FLG;
		if(i == 0){
			inst->satID		= DATA_ID;
			inst->chnlID	= B1DID;
		}
		else{
			inst->satID		= PILOT_ID;
			inst->chnlID	= B1PID;
		}

		codeGen(inst->satID,inst->code);

		acq_Init(acqH,inst->chnlID,inst->code);	
		trk_Init(trkH,inst->chnlID);
		// for test
		//inst->TCAR.phs = 0 ;
		//inst->TCAR.fcw = xx;
		//inst->TPRN.phs = 0;
		//inst->TPRN.fcw = xx;
		//inst->prnIndex = 0;
		// for test

	}
}
