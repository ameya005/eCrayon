//AVR program for eCrayon


#include <avr/io.h>
#define F_CPU 16000000L 
#include <util/delay.h>

#include <avr/pgmspace.h>

//#define digitalPinToTimer(P) ( pgm_read_byte( digital_pin_to_timer_PGM + (P) ) )
#define R 6
#define G 5
#define B 3



void pwmInit()
{
    
    DDRD |= (1 << PD3) | (1<<PD5) | (1<<PD6);
    /*********Timer 2B **********************/
    TCCR2A = 0x00;
    TCCR2B =0;
    OCR2B=0;
    
    TCCR2A |= (1<<COM2A1) | (1<<COM2B1);
    TCCR2A |= (1<<WGM21) | (1<<WGM20);
    TCCR2B |= (1<<CS20);
   /******************************************/
   /*****************Timer 0A*****************/
   
   TCCR0A = 0;
   TCCR0B =0;
   
   OCR0A=0;
   
   TCCR0A |= (1<<COM0A1) | (1<<COM0B1);
   TCCR0A |= (1<<WGM01) | (1<<WGM00);
   TCCR0B |= (1<<CS00);
   
   
   
   /******************************************/
}


void analogWrite(uint8_t pin, uint8_t value)
{
    switch(pin)
    {
        case 3:
            OCR2B = value;
            break;
        case 5:  
            OCR0B = value;
            value;
        case 6:
            OCR0A = value;
        default:
            OCR0A = 0x00;
            OCR0B = 0x00;
            OCR2B = 0x00;
    }       
            
    
}
int main()
{
    
    DDRD |= (1<<PD3) | (1<<PD5) | (1<<PD6);
    //Input pin for tactile switch
    DDRB &= ~(1<<PB0);
    //R, G and B pins
    PORTB |= (1<<PB0);
    int count=0;
    int a,b;
    
    //pwmInit();
    while(1)
    {
        if(!(PINB & (1<<PB0)))
        {
            _delay_ms(40);
            while(!(PINB & (1<<PB0)));
            count++;
            if( count > 7)
                count =0;
        }
        
        switch(count)
        {
            case 0:
                PORTD |= (1<<R);
                PORTD &= ~(1<<G);
                PORTD &= ~(1<<B);
                
                break;
            case 1:
                PORTD &= ~(1<<R);
                PORTD &= ~(1<<B);
                PORTD |= (1<<G);
                
                break;
            case 2:   
                PORTD &= ~(1<<R);
                PORTD &= ~(1<<G);
                PORTD |= (1<<B);
               
                break;
            case 3:
                PORTD |= (1<<R);
                PORTD |= (1<<G);
                PORTD &= ~(1<<B);
                
                break;
            case 4:
                PORTD |= (1<<R);
                PORTD |= (1<<B);
                PORTD &= ~(1<<G);
               
                break;
            case 5:
                PORTD |= (1<<G);
                PORTD |= (1<<B);
                PORTD &= ~(1<<R);
                
                break;
            case 6:
                PORTD |= (1<<R);
                PORTD |= (1<<G);
                PORTD |= (1<<B);
               
                break;
            case 7:
                PORTD &= ~(1<<R);
                PORTD &= ~(1<<G);
                PORTD &= ~(1<<B);
                
               
                break;
        }
            
        
    }
    
    return 0;
   
}
