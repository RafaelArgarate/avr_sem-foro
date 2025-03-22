#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

int estado = 0;
int tempo = 0;

int main(void)
{
    //Config. p/ entrada
    DDRB&= ~(1<<0);

    //Pull up
    PORTB|= (1<<0);

    //Config. p/ saída
    DDRB|=(1<<1);
    DDRB|=(1<<2);
    DDRB|=(1<<3);
    DDRB|=(1<<4);
    DDRB|=(1<<5);

    //Desliga semáforos
    PORTB &= ~(1<<1);
    PORTB &= ~(1<<2);
    PORTB &= ~(1<<3);
    PORTB &= ~(1<<4);
    PORTB &= ~(1<<5);

 
    while (1){
        if(estado==0)
        {
            PORTB &= ~(1<<1);
            PORTB &= ~(1<<2);            
            PORTB|= (1<<3);
            PORTB &= ~(1<<5);
            PORTB|= (1<<4);
            tempo=4200;
            estado=1;
        }
        
        if(estado==1)
        {
            --tempo;
            _delay_ms(10);
            if ((!(PINB & (1<<PINB0))) && tempo > 1000)
            {
                tempo = 1000;
            }
            if(tempo==0)
            {
                estado=2;
            }
            
        }

        if(estado==2)
        {
            PORTB &= ~(1<<3);
            PORTB|= (1<<2);
            tempo=300;
            estado=3;
        }

        if(estado==3)
        {
            --tempo;
            _delay_ms(10);
            if(tempo==0)
            {
                estado=4;
            }
            
        }
        
        if(estado==4)
        {
            PORTB &= ~(1<<2);
            PORTB|= (1<<1);
            PORTB &= ~(1<<4);
            PORTB|=(1<<5);
            tempo=1200;
            estado=5;
        }
        
        if(estado==5)
        {
            --tempo;
            _delay_ms(10);
            if (tempo == 300)
            {
                PORTB &= ~(1<<5);
                PORTB|=(1<<4);
                _delay_ms(500);
                PORTB &= ~(1<<4);
                _delay_ms(500);
                PORTB|=(1<<4);
                _delay_ms(500);
                PORTB &= ~(1<<4);
                _delay_ms(500);
                PORTB|=(1<<4);
                _delay_ms(500);
                PORTB &= ~(1<<4);
                _delay_ms(500);
                PORTB|=(1<<4);
            }
            
            if(tempo==0)
            {
                estado=0;
            }
            
        }

        
    }
    
}
