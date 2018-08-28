
/* 0.Documentation section
 -----------------------------------------------------------------------------------------------------------------------------------

 @file-main.cpp

@brief: Implementing Real time clock using Unix time and displaying it's value on PC terminal.

@author: Vikrant Waje and Michelle Russell

@date:24 October 2017


*/

/*------------------------------------------------------------------------------------------------------------------------------------*/
/*1. Preprocessor Directives*/
#include "mbed.h"
#include "dhry.h"
/*------------------------------------------------------------------------------------------------------------------------------------*/

DigitalOut myled(LED1); // Initialize internal LED
Timer t;                //Define timer for Dhrystone
/*--------------------------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------------------*/

/*
  @brief: Displaying Real time on PC terminal.

  This program uses UNIX time for real time clock and also blinks the internal LED

 @param: None

 @return: None
 */
/*-----------------------------------------------------------------------------------------------------------------------------*/
int main() {
    t.start(); // Start timer for Dhrystone calculation
    double benchtime, dps; // Variable for benchtime and dhrystone per second.
    unsigned long loops;    // Variable to store loop
     
    printf("RTC example\n\r"); 
    set_time(1510098007 ); // Set RTC time to current time.This value is obtained by entering data +%s in command line of linux
    printf("Date and time are set.\n\r");
    printf("Dhrystone Benchmark Program\n\r ");
    while(1) {


        time_t seconds = time(NULL);

        //printf("Time as seconds since January 1, 1970 = %d\n", seconds);
        
        printf("Time as a basic string = %s\n\r", ctime(&seconds)); //Display on PC terminal


        myled = !myled;      //Toggle the internal LED
        wait(1);
/*--------------------------------------Dhrystone calculation-----------------------------------------*/
                loops = 0l;

        t.reset();
                do {
            Proc0();
            Proc0();
            loops += LOOPS;
            benchtime = t.read();
        } while (benchtime <= 5.000);
        dps = (double)loops / benchtime;
        dps=dps/1757;
        printf("Dhrystone time for %ld passes = %.3f sec\n\r", loops, benchtime);
        printf("This machine benchmarks at %.0f dhrystones/second\n\r", dps);
/*---------------------------------------------------------------------------------------------------------------------*/    
    }
}
