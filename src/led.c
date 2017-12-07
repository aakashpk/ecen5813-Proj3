#include "led.h"

void RGB_LED_Init()
{

	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK; // Enable the PortB clock for red and green LED
	SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK; // Enable Port D clock for blue LED

	PORTB_PCR18 = PORT_PCR_MUX(1);	// Configure Mode PB.18 to GPIO use
	PORTB_PCR19 = PORT_PCR_MUX(1); // Configure Mode PB.19 to GPIO use
	PORTD_PCR1 = PORT_PCR_MUX(1); // Configure Mode PD.1 to GPIO use


	GPIOB_PDDR |= (1<<18); // Set Direction PB.18 to output  -- red led
	GPIOB_PDDR |= (1<<19); // Set Direction PB.19 to output -- green led
	GPIOD_PDDR |= (1<<1); // Set Direction PD.13 to output -- blue led

	REDOFF;GREENOFF;BLUEOFF;
}
