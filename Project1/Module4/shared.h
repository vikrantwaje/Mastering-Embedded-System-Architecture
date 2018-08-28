/**-----------------------------------------------------------------------------
      \file shared.h
--                                                                           --
--              ECEN 5803 Mastering Embedded System Architecture             --
--                  Project 1 Module 4                                       --
--                Microcontroller Firmware                                   --
--                      shared.h                                             --
--                                                                           --
-------------------------------------------------------------------------------
--
--  Designed for:  University of Colorado at Boulder
--               
--                
--  Designed by:  Tim Scherr
--  Revised by:  Student's name 
-- 
-- Version: 2.1
-- Date of current revision:  2017-09-25   
-- Target Microcontroller: Freescale MKL25ZVMT4 
-- Tools used:  ARM mbed compiler
--              ARM mbed SDK
--              Freescale FRDM-KL25Z Freedom Board
--               
-- 
-- Functional Description:  Header file for all globals
--
--      Copyright (c) 2015, 2016 Tim Scherr  All rights reserved.
--
*/              
                          
 #include "mbed.h"  
 
 /*****************************************************************************
* #defines available to all modules included here
******************************************************************************/ 
#define OFF 0                       /* used for readability */
#define ON 1                        /* used for readability */
#define NO 0                        /* used for readability */
#define YES 1                       /* used for readability */
#define TEN 10

#define TIMER0 TMR0
#define SEC 10000           /* 10000 timer0 interrupts per second (100 usec.) */
                   
#define T100MS 0.1*SEC
#define T2S    2*SEC
                              
#define LED_FLASH_PERIOD .5   /* in seconds */
 
#define CLOCK_FREQUENCY_MHZ 8
#define CODE_VERSION "2.0 2016/09/29"   /*   YYYY/MM/DD  */
#define COPYRIGHT "Copyright (c) University of Colorado" 
     
 enum boolean { FALSE, TRUE };         /// \enum boolean  
 enum dmode {QUIET, NORMAL, DEBUG, VERSION};      /// \enum dmode 
 
 typedef unsigned char UCHAR;
 typedef unsigned char bit;
 typedef unsigned int uint32_t;
 typedef unsigned short uint16_t;
 
#ifdef __cplusplus 
extern "C" {
#endif
 
/************************************************************************/
/*             Global Variable declarations                             */
/************************************************************************/
 
 extern unsigned char Error_status;          // Variable for debugging use
 extern UCHAR  display_timer;  // 1 second software timer for display   
 extern UCHAR  display_flag;   // flag between timer interrupt and monitor.c, like
                        // a binary semaphore
 extern UCHAR  adc_flag;  // flag which times ADC sampling using the timer 
                          // interrupt semaphore to main
 extern UCHAR tx_in_progress;                        
 extern UCHAR *rx_in_ptr; /* pointer to the receive in data */
 extern UCHAR *rx_out_ptr; /* pointer to the receive out data*/
 extern UCHAR *tx_in_ptr; /* pointer to the transmit in data*/
 extern UCHAR *tx_out_ptr; /*pointer to the transmit out */                       
#define RX_BUF_SIZE 10            /* size of receive buffer in bytes */
#define TX_BUF_SIZE 40           /* size of transmit buffer in bytes */
                                                                    
/******************************************************************************
* Some variable definitions are done in the module main.c and are externed in 
* all other modules.  The following section is visible to main.c only.
******************************************************************************/
#ifdef MAIN

 enum dmode display_mode = QUIET;
 
 UCHAR serial_flag = 0;
 
 UCHAR tx_in_progress; 
 UCHAR *rx_in_ptr; /* pointer to the receive in data */
 UCHAR *rx_out_ptr; /* pointer to the receive out data*/
 UCHAR *tx_in_ptr; /* pointer to the transmit in data*/
 UCHAR *tx_out_ptr; /*pointer to the transmit out */        
    
 UCHAR  rx_buf[RX_BUF_SIZE];      /* define the storage */
 UCHAR  tx_buf[TX_BUF_SIZE];      /* define the storage */

#define MSG_BUF_SIZE 10
 UCHAR msg_buf[MSG_BUF_SIZE]; // define the storage for UART received messages
 UCHAR msg_buf_idx = 0;    // index into the received message buffer       

/******************************************************************************
* Some variable definitions are done in the module main.c and are externed in 
* all other modules.  The following section is visible to all modules EXCEPT 
* main.c.
*******************************************************************************/
#else

/**********************/   
/*   Declarations     */
/**********************/

   extern volatile     UCHAR swtimer0;
   extern volatile     UCHAR swtimer1;
   extern volatile     UCHAR swtimer2;
   extern volatile     UCHAR swtimer3; 
   extern volatile     UCHAR swtimer4;    
   extern volatile     UCHAR swtimer5;    
   extern volatile     UCHAR swtimer6;    
   extern volatile     UCHAR swtimer7;    
  
  extern UCHAR serial_flag;
    
  extern enum dmode display_mode;
  
  
  extern UCHAR  rx_buf[];      /* declare the storage */
  extern UCHAR  tx_buf[];      /* declare the storage */

#define MSG_BUF_SIZE 10    
  extern  UCHAR msg_buf[MSG_BUF_SIZE]; // declare the storage for UART received messages
  extern  UCHAR msg_buf_idx;         // index into the received message buffer

#endif

/*************************************************************************************************************
* All function prototypes are externed in all the modules.
*************************************************************************************************************/
extern void monitor(void);  /* located in module monitor.c */
extern void timer0(void);   /* located in module timer0.c */
extern void serial(void);   /* located in module UART.c */

extern void UART_put(UCHAR);                   /* located in module UART.c */
extern UCHAR UART_get(void);                   /* located in module UART.c */
extern UCHAR UART_input(void);                 /* located in module UART.c */
extern void UART_direct_msg_put(const char *);
                                               /* located in module UART.c */
extern void UART_msg_put(const char *); 
                                               /* located in module UART.c */
extern void UART_direct_hex_put(UCHAR);        /* located in module UART.c */
extern void UART_direct_put(UCHAR);            /* located in module UART.c */
extern void UART_hex_put(UCHAR);               /* located in module UART.c */
extern void UART_low_nibble_put(UCHAR);        /* located in module UART.c */
extern void UART_high_nibble_put(UCHAR);       /* located in module UART.c */
extern void chk_UART_msg(void);               /* located in module monitor.c */
extern void UART_msg_process(void);          /* located in module monitors.c */
extern void status_report(void);             /* located in module monitor.c */  
extern void set_display_mode(void);          /* located in module monitor.c */

#ifdef __cplusplus
}
#endif

