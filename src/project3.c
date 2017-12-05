
/**
*@file project3.c
*@brief project3 implementation is done from this file
*@Author Aakash Kumar/ArunSundar
*@date Nov 20 2017

*/

#include "project3.h"

//#define KL25Z



void project3(void)
{
	#ifdef KL25Z
	// Initializations required only in KL25Z
	UART_configure();
	DMA_Init();
	SysTick_Init(1000000);

	NVIC_ClearPendingIRQ(DMA0_IRQn); // Clear pending DMA interrupts from NVIC ICPR register
	NVIC_EnableIRQ(DMA0_IRQn); // Enable DMA interrupt in NVIC ISER
	NVIC_SetPriority(DMA0_IRQn,2); //Set priority of 2 for TPM interrupt
	__enable_irq(); // Enable global interrupts
	
	#endif
	
	//
	uint8_t * src_addr=malloc(5000),* dst_addr=malloc(5000);
	
	//
	CB_log_t * Logger_q=malloc(sizeof(CB_log_t));
	logdata_t * logData = malloc(sizeof(logdata_t));
	CB_log_init(Logger_q,50);
	
	//
	profiling_memory_functions(src_addr,dst_addr);
	
	
	uint8_t test_data[7] = "testing";
	
	// Use logs like this , just change the logger enum, length and payload if present, else 0 and NULL like in next line 
	log_add(createLog(SYSTEM_INITIALIZED,7,(uint8_t *)test_data),Logger_q);
	log_add(createLog(PROFILING_STARTED,0,NULL),Logger_q);
	
	log_flush(Logger_q);
	LOG_RAW_STRING("\nDONE\n");

}



/*
	struct timeval time_value1;
	gettimeofday(&time_value1,NULL);
	uint8_t test_data[7] = "testing";
	log_add(createLog(logData,SYSTEM_INITIALIZED,time_value.tv_usec,7,(uint8_t *)test_data),Logger_q);
	log_add(createLog(logData,PROFILING_STARTED,time_value.tv_usec,0,NULL),Logger_q);
	

	uint8_t test_data[7] = "testing";
	//LOG_RAW_STRING("\n\rInitialized \r\n");
	//LOG_RAW_STRING("\n\r");

	
	printf("\nBuild time %d : %d : %d :%d \n",buildday,buildhour,buildmin,buildsec);
	

	//Jan 1 1970 00:00 linux epoch

*/




/*	LOG_RAW_STRING("\n\rDest Addr: ");
	LOG_RAW_INT(dst_addr);
	LOG_RAW_STRING("\n\rDest Data\n\r");
	LOG_RAW_DATA(dst_addr,test_transfer_length);

	my_memcpy(src_addr,dst_addr,test_transfer_length);
	my_memmove_dma(src_addr,dst_addr,test_transfer_length);


	LOG_RAW_STRING("\n\rSource Addr: ");
	LOG_RAW_INT(src_addr);
	LOG_RAW_STRING("\n\rSource Data\n\r");
	LOG_RAW_DATA(src_addr,test_transfer_length);
	LOG_RAW_STRING("\n\rDest Addr: ");
	LOG_RAW_INT(dst_addr);
	LOG_RAW_STRING("\n\rDest Data\n\r");
	LOG_RAW_DATA(dst_addr,test_transfer_length);*/

