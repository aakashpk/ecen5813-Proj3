/**
*@file project3.h
*@brief project3 functions
*@Author Aakash Kumar/ArunSundar
*@date Nov 11 2017

*/

#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>

#include "logger.h"
#include "memory.h"
#include "logger_queue.h"
#include "profiler.h"


//#define KL25Z

#ifdef KL25Z
#include "dma.h"
#include "led.h"

#endif
	
void project3(void);


void spi_nrf(void);

