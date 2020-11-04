#include "i2c.h"
#include "hal.h"

//I stole the code from the AVR-GCC i2cmaster library

void i2c_init(void)
{

    TWSR = 0;                                  /* no prescaler */
    TWBR = ((16000000UL / 100000UL) - 16) / 2; /* must be > 10 for stable operation */
}

/*************************************************************************
  Issues a start condition and sends address and transfer direction.
  return 0 = device accessible, 1= failed to access device
*************************************************************************/

uint8_t i2c_start(uint8_t address)
{

    // send START condition
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    // wait until transmission completed
    while ((TWCR & _BV(TWINT)) == 0)
        ;

    // check value of TWI Status Register. Mask prescaler bits.
    twst = TW_STATUS & 0xF8;
    if ((twst != TW_START) && (twst != TW_REP_START))
        return 1;

    // send device address
    TWDR = address;
    TWCR = (1 << TWINT) | (1 << TWEN);

    // wail until transmission completed and ACK/NACK has been received
    while ((TWCR & _BV(TWINT)) == 0)
        ;

    // check value of TWI Status Register. Mask prescaler bits.
    twst = TW_STATUS & 0xF8;
    if ((twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK))
        return 1;

    return 0;

} /* i2c_start */

/*************************************************************************
 Issues a start condition and sends address and transfer direction.
 If device is busy, use ack polling to wait until device is ready

 Input:   address and transfer direction of I2C device
*************************************************************************/
void i2c_start_wait(uint8_t address)
{

    while (1)
    {
        // send START condition
        TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

        // wait until transmission completed
        while ((TWCR & _BV(TWINT)) == 0)
            ;

        // check value of TWI Status Register. Mask prescaler bits.
        twst = TW_STATUS & 0xF8;
        if ((twst != TW_START) && (twst != TW_REP_START))
            continue;

        // send device address
        TWDR = address;
        TWCR = (1 << TWINT) | (1 << TWEN);

        // wail until transmission completed
        while ((TWCR & _BV(TWINT)) == 0)
            ;
        // check value of TWI Status Register. Mask prescaler bits.
        twst = TW_STATUS & 0xF8;
        if ((twst == TW_MT_SLA_NACK) || (twst == TW_MR_DATA_NACK))
        {
            /* device busy, send stop condition to terminate write operation */
            TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);

            // wait until stop condition is executed and bus released
            while (TWCR & (1 << TWSTO))
                ;

            continue;
        }
        //if( twst != TW_MT_SLA_ACK) return 1;
        break;
    }

} /* i2c_start_wait */

/*************************************************************************
 Issues a repeated start condition and sends address and transfer direction

 Input:   address and transfer direction of I2C device

 Return:  0 device accessible
          1 failed to access device
*************************************************************************/
uint8_t i2c_rep_start(uint8_t address)
{
    return i2c_start(address);

} /* i2c_rep_start */

/*************************************************************************
 Terminates the data transfer and releases the I2C bus
*************************************************************************/
void i2c_stop(void)
{
    /* send stop condition */
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);

    // wait until stop condition is executed and bus released
    while (TWCR & (1 << TWSTO))
        ;

} /* i2c_stop */

/*************************************************************************
  Send one byte to I2C device

  Input:    byte to be transfered
  Return:   0 write successful
            1 write failed
*************************************************************************/
uint8_t i2c_writeStream(uint8_t *data, uint8_t length)
{
    unsigned short int i = 0;
    while (i < length)
    {
        // send data to the previously addressed device
        TWDR = *(data + i);
        TWCR = (1 << TWINT) | (1 << TWEN);

        // wait until transmission completed
        while ((TWCR & _BV(TWINT)) == 0)
            ;

        // check value of TWI Status Register. Mask prescaler bits
        twst = TW_STATUS & 0xF8;
        i++;
        _delay_ms(5);
    }
    return 1;
} /* i2c_writeStream */

/*************************************************************************
 Read one byte from the I2C device, request more data from device

 Return:  byte read from I2C device
*************************************************************************/
uint8_t i2c_readAck(void)
{
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    while ((TWCR & _BV(TWINT)) == 0)
        ;

    return TWDR;

} /* i2c_readAck */

/*************************************************************************
 Read one byte from the I2C device, read is followed by a stop condition

 Return:  byte read from I2C device
*************************************************************************/
uint8_t i2c_readNak(void)
{
    TWCR = (1 << TWINT) | (1 << TWEN);
    while ((TWCR & _BV(TWINT)) == 0)
        ;

    return TWDR;

} /* i2c_readNak */

uint8_t i2c_write(uint8_t data)
{
    TWDR = data;
    TWCR = (TWINT << 1) | (TWEN << 1);
    while ((TWCR & _BV(TWINT)) == 0)
        ;

    return 1;
}
