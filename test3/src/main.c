#include "hal/i2c.h"
#include "hal/hal.h"
#include "hal/lcd.h"

static FILE uartStdOut = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

int main(void)
{
    hal_setupSerialPort();

    uint8_t zeal = 0x01;
    uint8_t *zealPtr = &zeal;
    i2c_start(0x4C | 0);
    _delay_ms(10);
    if (i2c_writeStream(zealPtr, 1))
        fprintf(&uartStdOut, "failure");

    while (true)
    {
        fprintf(&uartStdOut, "Test Value is: 15");
        _delay_ms(1000);
    }
}
