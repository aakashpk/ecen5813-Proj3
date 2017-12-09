
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

	void SysTick_Init(uint32_t ticks);

	void profiling_memset_dma(uint8_t * src_addr);

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


void profiling_my_memset(uint8_t * src_addr);

void profiling_memset(uint8_t * src_addr);

void profiling_my_memmove(uint8_t * src_addr,uint8_t * dst_addr);

void profiling_memmove(uint8_t * src_addr,uint8_t * dst_addr);

/*

Wrapper function to call all profiling functions together in project3()


*/
void profiling_memory_functions(uint8_t * src_addr,uint8_t * dst_addr);

#endif // End of profiler.h
