
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
#include "PushButton.h"
#include "SpeedHandler.h"


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




/******************************************************************************************
*                                                                                         *
*                                 IMPLEMENTATION                                          *
*																						  *
*																						  *
*******************************************************************************************/

ERROR_STATUS SpeedHandler_init(void)
{
	PushButton_Cfg_st Button_info = {BTN_0};
	pushButton_Init(&Button_info);
	Button_info.btn_id = BTN_1;
	pushButton_Init(&Button_info);
	return E_OK;
}




ERROR_STATUS SpeedHandler_Update(uint8 *velocity)
{
	pushButton_Update();
	uint8 Button_State = Released;
	pushButton_GetStatus(BTN_0, &Button_State);
	if (Button_State == Prepressed)
	{
		(*velocity)--;
	}
	Button_State = Released;
	pushButton_GetStatus(BTN_1, &Button_State);
	if (Button_State == Prepressed)
	{
		(*velocity)++;
	}
	return E_OK;
}