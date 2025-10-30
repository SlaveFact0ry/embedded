#define F_CPU
#include <avr/io.h>

#include <util/delay.h>

#define FOSC 16000000
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void USART_Init(unsigned int ubrr);

#define sbi(PORTX, BitX) (PORTX |= (1 <<BitX))
#define cbi(PORTX, BitX) (PORTX &= ~(1 << BitX))

unsigned char USART_Rx(void){
	while( !(UCSR0A & (1 << RXC0)));
	return UDR0;
}

void UART_TX_CH(char c){
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = c;
}
int main(void){
	unsigned char data;
	USART_Init(MYUBRR);
	
	while (1){
		data = USART_Rx();
		
		UART_TX_CH(data);
		_delay_ms(200);
		
	}
}
void USART_Init(unsigned int ubrr){
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;
	
	UCSR0B = (1 << RXEN0)|(1 << TXEN0);
	
	UCSR0C = (0 << USBS0)|(3 << UCSZ00);
}
