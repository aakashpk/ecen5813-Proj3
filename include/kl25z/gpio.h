/**
*@file gpio.h
*@brief gpio usage functions for KL25Z
*@Author Aakash Kumar/ArunSundar
*@date Nov 16 2017

*/


#ifndef GPIO_H
#define GPIO_H

#include<stdint.h>
#include<stdlib.h>
#include"MKL25Z4.h"
#include "logger_queue.h"


/**
@brief Configures the GPIO pins for nrf and spi modules
@param none
@return  none
*/
void nrf_cs_enable();
/**
@brief Configures the GPIO pins for nrf and spi modules
@param none
@return  none
*/
void nrf_cs_disable();
void nrf_powerup();


#endif
