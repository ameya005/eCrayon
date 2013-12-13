//AVR program for eCrayon


#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#define F_CPU 16000000L 
#define digitalPinToTimer(P) ( pgm_read_byte( digital_pin_to_timer_PGM + (P) ) )
#define R 3
#define G 5
#define B 6



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
    
    //DDRD |= (1<<PD5) | (1<<PD6) | (1<<PD7);
    //Input pin for tactile switch
    DDRB |= (1<<PB0);
    //R, G and B pins
    PORTB |= (1<<PD3) | (1<<PD5) | (1<<PD6);
    int count=0;
    int a,b;
    
    pwmInit();
    while(1)
    {
        /*****code for reading switch**********/
        if(~(PINB & (1<<0)))
        {
            _delay_ms(5);
            while(~(PINB & (1<<0)));
            count++;
            if( count > 7)
                count =0;
        }
        
        switch(count)
        {
            case 0:
                analogWrite(R,255);
                PINB |= (1<<G);
                PINB |= (1<<B);
                break;
            case 1:
                PINB |= (1<<R);
                PINB |= (1<<B);
                analogWrite(G,255);
                break;
            case 2:   
                PINB |= (1<<R);
                PINB |= (1<<G);
                analogWrite(B,255);
                break;
            case 3:
                analogWrite(R,175);
                analogWrite(G,45);          
                analogWrite(B,11);
                break;
            case 4:
                analogWrite(R,255);
                analogWrite(G,0);
                analogWrite(B,255);
                break;
            case 5:
                analogWrite(R,15);
                analogWrite(G,215);
                analogWrite(B,255);
                break;
            case 6:
                analogWrite(R,255);
                analogWrite(G,155);
                analogWrite(B,128);  
                break;
            case 7:
                PIND |= (1<<R);
                PIND |= (1<<G);
                PIND |= (1<<B);
                break;
        }
            
        
    }
    
    return 0;
   
}
