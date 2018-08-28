 /* 0.Documentation section
  -----------------------------------------------------------------------------------------------------------------------------------

  @file-main.cpp

 @brief: Using RTOS to execute four threads simultaneously.
        Thread 1: Blinking the internal LED
        Thread 2: Displaying incremental counter value on LCD
        Thread 3: Controlling the brightness of LED using a potentiometer.
        Thread 4: Displaying the temperature value on LCD

 @author: Vikrant Waje and Michelle Russell

 @date:7 November 2017
 
    
 */

/*------------------------------------------------------------------------------------------------------------------------------------*/
/*1. Preprocessor Directives*/

#include "mbed.h"
#include "pindef.h"
#include "rtos.h"
#include "NHD_0216HZ.h"
/*----------------------------------------------------------------------------------------------------------------------------------------*/

/* Initialisng all components*/

NHD_0216HZ lcd( SPI_CS,  SPI_MOSI, SPI_SCLK); //Defining the LCD

I2C temp_sensor(I2C_SDA, I2C_SCL); //I2C interface

Mutex lcdm; //Defining mutex

const int temp_addr = 0x90; //I2C address of temperature sensor DS1631

char start=0x51;    // Start operation command

char read=0xAA;     // Read operation command
char read_temp[2];  //Variable to store 16 byte temperature value

AnalogIn pot(PC_0); //Potentiometer

PwmOut my_led(PB_3); //LED whose brightness is to be controlled
 
DigitalOut led2(LED2); //Internal LED

Thread thread; //Define Thread
/*----------------------------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------------------*/

/*
  @brief: Executing thread 2

  This thread contains function to control the brightness of LED.

 @param: None

 @return: None
 */
/*-----------------------------------------------------------------------------------------------------------------------------*/
void thread2(void const *argument){
    while(1){
    my_led = pot.read(); // Read potentiometer value and give the output to PWM controlled LED
    Thread::wait(1);
    }
    } 
    
/*--------------------------------------------------------------------------------------------------------------------------------------*/

/*
  @brief: Executing thread 3

  This thread contains function to display the counter value on LCD. Since thread 3 and thread 4 share LCD, a mutex is used to protect access to this shared resource 

 @param: None

 @return: None
 */
/*-----------------------------------------------------------------------------------------------------------------------------*/
void thread3(void const *argument){
    
float c=0.0;
lcd.init_lcd(); //Initialise LCD
    lcd.set_cursor(0,0); //Set cursor position
    while(1) {
        lcdm.lock(); //Use mutex lock to block the LCD
       lcd.clr_lcd(); //Clear LCD screen
        lcd.printf("Counter:");
       lcd.set_cursor(0,1); //Set cursor position
        lcd.printf("%f",c++);
        wait(1);
        lcdm.unlock(); //Unblock the shared resource
        Thread::wait(1);
    }
}

/*--------------------------------------------------------------------------------------------------------------------------------------*/

/*
  @brief: Executing thread 4   

  This thread contains function to display the temperature value on LCD. Since thread 3 and thread 4 share LCD, a mutex is used to protect access to this shared resource 

 @param: None

 @return: None
 */
/*-----------------------------------------------------------------------------------------------------------------------------*/
    
void thread4(void const *argument) {
lcd.init_lcd();
    lcd.set_cursor(0,0);

    while(1) {
        lcdm.lock(); //Block LCD using mutex
       lcd.clr_lcd(); //Clear LCD screen
        lcd.set_cursor(0,0); //Set cursor position
          lcd.printf("Temperature:");
        temp_sensor.write(temp_addr,&start,1);//Start temperature measurement
        temp_sensor.write(temp_addr,&read,1);//Read command
        read_temp[0]=0;
        read_temp[1]=0;
        temp_sensor.read(temp_addr,read_temp,2);//Read the value from 2 byte register

        float temp = (float((read_temp[0] << 8) | read_temp[1]) / 256);//Conversion of temperature to celsius
        
        
        lcd.set_cursor(0,1);
        lcd.printf("%f",temp); //Print the temperature value on LCD
        wait(1);
        lcdm.unlock();
        Thread::wait(1);
        
}
}
 
 /*--------------------------------------------------------------------------------------------------------------------------------------*/

/*
  @brief: Defining four threads and start executing

  Use of four threads in RTOS to display temperature and counter value on LCD, controlling the brightness of LED using potentiometer and blinking the LED ON/OFF.

 @param: None

 @return: None
 */
/*-----------------------------------------------------------------------------------------------------------------------------*/

    int main()
{
    
   Thread t2(thread2); //start thread2
    Thread t3(thread3); //start thread2
    Thread t4(thread4); //start thread3

    // Main loop is also considered to be thread
    while (true) {
    
           led2=!led2; //Blink the internal LED
            Thread::wait(1000);   // wait 0.5s
    

    
    }
}