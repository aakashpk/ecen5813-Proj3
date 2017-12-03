
/**
*@file project3.c
*@brief project3 implementation is done from this file
*@Author Aakash Kumar/ArunSundar
*@date Nov 20 2017

*/

#include "project3.h"

#ifdef KL25Z

#define test_transfer_length 32


void project3_kl25z(void)
{
	UART_configure();
	DMA_Init();
	RGB_LED_Init();

	NVIC_ClearPendingIRQ(DMA0_IRQn); // Clear pending DMA interrupts from NVIC ICPR register
	NVIC_EnableIRQ(DMA0_IRQn); // Enable DMA interrupt in NVIC ISER
	NVIC_SetPriority(DMA0_IRQn,2); //Set priority of 2 for TPM interrupt
	__enable_irq(); // Enable global interrupts

	int k=0;

	LOG_RAW_STRING("\n\rInitialized \r\n");
	LOG_RAW_STRING("\n\r");

	uint8_t * src_addr=malloc(test_transfer_length),* dst_addr=malloc(test_transfer_length);

	my_memset_dma(src_addr,test_transfer_length,90);
	my_memset_dma(dst_addr,test_transfer_length,65);

	while(k<10000000) {k++;}

	LOG_RAW_STRING("\n\rDest Addr: ");
	LOG_RAW_INT(dst_addr);
	LOG_RAW_STRING("\n\rDest Data\n\r");
	LOG_RAW_DATA(dst_addr,test_transfer_length);

	my_memmove_dma(src_addr,dst_addr,test_transfer_length);
	k=0;
	while(k<10000000) {k++;}

	LOG_RAW_STRING("\n\rSource Addr: ");
	LOG_RAW_INT(src_addr);
	LOG_RAW_STRING("\n\rSource Data\n\r");
	LOG_RAW_DATA(src_addr,test_transfer_length);
	LOG_RAW_STRING("\n\rDest Addr: ");
	LOG_RAW_INT(dst_addr);
	LOG_RAW_STRING("\n\rDest Data\n\r");
	LOG_RAW_DATA(dst_addr,test_transfer_length);

}

#else



void project3(void)
{
	uint8_t test_data[7] = "testing";
	//LOG_RAW_STRING("\n\rInitialized \r\n");
	//LOG_RAW_STRING("\n\r");

	//void * logData=malloc(2*sizeof(logdata_t));
	CB_log_t * Logger_q=malloc(sizeof(CB_log_t));
	logdata_t * logData = malloc(sizeof(logdata_t));
	struct timeval * time_value=malloc(sizeof(struct timeval));
	/*
	logData->logID = SYSTEM_INITIALIZED;
	logData->timestamp=1234567;
	logData->logLength=6;
	logData->payload=(uint8_t *)test_data;
	logData->checksum=0;
	*/
	
	printf("\nBuild time %d : %d : %d :%d \n",buildday,buildhour,buildmin,buildsec);
	
	CB_log_init(Logger_q,10);
	
	gettimeofday(time_value,NULL);
	
	log_add(createLog(logData,SYSTEM_INITIALIZED,time_value->tv_usec,7,(uint8_t *)test_data),Logger_q);
	
	gettimeofday(time_value,NULL);
	log_add(createLog(logData,PROFILING_STARTED,time_value->tv_usec,0,NULL),Logger_q);
	
	log_flush(Logger_q);
	
	
	//Jan 1 1970 00:00 linux epoch
	//printf("%p ",logData);
	//printf("%d ",sizeof(logdata_t));
	//*(logdata_t *)logData = *logData1;
	//printf("%p ",((logdata_t *)logData+1));
	
	
	
	

	printf("\n -DONE- \n");
	

	//printf("\n%d\n",sizeof(char *) );


}


#endif
