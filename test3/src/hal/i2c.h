#include <inttypes.h>
#include <util/twi.h>

uint8_t twst;

uint8_t i2c_start(uint8_t);

void i2c_init(void);

void i2c_start_wait(uint8_t);

uint8_t i2c_rep_start(uint8_t);

void i2c_stop(void);

uint8_t i2c_writeStream(uint8_t *, uint8_t);

uint8_t i2c_readAck(void);

uint8_t i2c_readNak(void);

uint8_t i2c_write(uint8_t);
