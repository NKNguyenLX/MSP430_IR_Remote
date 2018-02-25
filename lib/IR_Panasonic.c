/******************************************************************************
 *
 * www.payitforward.edu.vn
 *
 ******************************************************************************/

/******************************************************************************
 *
 * TI LAUNCH PAD CODING
 *
 ******************************************************************************/

/******************************************************************************
 *
 *    Module       : IR_Panasonic
 *    Description  :
 *
 *  Tool           : CCS 7.4
 *  Chip           : MSP430G2xx3 (MCU that haves USCI_A0 module)
 *  History        : 12/2/2018
 *  Version        : 1.0
 *
 *  Author         : Nguyen Khoi Nguyen (knguyentnh98@gmail.com)
 *  Notes          :
 *      To apply these functions, you must include the header file uart.h and
 *      add this code file to your project.
 *
 *
******************************************************************************/

 /****************************************************************************
 * IMPORT
******************************************************************************/
#include <msp430.h>
#include <stdint.h>
#include <stdio.h>
#include "IR_Panasonic.h"





/****************************************************************************
* FUNCTIONS
******************************************************************************/
void sendPanasonic (unsigned int address,  unsigned long data)
{
	// Set IR carrier frequency
	//enableIROut(35);

	// Header
	mark(PANASONIC_HDR_MARK);
	space(PANASONIC_HDR_SPACE);

	// Address
	uint32_t mask;
	for (mask= 0x8000;  mask;  mask >>= 1) {
		mark(PANASONIC_BIT_MARK);
		if (address & mask)  space(PANASONIC_ONE_SPACE) ;
		else                 space(PANASONIC_ZERO_SPACE) ;
    }

	// Data
	for (mask= 0x80000000;  mask;  mask >>= 1) {
        mark(PANASONIC_BIT_MARK);
        if (data & mask)  space(PANASONIC_ONE_SPACE) ;
        else              space(PANASONIC_ZERO_SPACE) ;
    }

	// Footer
    mark(PANASONIC_BIT_MARK);
    space(0);  // Always end with the LED off
}


int decodePanasonic (decode_results *results)
{
    unsigned long long  data   = 0;
    int                 offset = 1;

    if (!MATCH_MARK(results->rawbuf[offset++], PANASONIC_HDR_MARK ))  return false ;
    if (!MATCH_MARK(results->rawbuf[offset++], PANASONIC_HDR_SPACE))  return false ;

    // decode address
    int i;
    for (i = 0;  i < PANASONIC_BITS;  i++) {
        if (!MATCH_MARK(results->rawbuf[offset++], PANASONIC_BIT_MARK))  return false ;

        if      (MATCH_SPACE(results->rawbuf[offset],PANASONIC_ONE_SPACE ))  data = (data << 1) | 1 ;
        else if (MATCH_SPACE(results->rawbuf[offset],PANASONIC_ZERO_SPACE))  data = (data << 1) | 0 ;
        else                                                                 return false ;
        offset++;
    }

    results->value       = (unsigned long)data;
    results->address     = (unsigned int)(data >> 32);
    results->decode_type = PANASONIC;
    results->bits        = PANASONIC_BITS;

    return true;
}


/******************************************************************************
 * END OF IRrecv.c
*******************************************************************************/
