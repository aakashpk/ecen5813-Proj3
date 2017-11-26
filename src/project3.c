
/**
*@file project3.c
*@brief project3 implementation is done from this file
*@Author Aakash Kumar/ArunSundar
*@date Nov 20 2017

*/

#include "project3.h"
#include <sys/time.h>

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

void print_log(logdata_type *logData)
{
	LOG_RAW_STRING(logId_texts[logData->logID]);
	LOG_RAW_STRING(" at time ");
	LOG_RAW_INT(logData->timestamp);
	LOG_RAW_STRING(" with payload ");
	LOG_RAW_DATA(logData->payload,logData->logLength);
}


logdata_type * addLog(logdata_type *logData , logid_type logID, uint32_t timestamp , size_t logLength, void* payload, uint8_t checksum)
{
	logData->logID=logID;
	logData->timestamp=timestamp;
	logData->logLength=logLength;
	logData->payload=payload;
	logData->checksum=checksum;
	return logData;
}

void project3(void)
{
	uint8_t test_data[6] = "abcdef";
	LOG_RAW_STRING("\n\rInitialized \r\n");
	LOG_RAW_STRING("\n\r");

	logdata_type * logData=malloc(sizeof(logdata_type)),* logData1=malloc(sizeof(logdata_type));

	/*
	logData->logID = SYSTEM_INITIALIZED;
	logData->timestamp=1234567;
	logData->logLength=6;
	logData->payload=(uint8_t *)test_data;
	logData->checksum=0;
	*/
	addLog(logData1,SYSTEM_INITIALIZED,123456789,6,(uint8_t *)test_data,0);

	*logData = *logData1;

	print_log(logData);

	printf("\n %d ",gettimeofday());

	//printf("\n%d\n",sizeof(char *) );


}


#endif
