#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <stdlib.h>  /*Header for memory allocation,process control,conversions*/
#include <stdint.h>   /* Standard types */
#include <time.h>	/*to get and manipulate date and time information.*/
#include "arduino-serial-lib.c"   /*To communiate with arduino*/
#include "arduino-serial-lib.h"		//To communicate with arduino
#include <unistd.h>   // for usleep()
#include <getopt.h>
#include <fcntl.h>    // File control definitions
#include <termios.h>  // POSIX terminal control definitions 
#include <sys/ioctl.h>

int main() {
	int j;
	int opt=-1500; //option
	int ard=serialport_init("/dev/ttyUSB0",9600); // REPRESEN ARDUİNO TO COMPUTER
	
			//DEFININIG OPTONS
	const char* opt1="x";  
	const char* opt2="y";
	const char* opt3="z";
	const char* opt4="t";
	const char* opt5="w";
			
			//DEFINING ARRAYS TO READ SERIAL DATA
	char arr[256];
	char arr2[256];
			
			//DEFINING INTEGERS TO SEND A NUMBER TO ARDUINO
	uint8_t sayi;
	uint8_t sayi2;
	
	printf("## WELCOME TO GTU ARDUINO LAB \t\t ##\n## STUDENT NAME: TALHA YOLCU \t\t ##\n");
	printf("## PLEASE SELECT FROM THE FOLLOWING MENU ##\n\n");
	printf("(1) TURN ON LED ON ARDUINO\n");
	printf("(2) TURN OFF LED ON ARDUINO\n");
	printf("(3) FLASH ARDUINO LED 3 TIMES\n");
	printf("(4) SEND A NUMBER TO ARDUINO TO COMPUTE SQUARE BY ARDUINO\n");
	printf("(5) PRESS BUTTON TO SEE HOW MANY TIMES (bonus item)\n");
	printf("(0) EXIT\n");
    start_point:  //FOR ASK AFTER EVERY OPERATON 
	sayi=0;
	sayi2=0;
	
	printf("PLEASE SELECT:");
	
	while (opt!=0) {
		scanf("%d",&opt);
		switch  (opt) {
			case 1 : //TURNING ON THE LED
				serialport_write(ard,opt1);
				opt=-1500;
				goto start_point; //FOR ASK AFTER EVERY OPTION
				break;
			case 2:   // TURNING OFF THE LED
				serialport_write(ard,opt2);  //SENDING CHOICE TO ARDUINO
				opt=-1500;
				goto start_point;  //FOR ASK AFTER EVERY OPTION
				break;
				 
			case 3:     // FLASH THE LED 3 TIMES
				serialport_write(ard,opt3);
				opt=-1500;
				goto start_point;  //FOR ASK AFTER EVERY OPTION
				break;
			case 4:    // COMPUTING A SQUARE OF NUMBER
				printf("Enter a number\n");
				scanf("%hhd",&sayi);
				sayi2=sayi;
				sayi2=sayi+99;
				serialport_writebyte(ard,sayi2);  //SENDING NUMBER TO ARDUINO
				sleep(2);
				
				serialport_read_until(ard,arr,'\n',256,10); //READING SERIAL DATA
				sleep(2);
				printf("\n%s\n",arr);
				
				goto start_point;   //FOR ASK AFTER EVERY OPTION
				break;
			case 5:
				printf("Press the button, answer will come up after 2 seconds");
				sleep(2);
				serialport_write(ard,opt5);   //SENDING CHOICE TO ARDUINO
				sleep(2);
				serialport_read_until(ard,arr2,'\n',256,10); //READING SERIAL DATA
				printf("\n YOU PRESSED %s time \n ",arr2);

				for(j=0;j<5000000;j++) {
					printf("Press the button, answer will come up after 2 seconds");
					sleep(2);
					serialport_write(ard,opt5); //SENDING CHOICE TO ARDUINO
					sleep(2);
					serialport_read_until(ard,arr2,'\n',256,10); //READING SERIAL DATA
					printf("\n YOU PRESSED %s times \n ",arr2);
                }
				
        }

    }
    return 0;
}
