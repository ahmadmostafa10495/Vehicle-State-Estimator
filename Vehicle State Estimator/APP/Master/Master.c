
/*
 * Master.c
 *
 * Created: 12/29/2019 6:22:06 PM
 *  Author: ahmad
 */ 




/******************************************************************************************
*                                                                                         *
*                                        INCLUDES                                         *
*																						  *
*																						  *
*******************************************************************************************/
#include "Master.h"
#include "Timer.h"
#include "common_macros.h"
#include "std_types.h"
#include "interrupt.h"
#include "registers.h"
#include "DIO.h"
#include "UARTIF.h"
#include "TIMERIF.h"
#include "SPI_If.h"
#include "SpeedHandler.h"
#include "Char_lcd.h"
#include "SPI.h"
#include <stdlib.h>
#include "softwareDelay.h"


/******************************************************************************************
*                                                                                         *
*                                        DEFINES                                          *
*																						  *
*																						  *
*******************************************************************************************/



/******************************************************************************************
*                                                                                         *
*                               STATIC VARIABLES                                          *
*																						  *
*																						  *
*******************************************************************************************/


static uint8 gsu8_SystemTime = 0;
static uint8 gsu8_SystemVelocity = 0;
static uint8 gsu8_SystemTimeTEMP = 0;
static uint8 gsu8_SystemVelocityTEMP = 0;

static uint8 gsu8_SPI_ExchangeData = 0xFF;
static uint8 gsu8_SPI_IdealExchangeData = 0xFF;

static uint8 gsu8_SPI_StartByte = 0xAA;
static uint8 gsu8_SPI_StopByte = 0x55;

static void sendFrame(void);

/******************************************************************************************
*                                                                                         *
*                                 IMPLEMENTATION                                          *
*																						  *
*																						  *
*******************************************************************************************/



void TIMER_IF_CBK(void);




ERROR_STATUS Master_init(void)
{
	UARTIf_init();
	SPIIf_init();
	TimerIf_init(TIMER_IF_CBK);
	SpeedHandler_init();
	UARTIf_getValues(&gsu8_SystemVelocity, &gsu8_SystemTime);
	TimerIf_start();
	SPIIf_update(&gsu8_SPI_IdealExchangeData);
	return E_OK;
}

ERROR_STATUS Master_Update(void)
{
	SpeedHandler_Update(&gsu8_SystemVelocity);
	
	return E_OK;
}


void TIMER_IF_CBK(void)
{
	
	gsu8_SystemTime++;
	/*send vel via SPI*/
	LCD_goto_xy(0, 0);
	char buff[16];
	itoa(gsu8_SystemTime, buff, 10);
	LCD_send_string("TIME:");
	LCD_send_string(buff);
	LCD_goto_xy(0, 1);
	itoa(gsu8_SystemVelocity, buff, 10);
	LCD_send_string("VELOCITY:");
	LCD_send_string(buff);	  
	gsu8_SystemTimeTEMP = gsu8_SystemTime;
	SPIIf_update(&gsu8_SystemTimeTEMP);
	gsu8_SystemVelocityTEMP = gsu8_SystemVelocity;
	SPIIf_update(&gsu8_SystemVelocityTEMP);


	
}


static void sendFrame(void)
{
	uint8 flag =0;
	while (!flag)
	{
		
		SPIIf_update(&gsu8_SPI_StartByte);
		if (gsu8_SPI_StartByte == 0xAA)
		{
			flag = 1;
			gsu8_SystemTimeTEMP = gsu8_SystemTime;
			SPIIf_update(&gsu8_SystemTimeTEMP);
			gsu8_SystemVelocityTEMP = gsu8_SystemVelocity;
			SPIIf_update(&gsu8_SystemVelocityTEMP);
			
		}
		else
		{
			flag = 0;
			gsu8_SPI_StartByte = 0xAA;
		}
}


}