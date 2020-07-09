#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>

#include "i2c.h"
#include "AT24C32.h"

#define DELAY_TIME 1000

int main(void) {
	
	clock_prescale_set(clock_div_1);
	init_i2c();
	AT24C32_clear_all();

	while (1) {
	  
	}
  
	return 0;
}
