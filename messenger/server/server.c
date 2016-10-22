#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

unsigned char re,flag=0,s=0;
int main()
{
DDRA=0x00;
DDRC=0xff;
DDRB=0xff;
PORTC=0x05;


int ubrr=25;
sei();
UBRRH = (unsigned char)(ubrr>>8);
UBRRL = (unsigned char)ubrr;
/* Enable receiver and transmitter */
UCSRB = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE);
/* Set frame format: 8data, 2stop bit */
UCSRC = (1<<USBS)|(3<<UCSZ0)|(1<<URSEL);
PORTA=0x00;
while(1)
{
}
return 0;
}
ISR(USART_RXC_vect)
{
re=UDR;
if(re>0 && re<4)
{
PORTC=re-1;
re=0;
}
else
{
while (!( UCSRA & (1<<UDRE)));
UDR=re;
}
}
