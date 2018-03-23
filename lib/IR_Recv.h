/******************************************************************************
 *
 * TI LAUNCH PAD CODING
 *
 ******************************************************************************/

/******************************************************************************
 *
 *    Module       : IRrecv
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

#ifndef IRRECV_H_
#define IRRECV_H_

#include "IR_Remote.h"

 /****************************************************************************
 * USER DEFINITIONS
******************************************************************************/
//#define DEBUG
//#define SAMPLING_TIME   (16*50)   //sampling at 50us with clock at 16MHz
//#define BTN1            BIT3
//#define LED_GREEN       BIT6
//#define PIN_IN          BIT3        //Read form P1.3

#define RAWBUF          101
#define MARK            0
#define SPACE           1


// Minimum gap between IR transmissions
#define USECPERTICK     50
#define _GAP            5000
#define GAP_TICKS       (_GAP/USECPERTICK)

// ISR State-Machine : Receiver States
#define STATE_IDLE      2
#define STATE_MARK      3
#define STATE_SPACE     4
#define STATE_STOP      5
#define STATE_OVERFLOW  6

/****************************************************************************
 * HARD DEFINITIONS
******************************************************************************/
typedef
    struct {
        // The fields are ordered to reduce memory over caused by struct-padding
        uint8_t       rcvstate;        // State Machine state
        uint8_t       recvpin;         // Pin connected to IR data from detector
        uint8_t       blinkpin;
        uint8_t       blinkflag;       // true -> enable blinking of pin on IR processing
        uint8_t       rawlen;          // counter of entries in rawbuf
        unsigned int  timer;           // State timer, counts 50uS ticks.
        unsigned int  rawbuf[RAWBUF];  // raw data
        uint8_t       overflow;        // Raw buffer overflow occurred
        uint8_t		  irrecvflag;	   // Flag indicate a button have been received
    }
irparams_t;

// Allow all parts of the code access to the ISR data
// NB. The data can be changed by the ISR at any time, even mid-function
// Therefore we declare it as "volatile" to stop the compiler/CPU caching it
volatile irparams_t irparams;

uint8_t irdata;

 /****************************************************************************
* FUNCTIONS 'S PROTOTYPES
******************************************************************************/



#endif /* IRRECV_H_ */
/******************************************************************************
 * END OF standard IRrecv.h
*******************************************************************************/


