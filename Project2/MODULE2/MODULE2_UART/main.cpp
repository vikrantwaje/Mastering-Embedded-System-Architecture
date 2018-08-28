/* 0.Documentation section
  -----------------------------------------------------------------------------------------------------------------------------------

  @file-main.cpp

 @brief: Print text to the PC via UART protocol

 @author: Vikrant Waje and Michelle Russell

 @date:31 October 2017
 
 Input: None
 
 Output: PC terminal
    
 */

/*------------------------------------------------------------------------------------------------------------------------------------*/
 /*1. Preprocessor Directives*/

#include "mbed.h"

 /*------------------------------------------------------------------------------------------------------------------------------------*/
 // Serial tx, rx connected to the PC via an USB cable
 
Serial pc(SERIAL_TX, SERIAL_RX);
/*--------------------------------------------------------------------------------------------------------------------------------------*/
/*
  @brief: Printing a string on Terminal using UART

  Using the UART protocol with appropriate baud rate to print string on terminal

 @param: None

 @return: None
 */
/*-----------------------------------------------------------------------------------------------------------------------------*/
 

int main() {
 pc.baud(9600);
 while(1){
     pc.printf("Be Boulder\n\r");
     wait(1);
     
     }
}
