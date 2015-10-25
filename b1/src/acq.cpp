/*
 * acq.cpp
 * Date   : 11-14-2014
 * Author : WangHanCheng
*/

#include<stdlib.h>
#include <stdio.h>
#include<string.h>
#include <math.h>

#include "../inc/cfg.h"
#include "../inc/type.h"
#include "../../pub/inc/fft.h"
#include "../../pub/inc/ioc.h"
static void srh_ASPT(B1AcqPrms *inst,char chnlID){
	unsigned int i;
	FLOAT sum = 0.0;
	FLOAT pk = 0.0;
	unsigned int phs = 0;
	complex tempBB[B1PKGLEN*2],tempBP[B1PKGLEN*2],corr_IFFT[B1PKGLEN*2];
	FFT(inst->fft_src,inst->FID);
	for(i=0;i<inst->FID;i++){
		tempBB[i].real = inst->fft_boc[i].real*inst->fft_src[i].real - inst->fft_boc[i].imag*inst->fft_src[i].imag;
		tempBB[i].imag = inst->fft_boc[i].real*inst->fft_src[i].imag + inst->fft_boc[i].imag*inst->fft_src[i].real;

		tempBP[i].real = inst->fft_prn[i].real*inst->fft_src[i].real - inst->fft_prn[i].imag*inst->fft_src[i].imag;
		tempBP[i].imag = inst->fft_prn[i].real*inst->fft_src[i].imag + inst->fft_prn[i].imag*inst->fft_src[i].real;
	}
	IFFT(tempBB,inst->FID);
	IFFT(tempBP,inst->FID);
	for(i=0;i<inst->FID;i++){
		corr_IFFT[i].real = tempBB[i].real*tempBB[i].real - tempBB[i].imag*tempBB[i].imag - (tempBP[i].real*tempBP[i].real - tempBP[i].imag*tempBP[i].imag);
		corr_IFFT[i].imag = tempBB[i].real*tempBB[i].imag - (tempBP[i].real*tempBP[i].imag);
		inst->corr[i] = sqrt(corr_IFFT[i].real*corr_IFFT[i].real + corr_IFFT[i].imag*corr_IFFT[i].imag);
		//inst->corr[i] = abs(tempBB[i].real*tempBB[i].real - tempBB[i].imag*tempBB[i].imag - (tempBP[i].real*tempBP[i].real - tempBP[i].imag*tempBP[i].imag));
		sum += inst->corr[i];
		if(inst->corr[i] > pk){
			pk = inst->corr[i];
			phs = i;
		}
	}
	inst->pk_srh[inst->did] = pk;
	inst->phs_srh[inst->did] = phs;
	inst->did ++;
	if(inst->did >= 2*(DOPPLERRANGE/DOPPLERSTEP)+1){
		pk = 0.0;
		for(i=0;i<2*(DOPPLERRANGE/DOPPLERSTEP)+1;i++){
			if(inst->pk_srh[i] > pk){
				pk = inst->pk_srh[i];
				inst->did = i;
			}
		}
		inst->FID = inst->phs_srh[inst->did];
		inst->flg = 1;
	}
	else{

		inst->car.fo = B1INTFRQ + inst->doppler[inst->did];
		inst->car.fcw = inst->car.fo * NCOTOTAL/SMPFRQ;
		printf("Chnl %d: \tdoppler=%d\n",chnlID,inst->doppler[inst->did]);

	}

	/*if(pk >= 30*sum/inst->FID){
		if(chnlID == B1DID){
			for(i=0;i<inst->FID;i++)
				writeToFile(inst->corr[i],B1D_ACQ_OUT);
			
			printf("DATA:doppler:%d\n",inst->doppler[inst->did]);
		}
		else{
			for(i=0;i<inst->FID;i++)
				writeToFile(inst->corr[i],B1P_ACQ_OUT);
			
			printf("PILOT:doppler:%d\n",inst->doppler[inst->did]);

		}
		inst->FID = phs;
		inst->flg = 1;
	}
	else{
		inst->did ++;
		if(inst->did >= 2*(DOPPLERRANGE/DOPPLERSTEP)+1)
			printf("The SAT not exist!!\n");
		else{
			inst->car.fo = B1INTFRQ + inst->doppler[inst->did];
			inst->car.fcw = inst->car.fo * NCOTOTAL/SMPFRQ;
			printf("Chnl %d: \tdoppler=%d\n",chnlID,inst->doppler[inst->did]);
		}
		
	}*/
}
static void acq_UPDT(B1AcqPrms *inst,char *flag,B1TrkPrms *trkH){
	*flag = TRK_FLG;
	inst->suc =1;
	trkH->doppler	= inst->doppler[inst->did];
	trkH->car.fo	= B1INTFRQ + trkH->doppler;
	trkH->car.fcw	= trkH->car.fo * NCOTOTAL/SMPFRQ;
	trkH->prn.fo	= B1PRNFRQ + trkH->doppler/AIDFCT;
	trkH->prn.fcw	= trkH->prn.fo * NCOTOTAL/SMPFRQ;
	trkH->sub_1.fo	= B1SUBFRQ + trkH->doppler/AIDFCT;
	trkH->sub_1.fcw = trkH->sub_1.fo * NCOTOTAL/SMPFRQ;
	trkH->sub_6.fo	= 6*B1SUBFRQ + 6*trkH->doppler/AIDFCT;
	trkH->sub_6.fcw = trkH->sub_6.fo * NCOTOTAL/SMPFRQ;
}
void B1AcqASPT(B1ChnlPrms *ChnlH,char dat_src){

	B1AcqPrms *inst = &ChnlH->acq;

	if(!inst->suc){
		if(!inst->FID){
			inst->pkg.phs = NCOTOTAL;
		}
		else{
			inst->fft_src[inst->pid].real += dat_src * cos(2*PI*inst->car.phs/NCOTOTAL);
			inst->fft_src[inst->pid].imag += dat_src * sin(2*PI*inst->car.phs/NCOTOTAL);
			inst->car.phs += inst->car.fcw;
			inst->pkg.phs += inst->pkg.fcw;
		}
		if(inst->car.phs >= NCOTOTAL)
			inst->car.phs -= NCOTOTAL;
		if(inst->pkg.phs >= NCOTOTAL){
			inst->pkg.phs -= NCOTOTAL;
			inst->pid ++;
			if(inst->pid >= inst->FID){
				inst->pid = 0;
				switch(inst->flg){
					case 0:	srh_ASPT(inst,ChnlH->chnlID);break;
					case 1: acq_UPDT(inst,&ChnlH->chnlPros,&ChnlH->trk);break;
					default:break;
				}
				memset(inst->fft_src,0,sizeof(inst->fft_src));	
			}
		}
	}


}