
/**
*@file project2.c
*@brief project2 implementation is done from this file 
*@Author Aakash Kumar/ArunSundar
*@date Oct 28 2017

*/

#include "project2.h"



CB_t * rx_cb,* tx_cb; // Receive and Transmit Circular Buffers

uint32_t* dataprocesser(CB_t* source_ptr,uint32_t* count)
{
uint8_t * removed_data=(uint8_t*)malloc(sizeof(uint8_t));
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


return count;
}



void dumpstatistics(CB_t* source_ptr,CB_t* destination_ptr,uint32_t* char_count)
{
	int toAddLength;
	uint8_t toAddData[8];
	dataprocesser(source_ptr,char_count); // run data processor on recive buffer to get the number of characters
		
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
