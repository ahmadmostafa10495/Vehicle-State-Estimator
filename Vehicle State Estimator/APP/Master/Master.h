
/*
 * Master.h
 *
 * Created: 12/29/2019 6:21:45 PM
 *  Author: ahmad
 */ 
#ifndef _MASTER_H_
#define _MASTER_H_





/******************************************************************************************
*                                                                                         *
*                                        INCLUDES                                         *
*																						  *
*																						  *
*******************************************************************************************/

#include "UARTIF.h"

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
*                                 PROTOTYPES                                              *
*																						  *
*																						  *
*******************************************************************************************/
ERROR_STATUS Master_init(void);


ERROR_STATUS Master_Update(void);

#endif

