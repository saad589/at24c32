#include "i2c.h"

void init_i2c(void) {
  TWBR = 32;
  TWCR |= (1 << TWEN);
}

void i2c_wait_for_complete(void) {
  loop_until_bit_is_set(TWCR, TWINT);
}

void i2c_start(void) {
  TWCR = (_BV(TWINT) | _BV(TWEN) | _BV(TWSTA));
  i2c_wait_for_complete();
}

void i2c_stop(void) {
  TWCR = (_BV(TWINT) | _BV(TWEN) | _BV(TWSTO));
}

uint8_t i2c_read_ack(void) {
  TWCR = (_BV(TWINT) | _BV(TWEN) | _BV(TWEA));
  i2c_wait_for_complete();
  return (TWDR);
}

uint8_t i2c_read_no_ack(void) {
  TWCR = (_BV(TWINT) | _BV(TWEN));
  i2c_wait_for_complete();
  return (TWDR);
}

void i2c_send(uint8_t data) {
  TWDR = data;
  TWCR = (_BV(TWINT) | _BV(TWEN));
  i2c_wait_for_complete();
}
