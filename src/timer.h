// Description: This file describes functions used by the timer
//----------------------------------------------------------------------//

#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>

void initTimer1();
void initTimer3();
void delayMs(unsigned int delay);
void delayS(unsigned int delay);

#endif
