
/*
 * SPI_If.h
 *
 * Created: 12/29/2019 7:43:23 PM
 *  Author: ahmad
 */ 

#ifndef _SPI_IF_H_
#define _SPI_IF_H_

/******************************************************************************************
*                                                                                         *
*                                        INCLUDES                                         *
*																						  *
*																						  *
*******************************************************************************************/


#include "std_types.h"
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

ERROR_STATUS SPIIf_init(void) ;

ERROR_STATUS SPIIf_update(uint8 *Data);


#endif