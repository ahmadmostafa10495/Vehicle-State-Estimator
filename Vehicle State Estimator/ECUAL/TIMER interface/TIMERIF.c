
/*
 * TIMERIF.c
 *
 * Created: 12/29/2019 6:57:02 PM
 *  Author: ahmad
 */ 

/******************************************************************************************
*                                                                                         *
*                                        INCLUDES                                         *
*																						  *
*																						  *
*******************************************************************************************/
#include "TIMERIF.h"
#include "Timer.h"
#include "interrupt.h"


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

volatile static uint8 gsu8_OVFCount= 0;
void (*TIMER_IF_CBK_ptr)(void) = NULL;


/******************************************************************************************
*                                                                                         *
*                                 IMPLEMENTATION                                          *
*																						  *
*																						  *
*******************************************************************************************/

void Timer_OVF_CBK(void);


ERROR_STATUS TimerIf_init(void (*TIMER_IF_CBK)(void))
{
	sei();
	Timer_cfg_s Timer_info ={TIMER_CH0, TIMER_MODE, TIMER_INTERRUPT_MODE, TIMER_PRESCALER_1024, Timer_OVF_CBK};
	Timer_Init(&Timer_info);
	TIMER_IF_CBK_ptr = TIMER_IF_CBK;
	return E_OK;	
}

ERROR_STATUS TimerIf_start(void )
{
	Timer_Start(TIMER_CH0,255);
	return E_OK;
}





void Timer_OVF_CBK(void)
{
	gsu8_OVFCount++;
	if (gsu8_OVFCount >= 61)
	{
		gsu8_OVFCount = 0;
		if (NULL != TIMER_IF_CBK_ptr)
		{
			TIMER_IF_CBK_ptr();
		}
		else
		{
			
		}
		
	}
}