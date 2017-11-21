/**
*@file logger.h
*@brief Binary Logger functions
*@Author Aakash Kumar/Arun Sundar
*@date Nov 13 2017

*/

#include<stdint.h>
#include<stdio.h>
#include "conversion.h"

//#define KL25Z

#ifndef LOGGER_H
#define LOGGER_H

typedef enum logId {
	LOGGER_INITIALZED,
	GPIO_INITIALZED,
	SYSTEM_INITIALIZED,
	SYSTEM_HALTED,
	INFO,
	WARNING,
	ERROR,
	PROFILING_STARTED,
	PROFILING_RESULT,
	PROFILING_COMPLETED,
	DATA_RECEIVED,
	DATA_ANALYSIS_STARTED,
	DATA_ALPHA_COUNT,
	DATA_NUMERIC_COUNT,
	DATA_PUNCTUATION_COUNT,
	DATA_MISC_COUNT,
	DATA_ANALYSIS_COMPLETED
	} logid_type;

#ifdef KL25Z
#include "uart.h"

#define LOG_RAW_DATA(data, len) log_data_uart(data, len)
#define LOG_RAW_STRING(string) log_string_uart(string)
#define LOG_RAW_INT(data) log_integer(data)

void log_data_uart(uint8_t * src, size_t length);

void log_string_uart(char * src);

void log_integer_uart(int data);

#else

#define LOG_RAW_DATA(data, len) log_data(data, len)
#define LOG_RAW_STRING(string) log_string(string)
#define LOG_RAW_INT(data) log_integer(data)	
	
/**
@brief Outputs a 
@param source pointer to data
@param length of data
@return  none
*/
void log_data(uint8_t * src, size_t length);

void log_string(char * src);

void log_integer(int data);

void log_flush();


#endif	




#endif // End of logger.h
