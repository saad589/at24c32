#include <avr/io.h>
#include "defines.h"

void init_i2c(void);
    /* Sets pullups and initializes bus speed to 100kHz (at FCPU=8MHz) */

void i2c_wait_for_complete(void);
                       /* Waits until the hardware sets the TWINT flag */

void i2c_start(void);
                               /* Sends a start condition (sets TWSTA) */
void i2c_stop(void);
                                /* Sends a stop condition (sets TWSTO) */

void i2c_send(uint8_t data);
                   /* Loads data, sends it out, waiting for completion */

uint8_t i2c_read_ack(void);
              /* Read in from slave, sending ACK when done (sets TWEA) */
uint8_t i2c_read_no_ack(void);
              /* Read in from slave, sending NOACK when done (no TWEA) */
