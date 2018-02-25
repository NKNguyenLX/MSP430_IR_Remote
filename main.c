#include <msp430.h> 
#include <stdint.h>
#include "lib/IR_Remote.h"


uint16_t  data[RAWBUF];
uint8_t	  data_len;
decode_results decode;
uint8_t irf_send;

#ifdef DEBUG
int iState = 1;
#endif

int main(void)
{
	Config_stop_WDT();
	Clock_Init();
	GPIO_Init();
	//Timer_Send_Enable();
	while(1)
	{
//		if(irparams.irrecvflag == 1)
//		{
////			s_copy(data,irparams.rawbuf);
////			data_len = irparams.rawlen;
//////			irparams.irrecvflag = 0;
//////			irparams.rcvstate = STATE_IDLE;
//			Timer_Recv_Disable();
//			Array_copy(decode.rawbuf,irparams.rawbuf);
//			decodePanasonic (&decode);
//			IR_reset();
//			Timer_Recv_Enable();
//		}
		//IR_read(data);
		if(irf_send == 1)
		{
			P1OUT ^= LED_GREEN;
			sendPanasonic(0x4004,0x0100BCBD);
			irf_send = 0;
		}
	}
	
}


#ifdef DEBUG
#pragma vector = PORT1_VECTOR
__interrupt void BUTTON_Interrupt_Handle(void)
{
    if (((P1IFG & BTN1) == BTN1) && (irf_send == 0))
    {
    	P1OUT ^= LED_RED;
        irf_send = 1;
    }
    P1IFG &= ~BTN1;
}
#endif


