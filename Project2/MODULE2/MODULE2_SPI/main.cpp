/* 0.Documentation section
  -----------------------------------------------------------------------------------------------------------------------------------

  @file-main.cpp

 @brief: Interface the LCD display using SPI protocol: display four checks (size 10x10pixels) at four corners of the LCD.

 @author: Vikrant Waje and Michelle Russell

 @date:30 October 2017
 
 Input: None
 
 Output: LCD display
    
 */

/*------------------------------------------------------------------------------------------------------------------------------------*/
 /*1. Preprocessor Directives*/

#include "NHD_0216HZ.h"

 /*------------------------------------------------------------------------------------------------------------------------------------*/
/*
  @brief: Controlling the LCD using SPI bus protocol

  Use the SPI bus protocol to output the value into shift register which then operates LCD in 4 bit mode.

 @param: None

 @return: None
 */
/*-----------------------------------------------------------------------------------------------------------------------------*/
 

int main() {
  init_spi();   // Initialise the SPI bus
  init_lcd();   //Initialise the LCD
    
  print_lcd("Do you even"); // Print something on LCD
    set_cursor(0,1);        // Set cursor position
    print_lcd("mbed, bro?");    // Print on LCD
}


