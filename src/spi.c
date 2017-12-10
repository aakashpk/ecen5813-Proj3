/**
*@file spi.h
*@brief SPI usage functions for KL25Z
*@Author Aakash Kumar/ArunSundar
*@date Nov 16 2017

*/


#include"spi.h"

// Uses UART0 on the FRDM Board
 
/**
@brief Configures the SPI0 to 38400 or 115200 baud when board
is working at 21Mhz. The baud rate can be set using macro in spi.h
@param none
@return  none
*/

void SPI_init()
{	

	  SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK; // Turn on clock to Port D module
	  SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK; // Turn on clock to SPI0 module
	// Enable the pins for the selected SPI

//	PORTC_PCR7 = PORT_PCR_MUX(0x1);  // for chip enable

	PORTD_PCR0 = PORT_PCR_MUX(0x1); // EnAble the spi chip select using GPIO , PD0

	PORTD_PCR1 = PORT_PCR_MUX(0x2); //Enable the SPI_SCK function on PTA15

	PORTD_PCR2 = PORT_PCR_MUX(0x2); // Enable the SPI_MOSI function on PTA16

	PORTD_PCR3 = PORT_PCR_MUX(0x2); // Enable the SPI_MISO function on PTA17

	PORTD_PCR5 = PORT_PCR_MUX(0x1);

	SPI0_C1=0X50;
	SPI0_C2=0X10;
	//SPI0_BR = (SPI_BR_SPPR(0X02) | SPI_BR_SPR(0X08));              //Configure the baud rate for spi based on the compile time switch
	SPI0_BR = 0X00;
	//SPI0_C1 |= SPI_C1_SPE_MASK;	        // Enabling SPI


}


/**
@brief Receives a byte of data from the SPI 
@param *byte_read byte pointer to location where received data is stored
@return  none
*/


void SPI_read_byte(uint8_t* byte_read)
{
	if(byte_read !=NULL)
	{	// Wait until SPRF is 1, ie data buffer is empty
        	while(!(SPI0_S & SPI_S_SPRF_MASK));
		//The while loop does not exit until SPRF is 1.
		*byte_read = SPI0_D; // Read data from SPI Data register
	}



}


/**
@brief Sends a single byte of data to SPI
@param *byte_write byte pointer to location of data to be transmitted
@return	None

*/



void SPI_write_byte(uint8_t* byte_write)
{

	if(byte_write !=NULL) 
	{
      while(!(SPI0_S & SPI_S_SPTEF_MASK));// Wait until SPTEF is 1, ie data buffer is full
		//The while loop does not exit until SPTEF is 1.
		
      SPI0_D = *byte_write; // Write data to SPI Data register to transmit the data once buffer is empty
	}

}



/**
@brief Sends a block of data to the SPI
@param *byte_tosend byte pointer to start location of memory block to be transmitted
@param length of memory block to be transmitted
@return  None

*/

void SPI_send_packet(uint8_t * byte_tosend,size_t length)
{
	int i=0;
	if(byte_tosend!=NULL && length >0)
	{
		
		for(i=0;i<length;i++)
		{
			SPI_write_byte((byte_tosend+i)); // Send one character at a time from the block of data
			// The SPI_write_byte function will take care of not writing when the buffer is not empty.
		}

	}

}

/**
@brief Blocks untill spi transmit buffer has completed transmitting
@param  None 
@return	None

*/


void SPI_flush()
{

while(SPI0_S & 0X20 != (0X20));
SPI_init();
}

