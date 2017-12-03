/**
*@file logger_queue.h
*@brief Binary Logger queue functions
*@Author Aakash Kumar/Arun Sundar
*@date Nov 23 2017

*/

#ifndef LOGGER_QUEUE_H
#define LOGGER_QUEUE_H

#include "circularbuffer.h"
#include "logger.h"

//#define LOG_ITEM() log_add(createLog())

typedef struct
{	
	logdata_t * base; // base address
	logdata_t * tail; // last value address
	logdata_t * head; // buffer top value address
	logdata_t * limit; // end address
	size_t length; // total no of items possible
	size_t count; // current total no of items in the buffer
} CB_log_t;

/*

*/
CB_status CB_log_init();

/*

*/

CB_status log_add (logdata_t *logVal, CB_log_t *source_ptr);


/*

*/
void print_log(logdata_t *logData);

/*

*/
CB_status log_remove(logdata_t * logValue, CB_log_t* source_ptr);

CB_status log_is_empty(CB_log_t* source_ptr);

void log_flush(CB_log_t *  source_ptr);

#endif // End of logger_queue.h
