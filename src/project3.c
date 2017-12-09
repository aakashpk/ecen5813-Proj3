
/**
*@file project3.c
*@brief project3 implementation is done from this file
*@Author Aakash Kumar/ArunSundar
*@date Nov 20 2017

*/

//#define KL25Z

#include "project3.h"

#ifdef KL25Z
#include "project2.h"

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

#endif

#define LOGGERSIZE 10


/**
@brief Implementation function for project3
@param none
@return  none
*/



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
	
	#ifdef KL25Z

	spi_nrf();
	
	uint32_t analysisResult[4]={0,0,0,0};

	while(1)
	{
		if(rx_cb->count == display_after_lim)

		{
			log_statistics(rx_cb,analysisResult);
		}
	}
	

	#endif

}



