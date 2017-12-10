/**
*@file logger.h
*@brief Binary Logger functions
*@Author Aakash Kumar/Arun Sundar
*@date Nov 13 2017

*/
#ifndef LOGGER_H
#define LOGGER_H

#include<stdint.h>
#include<stdio.h>
#include "conversion.h"
#include <sys/time.h>

#define KL25Z

extern uint8_t log_enable;


typedef enum logId {
	LOGGER_INITIALZED,
	GPIO_INITIALIZED,
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
	DATA_ANALYSIS_COMPLETED,
	HEART_BEAT,
	LED_STATUS
	} logid_t;
	
	
extern char logId_texts[18][23] ; // Array of strings to display the log value as string in UART/stdoutput


typedef struct log_data {
	logid_t logID;
	uint32_t timestamp;
	size_t logLength;
	uint8_t * payload;
	uint32_t checksum;
} __attribute__((packed)) logdata_t;

// One common container to pass logs to the log item function
logdata_t logData;

/**
@brief Logs integer data to the serial terminal 
@param int data data to be logged
@return  none
*/

void log_integer(int data);


/**
@brief Gets the  numerical calculationation on the
different types of data recieved and send its to a queue
@param logID pointer the structure containing details of the log 
@param size_t length of the log
@param uint8_t* pointer to the payload to be logged
@return  returns the structure pointer
*/
logdata_t * createLog(logid_t logID, size_t logLength, uint8_t * payload);



/**
@brief Performs checksums to validate data 
@param logID pointer the structure containing details of the log 
@param size_t length of the log
@param uint8_t* pointer to the payload to be logged
@param uint32_t timestamp contains the timestamp
@return  return the calculated checksum
*/
uint32_t calc_checksum(logid_t logID, uint32_t timestamp , size_t logLength, uint8_t * payload);

#ifdef KL25Z
#include "uart.h"
#include "rtc.h"

#define LOG_RAW_DATA(data, len) log_data_uart(data, len)
#define LOG_RAW_STRING(string) log_string_uart(string)
#define LOG_RAW_INT(data) log_integer(data)


/**
@brief sends data to the uart
@param uint8_t* src pointer to the data to be logged 
@param size_t length length of the source pointer
@return  none
*/

void log_data_uart(uint8_t * src, size_t length);



/**
@brief sends string data to the uart 
@param char* src pointer to the data to be logged 
@return  none
*/
void log_string_uart(char * src);


#else

#define LOG_RAW_DATA(data, len) log_data(data, len)
#define LOG_RAW_STRING(string) log_string(string)
#define LOG_RAW_INT(data) log_integer(data)	

struct timeval log_time;	
	
/**
@brief Outputs a 
@param source pointer to data
@param length of data
@return  none
*/
void log_data(uint8_t * src, size_t length);


/**
@brief logs string data for BBB
@param char* src pointer to the data to be logged 
@return  none
*/
void log_string(char * src);


/**
@brief gets time of the day
@param  none 
@return  none
*/
uint32_t getlogtime();

#endif	




#endif // End of logger.h
