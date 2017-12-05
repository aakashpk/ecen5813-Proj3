/**
*@file memory.h
*@brief Memory Manipulation functions
*@Author Aakash Kumar
*@date Sept 24 2017

*/
#ifndef MEMORY_H
#define MEMORY_H

#include<stdint.h>
#include<stdlib.h>
#define TWO 2
#define ONE 1
#define ZERO 0


uint8_t temp;

uint8_t * my_memmove(uint8_t * src, uint8_t * dst, size_t length);
/*
@brief function to move contents of memory given the start of source address, 
start of destination address and length of data to be moved 
@param *src byte pointer to source adress
@param *dst byte pointer to destination address
@param length of bytes to be copied
@return  byte pointer to the destination
*/

uint8_t * my_memcpy(uint8_t * src, uint8_t *dst, size_t length);
/*
@brief function to copy contents of memory from one location to another location
@param *src byte pointer to source address
@param * dst byte pointer to destination address
@param length of bytes to be copied
@return byte pointer to destination
*/
uint8_t *  my_memset(uint8_t  *  src,  size_t  length,  uint8_t  value);
/*
@brief function to set all locations of memory block to a given value
@param *src byte pointer to source location
@param length of memory block to be set
@param value to be set
@return byte pointer to source
*/

uint8_t *  my_memzero(uint8_t  *  src,  size_t  length);
/*
@brief function to set all locations of memory block to zero 
@param *src byte pointer to source location
@param length of memory block to be set
@return byte pointer to source
*/

uint8_t *  my_reverse(uint8_t  *  src,  size_t  length);
/*
@brief function to set reverse the order of all bytes
@param *src byte pointer to source location
@param length of memory block to be set
@return byte pointer to source
*/

int32_t *  reserve_words(size_t  length);
/*
@brief reserves a memory block of given length
@param length , no of words to reserve 
@return byte pointer to allocation if sucessful, NULL if failure
*/

void free_words(uint32_t  *  src);
/*
@brief frees a memory block allocation when pointer to the memory is provided
@param *src pointer to memory block
@return none
*/
#endif //MEMORY_h
