#include <Arduino.h>
#include "timer.h"
#include "cupsensor.h"
#include "serial.h"

void initPumps(){
  DDRA |= (1 << DDA0 | 1 << DDA1 | 1 << DDA2 | 1 << DDA3 | 1 << DDA4);
}


void makeDrink(int p0time,int p1time,int p2time, int p3time, int p4time){
  int ptimes[] = {p0time,p1time,p2time,p3time,p4time};

  //so we know which pumps are on while chekcing the cup sensor.
  int pumpsOn[] = {0,0,0,0,0};


  //sum of all time left on pumps
  int pTimeSum = p0time + p1time + p2time + p3time + p4time;
  int pMin = 1000;




  while(pTimeSum > 0) { //run until all pumps have 0 time left

    for(int i = 0; i < 5; i++){ //find the smallest non-zero time for a pump
      if((ptimes[i] < pMin) && (ptimes[i] != 0)){
        pMin = ptimes[i];
      }
    }

    while(!checkCupPlace()) { //don't start until cup placed

      USART_Transmit('s');
      delayMs(10);
    }

    USART_Transmit('r'); //cup in place begin

    //reset the checks for which pumps are on.
    pumpsOn[0] = 0;pumpsOn[1] = 0;pumpsOn[2] = 0;pumpsOn[3] = 0;pumpsOn[4] = 0;

    if(p0time != 0) {
      PORTA |= (1 << PORTA0);
      p0time -= pMin;
      pumpsOn[0] = 1;
    }
    if(p1time != 0) {
      PORTA |= (1 << PORTA1);
      p1time -= pMin;
      pumpsOn[1] = 1;
    }
    if(p2time != 0) {
      PORTA |= (1 << PORTA2);
      p2time -= pMin;
      pumpsOn[2] = 1;
    }
    if(p3time != 0) {
      PORTA |= (1 << PORTA3);
      p3time -= pMin;
      pumpsOn[3] = 1;
    }
    if(p4time != 0) {
      PORTA |= (1 << PORTA4);
      p4time -= pMin;
      pumpsOn[4] = 1;
    }

    int i = 0;

    for(i = 0; i < pMin * 1000; i++) {
      delayMs(1);

      if(checkCupPlace() == 0) { //cup was removed
          //turn off the pumps
          PORTA &= ~(1 << PORTA0 | 1 <<  PORTA1 | 1 << PORTA2 | 1 << PORTA3 | 1 <<  PORTA4);

          USART_Transmit('s'); //transmit cup has been removed to master

          while(!checkCupPlace()) {

            USART_Transmit('s');
            delayMs(10);
          }
          //cup has been placed back

          //Turn the pumps back on that are supposed to be on
          if(pumpsOn[0]) {
            PORTA |= (1 << PORTA0);
          }
          if(pumpsOn[1]) {
            PORTA |= (1 << PORTA1);
          }
          if(pumpsOn[2]) {
            PORTA |= (1 << PORTA2);
          }
          if(pumpsOn[3]) {
            PORTA |= (1 << PORTA3);
          }
          if(pumpsOn[4]) {
            PORTA |= (1 << PORTA4);
          }

          USART_Transmit('r'); //transmit cup has been replaced to master


      }
    }
    //delayS(pMin);

    PORTA &= ~(1 << PORTA0 | 1 <<  PORTA1 | 1 << PORTA2 | 1 << PORTA3 | 1 <<  PORTA4);

    pTimeSum = p0time + p1time + p2time + p3time + p4time;
  }

  USART_Transmit('t'); //send that time has finished
}

//
// void turnOnPumps(){
//   PORTA |= (1<< PORTA0);
//   for(int i = 0; i < 5; i++){
//     delayMs(1000);
//   }
//   PORTA &= ~(1 << PORTA0);
//
//   return;
// }
