#ifndef BAUD
#define BAUD 9600
#endif

void init_usart(void);

void transmit_byte(uint8_t my_byte);
uint8_t receive_byte(void);

void print_string(const char my_string[]);


void print_byte(uint8_t byte);
                  /* Prints a byte out as its 3-digit ascii equivalent */
void print_word(uint16_t word);
        /* Prints a word (16-bits) out as its 5-digit ascii equivalent */