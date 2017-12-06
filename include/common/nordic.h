
/**
*@file nordic.h
*@brief nordic module usage functions for KL25Z
*@Author Aakash Kumar/ArunSundar
*@date Nov 25 2017

*/



#include"MKL25Z4.h"
#include<stdint.h>
#include<stdlib.h>
#include"spi.h"
#include"gpio.h"
#define nrf_status_reg() (0x07)
#define nrf_config_reg() (0x00)
#define r_register (0x00)
#define w_register (0x20)
#define nrf_rf_ch_reg() (0x05)
#define nrf_rf_setup_reg() (0x06)
#define nrf_tx_addr_reg() (0x10)
#define nrf_fifo_status_reg() (0x17)
#define nrf_flush_tx_fifo_reg() (0xE1)
#define nrf_flush_rx_fifo_reg() (0XE2)
#define nrf_nop() (0xff)


/**
@brief Reads the value from the given register address
@param reg address of the register
@return value present in the given register
*/
uint8_t nrf_read_register(uint8_t reg);




/**
@brief Writes the value to the given register address
@param reg address of the register
@param value value to be written to the register
@return none
*/
void nrf_write_register(uint8_t reg,uint8_t value);




/**
@brief Reads the value from the status register
@param none
@return value present in the given register
*/
uint8_t nrf_read_status();




/**
@brief Reads the value from the config register
@param none
@return value present in the given register
*/
uint8_t nrf_read_config();




/**
@brief Writes the value to the config register
@param none
@return none
*/
void nrf_write_config();



/**
@brief Reads the value from the rf_setup register
@param none
@return value present in the given register
*/
uint8_t nrf_read_rf_setup();



/**
@brief Writes the value to the rf_setup register
@param none
@return none
*/
void nrf_write_rf_setup();


/**
@brief Reads the value from the rf_ch register
@param none
@return value present in the given register
*/
uint8_t nrf_read_rf_ch();

/**
@brief Writes the value to the rf_ch register
@param none
@return none
*/
void nrf_write_rf_ch();



/**
@brief Reads the value from the fifo_status register
@param none
@return value present in the given register
*/
uint8_t nrf_read_fifo_status();



/**
@brief Writes the value to the tx_fifo register
@param none
@return none
*/
void flush_tx_fifo();





/**
@brief Writes the value to the rx_fifo register
@param none
@return none
*/
void flush_rx_fifo();



/**
@brief Reads multiple values from the tx_addr register
@param tx_address starting address of the pointer to store the data 
@return none
*/
void nrf_read_tx_addr(uint8_t* tx_address);




/**
@brief Writes the value to the tx_addr register
@param tx_address starting address of the pointer which has the data 
@return none
*/
void nrf_write_tx_addr(uint8_t* tx_address);

