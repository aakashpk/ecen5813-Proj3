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

/*

*/

void log_item (logdata_type *logVal);


/*

*/
logdata_type * addLog(logdata_type *logData , logid_type logID, uint32_t timestamp , size_t logLength, void* payload);


void print_log(logdata_type *logData);

#endif // End of logger_queue.h
