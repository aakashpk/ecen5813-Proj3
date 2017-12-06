/**
*@file gpio.h
*@brief gpio usage functions for KL25Z
*@Author Aakash Kumar/ArunSundar
*@date Nov 16 2017
*/

#include"gpio.h"

/**
@brief Configures the GPIO pins for nrf and spi modules
@param none
@return  none
*/


void nrf_cs_enable()
{
// Set Direction PD.0 to output
GPIOD_PDDR |= (1<<0);
// SET CS PIN TO ACTIVE LOW
GPIOD_PCOR |= (1<<0);


}


void nrf_cs_disable()
{
// Set Direction PD.0 to output
GPIOD_PDDR |= (1<<0);
// SET CS PIN TO ACTIVE LOW
GPIOD_PSOR |= (1<<0);


}
void nrf_powerup()
{
	GPIOD_PDDR |= (1<<5);
	GPIOD_PSOR |= (1<<5);
}
