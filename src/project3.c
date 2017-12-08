
/**
*@file project3.c
*@brief project3 implementation is done from this file
*@Author Aakash Kumar/ArunSundar
*@date Nov 20 2017

*/

#include "project3.h"
#include "project2.h"

#define KL25Z

#define LOGGERSIZE 5


void project3(void)
{
	Logger_q=malloc(sizeof(CB_log_t));
	logdata_t * logData = malloc(sizeof(logdata_t));

	//Payload circular buffer----

	if(log_enable)
	{

		#ifdef KL25Z
		RTC_Init();
		#endif

		if(CB_log_init(Logger_q,LOGGERSIZE) == success) LOG_ITEM(createLog(LOGGER_INITIALZED,0,NULL),Logger_q);
	}


	#ifdef KL25Z
	// Initializations required only in KL25Z
	UART_configure();
	DMA_Init();
	SysTick_Init(1000000);

	NVIC_SetPriority(RTC_Seconds_IRQn,0);
	NVIC_SetPriority(DMA0_IRQn,2); //Set priority of 1 for DMA interrupt
	NVIC_SetPriority(UART0_IRQn,4); //Set priority of 2 for UART0 interrupt
	__enable_irq(); // Enable global interrupts
	
	 rx_cb=malloc(sizeof(CB_t));
	 CB_init(rx_cb,30);

	#endif

	LOG_ITEM(createLog(SYSTEM_INITIALIZED,0,NULL),Logger_q);

	//malloc 2 buffers for setting up profiling transfers
	uint8_t * src_addr=malloc(5000),* dst_addr=malloc(5000);

	//Run profiling analysis on the memory functions
	profiling_memory_functions(src_addr,dst_addr);

	// free the allocated pointers after profiling is done
	free(src_addr);
	free(dst_addr);

	spi_nrf();
	
	uint32_t analysisResult[4]={0,0,0,0};

	while(1)
	{
		if(rx_cb->count == display_after_lim)

		{
			log_statistics(rx_cb,analysisResult);
		}
	}

	
	
}

void spi_nrf(void)
{
			SPI_init();

		    nrf_read_status();

			nrf_write_config();
			nrf_read_config();

			nrf_write_rf_ch();
			nrf_read_rf_ch();

			nrf_write_rf_setup();
			nrf_read_rf_setup();

			uint8_t* byte_tosend=malloc(6*sizeof(uint8_t));

			nrf_write_tx_addr(byte_tosend);
			nrf_read_tx_addr(byte_tosend);

			nrf_read_fifo_status();


			flush_tx_fifo();
			nrf_read_status();
			flush_rx_fifo();
			nrf_read_status();


}



/*

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

