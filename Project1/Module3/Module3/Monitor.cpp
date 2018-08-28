/**----------------------------------------------------------------------------
             \file Monitor.cpp
--                                                                           --
--              ECEN 5003 Mastering Embedded System Architecture             --
--                  Project 1 Module 3                                       --
--                Microcontroller Firmware                                   --
--                      Monitor.cpp                                            --
--                                                                           --
-------------------------------------------------------------------------------
--
--  Designed for:  University of Colorado at Boulder
--               
--                
--  Designed by:  Tim Scherr
--  Revised by:  Student's name 
-- 
-- Version: 2.0
-- Date of current revision:  2016-09-29   
-- Target Microcontroller: Freescale MKL25ZVMT4 
-- Tools used:  ARM mbed compiler
--              ARM mbed SDK
--              Freescale FRDM-KL25Z Freedom Board
--               
-- 
   Functional Description: See below 
--
--      Copyright (c) 2015 Tim Scherr All rights reserved.
--
*/    

#include "mbed.h"
#include "tsi_sensor.h"
#include "MMA8451Q.h"


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
#include <stdio.h>
#include "shared.h"
int r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15;
TSIAnalogSlider tsi(ELEC0, ELEC1, 30);
MMA8451Q acc(SDA, SCL, MMA8451_I2C_ADDRESS);

/**@brief asm module to display the registers on screen*/
__asm int number(void){
    
    
    MOV r0,r0
    BX lr
    } 
    __asm int number1(void){
    
    
    MOV r0,r1
    BX lr
    }
        __asm int number2(void){
    
    
    MOV r0,r2
    BX lr
    }
    __asm int number3(void){
    
    
    MOV r0,r3
    BX lr
    }
    __asm int number4(void){
    
    
    MOV r0,r4
    BX lr
    }
    __asm int number5(void){
    
    
    MOV r0,r5
    BX lr
    }
    __asm int number6(void){
    
    
    MOV r0,r6
    BX lr
    }
    __asm int number7(void){
    
    
    MOV r0,r7
    BX lr
    }
    
    __asm int number8(void){
    
    
    MOV r0,r8
    BX lr
    }
    __asm int number9(void){
    
    
    MOV r0,r9
    BX lr
    }
    __asm int number10(void) {
    
    
    MOV r0,r10
    BX lr
    }
    __asm int number11(void){
    
    
    MOV r0,r11
    BX lr
    }
    __asm int number12(void){
    
    
    MOV r0,r12
    BX lr
    }
    __asm int number13(void){
    
    
    MOV r0,r13
    BX lr
    }
    __asm int number14(void){
    
    
    MOV r0,r14
    BX lr
    }
     __asm int number15(void){
    
    
    MOV r0,r15
    BX lr
    }
//rial pc(USBTX, USBRX);

/*******************************************************************************
* Set Display Mode Function
* Function determines the correct display mode.  The 3 display modes operate as 
*   follows:
*
*  NORMAL MODE       Outputs only mode and state information changes   
*                     and calculated outputs
*
*  QUIET MODE        No Outputs
*
*  DEBUG MODE        Outputs mode and state information, error counts,
*                    register displays, sensor states, and calculated output
*
*
* There is deliberate delay in switching between modes to allow the RS-232 cable 
* to be plugged into the header without causing problems. 
*******************************************************************************/

void set_display_mode(void)   
{
  UART_direct_msg_put("\r\nSelect Mode");
  UART_direct_msg_put("\r\n Hit NOR - Normal");
  UART_direct_msg_put("\r\n Hit QUI - Quiet");
  UART_direct_msg_put("\r\n Hit DEB - Debug" );
  UART_direct_msg_put("\r\n Hit V - Version#\r\n");
  UART_direct_msg_put("\r\nSelect:  ");
  
}


