#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>

#include "usart.h"

#include "i2c.h"
#include "AT24C32.h"

#define DELAY_TIME 100

int main(void) {
	
	uint16_t address = 0;
	uint16_t how_many_bytes = 569;
	print_string("ascii art\r\n");	

	clock_prescale_set(clock_div_1);
	init_usart();
	
	init_i2c();

	AT24C32_ascii_sequential_write(address, "                                     /$$ /$$$$$$$   /$$$$$$   /$$$$$$ \n                                    | $$| $$____/  /$$__  $$ /$$__  $$\n  /$$$$$$$  /$$$$$$   /$$$$$$   /$$$$$$$| $$      | $$  \\ $$| $$  \\ $$\n /$$_____/ |____  $$ |____  $$ /$$__  $$| $$$$$$$ |  $$$$$$/|  $$$$$$$\n|  $$$$$$   /$$$$$$$  /$$$$$$$| $$  | $$|_____  $$ >$$__  $$ \\____  $$\n \\____  $$ /$$__  $$ /$$__  $$| $$  | $$ /$$  \\ $$| $$  \\ $$ /$$  \\ $$\n /$$$$$$$/|  $$$$$$$|  $$$$$$$|  $$$$$$$|  $$$$$$/|  $$$$$$/|  $$$$$$/\n|_______/  \\_______/ \\_______/ \\_______/ \\______/  \\______/  \\______/ \n\r");
	
	_delay_ms(DELAY_TIME);
	
	AT24C32_sequential_read(address, how_many_bytes);

	while (1) {
		
	}
  
	return 0;
}
