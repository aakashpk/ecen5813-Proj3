/**
*@file circularbuffer.c
*@brief circularbuffer usage functions 
*@Author Aakash Kumar/ArunSundar
*@date Oct 16 2017

*/




#include "circularbuffer.h"

/**
@brief  Initializes the data memebers of the CB_t structure
        and allocates memory for the circularbuffer 

@param  CB_t* source_ptr pointer to the CB_t structure

@param  length gives the length of the circular buffer

@return returns the status of the operation on the buffer
*/


CB_status CB_init(CB_t* source_ptr, uint8_t length)
{	
	/*checks for null pointer */
	if(source_ptr==NULL || length<=0)
	{
		return null_error;
	}
	else 
	{       /* initializes the pointers to the circular buffer*/

		source_ptr->base=(uint8_t*)calloc(length,sizeof(uint8_t));

		source_ptr->head=source_ptr->base;
		
		source_ptr->tail=source_ptr->head;
		
		source_ptr->length=length;
		
		source_ptr->limit=source_ptr->base+(length-1);
		
		source_ptr->count=0;
		
		return success;	
	}
	
}

/**
@brief  Adds data to the circular buffer 

@param  CB_t* source_ptr pointer to the CB_t structure

@param  value gives the value to be added to the circular buffer

@return returns the status of the operation on the buffer
*/

CB_status CB_buffer_add_item(CB_t* source_ptr,uint8_t value)
{

	/*checks for null pointer */

	if(source_ptr==NULL)
	{
		return null_error;
	}

	else
	{	/*Checks if the buffer is full */ 

		if(source_ptr->count == source_ptr->length)

		{	
			return buffer_full;
			

		}
		else
		{	/* For adding when the buffer is not full */

			if(source_ptr->head>source_ptr->limit)
			{	source_ptr->head=source_ptr->base;
				*(source_ptr->head)=value;
				source_ptr->head+=1;
				
	   		}
			else
			{

				*(source_ptr->head)=value;
				source_ptr->head+=1;
				
				
			}

			

		}
	source_ptr->count++;

	return success;
	}
}


/***
@brief Add a block of data to the circular buffer
@param CB_t* source_buffer the input buffer to which the data is to be added
@param data pointer to base location of block of data to be added to the buffer
@param length length of data to be added to the buffer
@return  CB_status status of the operation

*/
CB_status CB_buffer_add_n(CB_t* source_ptr,uint8_t * data,uint32_t length)
{
	int l;
	CB_status last_status;
	for(l=0;l<length;l++)
	{
		last_status=CB_buffer_add_item(source_ptr,*(data+l));
	}
 return last_status;
}


/**
@brief  Removes data to the circular buffer 

@param  CB_t* source_ptr pointer to the CB_t structure

@param  value gets the value to be removed from the circular buffer

@return returns the status of the operation on the buffer
*/

CB_status CB_buffer_remove_item(CB_t* source_ptr,uint8_t* value)
{
	/*checks for null pointer */
	 
	if(source_ptr==NULL)
	{
		return null_error;
	}

	else
	{	if(source_ptr->count==0)
		{
			return buffer_empty;
		}
		/* gets the value that is removed */
		*value=*(source_ptr->tail);
		
		/* checks corner case and assigns tails to the base address */

		if(source_ptr->tail==source_ptr->limit)
		{

			source_ptr->tail=source_ptr->base;
			
		}
		else 
		{ 

			/* for regular cases other than the corner cases */	

			

			

			source_ptr->tail+=1;

			
		}
		source_ptr->count--;

		return success;
	}
}


/**
@brief  Peeks into the circular buffer 

@param  CB_t* source_ptr pointer to the CB_t structure

@param  peeked_ptr gives the peeked value from the circular buffer

@param  position gives the position to peek from the circular buffer

@return returns the status of the operation on the buffer
*/


CB_status CB_peek(CB_t* source_ptr,uint8_t position, uint8_t* peeked_ptr)
{


	/*checks for null pointer */

	if(source_ptr != NULL)
	{

		/* checks for non-corner cases */

		if(((source_ptr->head) + position) <= source_ptr->limit)
		{
			*peeked_ptr = *((source_ptr->head) + position);

			return success;
		}
 

		else if(((source_ptr->head) + position) > source_ptr->limit)
		{ 

			/*checks for corner cases */

			uint8_t difference = ((source_ptr->head) + position) - source_ptr->limit;

			*peeked_ptr=*((source_ptr->base) + difference);

			return success;
 

		}
		else return null_error;
	}
	else	
	{
		return null_error;
	}

}



/**
@brief  Checks if the circular buffer is full 

@param  CB_t* source_ptr pointer to the CB_t structure

@return returns the status of the operation on the buffer
*/



CB_status CB_is_full(CB_t* source_ptr)
{	

	/*checks for null pointer */


	if(source_ptr==NULL)
	{
		return null_error;
	}

	else
	{

		/* check buffer full condition */

		if(source_ptr->count==source_ptr->length)
		{
			return buffer_full;
		}
		else return ok;
	}
}


/**
@brief  Checks if the circular buffer is empty

@param  CB_t* source_ptr pointer to the CB_t structure

@return returns the status of the operation on the buffer
*/




CB_status CB_is_empty(CB_t* source_ptr)
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


/**
@brief  frees the memory allocated to the circular buffer

@param  CB_t* source_ptr pointer to the CB_t structure

@return returns the status of the operation on the buffer
*/




CB_status CB_destroy(CB_t* source_ptr)
{

	/* check for null pointer condition */

	if(source_ptr==NULL)
	{
		return null_error;
	}
	else
	{

		/* frees the allocated memory */ 

		free(source_ptr->base);

		return success;
	}
}


