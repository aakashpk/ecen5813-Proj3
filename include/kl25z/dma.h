/**
*@file dma.c
*@brief DMA and memory functions using DMA
*@Author Aakash Kumar
*@date Nov 22 2017
*/

#ifndef DMA_H
#define DMA_H

#include "MKL25Z4.h"
#include <stdlib.h>


void DMA_Init(void);

uint8_t * my_memmove_dma(uint8_t * src, uint8_t * dst, size_t length);


//@param transfer_size DMA transfer size can be 1,2 or 4 bytes for 8,16 or 32 bit transfers  , size_t transfer_size
uint8_t * my_memset_dma(uint8_t * src, size_t length, uint8_t value);

void DMA0_IRQHandler();

#endif // end of dma.h
