// Description: This file implements functions that utilize the timers
//----------------------------------------------------------------------//

#include "timer.h"
#include <Arduino.h>


/* Initialize timer 1, you should not turn the timer on here.
* You will need to use CTC mode
*/
void initTimer1(){
  //Set timer 1 to CTC:
  TCCR1A &= ~(1 << WGM10 | 1 << WGM11);
  TCCR1B &= ~(1 << WGM13);
  TCCR1B |= (1 << WGM12);

  // set clock/prescalar for timer 0 to be clk/256
 TCCR1B &= ~(1 << CS10 | 1 << CS11);
 TCCR1B |= (1 << CS12);

 OCR1AH = 0x00;
 OCR1AL = 0x40;
}

void initTimer3(){

    TCCR3B |= (1 << WGM32);
    TCCR3B &= ~(1 << CS30 | 1 << CS32 | 1 << CS31);

}

/* This delays the program an amount specified by unsigned int delay.
* Use timer 1. Keep in mind that you need to choose your prescalar wisely
* such that your timer is precise to 1 millisecond and can be used for 125
* 100 milliseconds
*/
void delayMs(unsigned int delay){
  TCNT1H = 0;
  TCNT1L = 0;

  TCCR1B &= ~(1 << CS10 | 1 << CS11);
  TCCR1B |= (1 << CS12);

  unsigned int i = 0;
  for(i =0; i < delay; i++){
    TIFR1 |= (1 << OCF1A);
    while(!(TIFR1 & (1 << OCF1A))){
    }
  }

  TCCR1B&= ~(1 << CS12);
}

void delayS(unsigned int delay) {

  unsigned int ticks = 15625*delay;

  TCNT3H = 0;
  TCNT3L = 0; //clear timer

  OCR3AH = ticks >> 8;
  OCR3AL = ticks & 0x00FF; //calculate high and low count amounts

  TCCR3B |= (1 << CS30 | 1 << CS32);
  TCCR3B &= ~(1 << CS31); //turn on the timer

  while(!(TIFR3 & (1 << OCF3A))); //do nothing until flag

  TIFR3 |= (1 << OCF3A); //clear flag
  TCCR3B &= ~(1 << CS31 | 1 << CS30 | 1 << CS32); //turn off timer

}
