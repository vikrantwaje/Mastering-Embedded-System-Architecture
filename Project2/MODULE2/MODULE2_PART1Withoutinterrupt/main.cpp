/*-----------------------------------------------------------------------------------------------------------------------------------*/
 /* 0.Documentation section
  -----------------------------------------------------------------------------------------------------------------------------------

  @file-main.cpp

 @brief: This file contains program to turn the internal and external LED of STM32F401 ON/OFF

 @author: Vikrant Waje and Michelle Russell

 @date:27 October 2017


 */

/*------------------------------------------------------------------------------------------------------------------------------------*/
/*1. Preprocessor Directives*/
#include "mbed.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*2. Defining BUS interface*/

BusIn inbus(PA_10,PB_3,PB_5,PB_4);
BusOut outbusi(LED1);
BusOut outbuse(PB_0);

/*------------------------------------------------------------------------------------------------------------------------------------*/
/*
  @brief: Control the LED of STM32F401 without any interrupt

  Turning ON/OFF the internal and external LED of STM32F401

 @param: None

 @return: None
 */
/*-----------------------------------------------------------------------------------------------------------------------------*/

int main() {
  while(1) {
    if (inbus==0x1) { //If switch 1 is pressed, turn the internal LED ON
      outbusi=(1<<0);

    }
    else if(inbus==0x2){
        outbusi=(0<<0); //If switch 2 is pressed, turn the internal LED OFF
        }

        else if(inbus==0x4){
        outbuse=(1<<0); // If switch 3 is pressed, turn the external LED ON
        }

        else if(inbus==0x8){

        outbuse=(0<0);  //If switch 4 is pressed, turn the external LED OFF
        }
  }
}
