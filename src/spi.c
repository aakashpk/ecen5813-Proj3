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
	// Enable clock gate to SPIO in System Clock Gating Control Register
	SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;
	//Disabling SPI 
	SPI0_C1 &= SPI0_C1_SPE;	
	// Enable port clock for portA 
	SIM_SCGC5 |= SIM_SCGC5_PORTA(1) ;
	
	// Enable the pins for the selected SPI

	PORTA_PCR13 = PORT_PCR_MUX(0x1);  // for chip enable

	PORTA_PCR14 = PORT_PCR_MUX(0x1); // Enble the spi chipselct using GPIO

	PORTA_PCR15 = PORT_PCR_MUX(0x2); //Enable the SPI_SCK function on PTA15

	PORTA_PCR16 = PORT_PCR_MUX(0x2); // Enable the SPI_MOSI function on PTA16

	PORTA_PCR17 = PORT_PCR_MUX(0x2); // Enable the SPI_MISO function on PTA17

	SPI0_C1 |= SPI0_C1_MSTR_MASK;         //Enable SPI in Master mode

	//SPI0_C1 |= SPI0_C1_SPIE_MASK;         //Enable SPI receiver interrupt

	SPI0_C1 &= SPI0_C1_LSBFE_MASK;	      //Enable SPI to transmit MSB first 

	//SPI0_C1 |= SPI0_C1_SPTIE_MASK;        //Enable SPI transmitter interrupt

	//SPI0_C2 |= SPI0_C1_CPHA;	

	SPI0_BR = (SPI_BR_SPPR(0X02) | SPI_BR_SPR(0X08));              //Configure the baud rate for spi based on the compile time switch
	
	SPI0_C1 |= SPI0_C1_SPE_MASK;	        // Enabling SPI


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
        	while(!(SPI0_S & SPI0_S_SPRF_MASK));  
		//The while loop does not exit until SPRF is 1.
		
      		*byte_read = SPI_D; // Read data from SPI Data register 
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
      while(!(SPI0_S & SPI0_S_SPTEF_MASK));// Wait until SPTEF is 1, ie data buffer is full  
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
		
		for(i=0;j<length;j++)
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

}







