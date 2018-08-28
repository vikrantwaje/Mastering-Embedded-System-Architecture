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
-- Functional Description:This function basically changes the color of RGB LED based upon the values of accelerometer x,y and z axis
--   
--
--      */


#include "mbed.h"
#include "MMA8451Q.h"


Timer t;
/**@brief This function basically enables serial transmission*/
Serial pc(USBTX, USBRX);
 


#if   defined (TARGET_KL25Z) || defined (TARGET_KL46Z)
  PinName const SDA = PTE25;
  PinName const SCL = PTE24;
#elif defined (TARGET_KL05Z)
  PinName const SDA = PTB4;
  PinName const SCL = PTB3;
#elif defined (TARGET_K20D50M)
  PinName const SDA = PTB1;
  PinName const SCL = PTB0;
#else
  #error TARGET NOT DEFINED
#endif

#define MMA8451_I2C_ADDRESS (0x1d<<1)
/**@brief This function causes the value of x,y and z axis to be read into variables based upon which the color of RGB led is changed
    @param: None*/
int main(void)
{
    t.start();
    MMA8451Q acc(SDA, SCL, MMA8451_I2C_ADDRESS);
    
    PwmOut rled(LED1);
    PwmOut gled(LED2);
    PwmOut bled(LED3);

    pc.printf("MMA8451 ID: %d\n", acc.getWhoAmI());

    while (true) {
        float x, y, z;
        x = abs(acc.getAccX());
        y = abs(acc.getAccY());
        z = abs(acc.getAccZ());
        rled = 1.0f - x;
        gled = 1.0f - y;
        bled = 1.0f - z;
        wait(0.1f);
        pc.printf("X: %1.2f\n\r, Y: %1.2f\n\r, Z: %1.2f\n\r", x, y, z);
        t.stop();
        printf("The time taken was %f seconds\n", t.read());
     
    }
}
