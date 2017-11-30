/**
*@file logger_queue.c
*@brief Binary Logger queue functions
*@Author Aakash Kumar/Arun Sundar
*@date Nov 23 2017

*/

#include "logger_queue.h"


void log_item (logdata_type *logVal){

}


logdata_type * addLog(logdata_type *logData , logid_type logID, uint32_t timestamp , size_t logLength, void* payload)
{
	logData->logID=logID;
	logData->timestamp=timestamp;
	logData->logLength=logLength;
	logData->payload=payload;
	//logData->checksum=checksum;
	return logData;
}


void print_log(logdata_type *logData)
{
	LOG_RAW_STRING(logId_texts[logData->logID]);
	LOG_RAW_STRING(" at ");
	LOG_RAW_INT(logData->timestamp);
	LOG_RAW_STRING(" with payload ");
	LOG_RAW_DATA(logData->payload,logData->logLength);
	LOG_RAW_STRING("\n\r");
}






