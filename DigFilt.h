/*
***************************** LIBRARY LEVEL ***********************************
*
* Module Name       : 	Digital LowPass Filter Library.
* File              : 	DigFilt.h
* Date              : 	12/12/2011
* Version           :
* Status            :
*
* Description       : 	Export API for Low Pass Digital Filtering.
*
* Developer         : 	Maurizio Malaspina.
*
* Modifications     :

	USAGE: 
		// declare a filter structure (i.e. "MyLowPassFilter")
		LPF_IIR_10bitDescr_t MyLowPassFilter;
		// eventually init it (i.e. to zero)
		LPF_Init10bitIIR1st(0, &MyLowPassFilter);
		
		// at run time apply the filter to your "MyInputVariable" 
		// (max a 10bit resolution value) by periodically calling 
		// the following macro every Ts:
		LPF_M_DO_10bit_IIR_1st(MyInputVariable, 0.001, 0.015, &MyLowPassFilter);
		// Here Ts = 0.001 s (1 ms) and Tau = 0.015 s (15 ms)
		// Note that, reasoning in ms, Tau has to be (2^n - 1) * Ts (in this case n=4)
		// in order to proper use shifting instead of division.
		
		// You can get the output of the filter simply using the following macro:
	    LPF_M_GET_10bit_IIR_1st_OUTPUT(MyLowPassFilter);	
		
		
*
*******************************************************************************
*/

#ifndef DIGITAL_FILTER_H
#define DIGITAL_FILTER_H

/* ________________ I N C L U D E D   F I L E S _____________________________*/
#include <stdint.h>
/* ________________ P U B L I C   I N T E R F A C E _________________________*/

/* ________________ D E F I N I T I O N S ___________________________________*/

/* ________________ T Y P E S _______________________________________________*/

/* Low Pass filters I/O types definition */

//Low pass filter for 32 bit data descriptor type definition
typedef struct
{
	uint32_t X;	// Filter Accumulator (state variable).
	uint16_t Y;	// Filter output
} LPF_IIR_10bitDescr_t;

/* ________________ O P E R A T I O N S _____________________________________*/

#define LPF_M_GET_10bit_IIR_1st_OUTPUT( LPFobj )        ( LPFobj.Y )
#define LPF_M_DO_10bit_IIR_1st( In, Ts, Tau, LPFobj )	LPF_Do10bitIIR1st( In, LPF_10bit_IIR_COEFF(Ts, Tau), LPFobj )

void LPF_Init10bitIIR1st( uint16_t In, LPF_IIR_10bitDescr_t * LPFobj );

/* ________________ P R I V A T E   I N T E R F A C E _______________________*/

/* ________________ T Y P E S _______________________________________________*/

/* ________________ O P E R A T I O N S _____________________________________*/

void LPF_Do10bitIIR1st( uint16_t In, uint8_t Coeff, LPF_IIR_10bitDescr_t * LPFobj );

/***************************************************************************************************
	@M Name 			LPF_xbit_IIR_COEFF
	@M Purpose:  		Use this macro to set @compile time low pass filter IIR coefficient. 
	@M Description:		Because of Euler discretization method, filter coefficient is:
						Ts/(Ts+Tau) * LPFxBIT_RESOLUTION 
	@M Notes:  			- Ts and Tau must be determined at compile time.
						Use them as immediate floating point numbers.
						- This macro should not be called directly, but through proper macros, 
						which get Ts and Tau from user and call it to determine proper coefficient 
						value.
						- Filter Coefficient is always < 1.
	@M Parameters List:
						- Ts: Filter sampling time.
						- Tau: Filter Time constant.
***************************************************************************************************/
#define LPF_10bit_IIR_COEFF(Ts, Tau)  (uint8_t)( ( ((float)Ts) / ( ((float)Ts) + ((float)Tau) ) ) * LPF10BIT_RESOLUTION +.5 )
// COEFF > 2^8 cannot be used. In this case Ts/(Ts+Tau) must be >= 4 and <= 1024

/* ________________ T Y P E S _______________________________________________*/

/* ________________ D E F I N I T I O N S ___________________________________*/

#define LPF10BIT_RESOLUTION	1024		/* low pass filter 10 bit coefficient resolution is 1/64 to fit in 16 bit fixed math */

/* ________________ D A T A _ _______________________________________________*/

#endif //DIGITAL_FILTER_H