//*****************************************************************************/
/// \fn void chk_UART_msg(void) 
///
//*****************************************************************************/
void chk_UART_msg(void)    
{
   UCHAR j;
   while( UART_input() )      // becomes true only when a byte has been received
   {                                    // skip if no characters pending
      j = UART_get();                 // get next character

      if( j == '\r' )          // on a enter (return) key press
      {                // complete message (all messages end in carriage return)
         UART_msg_put("->");
         UART_msg_process();
      }
      else 
      {
         if ((j != 0x02) )         // if not ^B
         {                             // if not command, then   
            UART_put(j);              // echo the character   
         }
         else
         {
           ;
         }
         if( j == '\b' ) 
         {                             // backspace editor
            if( msg_buf_idx != 0) 
            {                       // if not 1st character then destructive 
               UART_msg_put(" \b");// backspace
               msg_buf_idx--;
            }
         }
         else if( msg_buf_idx >= MSG_BUF_SIZE )  
         {                                // check message length too large
            UART_msg_put("\r\nToo Long!");
            msg_buf_idx = 0;
         }
         else if ((display_mode == QUIET) && (msg_buf[0] != 0x02) && 
                  (msg_buf[0] != 'D') && (msg_buf[0] != 'N') && 
                  (msg_buf[0] != 'V') &&
                  (msg_buf_idx != 0))
         {                          // if first character is bad in Quiet mode
            msg_buf_idx = 0;        // then start over
         }
         else {                        // not complete message, store character
 
            msg_buf[msg_buf_idx] = j;
            msg_buf_idx++;
            if (msg_buf_idx > 2)
            {
               UART_msg_process();
            }
         }
      }
   }
}

//*****************************************************************************/
///  \fn void UART_msg_process(void) 
///UART Input Message Processing
//*****************************************************************************/
void UART_msg_process(void)
{
   UCHAR chr,err=0;
//   unsigned char  data;


   if( (chr = msg_buf[0]) <= 0x60 ) 
   {      // Upper Case
      switch( chr ) 
      {
         case 'D':
            if((msg_buf[1] == 'E') && (msg_buf[2] == 'B') && (msg_buf_idx == 3)) 
            {
               display_mode = DEBUG;
               UART_direct_msg_put("\r\nMode=DEBUG\n");
               display_timer = 0;
               display_flag=1;
            }
            else
               err = 1;
            break;

         case 'N':
            if((msg_buf[1] == 'O') && (msg_buf[2] == 'R') && (msg_buf_idx == 3)) 
            {
               display_mode = NORMAL;
               UART_direct_msg_put("\r\nMode=NORMAL\n");
               //display_timer = 0;
               display_flag=1;
               
            }
            else
               err = 1;
            break;

    

         case 'Q':
            if((msg_buf[1] == 'U') && (msg_buf[2] == 'I') && (msg_buf_idx == 3)) 
            {
               display_mode = QUIET;
               UART_msg_put("\r\nMode=QUIET\n");
               display_timer = 0;
            }
            else
               err = 1;
            break;

         case 'V':
            display_mode = VERSION;
            UART_msg_put("\r\n");
            UART_msg_put( CODE_VERSION ); 
            UART_msg_put("\r\nSelect  ");
            display_timer = 0;
            break;
                
         default:
            err = 1;
      }
   }

   else 
   {                                 // Lower Case
      switch( chr ) 
      {
        default:
         err = 1;
      }
   }

   if( err == 1 )
   {
      UART_msg_put("\n\rError!");
   }   
   else if( err == 2 )
   {
      UART_msg_put("\n\rNot in DEBUG Mode!");
   }   
   else
   {
    msg_buf_idx = 0;          // put index to start of buffer for next message
      ;
   }
   msg_buf_idx = 0;          // put index to start of buffer for next message


}


//*****************************************************************************
///   \fn   is_hex
/// Function takes 
///  @param a single ASCII character and returns 
///  @return 1 if hex digit, 0 otherwise.
///    
//*****************************************************************************
UCHAR is_hex(UCHAR c)
{
   if( (((c |= 0x20) >= '0') && (c <= '9')) || ((c >= 'a') && (c <= 'f'))  )
      return 1;
   return 0;
}

/*******************************************************************************
*   \fn  DEBUG and DIAGNOSTIC Mode UART Operation
*******************************************************************************/

