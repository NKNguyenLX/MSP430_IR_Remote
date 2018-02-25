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

#ifndef IRSEND_H_
#define IRSEND_H_

#include "IR_Remote.h"

 /****************************************************************************
 * USER DEFINITIONS
******************************************************************************/



/****************************************************************************
 * HARD DEFINITIONS
******************************************************************************/



 /****************************************************************************
* FUNCTIONS 'S PROTOTYPES
******************************************************************************/
void mark (unsigned int time);
void space (unsigned int time);
void Timer_Send_Enable(void);
void Timer_Send_Disable(void);
void Delay_Microsec(int time);

#endif /* IRRECV_H_ */
/******************************************************************************
 * END OF standard IRrecv.h
*******************************************************************************/


