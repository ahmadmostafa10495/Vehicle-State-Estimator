/*
 * SPI_Pb.h
 *
 * Created: 12/20/2019 3:25:15 PM
 *  Author: Wave7
 */ 



#ifndef SPI_H_
#define SPI_H_

#include "std_types.h"
//#include "interrupts.h"

#define SPEED_REQUEST		(0x1f)
#define TIME_REQUEST		(0x0f)
/*
 * SPI Registers
 */

#define SPCR    *((reg_type8)(0x2D))
#define SPSR    *((reg_type8)(0x2E))
#define SPDR    *((reg_type8)(0x2F))


typedef struct {
uint8 u8_SPIMode;
uint8 u8_DataMode;
uint8 u8_DataOrder;
uint8 u8_InterruptMode;
uint8 u8_Prescaler;
void (*CBK_Func) (void);
}SPI_Cfg_s;


/* NORMAL SPEED */
#define SPI_PRESCALER_2     (0)
#define SPI_PRESCALER_4     (1)
#define SPI_PRESCALER_8     (2)
#define SPI_PRESCALER_16    (3)
#define SPI_PRESCALER_32    (4)
#define SPI_PRESCALER_64    (5)
#define SPI_PRESCALER_128   (6)

/* YOU CAN USE PRE_SCALER_F_64 FROM NORMAL SPEED ! */


/* Polling or Interrupt */
#define POLLING         (0)
#define INTERRUPT       (1)

/* Master or Slave */
#define SLAVE           (0)
#define MASTER          (1)

/* Most SB or Least SB */
#define MSB             (0)
#define LSB             (1)

/* Data modes */
#define MODE_0			(0)
#define MODE_1			(1)
#define MODE_2			(2)
#define MODE_3			(3)

/**
* @brief: Initialize SPI module
* @param:
* Input : SPI_Cfg_s* "Pointer to Struct of SPI Configration
* Output: None
* @return: Error codes if present
*/
ERROR_STATUS SPI_Init(SPI_Cfg_s* pstr_SPI_Confg);


/**
* @brief: Transmit one byte over SPI
* @param:
* Input : u8_Data "Byte to be sent"
* Output: None
* @return: Error codes if present
*/
ERROR_STATUS SPI_MasterTransmission(uint8* u8_Data);

/**
* @brief: Transmit one byte over SPI and receive the byte from the slave
* @param:
* Input/ : u8_Data "Byte to be sent and save the received byte"
* @return: Error codes if present
*/
ERROR_STATUS SPI_SlaveTransmission(uint8 *ptru8_Data);

/**
* @brief: Get status of SPI interrupt flag
* @param:
* Input : None
* Output: *u8_Data "points to where flag value is going to be stored in"
* @return: Error codes if present
*/
ERROR_STATUS SPI_GetStatus(uint8 *u8_Data);

/* for Estimation ECU when using interrupt */
ERROR_STATUS SPI_GetData(uint8* data);
ERROR_STATUS SPI_SetData(uint8 data);

#endif /* SPI_H_ */
