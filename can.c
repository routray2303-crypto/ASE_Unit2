/*
 *	Project Owner	: TU Chemnitz
 *	Project Name	: ASE Tutorial Unit-2
 *	File Name		: can.c
 *	Author			: ASE Admin
 *  Created on		: 25 Feb 2024
 */

/* Includes ******************************************************************/
#include "can.h"
#include "xpc56el.h"

/*
 * @brief	CAN0 initialization function
 *
 * @param	void
 * @retval	void
 */
void CAN_Init(void){
	can_lld_start(&CAND1, &can_config_cfg0);


	/* TO-DO: pre-configure message buffer(s) for sending here ***********************/

	/* Engine On */
	CAN_0.BUF[10u].MSG_CS.B.IDE = 0x01u;		/* Message/frame format: 1 = Extended, 0 = Standard/Base */		// HC - task 2, 3
	CAN_0.BUF[10u].MSG_ID.B.STD_ID = 0x00u;		/* Message ID for standard frame */								// HC - task 2, 3
	CAN_0.BUF[10u].MSG_ID.B.EXT_ID = 0xDA0u;	/* Message ID for extended frame*/								// HC - task 2, 3
	CAN_0.BUF[10u].MSG_CS.B.RTR = 0x00u;		/* Remote Transmission Request; 0 = Data Frame */				// HC - task 2, 3
	CAN_0.BUF[10u].CS.B.LENGTH = 0x00u;			/* Length of Payload, 0 - 8*/									// HC - task 2, 3

	/* Vehicle Speed */
	CAN_0.BUF[11u].MSG_CS.B.IDE = 0x01u;		/* Message/frame format: 1 = Extended, 0 = Standard/Base */		// HC - task 3
	CAN_0.BUF[11u].MSG_ID.B.STD_ID = 0x00u;		/* Message ID for standard frame */								// HC - task 3
	CAN_0.BUF[11u].MSG_ID.B.EXT_ID = 0x5A0u;	/* Message ID for extended frame*/								// HC - task 3
	CAN_0.BUF[11u].MSG_CS.B.RTR = 0x00u;		/* Remote Transmission Request; 0 = Data Frame */				// HC - task 3
	CAN_0.BUF[11u].CS.B.LENGTH = 0x01u;			/* Length of Payload, 0 - 8*/									// HC - task 3

	/* Engine RPM */
	CAN_0.BUF[12u].MSG_CS.B.IDE = 0x01u;		/* Message/frame format: 1 = Extended, 0 = Standard/Base */		// HC - task 3
	CAN_0.BUF[12u].MSG_ID.B.STD_ID = 0x00u;		/* Message ID for standard frame */								// HC - task 3
	CAN_0.BUF[12u].MSG_ID.B.EXT_ID = 0x280u;	/* Message ID for extended frame*/								// HC - task 3
	CAN_0.BUF[12u].MSG_CS.B.RTR = 0x00u;		/* Remote Transmission Request; 0 = Data Frame */				// HC - task 3
	CAN_0.BUF[12u].CS.B.LENGTH = 0x02u;			/* Length of Payload, 0 - 8*/									// HC - task 3

	/* Lights */
	CAN_0.BUF[13u].MSG_CS.B.IDE = 0x01u;		/* Message/frame format: 1 = Extended, 0 = Standard/Base */		// HC - task 3
	CAN_0.BUF[13u].MSG_ID.B.STD_ID = 0x00u;		/* Message ID for standard frame */								// HC - task 3
	CAN_0.BUF[13u].MSG_ID.B.EXT_ID = 0x470u;	/* Message ID for extended frame*/								// HC - task 3
	CAN_0.BUF[13u].MSG_CS.B.RTR = 0x00u;		/* Remote Transmission Request; 0 = Data Frame */				// HC - task 3
	CAN_0.BUF[13u].CS.B.LENGTH = 0x01u;			/* Length of Payload, 0 - 8*/									// HC - task 3

	/*************************************************************************/
}


/*
 * @brief	CAN message transmit function
 *
 * @param	CANTxFrame	txMsg
 * @param	canmbx_t	mbx
 * @retval	void
 */
void CAN_TxMessage(CANTxFrame txMsg, canmbx_t mbx){
	// nop
}
