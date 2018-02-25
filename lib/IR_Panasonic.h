/******************************************************************************
 *
 * TI LAUNCH PAD CODING
 *
 ******************************************************************************/

/******************************************************************************
 *
 *    Module       : IR_Panasonic
 *    Description  : This header file includes definitions and prototypes of
 *          API functions that support you to use UART Mode of USCI
 *
 *  Tool           : CCS 7.4
 *  Chip           : MSP430G2xx3 (MCU that haves USCI_A0 module)
 *  History        : 12/2/2018
 *  Version        : 1.0
 *
 *  Author         : Nguyen Khoi Nguyen (knguyentnh98@gmail.com)
 *  Notes          :
 *
 *
******************************************************************************/

#ifndef IRPANASONIC_H_
#define IRPANASONIC_H_

#include "IR_Remote.h"

 /****************************************************************************
 * USER DEFINITIONS
******************************************************************************/
#define false		0
#define RAWBUF      101

#define PANASONIC_HDR_MARK 		3502
#define PANASONIC_HDR_SPACE 	1750
#define PANASONIC_ONE_SPACE 	1244
#define PANASONIC_ZERO_SPACE 	400
#define PANASONIC_BIT_MARK 		502
#define PANASONIC_BITS 			48


/****************************************************************************
 * HARD DEFINITIONS
******************************************************************************/
typedef
	enum {
		UNKNOWN      = -1,
		UNUSED       =  0,
		RC5,
		RC6,
		NEC,
		SONY,
		PANASONIC,
		JVC,
		SAMSUNG,
		WHYNTER,
		AIWA_RC_T501,
		LG,
		SANYO,
		MITSUBISHI,
		DISH,
		SHARP,
		DENON,
		PRONTO,
		LEGO_PF,
	}
decode_type_t;

typedef
	struct
	{
		decode_type_t          decode_type;  	// UNKNOWN, NEC, SONY, RC5, ...
		unsigned int           address;      	// Used by Panasonic & Sharp [16-bits]
		unsigned long          value;        	// Decoded value [max 32-bits]
		int                    bits;         	// Number of bits in decoded value
		unsigned int  		   rawbuf[RAWBUF];  // Raw intervals in 50uS ticks
		int                    rawlen;       	// Number of records in rawbuf
		int                    overflow;     	// true iff IR raw code too long
	}
decode_results;


 /****************************************************************************
* FUNCTIONS 'S PROTOTYPES
******************************************************************************/
int decodePanasonic (decode_results *results);
void sendPanasonic (unsigned int address,  unsigned long data);


#endif /* IRRECV_H_ */
/******************************************************************************
 * END OF standard IRrecv.h
*******************************************************************************/


