#ifndef DEBUG_H
#define DEBUG_H

#include<stdio.h>
#include<stdint.h>

void print_memory(uint8_t * start, uint32_t length);
/*
@brief function to print contents of a block of memory
@param * start byte pointer to the source address of memory block to be printed
@param length length of memory block to be printed  
*/

#endif //debug.h
