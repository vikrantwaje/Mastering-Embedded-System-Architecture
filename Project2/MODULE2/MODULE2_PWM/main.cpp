/*----------------------------------------------------------------------------
LAB EXERCISE 9 - Analog input and PWM
 ----------------------------------------
    Use two potentiometers to adjust the volume and pitch of the output sound wave.

    Inputs: Virtual potentiometers 1 and 2
    Output: Virtual speaker,  Real PC

    GOOD LUCK!
 *----------------------------------------------------------------------------*/

/* 0.Documentation section
 -----------------------------------------------------------------------------------------------------------------------------------

 @file-main.cpp

@brief: Analog input and PWM

@author: Vikrant Waje and Michelle Russell

@date:4 November 2017

Input: Virtual potentiometers 1 and 2

Output: Virtual speaker,  Real PC

*/

/*------------------------------------------------------------------------------------------------------------------------------------*/
/*1. Preprocessor Directives*/
#include "mbed.h"
/*------------------------------------------------------------------------------------------------------------------------------------*/
/*Device initialises*/

//Define the PWM speaker output
PwmOut speaker(PB_10);

//Define analog inputs
AnalogIn pot1(PC_0);
AnalogIn pot2(PC_1);

//Define serial output
Serial pc(USBTX, USBRX);

//Write your code here


//Define variables
float i;
double v1,v2,d,p;

/*--------------------------------------------------------------------------------------------------------------------------------------*/

/*
  @brief: Controlling pitch and volume of speaker output.

  Using potentiometer 1 and potentiometer 2 to control volume and pitch of speaker output

 @param: None

 @return: None
 */
/*-----------------------------------------------------------------------------------------------------------------------------*/

int main()
{
    while(1) {
        wait(0.3);

        pc.printf("value of 1st potentiometer:%f value of 2nd potentiometer: %f\n\r",v1,v2);//Print values of the potentiometers to the PC serial terminal





        //Make the period and volume adjustable using the potentiometers

        v1=pot1.read(); //Read potentiometer 1 value which controls the frequency

        p=(0.003*v1)+0.000125; // When v1=1 corresponds to frequency of 320Hz and v1=0 corresponds to frequency of 8KHz

        speaker.period(p); // Frequency determines the pitch of sound waves

        for(i=0; i<=1; i+=p) {
            speaker=i;  //Generate triangular wave
        }
        for(i=1; i>0; i-=p) {
            speaker=i;  //Generate triangular wave
        }

        v2=pot2.read(); //Read potentiometer 2 which controls the duty cycle and hence the volume

        speaker.pulsewidth((v2*p)); //pulsewidth (dutycycle) will vary the average voltage and hence the volume of sound waves
    }
}

// *******************************ARM University Program Copyright � ARM Ltd 2014*************************************
