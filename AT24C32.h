#include <avr/io.h>
#include "defines.h"

#define AT24C32_ADDRESS_W	0b10100000
#define AT24C32_ADDRESS_R	0b10100001

#define AT24C32_BYTES_PER_PAGE       32
#define AT24C32_BYTES_MAX            4096

void AT24C32_send_16_bit_address(uint16_t address);
void AT24C32_clear_all(void);
void AT24C32_byte_write(uint16_t address, uint8_t byte);
void AT24C32_word_write(uint16_t address, uint16_t word);
void AT24C32_ascii_sequential_write(uint16_t address, const char my_string[]);
void AT24C32_sequential_read(uint16_t address, uint16_t how_many_bytes);
uint8_t AT24C32_current_address_read(void);
uint8_t AT24C32_random_read(uint16_t address);
uint8_t * AT24C32_sequential_read(uint16_t address, uint16_t how_many_bytes);







