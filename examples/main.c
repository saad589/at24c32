#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>

#include "defines.h"
#include "usart.h"

#include "i2c.h"
#include "AT24C32.h"

#define DELAY_TIME 1000

int main(void) {
	uint16_t address = 0;
	uint16_t how_many_bytes = 569;


	clock_prescale_set(clock_div_1);
	init_usart();
	print_string("Hello World!\r\n");
	print_string("What a nice day!\r\n");
	
	init_i2c();

//	uint16_t address = 0x0fff; // the very last byte
//	uint8_t receive_byte; // can grab both int and ascii

//	char send_byte = 's'; // ascii
//	uint8_t send_byte = 39;	// int

//	AT24C32_byte_write(address,byte);
//	receive_byte = AT24C32_random_read(address);

//	print_byte(receive_byte); // if int
//	transmit_byte(receive_byte); // if ascii


//	AT24C32_clear_all();
	
 
//	AT24C32_ascii_sequential_write(address, "                                     /$$ /$$$$$$$   /$$$$$$   /$$$$$$ \n                                    | $$| $$____/  /$$__  $$ /$$__  $$\n  /$$$$$$$  /$$$$$$   /$$$$$$   /$$$$$$$| $$      | $$  \\ $$| $$  \\ $$\n /$$_____/ |____  $$ |____  $$ /$$__  $$| $$$$$$$ |  $$$$$$/|  $$$$$$$\n|  $$$$$$   /$$$$$$$  /$$$$$$$| $$  | $$|_____  $$ >$$__  $$ \\____  $$\n \\____  $$ /$$__  $$ /$$__  $$| $$  | $$ /$$  \\ $$| $$  \\ $$ /$$  \\ $$\n /$$$$$$$/|  $$$$$$$|  $$$$$$$|  $$$$$$$|  $$$$$$/|  $$$$$$/|  $$$$$$/\n|_______/  \\_______/ \\_______/ \\_______/ \\______/  \\______/  \\______/ \n\r");
	

	_delay_ms(DELAY_TIME);
	
	AT24C32_sequential_read(address, how_many_bytes);

	_delay_ms(DELAY_TIME);
	

  while (1) {
                        
/* 
    printString("\r\n---AT24C32---\r\n");
    printString("Address\tValue\r\n");

    for (i = 0; i < 10; i++) {  //print out first ten bytes of memory
      printString("  ");
      printByte(i);
      printString("     ");
      printByte(EEPROM_readByte(i));
      printString("\r\n");
    }
    printString(" [e] to erase all memory\r\n");
    printString(" [w] to write byte to memory\r\n\r\n");

    switch (receiveByte()) {
    case 'e':
      printString("Clearing EEPROM, this could take a few seconds.\r\n");
      EEPROM_clearAll();
      break;
    case 'w':
      printString("Which memory slot would you like to write to?\r\n");
      address = getNumber();
      printString("\r\nWhat number would you like to store there?\r\n");
      i = getNumber();
      EEPROM_writeByte(address, i);
      printString("\r\n");
      break;
    default:
      printString("What??\r\n");
    }
 */

  }
  return 0;
}
