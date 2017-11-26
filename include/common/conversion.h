/*
*@file conversion.h
*@brief Data Manipulation functions
*@Author Aakash Kumar
*@date Sept 27 2017
*/
#ifndef CONVERSION_H
#define CONVERSION_H

#include<stdint.h>
#include"memory.h"

uint8_t my_itoa(int32_t data,uint8_t * ptr, uint32_t base);
/*
@brief Integer to ASCII conversion, converts passed 32 bit integer to ASCII string 
and copied to the pointer address passed. The conversion supports bases 2 to 16
@param data input 32 bit integer 
@param byte pointer to location where output has to be copied
@param base to which the conversion is to be done
@return length of converted data 

*/

int32_t my_atoi(uint8_t * ptr,uint8_t digits,uint32_t base);
/*
@brief ASCII to Integer conversion, converts passed ASCII string to 32 bit integer
and copied to the pointer address passed. The conversion supports bases 2 to 16
@param data input ASCII string 
@param byte pointer to location where output has to be copied
@param base to which the conversion is to be done
@return length of converted data 
*/

int8_t big_to_little32(uint32_t * data,uint32_t length);
/*
@brief Converts passed array of data from big endian to little endian respresentation
@param data input array to function
@param length , length of array passed
@return error code if conversion fails, 0 if successful
*/

int8_t little_to_big32(uint32_t * data,uint32_t length);
/*
@brief Converts passed array of data from little endian to big endian respresentation
@param data input array to function
@param length , length of array passed
@return error code if conversion fails, 0 if successful
*/

#endif //end of conversion.h