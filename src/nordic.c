
/**
*@file nordic.c
*@brief nordic module usage functions for KL25Z
*@Author Aakash Kumar/ArunSundar
*@date Nov 25 2017

*/


#include"nordic.h"
#include"gpio.h"

/**
@brief Reads the value from the given register address
@param reg address of the register
@return value present in the given register
*/
uint8_t nrf_read_register(uint8_t reg)
{


nrf_cs_enable();
uint8_t* data_read=malloc(1*sizeof(uint8_t));
uint8_t* byte_write=malloc(2*sizeof(uint8_t));
*byte_write=r_register | reg;
SPI_write_byte(byte_write);
*data_read=SPI0_D;
*(byte_write+1)=0xFF;
SPI_write_byte((byte_write+1));

*(data_read)=SPI0_D;
//nrf_cs_disable();
free(byte_write);
nrf_cs_disable();
return *(data_read+1);
}




/**
@brief Writes the value to the given register address
@param reg address of the register
@param value value to be written to the register
@return none
*/
void nrf_write_register(uint8_t reg,uint8_t value)
{
nrf_cs_enable();
uint8_t* byte_tosend=malloc(2*sizeof(uint8_t));
*byte_tosend=w_register | reg;
*(byte_tosend+1)=value;
SPI_write_byte(byte_tosend);
SPI_write_byte((byte_tosend+1));
nrf_cs_disable();
free(byte_tosend);
}





/**
@brief Reads the value from the status register
@param none
@return value present in the given register
*/
uint8_t nrf_read_status()
{
uint8_t reg=nrf_status_reg();
uint8_t value_status=nrf_read_register(reg);
return value_status;
}




/**
@brief Reads the value from the config register
@param none
@return value present in the given register
*/
uint8_t nrf_read_config()
{
uint8_t reg=nrf_config_reg();
uint8_t value_config=nrf_read_register(reg);
return value_config;
}




/**
@brief Writes the value to the config register
@param none
@return none
*/
void nrf_write_config()
{
uint8_t reg,value;
reg=nrf_config_reg();
value=0x08; //nrf_nop();
nrf_write_register(reg,value);

}




/**
@brief Reads the value from the rf_setup register
@param none
@return value present in the given register
*/
uint8_t nrf_read_rf_setup()
{
uint8_t reg=nrf_rf_setup_reg();
uint8_t value_rf_setup=nrf_read_register(reg);
return value_rf_setup;
}



/**
@brief Writes the value to the rf_setup register
@param none
@return none
*/
void nrf_write_rf_setup()
{
uint8_t reg,value;
reg=nrf_rf_setup_reg();
value=0x1f;                            //nrf_nop();
nrf_write_register(reg,value);

}



/**
@brief Reads the value from the rf_ch register
@param none
@return value present in the given register
*/
uint8_t nrf_read_rf_ch()
{
uint8_t reg=nrf_rf_ch_reg();
uint8_t value_rf_ch=nrf_read_register(reg);
return value_rf_ch;
}


/**
@brief Writes the value to the rf_ch register
@param none
@return none
*/
void nrf_write_rf_ch()
{
uint8_t reg,value;
reg=nrf_rf_ch_reg();
value=0x02;                   //nrf_nop();
nrf_write_register(reg,value);

}




/**
@brief Reads the value from the fifo_status register
@param none
@return value present in the given register
*/
uint8_t nrf_read_fifo_status()
{
uint8_t reg=nrf_fifo_status_reg();
uint8_t value_fifo_status=nrf_read_register(reg);
return value_fifo_status;
}


/**
@brief Writes the value to the tx_fifo register
@param none
@return none
*/
void flush_tx_fifo()
{
nrf_cs_enable();
uint8_t* byte_tosend=malloc(1*sizeof(uint8_t));
*byte_tosend=nrf_flush_tx_fifo_reg();

SPI_write_byte(byte_tosend);
nrf_cs_disable();
free(byte_tosend);
}






/**
@brief Writes the value to the rx_fifo register
@param none
@return none
*/
void flush_rx_fifo()
{
nrf_cs_enable();
uint8_t* byte_tosend=malloc(1*sizeof(uint8_t));
*byte_tosend=nrf_flush_rx_fifo_reg();

SPI_write_byte(byte_tosend);
nrf_cs_disable();
free(byte_tosend);
}



/**
@brief Reads multiple values from the tx_addr register
@param tx_address starting address of the pointer to store the data
@return none
*/
void nrf_read_tx_addr(uint8_t* tx_address)
{
int i;
nrf_cs_enable();
int reg=nrf_tx_addr_reg();


*tx_address=r_register | reg;
SPI_write_byte(tx_address);
uint8_t sr = SPI0_D;
for(i=1;i<=5;i++)
{ SPI_write_byte(0xff);

*(tx_address+i)=SPI0_D;
}

nrf_cs_disable();

}





/**
@brief Writes the value to the rx_fifo register
@param tx_address starting address of the pointer which has the data
@return none
*/

void nrf_write_tx_addr(uint8_t* tx_address)
{
int i;
nrf_cs_enable();
tx_address=nrf_tx_addr_reg();

for(i=0;i<=5;i++)
{
SPI_write_byte((tx_address+i));

}
nrf_cs_disable();

}

