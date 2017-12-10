#include"MKL25Z4.h"

// LEDs sink current on board setting the bit turns the LED OFF

#define REDON GPIOB_PCOR |= (1<<18)
#define REDOFF GPIOB_PSOR |= (1<<18)
#define GREENON GPIOB_PCOR |= (1<<19)
#define GREENOFF GPIOB_PSOR |= (1<<19)
#define BLUEON GPIOD_PCOR |= (1<<1)
#define BLUEOFF GPIOD_PSOR |= (1<<1)
#define BLUETOGGLE GPIOD_PTOR |= (1<<1)


/**
 @brief Function to initialize the RGB LED on FRDM board
 Initializes the onboard RGB LED. The pins sink current hence setting the bits turn the LED OFF
 writing high to a bit in PCOR port clear output register clears that bit in the PDOR and turns ON the LED
writing high to a bit in PSOR port set output register sets that bit in the PDOR and turns OFF the LED
These have been setup as macros above.
 @param None
 @return None

 */
void RGB_LED_Init();

void changecolour(uint8_t num);


