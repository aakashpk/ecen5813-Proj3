
/**
*@file project3.c
*@brief project3 implementation is done from this file 
*@Author Aakash Kumar/ArunSundar
*@date Nov 20 2017

*/

#include "project3.h"

char a[10]="abcdefghij";
int b=435865;

void project3(void)
{
	#ifdef KL25Z
	UART_configure();
	#endif
	
	LOG_RAW_STRING("\nChecking this function \r\n");
	LOG_RAW_STRING(a);
	LOG_RAW_STRING("\n\r");
	LOG_RAW_INT(b);
	LOG_RAW_STRING("\n\n\r");
}


