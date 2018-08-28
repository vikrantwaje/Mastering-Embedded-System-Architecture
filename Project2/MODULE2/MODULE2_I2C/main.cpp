
 /*-----------------------------------------------------------------------------------------------------------------------------------*/
 /* 0.Documentation section
  -----------------------------------------------------------------------------------------------------------------------------------

  @file-main.cpp

 @brief: Access the virtual temperature sensor via I2C interface, print the current temperature to the PC via UART

 @author: Vikrant Waje and Michelle Russell

 @date:28 October 2017


 */

/*------------------------------------------------------------------------------------------------------------------------------------*/
    
   /*1. Preprocessor Directives*/ 
    

#include "mbed.h"
#include "pindef.h"
/*---------------------------------------------------------------------------------------------------------------------------------------*/

//I2C interface
I2C temp_sensor(I2C_SDA, I2C_SCL);
Serial pc(UART_TX, UART_RX);

//I2C address of temperature sensor DS1631
const int temp_addr = 0x90;

char start=0x51;
char read=0xAA;
char read_temp[2];


/*------------------------------------------------------------------------------------------------------------------------------------*/
/*
  @brief: To detect the temperature using temperature sensor DS1631 and print the output on Serial terminal



 @param: None

 @return: None
 */
/*-----------------------------------------------------------------------------------------------------------------------------*/

int main(){
    while(1){
    
        temp_sensor.write(temp_addr,&start,1);//Write the Start Convert T command to the sensor.
        wait(0.76);
        temp_sensor.write(temp_addr,&read,1);//Write the Read Temperature command to the sensor.
        read_temp[0]=0;
        read_temp[1]=0;
        temp_sensor.read(temp_addr,read_temp,2);//Read the 16-bit temperature data.
        wait(0.76);
        
        float temp = (float((read_temp[0] << 8) | read_temp[1]) / 256);//Convert temperature to Celsius.
        
        pc.printf("Temperature is %f\n\r ",temp);//Print temperature to the serial monitor.
        
    }
}


