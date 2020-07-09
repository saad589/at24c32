#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>

#include "defines.h"
#include "usart.h"

#include "i2c.h"
#include "AT24C32.h"

#define DELAY_TIME 1000

int main(void) {

	uint16_t address = 0x0fff; // the very last byte
	uint8_t receive_byte;

	uint8_t send_byte = 13;

	clock_prescale_set(clock_div_1);
	init_usart();
	print_string("random r//w demo\r\n");
	
	init_i2c();

	AT24C32_byte_write(address,byte);
	receive_byte = AT24C32_random_read(address);

	print_byte(receive_byte); 

	while (1) {
						
	}
	
  return 0;
}
