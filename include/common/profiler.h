
#ifndef PROFILER_H
#define PROFILER_H

#include <stdint.h>
#include <string.h>
#include "logger_queue.h"
#include "conversion.h"

extern const size_t transfer_lengths[4];

//#define KL25Z

#ifdef KL25Z

	#include "dma.h"
	#include "MKL25Z4.h"

	#define getcount() (SysTick->VAL)
	#define systick_overflow (SysTick->CTRL&SysTick_CTRL_COUNTFLAG_Msk)
	#define systickzero() (SysTick->VAL= 0UL)
	#define disp_val (start_count-end_count)
	#define time_unit " Clock Cycles\n\r"
/**
@brief Configures the Ssystick for performing the profiling operations
@param ticks value to initialise the systick down counter
@return  none
*/
	void SysTick_Init(uint32_t ticks);
/**
@brief Does profiling for memmove using DMA
@param uint8_t * src_addr source pointer
@param uint8_t * dst_addr destination pointer
@return  none
*/
	void profiling_memset_dma(uint8_t * src_addr);

	/**
@brief Does profiling for memset using DMA
@param uint8_t * src_addr source pointer
@return  none
*/
	void profiling_memmove_dma(uint8_t * src_addr,uint8_t * dst_addr);

#else

	#include <sys/time.h>
	#include <time.h>

	struct timeval time_value;

	size_t getcount(void); 

	#define systickzero() {}
	#define disp_val (end_count-start_count)
	#define time_unit " uS\n\r"

#endif

/**
@brief Does profiling for memset 
@param uint8_t * src_addr source pointer
@return  none
*/

void profiling_my_memset(uint8_t * src_addr);

/**
@brief Does profiling for memset 
@param uint8_t * src_addr source pointer
@return  none
*/

void profiling_memset(uint8_t * src_addr);
/**
@brief Does profiling for memmove 
@param uint8_t * src_addr source pointer
@param uint8_t * dst_addr destination pointer
@return  none
*/
void profiling_my_memmove(uint8_t * src_addr,uint8_t * dst_addr);
/**
@brief Does profiling for memmove 
@param uint8_t * src_addr source pointer
@param uint8_t * dst_addr destination pointer
@return  none
*/
void profiling_memmove(uint8_t * src_addr,uint8_t * dst_addr);

/*

Wrapper function to call all profiling functions together in project3()


*/

/**
@brief Does profiling for all memory functions, 
		ie calls all the individual profiling functions
@param uint8_t * src_addr source pointer
@param uint8_t * dst_addr destination pointer
@return  none
*/
void profiling_memory_functions(uint8_t * src_addr,uint8_t * dst_addr);

#endif // End of profiler.h
