// Description: This file implements the initialization of an external
// switch.
//----------------------------------------------------------------------//

#include "cupsensor.h"
#include <avr/io.h>
#include "timer.h"
#include <Arduino.h>
/*
 * Initializes pull-up resistor on PB3 and sets it into input mode
 */
void initSwitchPB1(){
  PORTB |= (1 << PORTB2);
  DDRB &= ~(1 << DDB2);
}

int checkCupPlace(){
  //  Serial.begin(9600);
    //delayMs(100);
    if(PINB & (1 << PINB2)) {
      //delayMs(250);
      return 0; // if no cup  return 0
    }//else if (!(PINB & (1 << PINB1))) {
    else {
       //delayMs(250);
        return 1;// return 1 cup exist.
    }
    //return 0;
}
