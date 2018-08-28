 /* 0.Documentation section
  -----------------------------------------------------------------------------------------------------------------------------------

  @file-main.cpp

 @brief: Using Tactile switches to turn the LED ON/OFF using interrupt
        BUTTON 1 turns internal LED ON
        BUTTON 2 turns internal LED OFF
        BUTTON 3 turns external LED ON
        BUTTON 1 turns external LED OFF

 @author: Vikrant Waje and Michelle Russell

 @date:30 October 2017
 
    
 */

/*------------------------------------------------------------------------------------------------------------------------------------*/
/*1. Preprocessor Directives*/
#include "mbed.h"

/*----------------------------------------------------------------------------------------------------------------------------------------*/


DigitalOut led1(LED1);  //Internal LED
DigitalOut led2(PB_0);  //External LED


InterruptIn buttonpress1(PA_10);// Button 1
InterruptIn buttonpress2(PB_3); // Button 2
InterruptIn buttonpress3(PB_5);  //Button 3
InterruptIn buttonpress4(PB_4);  //Button 4
/*------------------------------------------------------------------------------------------------------------------------------------*/
/*Defining Interrupt Handler for each of the Button*/
//Handler for button 1
void B1_ISR(){
   led1=1; 
    
    }
// Handler for button 2
void B2_ISR(){
   led1=0; 
    
    }
// Handler for button 3
    void B3_ISR(){
   led2=1; 
    
    }
//  Handler for button 4
    void B4_ISR(){
   led2=0; 
    
    }
/*--------------------------------------------------------------------------------------------------------------------------------------*/

/*
  @brief: Turning the LED ON and OFF using interrupt 

  Interrupt handler is invoked when each of the button is pressed

 @param: None

 @return: None
 */
/*-----------------------------------------------------------------------------------------------------------------------------*/ 
        
int main() {
   //

    buttonpress1.fall(&B1_ISR);//CORRESPONDING TO BUTTON 1 ISR
    __wfi() ;
    buttonpress2.fall(&B2_ISR);//CORRESPONDING TO BUTTON 2 ISR
    __wfi() ;
    buttonpress3.fall(&B3_ISR);//CORRESPONDING TO BUTTON 3 ISR
    __wfi() ;
    buttonpress4.fall(&B4_ISR);//CORRESPONDING TO BUTTON 4 ISR
    __wfi() ;

}
