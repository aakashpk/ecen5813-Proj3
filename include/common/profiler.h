
#ifndef PROFILER_H
#define PROFILER_H

#include <stdint.h>
#include "MKL25Z4.h"

#define KL25Z

#ifdef KL25Z

#define getcount() (SysTick->VAL)
#define systick_overflow (SysTick->CTRL&SysTick_CTRL_COUNTFLAG_Msk)
#define systickzero() (SysTick->VAL= 0UL)

void SysTick_Init(uint32_t ticks);

#endif








#endif // End of profiler.h
