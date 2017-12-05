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

void project3(void);

#else

	
void project3(void);




#endif
