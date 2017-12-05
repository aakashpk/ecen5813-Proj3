#include "profiler.h"

#define KL25Z

#ifdef KL25Z

void SysTick_Init(uint32_t ticks)
{
	SysTick->LOAD  = (uint32_t)(ticks - 1UL);
	SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
	                   //SysTick_CTRL_TICKINT_Msk  |
	                   SysTick_CTRL_ENABLE_Msk;
	SysTick->VAL   = 0UL;
}

#endif

