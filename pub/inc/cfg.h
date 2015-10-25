/*
 * cfg.h
 * Date   : 11-14-2014
 * Author : HouBiao,WangHanCheng
*/
#ifndef CFG_H_
#define CFG_H_


	#define NCOTOTAL					1099511627776			// maximum nco value 2^40
	#define SMPFRQ						154000000.0				// sampling frequency
    
	#define DOPPLERSTEP					200						// doppler searching step is 200hz
	#define DOPPLERRANGE				1000					// doppler searching range ,from -1k to 1k,
	#define PI							3.141592653589793		// value of pi
	#define T							0.001					// Integration time
	
	#define ACQ_FLG   1											// Processing State
	#define TRK_FLG   2											// Processing State

	#define B1DID						1						// ID of channel b1 data
	#define B1PID						2						// ID of channel b1 pilot

	#define B2DID						3						// ID of channel b2 data
	#define B2PID						4						// ID of channel b2 pilot

	#define B3DID						5						// ID of channel b3 data
	#define B3PID						6						// ID of channel b3 pilot


#endif


