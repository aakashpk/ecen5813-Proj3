/**
*@file uart.c
*@brief UART0 usage functions for KL25Z
*@Author Aakash Kumar/ArunSundar
*@date Oct 16 2017

*/

#include "uart.h"

// Uses UART0 on the FRDM Board


/**
@brief Configures the UART0 to 38400 or 115200 baud when board
is working at 21Mhz. The baud rate can be set using macro in uart.h
@param none
@return  none
*/
void UART_configure(void)
{
	SIM_SCGC4|=	SIM_SCGC4_UART0_MASK; // Enable clock gate to UARTO in System Clock Gating Control Register

	UART0_C2 &= ~(UART0_C2_TE_MASK | UART0_C2_RE_MASK); // Ensure UART0 is disabled before changing registers

    SIM_SCGC5 |= SIM_SCGC5_PORTA(1) ;// Enable port clock for portA

    // Enable the pins for the selected UART
	PORTA_PCR1 = PORT_PCR_MUX(0x2); // Enable the UART_RXD function on PTA1

	PORTA_PCR2 = PORT_PCR_MUX(0x2); //Enable the UART_TXD function on PTA2

	SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1); // select the PLLFLLCLK as UART0 clock source

    SIM_SOPT2 &= ~SIM_SOPT2_PLLFLLSEL_MASK; // clear PLLFLLSEL to select the FLL for this clock source

    UART0_C4=(osr_val &UART0_C4_OSR_MASK); // set OSR as defined in UART.h based on baud compile time switch

    UART0_BDL=(bdl_val & UART_BDL_SBR_MASK);// set bdl as defined in UART.h based on baud compile time switch
	
    NVIC_ClearPendingIRQ(UART0_IRQn); // Clear pending UART interrupts from NVIC ICPR register
    NVIC_EnableIRQ(UART0_IRQn); // Enable UART0 interrupt in NVIC ISER
    UART0_C2 |= UART_C2_RIE_MASK;// Enable UART0 receive interrupt

    UART0_C2 |= (UART0_C2_TE_MASK| UART0_C2_RE_MASK );// Enable receiver and transmitter
}

/**
@brief Disables transmit interrupt on the UART 
@param none
@return  none
*/
void UART_TX_Int_Enable(void)
{
	UART0_C2 |= UART_C2_TIE_MASK;// Enable UART0 transmit interrupt
}

/**
@brief Enables transmit interrupt on the UART 
@param none
@return  none
*/
void UART_TX_Int_Disable(void)
{
	UART0_C2 &= ~UART_C2_TIE_MASK;// Disable UART0 transmit interrupt
}

/**
@brief Sends a single byte of data to UART
@param *data byte pointer to location of data to be transmitted
@return	None

*/
void UART_send(uint8_t * data)
{
	if(data !=NULL) 
	{
      while(!(UART0_S1 & UART0_S1_TDRE_MASK));// Wait until TDRE is 1, ie data buffer is empty  
		//The while loop does not exit until TDRE is 1.
		
      UART0_D = *data; // Write data to UART Data register to transmit the data once buffer is empty
	}

}

/**
@brief Sends a block of data to the UART
@param *src byte pointer to start location of memory block to be transmitted
@param length of memory block to be transmitted
@return  None

*/
void UART_send_n(uint8_t * src, size_t length)
{
	int j=0;
	if(src!=NULL && length >0)
	{
		
		for(j=0;j<length;j++)
		{
			UART_send((src+j)); // Send one character at a time from the block of data
			// The UART_Send function will take care of not writing when the buffer is not empty.
		}

	}
}

/**
@brief Receives a byte of data from the UART 
@param *dst byte pointer to location where received data is stored
@return  None

*/
uint8_t * UART_receive(uint8_t * dst)
{
	if(dst!=NULL)
	{
		
		while (!(UART0_S1 & UART0_S1_RDRF_MASK)); // Wait until RDRF flag is set, indicating data in buffer.
		// While loop does not exit until RDRF is 1
	  
		*dst = UART0_D; // Read data from buffer when available
		return dst; // Return pointer to received data
	}
	else return 0;
}

/**
@brief Receives a block of data from the UART
@param *dst byte pointer to start location of memory block where received data is stored
@param length of memory block received
@return * byte pointer to start of received block of data

*/
uint8_t * UART_receive_n(uint8_t * dst, size_t length)
{
	int j=0;

	if(dst!=NULL && length >0)
	{
		for(j=0;j<length;j++)
		{
			UART_receive((dst+j));
		}
		return dst;
	}
	else return 0;
}

/**
@brief Interrupt handler for UART send and receive. Handles send and receive interrupts.
associated flags are cleared in hardware once the interrupt is serviced.

@return none

*/
void UART0_IRQHandler()
{
	uint8_t b;

	if (UART0_S1&UART_S1_RDRF_MASK) // When data is received, add it into the circular buffer
	  {
		b=(UART0_D); //read UART0 data register
		CB_buffer_add_item(rx_cb,b); // Add read data to receive circular buffer
		LOG_ITEM(createLog(DATA_RECEIVED,1,((rx_cb->head)-1)),Logger_q); // Log received character
		if(b==27u)
		{
			if(log_enable) log_enable=0;
			else log_enable=1;
		}
		// Interrupt is cleared when data read from the register
		UART_send(&b); // echo received character to terminal
	  }
	
	/*
	if ((UART0_S1&UART_S1_TDRE_MASK)||(UART0_S1&UART_S1_TC_MASK))
	{
		while(CB_is_empty(tx_cb)!=0) // keep removing and transmitting till the buffer is empty
		{
			CB_buffer_remove_item(tx_cb,&b); // remove from buffer
			UART_send(&b); // transmit data removed from buffer.
		}


	}*/

}
