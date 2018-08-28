/**----------------------------------------------------------------------------
 
   \file main.cpp

--                                                                           --
--              ECEN 5803 Mastering Embedded System Architecture             --
--                  Project 1 Module 2                                      --
--                Microcontroller Firmware                                   --
--                      main.cpp                                            --
--                                                                           --
-------------------------------------------------------------------------------
--
--  
--               
--                
--  
--  @author:  Vikrant Waje and Preshit Harlikar
-- 
-- Version: 2.1
-- Date of current revision:  10/01/2017 
-- Target Microcontroller: Freescale MKL25ZVMT4 
-- Tools used:  ARM mbed compiler
--              ARM mbed SDK
--              Freescale FRDM-KL25Z Freedom Board
--               
-- 
-- Functional Description:This function basically changes the color of Led based on the vibrations of TSI 
--   
--
--      */


#include "mbed.h"
#include "tsi_sensor.h"
/**@brief this function enables serial transmission*/
Serial pc(USBTX, USBRX); 
/**@brief class for timer*/  
Timer t;

/* This defines will be replaced by PinNames soon */
#if defined (TARGET_KL25Z) || defined (TARGET_KL46Z)
  #define ELEC0 9
  #define ELEC1 10
#elif defined (TARGET_KL05Z)
  #define ELEC0 9
  #define ELEC1 8
#else
  #error TARGET NOT DEFINED
#endif



/**@brief: This function changes the intensity of red light based upon the percentage reading of TSI slider*/
int main(void) {
    t.start();
    PwmOut led(LED_GREEN);
    TSIAnalogSlider tsi(ELEC0, ELEC1, 30);
    
    while (true) {
        t.start();
        led = 1.0 - tsi.readPercentage();
        wait(0.1);
        t.stop();
      pc.printf("The time taken was %f seconds\n", t.read());
    }
   

 }




    
    

    