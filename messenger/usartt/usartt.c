#include<avr/io.h>
#include<util/delay.h>
#include<avr/elcd.h>
#include<avr/keypad.h>
#include<avr/interrupt.h>
#include<stdlib.h>
#define cid 8;
void uart_init();
void clera();
void clerb();
unsigned char re=0,ky=0,i=0,ct[10],j=0,x=0;
unsigned char text[20],buffer[10][20];
int main()
{
DDRB=0xff;
sei();
uart_init();
keypad_init('A');
lcd_init('C');
lcom(0x0c);
lxy(1,1);
lmove("      Messenger By G Saikiran        ",95);
while (1)
{
PORTB=0x00;
ky=getkey();
if(ky>47 && ky < 58 && i<12)
{
if(i==0)
lcom(0x01);
i=re;
ldata(ky);
text[i++]=ky;
ky=0;
re=i;
}
else if(ky=='C')
{
lcom(0x01);
clera();
re=0;
}
else if(ky=='=')
{
PORTB=0xff;
text[re]=cid;
if(i==0) 
lcom(0x01);
i=0;
if(text[0]>48 && text[0]<52)
text[0]=(text[0]&0x0f);
else
{lxy(1,2);
lprint("Wrong ID ! ");
}
while(i<12)
{while (!( UCSRA & (1<<UDRE)));
UDR=text[i++];
}
if(text[0]>0 && text[0]<4 )
{
lxy(1,2);
lprint("Sent !! ");
lxy(1,1);
}

clera();
re=0;
i=0;
}
if(ky=='*')
{
x--;
if(x>=0 && x<10)
{
lcom(0x01);
lprint(buffer[x]);
i=0;
lxy(1,2);
ldata(0x30+ct[x]);
}
else
lcom(0x01);

}
if(ky=='+')
{
lcom(0x01);
lprint(buffer[j-1]);
i=0;
lxy(1,2);
ldata(0x30+ct[j-1]);
x=j-1;
}
}
return 0;
}

ISR(USART_RXC_vect)
{
if(i==0)
clerb();
buffer[j][i]=UDR;
if(buffer[j][i]>5 && buffer[j][i]<10)
{ct[j]=buffer[j][i];
ct[j]=(ct[j]+4)-9;
}
i++;
if(i==11)
{i=0;
x=j;
j++;
}
}
void uart_init()
{
int ubrr=25;
unsigned char rec;
UBRRH = (unsigned char)(ubrr>>8);
UBRRL = (unsigned char)ubrr;
/* Enable receiver and transmitter */
UCSRB = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE);
/* Set frame format: 8data, 2stop bit */
UCSRC = (1<<USBS)|(3<<UCSZ0)|(1<<URSEL);
}
void clera()
{
i=0;
while(i<12)
text[i++]=0;
i=0;
}
void clerb()
{
i=0;
while(i<13)
buffer[j][i++]=0;
i=0;
}
