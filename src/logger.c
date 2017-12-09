/**
*@file logger.c
*@brief Binary Logger functions
*@Author Aakash Kumar/Arun Sundar
*@date Nov 13 2017

*/


#include "logger.h"
#define TEN 10

//#define KL25Z

#define DEBUG

#ifdef DEBUG
uint8_t log_enable=1;
#else
uint8_t log_enable=0;
#endif


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


uint8_t itoa_buffer[10]; // allocating a buffer of length 10 as 32 bit int will have max 10 characters

void log_integer(int data){

	size_t length;
	length=my_itoa(data,itoa_buffer,TEN); // Converting in base 10
	LOG_RAW_DATA(itoa_buffer,length);
}

logdata_t * createLog(logid_t logID, size_t logLength, uint8_t * payload)
{
	if(log_enable)
	{
		logData.logID=logID;
		logData.timestamp=getlogtime();
		logData.logLength=logLength;
		logData.payload=payload;
		logData.checksum=calc_checksum(logData.logID,logData.timestamp,logData.logLength,logData.payload);
	}

	return &logData;
}


uint32_t calc_checksum(logid_t logID, uint32_t timestamp , size_t logLength, uint8_t * payload)
{
	return ((uint32_t)logID+timestamp+(uint32_t)logLength+(uint32_t)payload);
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
	while(*(src+j)!='\0') // print characters till string termination character
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

uint32_t getlogtime()
{
		gettimeofday(&log_time,NULL);
		return log_time.tv_sec;
}

#endif
