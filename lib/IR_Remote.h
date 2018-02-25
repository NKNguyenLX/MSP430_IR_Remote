/******************************************************************************
 *
 * TI LAUNCH PAD CODING
 *
 ******************************************************************************/

/******************************************************************************
 *
 *    Module       : IR_Remote
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

#ifndef IR_REMOTE_H_
#define IR_REMOTE_H_

 /****************************************************************************
 * USER INCLUDES
******************************************************************************/
#include "IRrecv.h"
#include "IR_Panasonic.h"
#include "IR_Send.h"

 /****************************************************************************
 * USER DEFINITIONS
******************************************************************************/
#define true            1
#define false           0

// Hardware initialize

#define DEBUG
#define CLK_FREQUENCY	16		 	// frequency of Master Clock in MHz
#define SAMPLING_TIME   (16*50)     // sampling at 50us with clock at 16MHz
#define BTN1            BIT3
#define LED_GREEN       BIT6
#define LED_RED			BIT0
#define PIN_IN          BIT4        // read form P1.4
#define PIN_OUT			BIT1		// out at P2.1

// Due to sensor lag, when received, Marks  tend to be 40us too long and
//                                   Spaces tend to be 40us too short
#define MARK_EXCESS     40

// Upper and Lower percentage tolerances in measurements
#define TOLERANCE       30
#define LTOL            (1.0 - (TOLERANCE/100.))
#define UTOL            (1.0 + (TOLERANCE/100.))

// Set Out Mode frequency, expected at 38 KHz
#define CARRY_DURATION 	26 			// 26 = 1/38000 * 1000000
#define CARRY_TICK 		(CARRY_DURATION*CLK_FREQUENCY)

#define TICKS_LOW(us)   ((int)(((us)*LTOL/USECPERTICK)))
#define TICKS_HIGH(us)  ((int)(((us)*UTOL/USECPERTICK + 1)))


/****************************************************************************
 * HARD DEFINITIONS
******************************************************************************/



 /****************************************************************************
* FUNCTIONS 'S PROTOTYPES
******************************************************************************/
void Config_stop_WDT(void);
void Clock_Init(void);
void Timer_Recv_Enable(void);
void Timer_Recv_Disable(void);
void GPIO_Init(void);

void Array_copy(uint16_t s_2[],volatile uint16_t s_1[]);
void IR_read(uint16_t data[]);
void IR_reset(void);

int  MATCH_MARK (int measured_ticks,  int desired_us);
int  MATCH_SPACE (int measured_ticks,  int desired_us);


#endif /* IRRECV_H_ */
/******************************************************************************
 * END OF standard IRrecv.h
*******************************************************************************/



