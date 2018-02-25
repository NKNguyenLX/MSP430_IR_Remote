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
 *    Module       : IRrecv
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
#include "IRrecv.h"




/****************************************************************************
* FUNCTIONS
******************************************************************************/

#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer0_A1_ISR(void)
{
    switch( TA0IV )
    {
    case  2:                            // CCR1 not used
        break;
    case  4:                            // CCR2 not used
        break;
    case 10:                            // overflow
        // Read if IR Receiver -> SPACE [xmt LED off] or a MARK [xmt LED on]
        // digitalRead() is very slow. Optimisation is possible, but makes the code unportable
        // unsigned char irdata;
        if (P1IN & PIN_IN)
            irdata = 1;
        else irdata =0;

        irparams.timer++;  // One more 50uS tick
        if (irparams.rawlen >= RAWBUF)  irparams.rcvstate = STATE_OVERFLOW ;  // Buffer overflow

        switch(irparams.rcvstate) {
            //......................................................................
            case STATE_IDLE: // In the middle of a gap
                if (irdata == MARK) {
                    if (irparams.timer < GAP_TICKS)  {  // Not big enough to be a gap.
                        irparams.timer = 0;

                    } else {
                        // Gap just ended; Record duration; Start recording transmission
                        irparams.overflow                  = false;
                        irparams.rawlen                    = 0;
                        irparams.rawbuf[irparams.rawlen++] = irparams.timer;
                        irparams.timer                     = 0;
                        irparams.rcvstate                  = STATE_MARK;
                    }
                }
                break;
            //......................................................................
            case STATE_MARK:  // Timing Mark
                if (irdata == SPACE) {   // Mark ended; Record time
                    irparams.rawbuf[irparams.rawlen++] = irparams.timer;
                    irparams.timer                     = 0;
                    irparams.rcvstate                  = STATE_SPACE;
                }
                break;
            //......................................................................
            case STATE_SPACE:  // Timing Space
                if (irdata == MARK) {  // Space just ended; Record time
                    irparams.rawbuf[irparams.rawlen++] = irparams.timer;
                    irparams.timer                     = 0;
                    irparams.rcvstate                  = STATE_MARK;

                } else if (irparams.timer > GAP_TICKS) {  // Space
                        // A long Space, indicates gap between codes
                        // Flag the current code as ready for processing
                        // Switch to STOP
                        // Don't reset timer; keep counting Space width
                        irparams.rcvstate = STATE_STOP;
                }
                break;
            //......................................................................
            case STATE_STOP:  // Waiting; Measuring Gap
                if (irdata == MARK)  irparams.timer = 0 ;  // Reset gap timer
                irparams.irrecvflag = 1;
                break;
            //......................................................................
            case STATE_OVERFLOW:  // Flag up a read overflow; Stop the State Machine
                irparams.overflow = true;
                irparams.rcvstate = STATE_STOP;
                break;
        }
        P1OUT ^= LED_GREEN;
        break;
    }
}

/******************************************************************************
 * END OF IRrecv.c
*******************************************************************************/

