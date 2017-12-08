
/**
*@file nordic.c
*@brief nordic module usage functions for KL25Z
*@Author Aakash Kumar/ArunSundar
*@date Nov 25 2017

*/


#include"nordic.h"
#include"gpio.h"
#include"spi.h"
#include"logger.h"
/**
@brief Reads the value from the given register address
@param reg address of the register
@return value present in the given register
*/
uint8_t nrf_read_register(uint8_t reg)
{
uint8_t data_read0,data_read1,data_read2,data_read3,data_read4;
uint8_t a =r_register | reg;
nrf_cs_enable();
SPI_write_byte(&a);
data_read0=SPI0_D;

a=0xFF;
SPI_write_byte(&a);
data_read3=SPI0_D;
SPI_write_byte(&a);
data_read4=SPI0_D;
char str[20]="status register :";
LOG_RAW_STRING(str);
LOG_RAW_INT(data_read3);

char newline[3]="\n\r";
LOG_RAW_STRING(newline);
nrf_cs_disable();
return data_read4;
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
uint8_t  byte_tosend,val;
byte_tosend=w_register | reg;
val=value;
SPI_write_byte(&byte_tosend);
SPI_write_byte(&val);
nrf_cs_disable();
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
char str[20]="config register :";
LOG_RAW_STRING(str);
LOG_RAW_INT(value_config);
char newline[3]="\n\r";
LOG_RAW_STRING(newline);

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
char str[25]="rf_setup register :";
LOG_RAW_STRING(str);
LOG_RAW_INT(value_rf_setup);
char newline[3]="\n\r";
LOG_RAW_STRING(newline);

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
char str[25]="rf_ch register :";
LOG_RAW_STRING(str);
LOG_RAW_INT(value_rf_ch);
char newline[3]="\n\r";
LOG_RAW_STRING(newline);

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
char str[25]="fifo_status register :";
LOG_RAW_STRING(str);
LOG_RAW_INT(value_fifo_status);
char newline[3]="\n\r";
LOG_RAW_STRING(newline);

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
uint8_t byte_tosend;
byte_tosend=nrf_flush_tx_fifo_reg();

SPI_write_byte(&byte_tosend);
nrf_cs_disable();
}






/**
@brief Writes the value to the rx_fifo register
@param none
@return none
*/
void flush_rx_fifo()
{
nrf_cs_enable();
uint8_t byte_tosend;
byte_tosend=nrf_flush_rx_fifo_reg();

SPI_write_byte(&byte_tosend);
nrf_cs_disable();

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
uint8_t nop=0xff;
SPI_write_byte(&nop);
sr = SPI0_D;
for(i=1;i<=5;i++)
{
	SPI_write_byte(&nop);

*(tx_address+i)=SPI0_D;
char str[25]="tx_addr register :";
LOG_RAW_STRING(str);
LOG_RAW_INT(*(tx_address+i));
char newline[3]="\n\r";
LOG_RAW_STRING(newline);

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
*tx_address=nrf_tx_addr_reg();

for(i=0;i<=5;i++)
{
SPI_write_byte((tx_address+i));

}
nrf_cs_disable();

}

