/**
*@file uart.h
*@brief UART usage functions for KL25Z
*@Author Aakash Kumar/ArunSundar
*@date Oct 10 2017

*/
#ifndef UART_H
#define UART_H

#include<stdint.h>
#include<stdlib.h>
#include"MKL25Z4.h"
#include "circularbuffer.h"
#include "led.h"
#include "logger_queue.h"

#define BAUD 38400

#if(BAUD==9600)
#define	osr_val 0x19
#define bdl_val 0x54
#endif


#if(BAUD==115200)
#define	osr_val 0x07
#define bdl_val 0x19
#endif

#if(BAUD==38400)
#define osr_val 0x14
#define bdl_val 0x1A
#endif

extern CB_t * rx_cb,* tx_cb;

void UART_configure(void);
/**
@brief Configures the UART0 to 38400 or 115200 baud when board
is working at 21Mhz. The baud rate can be set using macro in uart.h
@param none
@return  none
*/

void UART_send(uint8_t * data);
/**
@brief Sends a single byte of data to UART
@param *data byte pointer to location of data to be transmitted
@return	None

*/

void UART_send_n(uint8_t * src, size_t length);
/**
@brief Sends a block of data to the UART
@param *src byte pointer to start location of memory block to be transmitted
@param length of memory block to be transmitted
@return  None

*/

uint8_t * UART_receive(uint8_t * dst);
/**
@brief Receives a byte of data from the UART 
@param *dst byte pointer to location where received data is stored
@return  byte pointer to location where received data is stored

*/

uint8_t * UART_receive_n(uint8_t * dst, size_t length);
/**
@brief Receives a block of data from the UART
@param *dst byte pointer to start location of memory block where received data is stored
@param length of memory block received
@return * byte pointer to start of received block of data

*/

void UART_IRQHandler();
/**
@brief Interrupt handler for UART send and receive. Handles send and receive interrupts.
associated flags are cleared in hardware once the interrupt is serviced.

@return none

*/

void UART_TX_Int_Enable(void);
/**
@brief Disables transmit interrupt on the UART 
@param none
@return  none
*/

void UART_TX_Int_Disable(void);
/**
@brief Enables transmit interrupt on the UART 
@param none
@return  none
*/

#endif// End of uart.h
