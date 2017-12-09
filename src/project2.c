
/**
*@file project2.c
*@brief project2 implementation is done from this file 
*@Author Aakash Kumar/ArunSundar
*@date Oct 28 2017

*/

#include "project2.h"



CB_t * rx_cb,* tx_cb; // Receive and Transmit Circular Buffers

// Strings required to be printed on terminal every time statistics is shown
uint8_t test_data[19]="UART0 Initialized\n\r";
uint8_t num_alphabets[21]="\n\rNo of Alphabets is:";
uint8_t num_integers[20]="\n\rNo of Integers is:";
uint8_t num_punctuations[24]="\n\rNo of Punctuations is:";
uint8_t num_specialchars[27]="\n\rNo of Misc Characters is:";
uint8_t nextline[2]="\n\r";

uint32_t display_after_lim=25; // No of characters after which statistics is displayed

/**
@brief Get the input data stream and performs numerical calculationation on the
different types of data recieved
@param CB_t* source_ptr input data buffer
@param uint32_t* count contains the count value for different types of data
@return  returns the pointer to the count
*/


uint32_t* dataprocesser(CB_t* source_ptr,uint32_t* count)
{
uint8_t * removed_data=(uint8_t*)malloc(sizeof(uint8_t)); // change to array;
uint8_t index=0;
	while(source_ptr->count >0)
	{
			CB_buffer_remove_item(source_ptr,removed_data);
			
			if(alphabet_condition1 | alphabet_condition2) // Check for alphabet character condition and increment count of alphabets
			{
				count[0]++;
				
			}
	
			else if(number_condition1) // Check for number characters and increment number count
			{	
				count[1]++;
			}

			else if(punctuation_condition1 || punctuation_condition2 || punctuation_condition3 || punctuation_condition4 || punctuation_condition5 || punctuation_condition6)
			// check for punctuation characters and increment count
			{	
				count[2]++;
			}
		
			else // if none of the above then increment miscellaneous characters
			{	
				count[3]++;
			}

			
			index++;
		
	}

	free(removed_data);
return count;
}

/**
@brief Gets the  numerical calculationation on the
different types of data recieved and send its to a queue
@param CB_t* source_ptr input data buffer
@param CB_t* destination_ptr output data buffer
@param uint32_t* char_count contains the count value for different types of data
@return  none
*/


void dumpstatistics(CB_t* source_ptr,CB_t* destination_ptr,uint32_t* char_count)
{
	int toAddLength;
	uint8_t toAddData[8];
	dataprocesser(source_ptr,char_count); // run data processor on receive buffer to get the number of characters
		
		// add the calculated count to transmit buffer along with required display strings
		for(int k=0;k<4;k++)
	    			{
	    				toAddLength=my_itoa(*(char_count+k),toAddData,10); // Convert the integer count to characters
						
						// Display the type of character for which count is being printed
	    				if(k==0) CB_buffer_add_n(destination_ptr,num_alphabets,21);  
	    				if(k==1) CB_buffer_add_n(destination_ptr,num_integers,20);
	    				if(k==2) CB_buffer_add_n(destination_ptr,num_punctuations,24);
	    				if(k==3) CB_buffer_add_n(destination_ptr,num_specialchars,27);

	    				CB_buffer_add_n(destination_ptr,toAddData,toAddLength);

	    			}
	    			CB_buffer_add_n(destination_ptr,nextline,2); // go to newline after display
}

/**
@brief Gets the  numerical calculationation on the
different types of data recieved and logs to the serial terminal
@param CB_t* source_ptr input data buffer
@param uint32_t* char_count contains the count value for different types of data
@return  none
*/


void log_statistics(CB_t* source_ptr,uint32_t* char_count)
{
	uint8_t PayloadData[4][10],statLength;
	LOG_ITEM(createLog(DATA_ANALYSIS_STARTED,0,NULL),Logger_q);
	dataprocesser(source_ptr,char_count); // run data processor on receive buffer to get the number of characters

	for(int k=0;k<4;k++)
			{
				statLength=my_itoa(*(char_count+k),PayloadData[k],10); // Convert the integer count to characters

				// Log Character statistics
				if(k==0) LOG_ITEM(createLog(DATA_ALPHA_COUNT,statLength,PayloadData[k]),Logger_q);
				if(k==1) LOG_ITEM(createLog(DATA_NUMERIC_COUNT,statLength,PayloadData[k]),Logger_q);
				if(k==2) LOG_ITEM(createLog(DATA_PUNCTUATION_COUNT,statLength,PayloadData[k]),Logger_q);
				if(k==3) LOG_ITEM(createLog(DATA_MISC_COUNT,statLength,PayloadData[k]),Logger_q);


			}

	LOG_ITEM(createLog(DATA_ANALYSIS_COMPLETED,0,NULL),Logger_q);
}
/**
@brief Implementation function for project2
@param none
@return  none
*/




void project2(void)
{
	uint32_t character_count[4]={0,0,0,0};
	
    UART_configure(); // Initialize UART0
    RGB_LED_Init(); // Initialize the LED

    // interrupt and NVIC functions from core_cm0plus.h
    __enable_irq(); // Enable global interrupts

	// Initialize Receive Buffer
    rx_cb=malloc(sizeof(CB_t));
    CB_init(rx_cb,100);
	
	// Initialize Transmit buffer
    tx_cb=malloc(sizeof(CB_t));
    CB_init(tx_cb,200);
	
	// Send test characters to terminal
    UART_send_n(test_data,17);
    UART_send_n(nextline,2);

    for (;;) 
	{
    	 UART_TX_Int_Disable();
    	if(rx_cb->count == display_after_lim) // wait till the preset number of characters
    	{
    		dumpstatistics(rx_cb,tx_cb,character_count); // dump statistics into the transmit buffer 
    		UART_TX_Int_Enable();// enable transmit interrupt to send data from ISR
    	}

    }

}


/**
@brief Implementation function for project2 demo problem
@param none
@return  none
*/



void project2_demo(void)
{

    UART_configure(); // Initialize UART0
    RGB_LED_Init(); // Initialize the LED

	// Send test character terminal
    UART_send_n(test_data,17);
    UART_send_n(nextline,2);

    for (;;)
	{
    	uint8_t b[1];

    	UART_receive(b);
		if(*b=='r')
		{
			REDON; GREENOFF; BLUEOFF;
		}
		else if(*b=='g')
		{
			REDOFF; BLUEOFF; GREENON;
		}
		else if(*b=='b')
		{
			REDOFF; GREENOFF; BLUEON;
		}
		else
		{
			REDOFF; GREENOFF;BLUEOFF;
		}

    }

}
