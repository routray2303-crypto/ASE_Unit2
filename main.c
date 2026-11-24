/*
 *	Project Owner	: TU Chemnitz
 *	Project Name	: ASE Tutorial Unit-2
 *	File Name		: main.c
 *	Author			: ASE Admin
 *  Created on		: 25 Feb 2024
 */

/* Includes ******************************************************************/
#include "init.h"


/* Global variables **********************************************************/
int speed = 0u;
int rpm = 8000u;
int rpm_dir = -1;
int pot_val = 0u;
int light_val = 0u;

void can_send_engine_on(void){

	/* TO-DO: your task implementations **************************************/

    // set payload bytes, if necessary
	// CAN_0.BUF[10u].DATA.B[0u] = 0x11u;			// HC - task 2
	// CAN_0.BUF[10u].DATA.B[1u] = 0x12u;			// HC - task 2
	// CAN_0.BUF[10u].MSG_CS.B.LENGTH = 0x02u;		// HC - task 2

	// write the correct CODE value to this register to instruct the CAN controller to transmit the CAN message
	CAN_0.BUF[10u].CS.B.CODE = 0x0Cu;				// HC - task 2, 3
	
}

void can_send_speed(int value){
	/* TO-DO: your task implementations **************************************/
	speed = (240 * value) / (4095);					// HC - task 3

	CAN_0.BUF[11u].DATA.B[0u] = speed;				// HC - task 3

	CAN_0.BUF[11u].CS.B.CODE = 0x0Cu;				// HC - task 3

}

void can_send_rpm(){
	/* TO-DO: your task implementations **************************************/

	CAN_0.BUF[12u].DATA.B[0u] = (rpm & 0xFFu);

	CAN_0.BUF[12u].DATA.B[1u] = ((rpm >> 8) & 0xFFu);

	CAN_0.BUF[12u].CS.B.CODE = 0x0Cu;

}

void can_send_lights(void){
	/* TO-DO: your task implementations **************************************/

	CAN_0.BUF[13u].DATA.B[0u] = light_val;

	CAN_0.BUF[13u].CS.B.CODE = 0x0Cu;

}

void can_send(void){

	/* TO-DO: your task implementations **************************************/

	pot_val = POT;
	LED_Rx = 0x00u;
	// LED_U1 = 0x00u;

	/*************************************************************************/
}


/*
 * @brief	Main program
 *
 * @param	void
 * @retval	int
 */
int main(void) {
	/* peripherals initialization */
	peripheralsInit();



	/* TO-DO: your task implementations **************************************/

	/* Configure and start timer channels */
	/* PIT timer channel 1, period = 1000 ms */
	PIT_ConfigureTimer(1u, 100u);	// HC - task 2
	PIT_ConfigureTimer(2u, 1000u);
	PIT_ConfigureTimer(3u, 500u);
	// PIT_StartTimer(1u);				// HC - task 2
	/*************************************************************************/


	/* main program */
	while(1){
		/* System function */
		systemFunction();

		/* TO-DO: your task implementations **********************************/

		can_send();

		/*********************************************************************/

		/* 10 ms OS delay */
		osalThreadDelayMilliseconds(10UL);
	}
}


/*
 * @brief	CAN receive interrupt
 *
 * @param   CANDriver   canp	The CAN controller which received a message
 * @param	CANRxFrame	crfp	The message which was received
 * @retval	void
 */
void can_receive(CANRxFrame crfp) {
    if(crfp.IDE == CAN_IDE_STD) // a standard message frame has been received
    {
        /* TO-DO: your task implementations ******************************/
		LED_Rx = 0x01u;	// HC - task 1
        if (crfp.SID == 0x11u) // check the Message ID	// HC - task 1
        {
			// LED_U1 = 0x01u;	// HC - task 1
			LED_P = 0x01u;		// HC - task 3
			PIT_StartTimer(1u);	// HC - task 3
			PIT_StartTimer(2u);
			PIT_StartTimer(3u);
        }
		else if (crfp.SID == 0x10u)		// HC - task 3
		{
			PIT_StopTimer(1u);			// HC - task 3
			PIT_StopTimer(2u);
			PIT_StopTimer(3u);
			LED_P = 0x00u;				// HC - task 3
			LED_U1 = 0x00u;				// HC - task 3
			LED_U3 = 0x00u;				// HC - task 3
			LED_Tx = 0x00u;
		}
		else
		{
			/* Do nothing */
		}
    }
}


/*
 * @brief	PIT timer channel 1 IRQ callback
 *
 * @param	void
 * @retval	void
 */
void PIT_Channel_1(void){
	/* TO-DO: your task implementations **************************************/
	LED_Tx = !LED_Tx;
	can_send_engine_on();			// HC - task 2, 3
	can_send_speed(pot_val);		// HC - task 3
	can_send_rpm();
	can_send_lights();
}


/*
 * @brief	PIT timer channel 2 IRQ callback
 *
 * @param	void
 * @retval	void
 */
void PIT_Channel_2(void){
	/* TO-DO: your task implementations **************************************/

	if ((rpm == 0) && (rpm_dir == -1))
	{
		rpm_dir = 1;
	}
	else if ((rpm == 8000) && (rpm_dir == 1))
	{
		rpm_dir = -1;
	}
	else
	{
		/* Do nothing */
	}
	rpm += (rpm_dir * 250u);
}


/*
 * @brief	PIT timer channel 3 IRQ callback
 *
 * @param	void
 * @retval	void
 */
void PIT_Channel_3(void){
	/* TO-DO: your task implementations **************************************/

	if (SW1 && SW2)
	{
		LED_U1 = !LED_U1;
		LED_U3 = LED_U1;
		light_val = 0x03u;
	}
	else if (SW1 && !SW2)
	{
		LED_U3 = !LED_U3;
		LED_U1 = 0x00u;
		light_val = 0x02u;
	}
	else if (!SW1 && SW2)
	{
		LED_U1 = !LED_U1;
		LED_U3 = 0x00u;
		light_val = 0x01u;
	}
	else
	{
		LED_U1 = 0x00u;
		LED_U3 = 0x00u;
		light_val = 0x00u;
	}
}
