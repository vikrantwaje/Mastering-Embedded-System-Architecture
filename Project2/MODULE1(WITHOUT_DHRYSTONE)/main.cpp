#include "mbed.h"

DigitalOut myled(LED1);

int main() {
    
    printf("RTC example\n"); 
    set_time(1510098007 ); // Set RTC time to current time.This value is obtained by entering data +%s in command line of linux
    printf("Date and time are set.\n");

    while(1) {

        time_t seconds = time(NULL);

        //printf("Time as seconds since January 1, 1970 = %d\n", seconds);
        
        printf("Time as a basic string = %s\n\r", ctime(&seconds));

        //char buffer[32];
        //strftime(buffer, 32, "%I:%M:%S %p\n", localtime(&seconds));
        //printf("Time as a custom formatted string = %s", buffer);

        myled = !myled;      
        wait(1);
    }
}
