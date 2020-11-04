#include "hal.h"

#define UNUSED(x) (void)(x)
#define BRC ((16000000 / 16 / 9600) - 1) //BAUD rate for the serial port.

//=== Variables ===

static bool hasInterrupted = false;
static uint8_t funcOutput = 0;

//===================================== HAL FUNCTIONS =====================================

//=== Setup for pins ===

void hal_setupPins(void)
{

    //This is in-built LED
    DDRB |= _BV(DDB5);

    //This is for Grove D5- Tilt Switch
    DDRD |= _BV(DDD5);  //<-- Write
    DDRD &= ~_BV(DDD6); //<--Read

    //This is for Grove D7- Buzzer
    DDRD |= _BV(DDD7);

    //This is for Grove D3- Line Finder
    DDRD &= ~_BV(DDD3);
}
void hal_setupAnalog(void)
{
    //Enables ADLAR i.e. saves the last 8 bits in ADCH and sets the ref values to VCC and GND
    ADMUX |= (1 << 5) | (1 << 6);

    //Bit 7 enables ADC, bit 2 sets the prescaler factor to 16
    ADCSRA |= (1 << 7) | (1 << 2);

    //DIDR0 sets pins A0 and A1 to be analog pins (Im unsure which I'll be using so I enabled both)
    DIDR0 |= (1 << 0) | (1 << 2);
}

//=== Interrupts ===

void hal_setupInterrupts(void)
{
    OCR1A = (F_CPU >> 10); //Sets the amount of ticks to pass before we get an interrupt

    TCCR1B = 0x00;

    TCCR1A |= (1 << WGM12); // Sets the mode to CTC.

    TCCR1A |= (1 << CS12) | (1 << CS10); // Set the prescaler to /1024

    TIMSK1 |= (1 << OCIE1A); //Enables thes OCIE1A interrupt vector for the ISR
}

bool hal_interruptHappened(void)
{

    bool ret = hasInterrupted;
    hasInterrupted = false;
    return ret;
}

void hal_enableInterrupts(void)
{

    sei();
}

void hal_disableInterrupts(void)
{

    cli();
}

ISR(TIMER1_COMPA_vect)
{
    hasInterrupted = true;
}

//=== Serial port ===

void hal_setupSerialPort(void)
{

    UBRR0H = (BRC >> 8); //Sets BAUD rate in UBRR0
    UBRR0L = BRC;        //Sets BAUD rate in UBRR0

    UCSR0B = (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); //Sets the dataframe to 8 bits
}

void hal_sendFloatUART(float sentChar)
{
    char tempArray[5];
    itoa(sentChar, tempArray, 10);

    for (int i = 0; i < 5; i++)
    {
        UDR0 = tempArray[i];
    }
}

void hal_sendCharUART(char sentChar)
{
    UDR0 = sentChar;
}

int uart_putchar(char c, FILE *stream)
{

    if (c == '\n')
        uart_putchar('\r', stream);
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;
    return 0;
}

//=== Temp/Humidity Sensor ===

static void hal_tempRequest(void) //Microcontroller send start pulse/request
{
    DDRD |= _BV(DDD7);
    PORTD &= ~_BV(PORTD7); //Set to LOW
    _delay_ms(20);
    PORTD |= _BV(PORTD7); //Set to HIGH
}

static void hal_tempResponse(void)
{
    DDRD &= ~_BV(PORTD7);
    while (PIND & _BV(PORTD7))
        ;
    while ((PIND & (_BV(PORTD7))) == 0)
        ;
    while (PIND & (_BV(PORTD7)))
        ;
}

static uint8_t hal_tempDataReceive(void)
{

    for (int q = 0; q < 8; q++)
    {
        while ((PIND & (_BV(PORTD7))) == 0)
            ; // check received bit 0 or 1
        _delay_us(30);
        if (PIND & (_BV(PORTD7)))                    // if high pulse is greater than 30ms
            funcOutput = (funcOutput << 1) | (0x01); // then its logic HIGH
        else                                         // otherwise its logic LOW
            funcOutput = (funcOutput << 1);
        while (PIND & _BV(PORTD7))
            ;
    }

    return funcOutput;
}

void hal_getTempSensorData(hal_tempHumidityRead_t *humidityData)
{
    uint8_t tempByteH, tempByteL, humByteH, humByteL;

    hal_tempRequest();
    hal_tempResponse();

    humByteH = hal_tempDataReceive(); //This is for the 1st humidity byte (40,50,60 etc.)
    humByteL = hal_tempDataReceive(); //This is for the 2nd humidity byte (.4, .5, .6 etc.)

    tempByteH = hal_tempDataReceive(); //This is the 1st temperature byte, same as above
    tempByteL = hal_tempDataReceive(); //This is the 2nd temperature byte, same as above

    humidityData->checksum = hal_tempDataReceive();

    humidityData->Humidity = (float)humByteH + (float)humByteL / 10.0;
    humidityData->Temperature = (float)tempByteH + (float)tempByteL / 10.0;
}

//=== Light Sensor ===

unsigned int hal_readLightsensor(void)
{
    //It should be reading pin ADC0 as all of the MUX pins are 0s

    ADCSRA = ADCSRA | (1 << ADSC); //Starts conversion

    while (ADCSRA & (1 << ADSC))
        ;

    return ADCH;
}

//=== LED ===
void hal_ledON(void)
{

    PORTB |= _BV(PORTB5);
}

void hal_ledOFF(void)
{

    PORTB &= ~_BV(PORTB5);
}

void hal_ledPulse(unsigned int Pulse)
{
    hal_ledON();

    while (Pulse--)
    {
        _delay_ms(10);
    }

    hal_ledOFF();
    _delay_ms(5);
}

//=== Buzzer ===
void hal_buzzerON(void)
{

    PORTD |= _BV(PORTD7);
}

void hal_buzzerOFF(void)
{

    PORTD &= ~_BV(PORTD7);
}

//=== Button ===
bool hal_readButton(void)
{

    bool check = PIND & (1 << PIND6);

    return check;
}

//=== Line Finder ===

bool hal_lineFound(void)
{

    bool check = PIND & (1 << PIND3);

    return check;
}
