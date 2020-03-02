/*
 * SPI.c
 *
 * Created: 12/28/2019 6:38:14 PM
 *  Author: Ahmed
 */ 

#include "DIO.h"
#include "SPI.h"
#include "registers.h"
#include "interrupt.h"


/**
* @brief: Initialize SPI module
* @param:
* Input : SPI_Cfg_s* "Pointer to Struct of SPI Configration
* Output: None
* @return: Error codes if present
*/


//SPSR-Register//
#define SPIF	BIT7
#define WCOL	BIT6
#define SP12X	BIT0

//SPCR register//
#define SPIE	BIT7
#define SPE		BIT6
#define DORD	BIT5
#define MSTR	BIT4
#define CPOL	BIT3
#define CPHA	BIT2
#define SPR1	BIT1
#define SPR0	BIT0

//-------------------------------//

#define SS		    BIT4 
#define MOSI		BIT5
#define MISO		BIT6
#define SCLK	    BIT7
#define SPI_PORT	GPIOB

static void (*gp_SPI_CBK)(void)=NULL;

ERROR_STATUS SPI_Init(SPI_Cfg_s* pstr_SPI_Confg)
{
	ERROR_STATUS ErrorStatus = E_OK;
	gp_SPI_CBK=pstr_SPI_Confg->CBK_Func;
	
	DIO_Cfg_s Spi_Dio_s1;
	Spi_Dio_s1.dir=INPUT;
	Spi_Dio_s1.pins=MISO;
	Spi_Dio_s1.GPIO=SPI_PORT;
	DIO_init(&Spi_Dio_s1);
	
	DIO_Cfg_s Spi_Dio_s2;
	Spi_Dio_s2.dir=OUTPUT;
	Spi_Dio_s2.pins=MOSI|SS|SCLK;
	Spi_Dio_s2.GPIO=SPI_PORT;
	DIO_init(&Spi_Dio_s2);
	
//******************************************************************//		
	switch(pstr_SPI_Confg->u8_Prescaler)
	{
		case SPI_PRESCALER_2:
		SPSR|=(SP12X) ;
		SPCR&=~(SPR0);
		SPCR&=~(SPR1);
		break;
		
		case SPI_PRESCALER_4:
		SPSR&=~(SP12X);
		SPCR&=~(SPR0);
		SPCR&=~(SPR1);		
		break;	
		
		case SPI_PRESCALER_8:
		SPSR|=(SP12X);
		SPCR|=(SPR0);		
		SPCR&=~(SPR1);
		break;
		
		case SPI_PRESCALER_16:
		SPSR&=~(SP12X);
		SPCR|=(SPR0);
		SPCR&=~(SPR1);
		break;
		
		case SPI_PRESCALER_32:
		SPSR|=(SP12X);
		SPCR&=~(SPR0);
		SPCR|=(SPR1);
		break;
		
		case SPI_PRESCALER_64:
		SPSR&=~(SP12X);
		SPCR&=~(SPR0);
		SPCR|=(SPR1);
		break;	
		
		case SPI_PRESCALER_128:
		SPSR&=~(SP12X);
		SPCR|=(SPR0);
		SPCR|=(SPR1);
		break;					
	}
	
	switch(pstr_SPI_Confg->u8_SPIMode)
	{
		case MASTER:
		SPCR |=(MSTR);
		DIO_Cfg_s Spi_Dio_Master;
		Spi_Dio_Master.dir=INPUT;
		Spi_Dio_Master.pins=BIT6;
		Spi_Dio_Master.GPIO=GPIOB;
		DIO_init(&Spi_Dio_Master);
		
		DIO_Cfg_s Spi_Dio_Slave;
		Spi_Dio_Slave.dir=OUTPUT;
		Spi_Dio_Slave.pins=BIT5|BIT4|BIT7;
		Spi_Dio_Slave.GPIO=GPIOB;
		DIO_init(&Spi_Dio_Slave);	
		break;
		
		case SLAVE:
		SPCR&=~(MSTR);
		DIO_Cfg_s Spi_Dio_s1;
		Spi_Dio_s1.dir=OUTPUT;
		Spi_Dio_s1.pins=BIT6;
		Spi_Dio_s1.GPIO=GPIOB;
		DIO_init(&Spi_Dio_s1);
		
		DIO_Cfg_s Spi_Dio_s2;
		Spi_Dio_s2.dir=INPUT;
		Spi_Dio_s2.pins=BIT5|BIT4|BIT7;
		Spi_Dio_s2.GPIO=GPIOB;
		DIO_init(&Spi_Dio_s2);		
		break;
	}
	
	switch(pstr_SPI_Confg->u8_DataOrder)
	{
		case MSB:
		SPCR&=~(DORD);
		break;
		
		case LSB:
		SPCR|=(DORD);
		break;
	}
	
	switch(pstr_SPI_Confg->u8_InterruptMode)
	{
		case POLLING:
		SPCR&=~(SPIE);
		break;
		
		case INTERRUPT:
		SPCR|=(SPIE);
		break;
	}
	
	switch (pstr_SPI_Confg->u8_DataMode)
	{
		case MODE_0:
		SPCR&=~(CPHA);
		SPCR&=~(CPOL);				
		break;
		
		case MODE_1:
		SPCR|=(CPHA);
		SPCR&=~(CPOL);		
		break;

		case MODE_2:
		SPCR&=~(CPHA);
		SPCR|=(CPOL);		
		break;
		
		case MODE_3:
		SPCR|=(CPHA);
		SPCR|=(CPOL);		
		break;				
	}
	SPCR |=(SPE);
	return ErrorStatus;
}

