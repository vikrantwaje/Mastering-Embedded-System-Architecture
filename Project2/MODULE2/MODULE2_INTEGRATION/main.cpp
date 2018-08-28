
 /* 0.Documentation section
  -----------------------------------------------------------------------------------------------------------------------------------

  @file-main.cpp

 @brief: Display the virtual temperature on LCD using SPI and I2C protocol.

 @author: Vikrant Waje and Michelle Russell

 @date:2 November 2017
 
Input: virtual DS1631 temperature sensor

 Output: virtual LCD display
    
 */

/*------------------------------------------------------------------------------------------------------------------------------------*/
/*1. Preprocessor Directives*/

#include "NHD_0216HZ.h"
#include "pindef.h"
/*----------------------------------------------------------------------------------------------------------------------------------------*/
//Define the LCD and the temperature sensor

NHD_0216HZ lcd( SPI_CS,  SPI_MOSI, SPI_SCLK);//Define the LCD

float temp;//Define a variable to store temperature measurement

//I2C interface
I2C temp_sensor(I2C_SDA, I2C_SCL);
Serial pc(UART_TX, UART_RX);

//I2C address of temperature sensor DS1631
const int temp_addr = 0x90;

char start=0x51;// Start operation command
char read=0xAA;// Read operation command
char read_temp[2];// Variable to store the 16 bit quantity 

/*--------------------------------------------------------------------------------------------------------------------------------------*/

/*
  @brief: Displaying temperature on LCD 

  Using SPI and I2C protocol to display the temperature on LCD

 @param: None

 @return: None
 */
/*-----------------------------------------------------------------------------------------------------------------------------*/

int main() {
    
    lcd.init_lcd(); //Initialise the LCD
    lcd.set_cursor(0,0);//Set the cursor position
    
    
    lcd.printf("Temperature:");
    while(1) {
        temp_sensor.write(temp_addr,&start,1);//Start temperature measurement
        wait(0.76);
        temp_sensor.write(temp_addr,&read,1);//Read command
        read_temp[0]=0;
        read_temp[1]=0;
        temp_sensor.read(temp_addr,read_temp,2);//Read the value from 2 byte register
        wait(0.76);
        
        
        
        float temp = (float((read_temp[0] << 8) | read_temp[1]) / 256);//Conversion of temperature to celsius
        
        pc.printf("Temperature is %f\n\r",temp);    //print the temperature value on PC terminal
        lcd.set_cursor(0,1);//Set cursor position
        //Write your code here
        lcd.printf(" %f ",temp);
    }
}