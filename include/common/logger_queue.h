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


#ifdef KL25Z
	#include "MKL25Z4.h"

	// defining critical sections

	#define START_CRITICAL() __disable_irq()
	#define END_CRITICAL() __enable_irq()

#else
	
	//Dummy critical sections to prevent code from breaking on BBB & HOST
	#define START_CRITICAL() {}
	#define END_CRITICAL() {}

#endif

#define LOG_ITEM(logitem,logbuffer) log_add(logitem,logbuffer)

typedef struct
{	
	logdata_t * base; // base address
	logdata_t * tail; // last value address
	logdata_t * head; // buffer top value address
	logdata_t * limit; // end address
	size_t length; // total no of items possible
	size_t count; // current total no of items in the buffer
} CB_log_t;

CB_log_t * Logger_q;

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



 #ifdef KL25Z 
 /**
 * Function setup as static inline, hence defined in the header file
 *
 */
	__attribute__((always_inline)) __STATIC_INLINE CB_status log_is_full(CB_log_t* source_ptr)
	{

		// checks for null pointer


		if(source_ptr==NULL)
		{
			return null_error;
		}

		else
		{

			// check buffer full condition

			if(source_ptr->count==source_ptr->length)
			{
				return buffer_full;
			}
			else return ok; // if buffer is not full and valid pointer is passed , return ok
		}
	}
	
/**
 * Function setup as static inline, hence defined in the header file
 *
 */
	__attribute__((always_inline)) __STATIC_INLINE CB_status log_is_empty(CB_log_t* source_ptr) 
	{
		/*checks for null pointer */
		if(source_ptr==NULL)
		{
			return null_error;
		}
		else
		{

			/* check buffer full condition */

			if(source_ptr->count==0)
			{
				return buffer_empty;
			}
			else return ok;
		}
	}
	

#else 
	CB_status log_is_full(CB_log_t* source_ptr);
	CB_status log_is_empty(CB_log_t* source_ptr);
#endif	

void log_flush(CB_log_t *  source_ptr);
	



#endif // End of logger_queue.h
