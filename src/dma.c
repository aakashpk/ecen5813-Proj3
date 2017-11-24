/**
*@file dma.c
*@brief DMA and memory functions using DMA
*@Author Aakash Kumar
*@date Nov 22 2017
*/

#include "dma.h"
#include "led.h"

void DMA_Init(){
	// Enable clock gate for DMAMUX and DMA
	SIM_SCGC6|=SIM_SCGC6_DMAMUX_MASK;
	SIM_SCGC7|=SIM_SCGC7_DMA_MASK;

	//Set Source size and destination size to 8bit
	DMA_DCR0|=DMA_DCR_SSIZE(1);
	DMA_DCR0|=DMA_DCR_DSIZE(1);

	//Enable DMA Interrupts
	//DMA_DCR0|=DMA_DCR_EINT_MASK;

	DMA_DCR0&=(~DMA_DCR_EINT_MASK);// Disable Interrupt
}

uint8_t * my_memset_dma(uint8_t * src, size_t length, uint8_t value){

	if(src!=NULL && length>0) // Check for NULL pointer and valid length
	{
		// Destination increment, keep source at same value
		DMA_DCR0|=DMA_DCR_DINC_MASK;


		uint8_t *temp_value=malloc(1);
		*temp_value=value;

		//uint16_t *temp_value=malloc(2);
		//*temp_value=(value|value<<8);

		//uint32_t *temp_value=malloc(4);
		//*temp_value=(value|value<<8|value<<16|value<<24);

		DMA_SAR0=temp_value; //DMA Source register to src value
		DMA_DAR0=src; //DMA destination register to dst value
		DMA_DSR_BCR0=DMA_DSR_BCR_BCR(length); //length of data to be transferred to BCR

		DMA_DCR0|=DMA_DCR_START_MASK; // Start DMA transfer
		//DMA_DSR0 |= DMA_DSR_BCR_DONE_MASK; // Reset flags in DSR by writing one to DONE bit

		free(temp_value);

		return src;
	}
		else return 0; // return 0 in case of NULL pointer or invalid length
	//DMA_DCR0|=DMA_DCR_EINT_MASK;
}

uint8_t * my_memmove_dma(uint8_t * src, uint8_t * dst, size_t length){

	if(src!=NULL && dst!=NULL && length>0) // Check for NULL pointer and valid length
		{
			// Source increment and destination increment
			DMA_DCR0|=(DMA_DCR_SINC_MASK|DMA_DCR_DINC_MASK);

			DMA_SAR0=src; //DMA Source register to src value
			DMA_DAR0=dst; //DMA destination register to dst value
			DMA_DSR_BCR0=DMA_DSR_BCR_BCR(length); //length of data to be transferred to BCR

			DMA_DCR0|=DMA_DCR_START_MASK; // Start DMA transfer
			DMA_DSR0 |= DMA_DSR_BCR_DONE_MASK; // Reset flags in DSR by writing one to DONE bit
			//DMA_DCR0|=DMA_DCR_EINT_MASK;

			return src;
		}
	else return 0;  // return 0 in case of NULL pointer or invalid length
}

void DMA0_IRQHandler(){

	DMA_DCR0&=(~DMA_DCR_EINT_MASK);
	if(DMA_DSR0 & DMA_DSR_BCR_DONE_MASK) DMA_DSR0 |= DMA_DSR_BCR_DONE_MASK;
	BLUEON;
	//LOG_RAW_STRING("\n\rISR reached ");

}
