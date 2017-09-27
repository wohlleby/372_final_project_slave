 //Developer: Team 212
//Purpose: Main function for the slave/pump controller

#include <Arduino.h>
#include <avr/io.h>
#include "drinks.h"
#include "serial.h"
#include "pumps.h"
#include "timer.h"
#include "cupsensor.h"


typedef enum stateType_enum{
  waitForInstruction, executeDrinkOrder
}stateType;

volatile int drinkRequested = 0;
volatile stateType state = waitForInstruction;

int** drinkList = initDrinks();

int main() {
  //Initialization:
  int drinkSelected = 0;
  initSerial();
  initTimer1();
  initPumps();
  int** drinkList = initDrinks();

  while(1) {

    delayMs(10);

     switch(state){
       
       case waitForInstruction: //Waits for a drink order from master
       drinkSelected = USART_Receive() - 'a';

       if(drinkSelected >= 0 && drinkSelected < 11){
         state = executeDrinkOrder; //execute the drink
       }

       break;

       case executeDrinkOrder: //Executes drink order

        makeDrink(drinkList[drinkSelected][0], drinkList[drinkSelected][1],
                drinkList[drinkSelected][2], drinkList[drinkSelected][3],
                drinkList[drinkSelected][4]); //send the timings for the correct drink

        state = waitForInstruction; //finished, wait for more instructions
       break;
     }
  }
}
