#include <util/delay.h>
#include "AT24C32.h"
#include "usart.h"

#include "i2c.h"

void AT24C32_send_16_bit_address(uint16_t address) {
  i2c_send((uint8_t) (address >> 8));    /* most significant byte */
  i2c_send((uint8_t) address);          /* least significant byte */
}

void AT24C32_clear_all(void) {
	uint8_t i;
	uint16_t page_address = 0;
	i2c_start();
	i2c_send(AT24C32_ADDRESS_W);
	while (page_address < AT24C32_BYTES_MAX) {
		i2c_start();
		i2c_send(AT24C32_ADDRESS_W);
		AT24C32_send_16_bit_address(page_address);
		for (i = 0; i < AT24C32_BYTES_PER_PAGE; i++) {
			i2c_send(255);
		}
		i2c_stop();
		_delay_ms(20); // write cycle time 
		page_address += AT24C32_BYTES_PER_PAGE;
	}
	i2c_stop();
}

void AT24C32_byte_write(uint16_t address, uint8_t byte) {
	i2c_start();
	i2c_send(AT24C32_ADDRESS_W);
	AT24C32_send_16_bit_address(address);
	i2c_send(byte);
	i2c_stop();
	_delay_ms(20); // write cycle time
}

void AT24C32_word_write(uint16_t address, uint16_t word) {
	i2c_start();
	i2c_send(AT24C32_ADDRESS_W);
	AT24C32_send_16_bit_address(address);
	i2c_send((uint8_t) (word >> 8));
	i2c_send((uint8_t) word);
	i2c_stop();
	_delay_ms(20); // write cycle time
}

/* void AT24C32_page_write(uint16_t address, const uint8_t my_page[]) {
	if ((address % AT24C32_BYTES_PER_PAGE) == 0) {
		i2c_start();
		i2c_send(AT24C32_ADDRESS_W);
		AT24C32_send_16_bit_address(address);
		for (i = 0; i < AT24C32_BYTES_PER_PAGE; i++) {
			i2c_send(my_page[i]);
		}
		i2c_stop();		
	}
	else {
		print_string("Invalid page address! Must be a multiple of 32.\r\n");
	}	
} */

void AT24C32_ascii_sequential_write(uint16_t address, const char my_string[]) {
	uint32_t i = 0;
	i2c_start();
	i2c_send(AT24C32_ADDRESS_W);
	AT24C32_send_16_bit_address(address);
	while (my_string[i]) {
		if ((i > 0) & ((i % AT24C32_BYTES_PER_PAGE) == 0)) {
			address += AT24C32_BYTES_PER_PAGE;
			i2c_stop();
			_delay_ms(20); // write cycle time 
			i2c_start();
			i2c_send(AT24C32_ADDRESS_W);
			AT24C32_send_16_bit_address(address);
			i2c_send(my_string[i]);
			i++;
		}
		else {
			i2c_send(my_string[i]);
			i++;
		}
	}
	i2c_stop();
	_delay_ms(20); // write cycle time 
}

uint8_t AT24C32_current_address_read(void) {
	uint8_t byte;
	i2c_start();
	i2c_send(AT24C32_ADDRESS_R);
	byte = i2c_read_no_ack();
    i2c_stop();	
	return (byte);
}

uint8_t AT24C32_random_read(uint16_t address) {
	uint8_t byte;
	i2c_start();
	i2c_send(AT24C32_ADDRESS_W);
	AT24C32_send_16_bit_address(address);
	i2c_start();
	i2c_send(AT24C32_ADDRESS_R);
	byte = i2c_read_no_ack();
    i2c_stop();	
	return (byte);
}

/* 
C programming does not allow to return an entire array as an argument to a function. 
However, you can return a pointer to an array by specifying the array's name without an index.
Second point to remember is that C does not advocate to return the address of a local variable 
to outside of the function, so you would have to define the local variable as static variable.
Here I cannot use static because storage size of 'byte' isn't constant. But it compiles with 
an warning. However, if I call this function, the warning disappears.

uint8_t * AT24C32_sequential_read(uint16_t address, uint16_t how_many_bytes) {
	uint16_t i;
	uint8_t byte[how_many_bytes];
	i2c_start();
	i2c_send(AT24C32_ADDRESS_W);
	AT24C32_send_16_bit_address(address);
	i2c_start();
	i2c_send(AT24C32_ADDRESS_R);
	for (i = 0; i < how_many_bytes; i++) {
		if (i == (how_many_bytes - 1)){
			byte[i] = i2c_read_no_ack();
		}
		else {
			byte[i] = i2c_read_ack();
		}		
	}
	i2c_stop();	
	return (byte);
}

Now inside main.c, 

	uint16_t address = 0;
	uint16_t how_many_bytes = 569;
	
	uint16_t i;
	uint8_t *p;
	
	p = AT24C32_sequential_read(address, how_many_bytes);
	for ( i = 0; i < how_many_bytes; i++ ) {
		transmit_byte(*(p + i));
	}

This function can do only so much because m168 has only got 2KBytes of internal SRAM and 
I can at best read 900-1000 bytes/character off of the i2c memory, depending on what else is running, 
before the MCU runs off its RAM memory.

However, an easy solution can be made: dont output anything, just print from within...
*/
 
void AT24C32_sequential_read(uint16_t address, uint16_t how_many_bytes) {
	uint16_t i;
	i2c_start();
	i2c_send(AT24C32_ADDRESS_W);
	AT24C32_send_16_bit_address(address);
	i2c_start();
	i2c_send(AT24C32_ADDRESS_R);
	for (i = 0; i < how_many_bytes; i++) {
		if (i == (how_many_bytes - 1)){
			transmit_byte(i2c_read_no_ack());
		}
		else {
			transmit_byte(i2c_read_ack());
		}		
	}
	i2c_stop();	
}