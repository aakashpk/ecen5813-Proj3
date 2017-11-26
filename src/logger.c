/**
*@file logger.c
*@brief Binary Logger functions
*@Author Aakash Kumar/Arun Sundar
*@date Nov 13 2017

*/


# include "logger.h"
//#define KL25Z

int j=0;

char logId_texts[18][23] = {
	"LOGGER_INITIALZED",
	"GPIO_INITIALZED",
	"SYSTEM_INITIALIZED",
	"SYSTEM_HALTED",
	"INFO",
	"WARNING",
	"ERROR",
	"PROFILING_STARTED",
	"PROFILING_RESULT",
	"PROFILING_COMPLETED",
	"DATA_RECEIVED",
	"DATA_ANALYSIS_STARTED",
	"DATA_ALPHA_COUNT",
	"DATA_NUMERIC_COUNT",
	"DATA_PUNCTUATION_COUNT",
	"DATA_MISC_COUNT",
	"DATA_ANALYSIS_COMPLETED",
	"HEART_BEAT"
};	



void log_integer(int data){
	uint8_t * buffer = (uint8_t *)calloc(10,sizeof(char)); // allocating a buffer of length 10 as 32 bit int will have max 10 characters
	size_t length;
	length=my_itoa(data,buffer,10); // Converting in base 10
	LOG_RAW_DATA(buffer,length);
}


#ifdef KL25Z


void log_data_uart(uint8_t * src, size_t length)
{
	j=0;
	if(src!=NULL) {
		UART_send_n(src,length);
	 }
}


void log_string_uart(char * src){
	j=0;
	while(*(src+j)!='\0') // print charcters till string termination character
	{
		UART_send(src+j);
		j++;
	}
}

#else

void log_data(uint8_t * src, size_t length)
{
	j=0;
	if(src!=NULL) {
		for(j=0;j<length;j++){
		printf("%c",*(src+j));
	 }
	}
}

void log_string(char * src){
	j=0;
	while(*(src+j)!='\0') // print characters till string termination character
	{
		printf("%c",*(src+j));
		j++;
	}
}


#endif
