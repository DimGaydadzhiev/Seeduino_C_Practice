#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdlib.h>
#include <util/delay.h>

//=== Structs ===

typedef struct
{
    float Humidity;
    float Temperature;
    uint8_t checksum; //this isnt needed really
} hal_tempHumidityRead_t;

// ========================== SETUP FUNCTIONS ===================================

void hal_setupPins(void); //Setups pins for read/write

void hal_setupInterrupts(void); //Enables interrupts and tunes the system clock

void hal_setupAnalog(void); //Enables analog reading and enables ADLAR

void hal_setupSerialPort(void); //Sets up the serial port connection and BAUD rate to 9600

int uart_putchar(char c, FILE *stream);
// =========================== TOGGLE FUNCTIONS =================================

void hal_enableInterrupts(void);
//Self-explanatory
void hal_disableInterrupts(void);

void hal_ledON(void);

void hal_ledOFF(void);

void hal_buzzerON(void);

void hal_buzzerOFF(void);

// =========================== READ FUNCTIONS ===================================

bool hal_interruptHappened(void);

bool hal_readButton(void);

bool hal_lineFound(void);

void hal_getTempSensorData(hal_tempHumidityRead_t *dataName); //Calls all the hal_temp functions, places the data in a uint8_t array

static uint8_t hal_tempDataReceive(void); //Gets data from temp sensor

unsigned int hal_readLightsensor(void); //Returns ADCH, i.e. 8bit resolution.

// ========================== MISC/UTILITY FUNCTIONS =============================

void hal_ledPulse(unsigned int);

void hal_sendFloatUART(float);
void hal_sendCharUART(char); // Converts to a char array and sends it to UDR0

void hal_tempHumidityDataSend(void);
