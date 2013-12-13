#include <avr/io.h>
#define F_CPU 16000000L 
#include <util/delay.h>

#include <avr/pgmspace.h>



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

int main()
{
    char var=1;
    OCR2B = 0xFF;
    pwmInit();
    DDRD |= (1<<PD3) | (1<<PD5) | (1<<PD6);
    int flag =0;
    while(1)
    {
        while(flag ==0)
        {
            OCR2B += var;
            _delay_ms(1);
            if(OCR2B == 0xFF)
            {
                var*=-1;
            }
            if(OCR2B == 0)
            {
                flag =1;
            }
        }
        
         while(flag ==1)
        {
            OCR0A += var;
            _delay_ms(1);
            if(OCR0A == 0xFF)
            {
                var*=-1;
            }
            if(OCR0A == 0)
            {
                flag =2;
            }
        }
        
         while(flag ==2)
        {
            OCR0B += var;
            _delay_ms(1);
            if(OCR0B == 0xFF)
            {
                var*=-1;
            }
            if(OCR0B == 0)
            {
                flag =0;
            }
        }
    }
    return 0;
    
}
