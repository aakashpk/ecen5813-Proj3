/**
*@file my_circularbuffer.h
*@brief circularbuffer usage functions
*@Author Arunsundar Kannan
*@date Oct 10 2017

*/
#ifndef CIRCULARBUFFER
#define CIRCULARBUFFER

#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>


typedef struct
{	
	uint8_t* base; // base address
	uint8_t* tail; // last value address
	uint8_t* head; // buffer top value address
	uint8_t* limit; // end address
	size_t length; // total no of items possible
	uint8_t count; // current total no of items in the buffer
} CB_t;

typedef enum
{
	buffer_empty,
	buffer_full,
	success,
	null_error
}CB_status;



CB_status CB_buffer_add_item(CB_t* source_ptr,uint8_t value);
/*
@brief Add a new data to the circular buffer 
@param CB_t* source_buffer the input buffer to which the data is to be added
@param value data to be added to the buffer
@return  CB_status status of the operation

*/

CB_status CB_buffer_add_n(CB_t* source_ptr,uint8_t * data,uint32_t length);
/*
@brief Add a block of data to the circular buffer
@param CB_t* source_buffer the input buffer to which the data is to be added
@param data pointer to base location of block of data to be added to the buffer
@param length length of data to be added to the buffer
@return  CB_status status of the operation

*/

CB_status CB_buffer_remove_item(CB_t* source_ptr, uint8_t * value);
/*
@brief remove a new data to the circular buffer 
@param CB_t* source_buffer the input buffer from which the data is to be removed
@param data variable to store the data to be removed from the buffer
@return  CB_status status of the operation

*/
CB_status CB_is_full(CB_t* source_ptr);
/*
@brief checks if the buffer is full
@param CB_t* source_buffer the input buffer which is to be checked
@return  CB_status status of the operation or an error code

*/

CB_status CB_is_empty(CB_t* source_ptr);
/*
@brief checks if the buffer is empty
@param CB_t* source_buffer the input buffer which is to be checked
@return  CB_status status of the operation or an error code

*/



CB_status CB_peek(CB_t* source_buffer, uint8_t position, uint8_t* peeked_ptr);
/*

@brief peeks at a particuluar position in the buffer 
@param CB_t* source_buffer the input buffer which is to be poked at
@param position position to peek in the circular buffer
@param peeked_ptr gives the to peek in the circular buffer

@return  CB_status status of the operation

*/


CB_status CB_init(CB_t* source_buffer, uint8_t length);
/*
@brief reserves some memory for circular buffer 
@param CB_t* source_buffer the pointer to the buffer which is initialised 
@param length number of elements to allocated memory in the circular buffer
@return  CB_status status of the operation

*/


CB_status CB_destroy(CB_t* source_ptr);
/*
@brief frees memory allocated for circular buffer 
@param CB_t* source_buffer the pointer to the buffer which is initialised 
@return  CB_status status of the operation

*/



#endif // End of my_circularbuffer.h


