
/*
 * Initialization.c
 *
 * Created: 12/29/2019 2:50:21 PM
 *  Author: ahmad
 */ 


/******************************************************************************************
*                                                                                         *
*                                        INCLUDES                                         *
*																						  *
*																						  *
*******************************************************************************************/

#include "UART.h"
#include "common_macros.h"
#include "std_types.h"
#include "interrupt.h"
#include "registers.h"
#include "DIO.h"
#include "UARTIF.h"
#include "softwareDelay.h"
#include "Char_lcd.h"

/******************************************************************************************
*                                                                                         *
*                                        DEFINES                                          *
*																						  *
*																						  *
*******************************************************************************************/

#define BAUD_RATE_9600					(9600U)

/******************************************************************************************
*                                                                                         *
*                               STATIC VARIABLES                                          *
*																						  *
*																						  *
*******************************************************************************************/



/******************************************************************************************
*                                                                                         *
*                                 IMPLEMENTATION                                          *
*																						  *
*																						  *
*******************************************************************************************/



/******************************************************************************************
* brief(Initialization_init): initializes the UART                                        *
* INPUT:                                                                                  *
* OUTPUT:																				  *
* RETURN: ERROR_STATUS																	  *
*******************************************************************************************/
ERROR_STATUS UARTIf_init(void)
{
	UART_cfg_s UART_info = {UART_POLLING, TRANSCEIVER, UART_DOUBLE_SPEED, UART_ONE_STOP_BIT, UART_NO_PARITY, UART_8_BIT, BAUD_RATE_9600, NULL, NULL, NULL};
	UART_Init(&UART_info);
	return E_OK;
}


/******************************************************************************************
* brief(Initialization_getValues): gets initialization values                             *
* INPUT:                                                                                  *
* OUTPUT(velocity):	initial velocity													  *
* OUTPUT(time):	initial time															  *
* RETURN: ERROR_STATUS																	  *
*******************************************************************************************/
ERROR_STATUS UARTIf_getValues(uint8 *velocity, uint8 *time)
{
	uint8 u8a_helpGuideTime[] = "Please enter time\n";
	uint8 u8a_helpGuideVelocity[] = "Please enter velocity\n";
	uint8 u8_counter = 0;
	uint8 u8_temp_time = 0;
	uint8 u8_temp_velocity = 0;
	uint8 u8_temp_time1 = 0;
	uint8 u8_temp_velocity1 = 0;
	SwDelay_ms(50);
	while (u8a_helpGuideTime[u8_counter] != '\0')
	{
		UART_SendByte(u8a_helpGuideTime[u8_counter]);

		u8_counter++;
	}
	UART_ReceiveByte(&u8_temp_time);
	while ( u8_temp_time != '\r')
	{
		u8_temp_time -= 48;
		u8_temp_time1 *=10;
		u8_temp_time1 += u8_temp_time;
		UART_ReceiveByte(&u8_temp_time);
	}
	
	u8_counter = 0;
	while (u8a_helpGuideVelocity[u8_counter] != '\0')
	{
		UART_SendByte(u8a_helpGuideVelocity[u8_counter]);
		u8_counter++;
	}
	UART_ReceiveByte(&u8_temp_velocity);
	while (u8_temp_velocity != '\r')
	{
		u8_temp_velocity -= 48;
		u8_temp_velocity1 *=10;
		u8_temp_velocity1 += u8_temp_velocity;
		UART_ReceiveByte(&u8_temp_velocity);
	}	
	*time = u8_temp_time1;
	*velocity = u8_temp_velocity1;
	return E_OK;
}