ERROR_STATUS SPI_GetData(uint8* data)
{
	ERROR_STATUS ErrorStatus = E_OK;
	*data = SPDR;
	return ErrorStatus;
}

ERROR_STATUS SPI_SetData(uint8 data)
{
	ERROR_STATUS ErrorStatus = E_OK;
	SPDR = data;
	return ErrorStatus;
}

/**
* @brief: Transmit one byte over SPI and receive the byte from the slave
* @param:
* Input/ : u8_Data "Byte to be sent and save the received byte"
* @return: Error codes if present
*/
ERROR_STATUS SPI_MasterTransmission(uint8 *u8_Data)
{
	ERROR_STATUS Error_Status = E_OK;
	DIO_Write(GPIOB,SS,LOW);
	SPDR= *u8_Data;
	while(((SPSR&SPIF)/SPIF)==0);
	*u8_Data=SPDR;
	DIO_Write(GPIOB,SS,HIGH);
	return Error_Status;
}

/**
* @brief: Transmit one byte over SPI and receive the byte from the slave
* @param:
* Input/ : u8_Data "Byte to be sent and save the received byte"
* @return: Error codes if present
*/
ERROR_STATUS SPI_SlaveTransmission(uint8 *ptru8_Data)
{
	ERROR_STATUS Error_Status = E_OK;
	SPDR = *ptru8_Data;
	while(((SPSR&SPIF)/SPIF)==0);
	*ptru8_Data=SPDR;
	return Error_Status;
}

/**
* @brief: Get status of SPI interrupt flag
* @param:
* Input : None
* Output: *u8_Data "points to where flag value is going to be stored in"
* @return: Error codes if present
*/
ERROR_STATUS SPI_GetStatus(uint8 *u8_Data)
{
	ERROR_STATUS Error_Status = E_OK;
	*u8_Data |=(SPSR&SPIF)/SPIF;
	return Error_Status;
}



ERROR_STATUS SPI_Exchange(uint8 *ptru8_Data)
{
	ERROR_STATUS Error_Status = E_OK;
		SPDR=*ptru8_Data;
		while(((SPSR&SPIF)/SPIF));
		*ptru8_Data = SPDR;
	
	return Error_Status;
	
}

ISR(SPI_STC_vect)
{
	gp_SPI_CBK();
}

/* for Estimation ECU when using interrupt */
ERROR_STATUS SPI_GetData(uint8* data);
ERROR_STATUS SPI_SetData(uint8 data);