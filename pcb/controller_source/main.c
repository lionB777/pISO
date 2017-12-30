/*
 * pISO.c
 *
 * Created: 12/4/2017 9:03:34 PM
 * Author : James Tate
 * Must use -Os or this will not fit in the 102
 */ 
#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/iotn102.h>
#include <util/delay.h> 
#include <avr/pgmspace.h> 

#define RST PORTA0
#define DC	PORTA1
#define CS	PORTB3

#define RST_HIGH	PORTA |= (1<<RST)
#define RST_LOW		PORTA &= ~(1<<RST)
#define DC_HIGH		PORTA |= (1<<DC)
#define DC_LOW		PORTA &= ~(1<<DC)
#define CS_HIGH		PORTB |= (1<<CS)
#define CS_LOW		PORTB &= ~(1<<CS)

#define	   BUFF_SIZE			1024
#define    SETCONTRAST			0x81
#define    DISPLAYALLON_RESUME  0xA4
#define    DISPLAYALLON			0xA5
#define    NORMALDISPLAY		0xA6
#define    INVERTDISPLAY		0xA7
#define    DISPLAYOFF			0xAE
#define    DISPLAYON			0xAF
#define    SETDISPLAYOFFSET		0xD3
#define    SETCOMPINS			0xDA
#define    SETVCOMDETECT		0xDB
#define    SETDISPLAYCLOCKDIV	0xD5
#define    SETPRECHARGE			0xD9
#define    SETMULTIPLEX			0xA8
#define    SETLOWCOLUMN			0x00
#define    SETHIGHCOLUMN		0x10
#define    SETSTARTLINE			0x40
#define    MEMORYMODE			0x20
#define    COLUMNADDR			0x21
#define    PAGEADDR				0x22
#define    COMSCANINC			0xC0
#define    COMSCANDEC			0xC8
#define    SEGREMAP				0xA0
#define    CHARGEPUMP			0x8D
#define    EXTERNALVCC			0x01
#define    SWITCHCAPVCC			0x02
#define	   LCDHEIGHT            64
#define	   LCDWIDTH				128

// change this image for the ATtiny25 since we have more memory
// since we don't have but a whole 32 bytes of SRAM, we have to do this in program memory
const uint8_t btm[] PROGMEM = {
	0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xF8, 0xFC, 0xFC, 0xFC, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE,
	0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE,
	0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE,
	0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE,
	0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE,
	0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE,
	0xFE, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60,
	0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0xE0, 0xE0, 0xE0, 0xE0, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
	0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x0F, 0x0F, 0x0F, 0xFF, 0xFF,
	0x3F, 0x1F, 0x0F, 0x0F, 0xC7, 0xC7, 0xCF, 0x8F, 0x8F, 0x9F, 0xFF, 0xFF, 0xFF, 0x3F, 0x1F, 0x1F,
	0x8F, 0x8F, 0xCF, 0xCF, 0xC7, 0xC7, 0xCF, 0xCF, 0xCF, 0x8F, 0x1F, 0x1F, 0x3F, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x7F, 0x01, 0x00, 0xFB, 0x00,
	0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x9C, 0x3E,
	0x3E, 0x3E, 0x3E, 0x3E, 0x1C, 0x80, 0x80, 0xC1, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
	0xCF, 0x8E, 0x0C, 0x1C, 0x3C, 0x38, 0x39, 0x11, 0x81, 0x83, 0xE7, 0xFF, 0xF8, 0xE0, 0xC0, 0x86,
	0x8F, 0x1F, 0x1F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x1F, 0x8F, 0x87, 0xC0, 0xE0, 0xF0, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFB, 0x00, 0x00, 0x6D, 0x00,
	0x00, 0x1F, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x61, 0x61, 0x61, 0x61, 0x61, 0x60, 0x60,
	0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7F, 0x7F, 0x7F, 0x00, 0xED, 0x00, 0x00, 0xB7, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x07, 0x0F, 0x0F, 0x17, 0x17, 0x37, 0x2F, 0x2F,
	0x4F, 0x6F, 0x2F, 0x2F, 0xAF, 0x8F, 0xAF, 0xAF, 0x2F, 0x8F, 0x8F, 0xA0, 0x20, 0x20, 0x8F, 0xAF,
	0xAF, 0x2F, 0xAF, 0x8F, 0xAF, 0xAF, 0x2F, 0x8F, 0xAF, 0xAF, 0x2F, 0xAF, 0x8F, 0xAF, 0xAF, 0x2F,
	0xAF, 0x8F, 0xAF, 0x2F, 0x2F, 0x8F, 0xAF, 0xAF, 0x2F, 0xAF, 0x8F, 0xAF, 0xAF, 0x2F, 0xAF, 0x8F,
	0xAF, 0x2F, 0x2F, 0x8F, 0xAF, 0xAF, 0x2F, 0xAF, 0x8F, 0xAF, 0xAF, 0x2F, 0x8F, 0x8F, 0xAF, 0x2F,
	0xAF, 0x8F, 0xAF, 0xAF, 0x2F, 0xAF, 0x8F, 0xAF, 0x2F, 0x2F, 0x8F, 0xAF, 0xAF, 0x2F, 0xAF, 0x8F,
	0xA7, 0xA0, 0x20, 0xBB, 0x80, 0x80, 0xED, 0x01, 0x01, 0x04, 0x05, 0x05, 0x01, 0x05, 0x04, 0x05,
	0x05, 0x01, 0x04, 0x04, 0x05, 0x01, 0x01, 0x04, 0x05, 0x05, 0x01, 0x05, 0x04, 0x04, 0x05, 0x00
	
	};

