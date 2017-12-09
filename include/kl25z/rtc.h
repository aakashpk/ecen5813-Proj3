/**
*@file rtc.h
*@brief RTC implementation is done from this file
*@Author Aakash Kumar/ArunSundar
*@date Nov 20 2017

*/
#ifndef RTC_H
#define RTC_H

#include <stdint.h>
#include "MKL25Z4.h"
#include "logger_queue.h"

/**
@brief Configures the RTC for performing for sending time
@param none
@return  none
*/
void RTC_Init();

/**
@brief gives the time for the logs
@param none
@return returns seconds from rtc 
*/

uint32_t getlogtime();









/** 
@brief IRQ handler for RTC interrupt
@param none
@return none
*/
void RTC_Seconds_IRQHandler();

#endif // end of rtc.h
