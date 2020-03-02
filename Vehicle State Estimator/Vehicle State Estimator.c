/*
 * Vehicle_State_Estimator.c
 *
 * Created: 12/29/2019 2:34:50 PM
 *  Author: ahmad
 */ 

#include "Char_lcd.h"
#include "Master.h"
#include <stdlib.h>

int main(void)
{
	LCD_init();
	Master_init();
	/*UARTIf_init();
	uint8 velocity = 0, time = 0;
	UARTIf_getValues(&velocity, &time);

	char charbuff[16];
	LCD_goto_xy(0,0);
	itoa(time, charbuff, 10);
	LCD_send_string(charbuff);
	itoa(velocity, charbuff, 10);
	LCD_goto_xy(0,1);
	LCD_send_string(charbuff);	*/
    while(1)
    {
		Master_Update();
        //TODO:: Please write your application code 
    }
}