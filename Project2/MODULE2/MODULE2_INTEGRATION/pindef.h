/*----------------------------------------------------------------------------
 Pin definitions
 *----------------------------------------------------------------------------*/

#ifndef PINDEF_H
#define PINDEF_H
 
//Define pins below

//Digital input pins
#define Din0 PA_10
#define Din1 PB_3
#define Din2 PB_5
#define Din3 PB_4

//Digital output pins
#define Dout0 PB_10
#define Dout1 PA_8
#define Dout2 PA_9
#define Dout3 PC_7

//Analog input pins
#define Ain0 PA_0
#define Ain1 PA_1
#define Ain2 PA_4
#define Ain3 PB_0
#define Ain4 PC_1
#define Ain5 PC_0

//Analog output pins
#define Aout0
#define Aout1
#define Aout2
#define Aout3
#define Aout4
#define Aout5

//Communication pins
#define I2C_SCL PB_8
#define I2C_SDA PB_9

#define SPI_MOSI PA_7
#define SPI_MISO PA_6
#define SPI_SCLK PA_5
#define SPI_CS PB_6

#define UART_TX PA_2
#define UART_RX PA_3

//If any on board RGB LEDs are present:
#define LED_r PB_10
#define LED_g PA_8
#define LED_b PA_9

#endif
 
// *******************************ARM University Program Copyright © ARM Ltd 2014*************************************
