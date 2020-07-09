#include <avr/io.h>

#include <util/setbaud.h>

#include "usart.h"

void init_usart(void) {
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
	
#if USE_2X
	UCSR0A |= (1 << U2X0);
#else
	UCSR0A &= ~(1 << U2X0);
#endif
	
	UCSR0B = (1 << TXEN0) | (1 << RXEN0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
} 

void transmit_byte(uint8_t my_byte) {
	loop_until_bit_is_set(UCSR0A,UDRE0);
	UDR0 = my_byte;
}

uint8_t receive_byte(void) {
	loop_until_bit_is_set(UCSR0A,RXC0);
	return UDR0;
}

void print_string(const char my_string[]) {
	uint8_t i = 0;
	while(my_string[i]) {
		transmit_byte(my_string[i]);
		i++;
	}
}

void print_byte(uint8_t byte) {
              /* Converts a byte to a string of decimal text, sends it */
  transmit_byte('0' + (byte / 100));                        /* Hundreds */
  transmit_byte('0' + ((byte / 10) % 10));                      /* Tens */
  transmit_byte('0' + (byte % 10));                             /* Ones */
}

void print_word(uint16_t word) {
  transmit_byte('0' + (word / 10000));                 /* Ten-thousands */
  transmit_byte('0' + ((word / 1000) % 10));               /* Thousands */
  transmit_byte('0' + ((word / 100) % 10));                 /* Hundreds */
  transmit_byte('0' + ((word / 10) % 10));                      /* Tens */
  transmit_byte('0' + (word % 10));                             /* Ones */
}