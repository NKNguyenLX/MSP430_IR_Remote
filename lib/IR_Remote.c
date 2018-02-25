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
 *    Module       : IR_Remote
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
#include "IR_Remote.h"




/****************************************************************************
* FUNCTIONS
******************************************************************************/

void Config_stop_WDT(void)
{
    WDTCTL = WDTPW + WDTHOLD;
}
void Clock_Init(void)
{
    DCOCTL = 0;
    BCSCTL1 = CALBC1_16MHZ;          			// set range
    DCOCTL = CALDCO_16MHZ;           			// set DCO step + moudulation
}

void Timer_Recv_Enable(void)
{
    TA0CCR0 = SAMPLING_TIME;
    TA0CTL = TASSEL_2 + MC_1 + TAIE;           // SMCLK, Up mode, Overflow interrupt
    TA0CCTL0 &= ~CCIFG;
    // Initialize state machine variables
    irparams.rcvstate = STATE_IDLE;
    irparams.rawlen = 0;
}

void Timer_Recv_Disable(void)
{
	TA0CTL = 0 ;
	TA0R = 0;
	P1OUT  &= ~LED_GREEN;
}

void GPIO_Init(void)
{
    P1SEL  &= ~(BTN1 + LED_GREEN);
    P1SEL2 &= ~(BTN1 + LED_GREEN);
    //Init button
    P1DIR  &= ~BTN1;
    P1REN  |= BTN1;
    P1OUT  |= BTN1;
#ifdef DEBUG
    P1IE   |= BTN1;
    P1IES  |= BTN1;
    P1IFG  &= ~BTN1;
#endif
    //Init LED GREEN
    P1DIR |= LED_GREEN;
    P1OUT &= ~LED_GREEN;
    //Init LED RED
    P1DIR |= LED_RED;
    P1OUT |= LED_RED;
    //Init in pin
    P1DIR  &= ~PIN_IN;
    P1REN  |= PIN_IN;
    P1OUT  |= PIN_IN;
    //Init send pin
    P2DIR |= PIN_OUT;
    P2OUT &= ~PIN_OUT;
    P2SEL|= PIN_OUT;
    _BIS_SR(GIE);
}

void Array_copy(uint16_t s_2[],volatile uint16_t s_1[])
{
	int i = 0;
	while(s_1[i] != 0)
	{
		s_2[i] = s_1[i];
		i++;
	}
}

void IR_reset(void)
{
	int i;
	irparams.irrecvflag = 0;
	irparams.rcvstate = STATE_IDLE;
	for(i=0;i<RAWBUF;i++)
		irparams.rawbuf[i]=0;
}

void IR_read(uint16_t data[])
{
	if(irparams.irrecvflag == 1)
	{
		Array_copy(data,irparams.rawbuf);
//			irparams.irrecvflag = 0;
//			irparams.rcvstate = STATE_IDLE;
		IR_reset();
	}
}


//+========================================================
// Due to sensor lag, when received, Marks tend to be 40us too long
//
int  MATCH_MARK (int measured_ticks,  int desired_us)
{
  uint8_t passed = ((measured_ticks >= TICKS_LOW (desired_us + MARK_EXCESS))
                && (measured_ticks <= TICKS_HIGH(desired_us + MARK_EXCESS)));
 	return passed;
}

//+========================================================
// Due to sensor lag, when received, Spaces tend to be 40us too short
//
int  MATCH_SPACE (int measured_ticks,  int desired_us)
{
  uint8_t passed = ((measured_ticks >= TICKS_LOW (desired_us - MARK_EXCESS))
                && (measured_ticks <= TICKS_HIGH(desired_us - MARK_EXCESS)));
 	return passed;
}


/******************************************************************************
 * END OF IRrecv.c
*******************************************************************************/
