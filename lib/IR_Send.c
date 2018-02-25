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
void mark (unsigned int time)
{
	Timer_Send_Enable();
	if (time > 0)
		Delay_Microsec(time);
}

void space (unsigned int time)
{
	Timer_Send_Disable();
	if (time > 0)
		Delay_Microsec(time);
}

void Timer_Send_Enable(void)
{
	TA1CCR0 = CARRY_TICK;
	TA1CCR1 = (uint16_t)(CARRY_TICK/2);
	TA1CTL = TASSEL_2 + MC_1 + ID_3 ;                 // SMCLK, Up mode
	TA1CCTL1 = OUTMOD_7; //+ CCIE;      			// falling edge & raising edge, capture mode, capture/compare
}

void Timer_Send_Disable(void)
{
	TA1CCR0 = 0;
	TA1CCR1 = 0;
	TA1CTL = 0 ;
	TA1CCTL1 = 0;
	P2OUT &= ~PIN_IN;
}
void Delay_Microsec(int time)
{
	int i;
	for(i=0;i<time;i++)
		__delay_cycles(CLK_FREQUENCY);
}


/******************************************************************************
 * END OF IRrecv.c
*******************************************************************************/