void sendSPIcommand(uint8_t data){
	CS_LOW;
	// send data
	UDR = data;
	_delay_us(25); // this can be changed since the 25 will be able to run at a higher SPI clk.
	CS_HIGH;
}

void sendSPIdata(uint8_t data){
	// send data
	UDR = data;
	while ( !(UCSRA & (1<<UDRE)));
}

void shutdownIO(){
	// release TX
	UCSRB = (0<<TXEN);
	// set all ports to input
	DDRA = 0;
	DDRB = 0;
	SMCR = 5;
}

int main(void)
{
	// set CS RST and DC to output
	DDRB |= 1<<CS;
	DDRA |= 1<<RST;
	DDRA |= 1<<DC;
	
	//set BAUD = 0
	UBRR = 0;
	// set CLK to output for master mode
	DDRB |= (1<<DDRB1);
	// Set MSPI mode of operation and SPI data mode 0. 
	UCSRC = (1<<UMSEL1) // Master SPI
		|(1<<UMSEL0);	// Master SPI
	// Enable TX 
	UCSRB = (1<<TXEN);
	// set BAUD to rate
	UBRR = 0;
	
	RST_HIGH;
	DC_HIGH;
	CS_HIGH;
	_delay_ms(1);
	RST_LOW;
	_delay_ms(10);
	RST_HIGH;
	_delay_ms(1);
	DC_LOW;
	sendSPIcommand(DISPLAYOFF);
	sendSPIcommand(SETDISPLAYCLOCKDIV);
	sendSPIcommand(0x80); // the suggested ratio 0x80
	sendSPIcommand(SETMULTIPLEX);
	sendSPIcommand(LCDHEIGHT - 1);
	sendSPIcommand(SETDISPLAYOFFSET | 0x0);
	sendSPIcommand(0x0);                                      // no offset
	sendSPIcommand(SETSTARTLINE); // line #0
	sendSPIcommand(CHARGEPUMP);
	sendSPIcommand(0x14);
	sendSPIcommand(MEMORYMODE);
	sendSPIcommand(0x00); // 0x0 act like ks0108
	sendSPIcommand(SEGREMAP | 0x1);
	sendSPIcommand(COMSCANDEC);
	sendSPIcommand(SETCOMPINS);
	sendSPIcommand(0x12);
	sendSPIcommand(SETCONTRAST);
	sendSPIcommand(0xCF);
	sendSPIcommand(SETPRECHARGE);
	sendSPIcommand(0xF1);
	sendSPIcommand(SETVCOMDETECT);
	sendSPIcommand(0x40);
	sendSPIcommand(DISPLAYALLON_RESUME);
	sendSPIcommand(NORMALDISPLAY);
	sendSPIcommand(DISPLAYON);
	sendSPIcommand(COLUMNADDR);
	sendSPIcommand(0);                 // Column start address. (0 = reset)
	sendSPIcommand(LCDWIDTH-1); // Column end address.
	sendSPIcommand(PAGEADDR);
	sendSPIcommand(0);                     // Page start address. (0 = reset)
	sendSPIcommand(7); // Page end address.
	
	// send data
	DC_HIGH;
	CS_LOW;
	uint16_t i = 0;
	while(i < BUFF_SIZE + 1){
		if(i < 256)
			sendSPIdata(0x00);
		else if(i < 896){ //640 + 256
			sendSPIdata(btm[i - 256]);
		}
		else
			sendSPIdata(0x00);
		i++;
	}
	CS_HIGH;
	while(1);
	// shutdownIO(); 
}