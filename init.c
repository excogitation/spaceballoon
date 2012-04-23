#include <avr/io.h>
#include <avr/interrupt.h>
#ifndef F_CPU
#define F_CPU 9600000UL
#endif
#include <util/delay.h>

volatile int timer_overflow_count = 0;
volatile int timer_overflow_count_meta = 1501;

ISR(TIM0_OVF_vect) {// a timer overflow occurs 4.6 times per second
  ++timer_overflow_count;
  
  //Timelapse
  if((timer_overflow_count%22)==1) //once per ~5s
  {
    // Toggle PB0 output state
    PORTB ^= 1<<PB0;
  } else if((timer_overflow_count%22)==5)
    {
      // Toggle PB0 output state
      PORTB ^= 1<<PB0;
    }

  //Blinking leds
  if((timer_overflow_count%5)==1) //once per ~1s
  {
   // Toggle PB3 output state
   PORTB ^= 1<<PB3;
  } else if((timer_overflow_count%5)==2) //blink for ~1/5th s
    {
      // Toggle PB1 output state
      PORTB ^= 1<<PB3;
    }


  //restart recording every ~23min
  if((timer_overflow_count%44)==1) //once per ~10s
  {
    ++timer_overflow_count_meta;
      //reset timer_overflow_count after 10s -> else it happens when the 8 bit var overflows ... ~59s
    } else if((timer_overflow_count%44)==43) {
      timer_overflow_count = 0;
    }

  if(timer_overflow_count_meta>1500) {
    if((timer_overflow_count%44)==1) //once per ~10s
    {
      // Toggle PB1 output state
      PORTB ^= 1<<PB1;
    } else if((timer_overflow_count%44)==23) //pulldown button for ~5s
    {
      // Toggle PB1 output state
      PORTB ^= 1<<PB1;
      
      //reset timver_overflow_count_meta
      timer_overflow_count_meta = 0;
    }
  }
  
}

int main(void)
{
    

   // prescale timer to 1s <- whaat? gets longer and loonger
   //  TCCR0B |= (1<<CS01) | (1<<CS02);

   // prescale timer to 1/1024th of a second
    TCCR0B |= (1<<CS02) | (1<<CS00);


   // enable timer overflow interrupt
   TIMSK0 |=1<<TOIE0;
   sei();

   // Set up Port PBx mode to output
    DDRB |= _BV( PB3 );
    DDRB |= _BV( PB0 );
    DDRB |= _BV( PB1 );
    while( 1 ) { 

/*	iBlink++;
	if(iBlink==1) {
	  PORTB |=  _BV( PB3 );
	  //_delay_ms(10);
	  iBlink = 1;
	} else if(iBlink==4) {
	  PORTB &=~ _BV( PB3 );
	  //_delay_ms(10);
	  iBlink = 0;
	}
        
        
        //PORTB |=  _BV( PB1 );

        _delay_ms(50);
        //PORTB &=~ _BV( PB1 );


       // PORTB |=  _BV( PB3 );
       // _delay_ms(50);
       // PORTB &=~ _BV( PB3 );
        _delay_ms(100);
 */ 
   }

}


