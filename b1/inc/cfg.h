/*
 * cfg.h
 * Date   : 11-14-2014
 * Author : WangHanCheng
*/

#ifndef B1CFG_H_
#define B1CFG_H_
#include "../../pub/inc/cfg.h"

	#define B1INTFRQ					5000000.0		// Intermediate frequency of B1
	#define B1CARFRQ					1575420000.0			// Radio frequency of B1
	#define B1PKGLEN					4096					// packet length of B1 
	#define B1PKGFRQ					4096000.0				// packet frequency of B1
	#define B1PRNLEN					1023					// code length of B1
	#define B1PRNFRQ					1023000.0				// code frequency of B1
	#define B1SUBFRQ					1023000.0				// sub-carrier frequency of B1
	#define B1NHLEN						20						// NH code length

	#define B1DELTA						0.25					// the difference in chip between promote channel and early channel 

#define B1WND		0.8/0.53
#define B1DLL_A		1.0*B1WND*B1WND
#define B1DLL_B		1.414*B1WND

#define B1WNF		18/0.53
#define B1WNP		18/0.7845
#define B1PLL_A		1.0*B1WNP*B1WNP*B1WNP
#define B1PLL_B		1.1*B1WNP*B1WNP
#define B1PLL_C		2.4*B1WNP
#define B1FLL_A		1.0*B1WNF*B1WNF
#define B1FLL_B		1.414*B1WNF
#define B1DLLGAIN     1.0
#define B1PLLGAIN     3.0
#define B1FLLGAIN	  1000*0.1

#define DATA_ID		1
#define PILOT_ID	2

#define AIDFCT	  1540.0
#endif