void monitor(void)
{

/**********************************/
/*     Spew outputs               */
/**********************************/

   switch(display_mode)
   {
      case(QUIET):
         {
             UART_msg_put("\r\n ");
             display_flag = 0;
         }  
         break;
      case(VERSION):
         {
             display_flag = 0;
         }  
         break;         
      case(NORMAL):
         {
            if (display_flag == 1)
            {
               
               UART_direct_msg_put(" Flow: ");
                UART_direct_hex_put(0x89);
               
               // ECEN 5803 add code as indicated
               //  add flow data output here, use UART_hex_put or similar for 
               // numbers
               UART_direct_msg_put(" Temp: ");
               UART_direct_hex_put(0x54);
               //  add flow data output here, use UART_hex_put or similar for 
               // numbers
               UART_direct_msg_put(" Freq: ");
               UART_direct_hex_put(0x83);
               UART_direct_msg_put(" \b ");
               //  add flow data output here, use UART_hex_put or similar for 
               // numbers
               display_flag = 0;
            }
         }  
         break;
         
      case(DEBUG):
         {
            if (display_flag == 1)
            {
               
               UART_direct_msg_put(" Flow: ");
               UART_direct_hex_put(0x87);
               // ECEN 5803 add code as indicated               
               //  add flow data output here, use UART_hex_put or similar for 
               // numbers
               UART_direct_msg_put(" Temp: ");
               UART_direct_hex_put(0x47);
               //  add flow data output here, use UART_hex_put or similar for 
               // numbers
               UART_direct_msg_put(" Freq: ");
                UART_direct_hex_put(0x53);
                UART_direct_msg_put(" \b ");
               //  add flow data output here, use UART_hex_put or similar for 
               // numbers
               
               
 /****************      ECEN 5803 add code as indicated   ***************/             
               //  Create a display of  error counts, sensor states, and
               //  ARM Registers R0-R15
               UART_direct_msg_put("\r\n");
               UART_direct_msg_put("R0:");
               //t b=r0;
               int r0=number();
               UART_direct_hex_put(r0);
               UART_direct_msg_put("\n\r");
               UART_direct_msg_put("R1:");
               r1=number1();
               UART_direct_hex_put(r1);
               UART_direct_msg_put("\n\r");               
               UART_direct_msg_put("R2:");
               r2=number2();
               UART_direct_hex_put(r2);
               UART_direct_msg_put("\n\r");
               UART_direct_msg_put("R3:");
               r3=number3();
               UART_direct_hex_put(r3);
               UART_direct_msg_put("\n\r");
               UART_direct_msg_put("R4:");
               r4=number4();
               UART_direct_hex_put(r4);
               UART_direct_msg_put("\n\r");
               UART_direct_msg_put("R5:");
               r5=number5();
               UART_direct_hex_put(r5);
               UART_direct_msg_put("\n\r");
               UART_direct_msg_put("R6:");
               
              
               r6=number6();
               UART_direct_hex_put(r6);
               UART_direct_msg_put("\n\r");
               UART_direct_msg_put("R7:");
               r7=number7();
               UART_direct_hex_put(r7);
               UART_direct_msg_put("\n\r");
               
               UART_direct_msg_put("R8:");
               r8=number8();
               UART_direct_hex_put(r8);
               UART_direct_msg_put("\n\r");
               UART_direct_msg_put("R9:");
               r9=number9();
               UART_direct_hex_put(r9);
               UART_direct_msg_put("\n\r");
               UART_direct_msg_put("R10:");
               r10=number10();
               UART_direct_hex_put(r10);
               UART_direct_msg_put("\n\r");
               UART_direct_msg_put("R11:");
               r11=number11();
               UART_direct_hex_put(r11);
               UART_direct_msg_put("\n\r");
               UART_direct_msg_put("R12:");
               r12=number12();
               UART_direct_hex_put(r12);
               UART_direct_msg_put("\n\r");
               UART_direct_msg_put("R13:");
               r13=number13();
               UART_direct_hex_put(r13);
               UART_direct_msg_put("\n\r");
               UART_direct_msg_put("R14:");
               r14=number14();
               UART_direct_hex_put(r14);
               UART_direct_msg_put("\n\r");
               UART_direct_msg_put("R15:");
               r15=number15();
               UART_direct_hex_put(r15);
               UART_direct_msg_put("\n\r");
               
               
               UART_direct_msg_put("Sensor states:\r\n");
               int s=tsi.readPercentage();
               UART_direct_msg_put("tsi:");
               UART_direct_hex_put(s);
        UART_direct_msg_put("\n\r");       
                     float x, y, z;
        UART_direct_msg_put("x:");
        x = abs(acc.getAccX());
        UART_direct_hex_put(x);
        UART_direct_msg_put("\n\r");
      y = abs(acc.getAccY());
        UART_direct_msg_put("y:");
        UART_direct_hex_put(y);
        UART_direct_msg_put("\n\r");
        z = abs(acc.getAccZ());
        UART_direct_msg_put("z:");
        UART_direct_hex_put(z);  
              
              
               //  Create a command to read a section of Memory and display it

               
               
               
               //  Create a command to read 16 words from the current stack 
               // and display it in reverse chronological order.
              
              
               // clear flag to ISR      
               display_flag = 0;
             }   
         }  
         break;

      default:
      {
         UART_msg_put("Mode Error");
      }  
   }
}  

