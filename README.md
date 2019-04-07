# Infrared Remote Control
This document is written for those who are new to infrared transmission. Specially, for user of MSP430G2xx microcontroller.

## **What is Infrared remote control (IRC)?**

<img src="https://github.com/NKNguyenLX/MSP430_IR_Remote/blob/master/images/ir_remote_1.jpg" width="500">

Infrared control is a way that you can control your everyday electronic devices such as: TV, air conditioner, projector, etc, using infrared light. IRC has two LEDs, one emits infrared light while the other receives infrared light from many sources (include the one that emitting).  The information sent or received by infrared LEDs is in HEX form and encoded by the length of high volt level (VCC or mark) and low volt level (GND or space).

## **A brief about the theory**

So you know what is sent between the two LEDs but the important question is "How the information is sent?"

The message bits are depended on the producer (LG, Panasonic, Samsung, etc) but it usually has three parts: Start bits, Data, End bits. When there is no message it stays in IDLE state (VCC). For easy understanding, I will divide into two parts (receive and transmission) and use NEC protocol to demonstrate how information is received.

**NEC protocol**

_Transmission process:_

<img src="https://github.com/NKNguyenLX/MSP430_IR_Remote/blob/master/images/ir_remote_7.png" width="700">

The two periods (9ms, 4.5ms) are the Start bits. The following periods are the information it contain: Address, Address Inverse, Command, Command Inverse. The End bit is the final pulse (VCC).

Now, have a closer look into the Data: 

-	Logical '0' – a 562.5µs pulse mark (VCC) followed by a 562.5µs space (GND)

-	Logical '1' – a 562.5µs pulse mark (VCC) followed by a 1.6875ms space (GND)

_Repeat code:_

<img src="https://github.com/NKNguyenLX/MSP430_IR_Remote/blob/master/images/ir_remote_6.png" width="700">

If the key on the remote controller is kept depressed, a repeat code will be issued, typically around 40ms after the pulse burst that signified the end of the message. A repeat code will continue to be sent out at 108ms intervals, until the key is finally released. _However, in other protocols, the whole initial message will be repeated_.


_Receiving process:_

For consistent we assume mark and space are high and low period of receiver.

The receiving process is quite similar to the transmission with: Start bits, Data, End bits and the duration of each mark and space are the same. To avoid interference of infrared light from the environment, we transmit the space by a carrier wave with a frequency of 38KHz. Which meant no transmission for mark and 38KHz wave for space (with total length equal space length). Noticed that, receiver is in IDLE state, which mean mark and turn into space when receive carrier wave.

**In summary**

Different producers will have different protocols but the frame remain the same with Start bits, Data, Stop bits. The differences are: 

-	How the Start bits and Stop bits are defined.

-	The length of mark and space for logical “0” and logical “1”.

-	For R5 and R6 protocol, Manchester encoding is used. That mean “1” starts with a mark and “0” starts with a space as shown on figure 3.

<img src="https://github.com/NKNguyenLX/MSP430_IR_Remote/blob/master/images/ir_remote_%202.PNG" width="400">

## **Hardware**

**Hardware selection:**

-	Resistor: 33 ohm – 0.5W  

-	Capacitor: 100uF

-	Emitting infrared LED

-	Receiving infrared LED: TSOP31238

-	MOSFET: LN2302LT1G

<img src="https://github.com/NKNguyenLX/MSP430_IR_Remote/blob/master/images/ir_remote_3.PNG" width="500">


## **Firmware**

**Receive process:**

<img src="https://github.com/NKNguyenLX/MSP430_IR_Remote/blob/master/images/ir_remote_4.PNG" width="500">

-	Timer is initialized and ready for receive message. Timer will get sample every 50us and count how many time (tick) of one status (mark or space). If the status changes, the code will put the number of tick (how long) into an array, reset the tick counter and count again. The process will continue until Stop bits are read. The number of tick is called raw code. Be noticed that after Stop bits, timer still continue taking sample but the information will not be record until Start bits are read again.

-	 The raw code then decoded into Hex form by using the producer protocol.

**Transmission process:**

<img src="https://github.com/NKNguyenLX/MSP430_IR_Remote/blob/master/images/ir_remote_5.PNG" width="500">

-	Hex data is encoded by producer protocol into mark and space.

-	Timer’s Outmode function is initialized to generate PWM carrier wave at 38KHz to transmits the message.

## **References**

[1] Ken Shirriff, “A Multi-Protocol Infrared Remote Library for the Arduino”, available [here](http://www.righto.com/2009/08/multi-protocol-infrared-remote-library.html)

[2] Altium Tech Docs, “NEC Infrared Transmission Protocol”, available [here](http://techdocs.altium.com/display/FPGA/NEC+Infrared+Transmission+Protocol)

[3] EEVblog, “EEVblog #506 - IR Remote Control Arduino Protocol Tutorial”, available [here](https://www.youtube.com/watch?v=BUvFGTxZBG8)

[4] huunho, “Nguyen ly va giai ma dieu khien tu xa hong ngoai”, available [here](http://codientu.org/threads/10714)
