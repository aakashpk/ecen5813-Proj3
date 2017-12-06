/**
*@file spi.h
*@brief SPI usage functions for KL25Z
*@Author Aakash Kumar/ArunSundar
*@date Nov 16 2017

*/
#ifndef SPI_H
#define SPI_H

#include<stdint.h>
#include<stdlib.h>
#include"MKL25Z4.h"

//#define BAUD 38400

//#if(BAUD==9600)

//#define spibaud = 0x22
//#endif


//#if(BAUD==115200)
//#define	spibaud = 0X41
//#endif

//#if(BAUD==38400)
//#define spibaud() (0x12)

//#endif


void SPI_init();
/**
@brief Configures the SPI0 to 38400 or 115200 baud when board
is working at 21Mhz. The baud rate can be set using macro in spi.h
@param none
@return  none
*/



void SPI_read_byte(uint8_t* byte_read);
/**
@brief Receives a byte of data from the SPI 
@param *byte_read byte pointer to location where received data is stored
@return  none
*/



 

void SPI_write_byte(uint8_t* byte_write);
/**
@brief Sends a single byte of data to SPI
@param *byte_write byte pointer to location of data to be transmitted
@return	None

*/





void SPI_send_packet(uint8_t * byte_tosend,size_t length);
/**
@brief Sends a block of data to the SPI
@param *byte_tosend byte pointer to start location of memory block to be transmitted
@param length of memory block to be transmitted
@return  None

*/



void SPI_flush();

/**
@brief Blocks untill spi transmit buffer has completed transmitted
@param  None 
@return	None

*/



#endif// End of spi.h


