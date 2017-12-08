#include<stdint.h>
#include<stdlib.h>


#include "uart.h"
#include "conversion.h"

#ifndef PROJECT2_H
#define PROJECT2_H

#define alphabet_condition1 (((*removed_data)>=65) && ((*removed_data) <=90))
#define alphabet_condition2 (((*removed_data)>=97) && ((*removed_data) <=122))
#define number_condition1   (((*removed_data)>=48) && ((*removed_data) <=57))
#define punctuation_condition1   (((*removed_data)==34) | ((*removed_data)==33))
#define punctuation_condition2   (((*removed_data)>=39) && ((*removed_data)<=41))
#define punctuation_condition3   (((*removed_data)>=44) && ((*removed_data) <=46))
#define punctuation_condition4   (((*removed_data)==58) | ((*removed_data) ==59))
#define punctuation_condition5   (((*removed_data)==125) |((*removed_data) ==123))
#define punctuation_condition6   (((*removed_data)==63) | ((*removed_data) ==95))
#define misc_condition1   (((*removed_data)>=1) && ((*removed_data) <=32))

// Strings required to be printed on terminal every time statistics is shown
extern uint8_t test_data[19];
extern uint8_t num_alphabets[21];
extern uint8_t num_integers[20];
extern uint8_t num_punctuations[24];
extern uint8_t num_specialchars[27];
extern uint8_t nextline[2];

extern uint32_t display_after_lim; // No of characters after which statistics is displayed

/**
@brief uint8_t* count counts the number of alphabets,numbers,punctuations, miscellaneous characters recieved 
@param CB_t* source_buffer the input buffer which is to be checked
@return  numbers of alphabets count

*/

uint32_t* dataprocesser(CB_t* source_ptr,uint32_t* count);


/**
@brief project2 enables interrupts and displays the statistics of characters typed in at set intervals
@param none
@return none
*/
void project2(void);


void project2_demo(void);

void log_statistics(CB_t* source_ptr,uint32_t* char_count);


#endif


