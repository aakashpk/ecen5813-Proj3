/**
*@file dma.c
*@brief DMA and memory functions using DMA
*@Author Aakash Kumar
*@date Nov 22 2017
*/

#include "dma.h"
#include "led.h"
#include "logger_queue.h"



uint8_t two_byte_buffer[2],four_byte_buffer[4];
size_t curmovelength=0,lastmovelength=0,checkval;

uint8_t mem_buffer[5000];


void DMA_Init(){
	// Enable clock gate for DMAMUX and DMA
	SIM_SCGC6|=SIM_SCGC6_DMAMUX_MASK;
	SIM_SCGC7|=SIM_SCGC7_DMA_MASK;

	NVIC_ClearPendingIRQ(DMA0_IRQn); // Clear pending DMA interrupts from NVIC ICPR register
	NVIC_EnableIRQ(DMA0_IRQn); // Enable DMA interrupt in NVIC ISER

	//Enable DMA Interrupts
	DMA_DCR0|=DMA_DCR_EINT_MASK;

}

uint8_t * my_memset_dma(uint8_t * src, size_t length, uint8_t value){

	if(src!=NULL && length>0) // Check for NULL pointer and valid length
	{
		// Destination increment, keep source at same value
		DMA_DCR0|=DMA_DCR_DINC_MASK;

		checkval=length/4;
		curmovelength=checkval*4;
		//Set with 4 byte transfer for as much length possible
		if(curmovelength>0)
		{
			my_memset_dma_size(src,curmovelength,value,4);
		}
		lastmovelength=curmovelength;
		curmovelength=(length-lastmovelength);
		//Set remaining as 1 byte transfer
		if(curmovelength>0)
		{
			my_memset_dma_size((src+lastmovelength),curmovelength,value,1);
		}

		return src;
	}
		else return 0; // return 0 in case of NULL pointer or invalid length
	//DMA_DCR0|=DMA_DCR_EINT_MASK;
}


uint8_t * my_memset_dma_size(uint8_t * src, size_t length, uint8_t value,uint8_t size){

	if(src!=NULL && length>0) // Check for NULL pointer and valid length
	{
		if(size==4)
		{
			//Set Source size and destination size to 4 byte
			DMA_DCR0|=DMA_DCR_SSIZE(0);
			DMA_DCR0|=DMA_DCR_DSIZE(0);

			for(int l=0;l<4;l++)
			{
				four_byte_buffer[l]=value;
			}

			DMA_SAR0=four_byte_buffer; //DMA Source register to value
		}
		else if(size==2)
		{
			//Set Source size and destination size to 2 byte
			DMA_DCR0|=DMA_DCR_SSIZE(2);
			DMA_DCR0|=DMA_DCR_DSIZE(2);

			for(int l=0;l<2;l++)
			{
				two_byte_buffer[l]=value;
			}

			DMA_SAR0=two_byte_buffer; //DMA Source register to value
		}
		else // Use 1 byte transfer as default, even in case of errored transfer size
		{
			//Set Source size and destination size to 1 byte
			DMA_DCR0|=DMA_DCR_SSIZE(1);
			DMA_DCR0|=DMA_DCR_DSIZE(1);

			DMA_SAR0=&value; //DMA Source register to value
		}


		DMA_DAR0=src; //DMA destination register to address to be set
		DMA_DSR_BCR0=DMA_DSR_BCR_BCR(length); //length of data to be transferred to BCR

		DMA_DCR0|=DMA_DCR_START_MASK; // Start DMA transfer
		//DMA_DSR0 |= DMA_DSR_BCR_DONE_MASK; // Reset flags in DSR by writing one to DONE bit


		return src;
	}
		else return 0; // return 0 in case of NULL pointer or invalid length


}

uint8_t * my_memmove_dma(uint8_t * src, uint8_t * dst, size_t length){

	if(src!=NULL && dst!=NULL && length>0) // Check for NULL pointer and valid length
		{
			// Source increment and destination increment
			DMA_DCR0|=(DMA_DCR_SINC_MASK|DMA_DCR_DINC_MASK);

			checkval=length/4;
			curmovelength=checkval*4;
			//Transfer with 4 byte transfer for as much length possible
			if(curmovelength>0)
			{
				my_memmove_dma_size(src,dst,curmovelength,4);
			}
			lastmovelength=curmovelength;
			curmovelength=(length-lastmovelength);
			//Transfer remaining as 8 bit transfer
			if(curmovelength>0)
			{
				my_memmove_dma_size((src+lastmovelength),(dst+lastmovelength),curmovelength,1);
			}

			return src;
		}
	else return 0;  // return 0 in case of NULL pointer or invalid length
}


uint8_t * my_memmove_dma_size(uint8_t * src, uint8_t * dst, size_t length,uint8_t transfer_size)
{
	if(src!=NULL && dst!=NULL && length>0) // Check for NULL pointer and valid length
	{
			if(transfer_size==4)
			{
				DMA_DCR0|=DMA_DCR_SSIZE(0);
				DMA_DCR0|=DMA_DCR_DSIZE(0);
			}
			else if(transfer_size==2)
			{
				DMA_DCR0|=DMA_DCR_SSIZE(2);
				DMA_DCR0|=DMA_DCR_DSIZE(2);
			}
			else if(transfer_size==1)
			{
				DMA_DCR0|=DMA_DCR_SSIZE(1);
				DMA_DCR0|=DMA_DCR_DSIZE(1);
			}
			else // Use 1 byte transfer as default, even in case of errored transfer size
			{
				DMA_DCR0|=DMA_DCR_SSIZE(1);
				DMA_DCR0|=DMA_DCR_DSIZE(1);
				LOG_ITEM(createLog(WARNING,23,"WRONG DMA TRANSFER SIZE"),Logger_q);
			}

		//DMA_DSR0 |= DMA_DSR_BCR_DONE_MASK; // Reset flags in DSR by writing one to DONE bit

		//Move data into a temporary buffer to prevent overwrite in case of address overlap
		DMA_SAR0=src; //DMA Source register to src value
		DMA_DAR0=mem_buffer; //DMA destination register to dst value
		DMA_DSR_BCR0=DMA_DSR_BCR_BCR(length); //length of data to be transferred to BCR
		DMA_DCR0|=DMA_DCR_START_MASK; // Start DMA transfer

		// Wait for first DMA transfer to finish before starting second to prevent corruption of data
		//while(!(DMA_DSR_BCR0 & DMA_DSR_BCR_DONE_MASK)) ;

		// Transfer data from buffer to destination address
		DMA_SAR0=mem_buffer; //DMA Source register to src value
		DMA_DAR0=dst; //DMA destination register to dst value
		DMA_DSR_BCR0=DMA_DSR_BCR_BCR(length); //length of data to be transferred to BCR

		DMA_DCR0|=DMA_DCR_START_MASK; // Start DMA transfer

		//while(!(DMA_DSR_BCR0 & DMA_DSR_BCR_DONE_MASK)) ;// wait for transfer to finish

		return src;
	}
	else
	{
		return 0;
	}


}

void DMA0_IRQHandler(){

	DMA_DCR0&=(~DMA_DCR_EINT_MASK);
	if(DMA_DSR_BCR0 & DMA_DSR_BCR_DONE_MASK) DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;
	LOG_ITEM(createLog(INFO,8,"DMA INTR"),Logger_q);
	DMA_DCR0|=DMA_DCR_EINT_MASK;
	//BLUEON;
	//LOG_RAW_STRING("\n\rISR reached ");

}

