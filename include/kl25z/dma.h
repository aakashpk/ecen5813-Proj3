/**
*@file dma.h
*@brief DMA and memory functions using DMA
*@Author Aakash Kumar
*@date Nov 22 2017
*/

#ifndef DMA_H
#define DMA_H

#include "MKL25Z4.h"
#include <stdlib.h>

extern uint8_t mem_buffer[5000];


/**
@brief Configures the DMA for performing the memory operations
@param none
@return  none
*/

void DMA_Init(void);


/**
@brief Performs memset for using DMA for KL25Z
@param uint8_t* src pointer the memory to be set
@param size_t length of the memory
@param uint8_t value value to set the memory
@return  returns the  pointer to the memory
*/

uint8_t * my_memmove_dma(uint8_t * src, uint8_t * dst, size_t length);


//@param transfer_size DMA transfer size can be 1,2 or 4 bytes for 8,16 or 32 bit transfers  , size_t transfer_size


/**
@brief Performs memset for using DMA for different byte sizes for KL25Z
@param uint8_t* src pointer the memory to be set
@param size_t length of the memory
@param uint8_t value value to set the memory
@param uint8_t size size to be moved in a single operation 
@return  returns the  pointer to the memory
*/


uint8_t * my_memset_dma(uint8_t * src, size_t length, uint8_t value);


/**
@brief Performs memmove for using DMA for KL25Z
@param uint8_t* src pointer the memory to be set
@param size_t length of the memory
@param uint8_t* dst pointer to the destination
@return  returns the  pointer to the memory
*/

uint8_t * my_memmove_dma_size(uint8_t * src, uint8_t * dst, size_t length,uint8_t transfer_size);




/**
@brief Performs memmove for using DMA for different byte sizes for KL25Z
@param uint8_t* src pointer the memory to be set
@param size_t length of the memory
@param uint8_t* dst pinter to the destination 
@param uint8_t transfer_size size to be moved in a single operation 
@return  returns the  pointer to the memory
*/

uint8_t * my_memset_dma_size(uint8_t * src, size_t length, uint8_t value,uint8_t size);


/** 
@brief IRQ handler for DMA interrupt
@param none
@return none
*/

void DMA0_IRQHandler();

#endif // end of dma.h
