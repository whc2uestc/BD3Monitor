/*
 * cfg.h
 * Date   : 11-14-2014
 * Author : HouBiao
*/
#ifndef B2CFG_H_
#define B2CFG_H_
#include "../../pub/inc/cfg.h"

	#define B2INTFRQ					55549999.999999955		// Intermediate frequency of B2
	#define B2CARFRQ					1176450000.0			// Radio frequency of B2
	#define B2PKGLEN					32768					// packet length of B2 
	#define B2PKGFRQ					32768000.0				// packet frequency of B2
	#define B2PRNLEN					10230					// code length of B2
	#define B2PRNFRQ					10230000.0				// code frequency of B2

	#define B2DELTA						0.5						// the difference in chip between promote channel and early channel 
	
	#define B3INTFRQ					36519999.999999982		// Intermediate frequency of B3
	#define B3CARFRQ					1268520000.0			// Radio frequency of B3

	#define B2FLLMAXTIME				0						// fll time

//B1 与B2.B3的环路参数与结构还需要统一
	#define ALPHACODE					1.414
    #define BANDWITHCODE				1.0
	#define CODELOOPGAIN				1.5

	#define ALPHAFLL					1.414
	#define ALPHAPLL					1.1
	#define BETAPLL						2.4
	#define BANDWITHFLL					18.0
	#define BANDWITHPLL					18.0
	#define CARRIERLOOPGAINPLL			(1.0/2.0/PI)
	#define CARRIERLOOPGAINFLL			((1.0/2.0/PI/T))

	

//相当于B1的DATA_ID PILOT_ID 那里是用code_gen产生码，这里是直接读取,这里用绝对路径，实际仿真时是没有绝对路径的。
	#define B2DCODEPATH					"D:/codeb2d.bin"				// B2D码路径
	#define B2PCODEPATH					"D:/codeb2p.bin"				// B2P码路径				
	#define B3DCODEPATH					"D:/code1.bin"				// B3D码路径
	#define B3PCODEPATH					"D:/code2.bin"				// B3P码路径


	

#endif