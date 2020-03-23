/*
***************************** LIBRARY LEVEL ***********************************
*
* Module Name       : 	Digital LowPass Filter Library.
* File              : 	DigFilt.c
* Date              : 	12/12/2011
* Version    		:
* Status     		:
*
* Document related	:
*
* Description		: This module implements a 1st IIR digital LP filtering.
*
* Functions Defined in the file:
*	LPF_Do10bitIIR1st
*	LPF_Init10bitIIR1st
*
* Developer			: Maurizio Malaspina.
*
* Modifications     :
*
*******************************************************************************
*/
 
/**************************** INCLUDED FILES *********************************/

#include "DigFilt.h"

/**************************** LOCAL DEFINITIONS ******************************/

/**************************** TYPES DEFINITIONS ******************************/

/**************************** GLOBAL VARIABLES *******************************/

/**************************** LOCAL VARIABLES ********************************/

/**************************** MACROS DEFINITIONS *****************************/

/**************************** FUNCTION DEFINITIONS ***************************/

/*
***************************** LIBRARY LEVEL ***********************************
*
* Function Name 	: 	LPF_Do10bitIIR1st
* File              : 	DigFilt.c
* Date              : 	12/12/2011
* Version    		:
* Status     		:
*
* Description		: Performs a low pass digital IIR filtering for 10 bit data.
*
* Notes             : - Discretization is performed through Euler approximation
*
*                     - PARAMETERS LIST:
*                       - In: data to be filtered   (unsigned int type).
*                       - Coeff: filter coeff (unsigned char type) = ( Ts/(Ts+Tau) ).
*                       - LPFobj: low pass filter data structure (LPF_IIR_10bitDescr_t type)
*
* Document related	:
*
* Developer			: Maurizio Malaspina.
*
* Modifications     :
*
*******************************************************************************
*/
void LPF_Do10bitIIR1st( uint16_t In, uint8_t Coeff, LPF_IIR_10bitDescr_t *  LPFobj )
{
    // Compute the difference between current filter input and previous filter output
    if ( In > LPFobj->Y )
    {
        LPFobj->X += (uint32_t)Coeff * ( In - LPFobj->Y );
    }
    else
    {
        LPFobj->X -= (uint32_t)Coeff * ( LPFobj->Y - In );
    }

	// return filtered output = ( X[n] + 512 ) / 1024
    LPFobj->Y = ( ( LPFobj->X + (LPF10BIT_RESOLUTION/2) ) / LPF10BIT_RESOLUTION );
}

/*
***************************** LIBRARY LEVEL ***********************************
*
* Function Name 	: 	LPF_Init10bitIIR1st
* File              : 	DigFilt.c
* Date              : 	12/12/2011
* Version    		:
* Status     		:
*
* Description		: 	Performs a low pass digital IIR filter for 12 bit data
*						initialization.
*
*                     - PARAMETERS LIST:
*                       - In: data to be filtered   (unsigned inte  type).
*                       - LPFobj: low pass filter data structure (LPF_IIR_8bitDescr_t type)
*
* Document related	:
*
* Developer			: Maurizio Malaspina.
*
* Modifications     :
*
*******************************************************************************
*/
void LPF_Init10bitIIR1st( uint16_t In, LPF_IIR_10bitDescr_t * LPFobj )
{
    LPFobj->X = (uint32_t)In * LPF10BIT_RESOLUTION;
    LPFobj->Y = In;         				 
}

