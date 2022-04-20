
#ifndef __MYTHREADCPP
#define __MYTHREADCPP


#include <common/types.h>
#include <gdt.h>
#include <hardwarecommunication/interrupts.h>
#include <hardwarecommunication/pci.h>
#include <drivers/driver.h>
#include <drivers/keyboard.h>
#include <drivers/mouse.h>
#include <drivers/vga.h>
#include <gui/desktop.h>
#include <gui/window.h>
#include <multitasking.h>

using namespace myos::common;
using namespace myos::drivers;
using namespace myos::hardwarecommunication;
using namespace myos::gui;
using namespace myos;


#define N2 2
#define N 100
#define FALSE 0
#define TRUE 1


int turn;
int interested[N2]={0,0};
int count=0;
int start_number=2347;
int exit_counter=0;

TaskManager taskManager;
void printfHex(uint8_t key);
void printf(char* buf);




int calculate_digit(int& num) {
    //calculate number of digit
    if(num<10) {
        return 1;
    }
    int div=num/10;
    int digit=calculate_digit(div);
    return (digit+1);
}
void toChar(char* buf,int num) {
    //write number into the buffer
    char*buf2;
    int digit=calculate_digit(num);
    for(int i=0;i<digit;i++) {
        int div=num/10;
        int mod=num%10;
        buf2[i]=mod+'0';
        num=div;
    }
    for(int i=0;i<digit;i++) {
        buf[i]=buf2[digit-i-1];
    }
}
void sleep() {
    //busy wait
    int i=0;
    while(i<500000) {
        i++;
    }
}

int produce_item() {
    return start_number;
}

void insert_item(int item) {
    start_number++;
}
int remove_item() {
    return start_number;
}
void consume_item(int item) {
    start_number--;
}
int enter_region(int process) {
    //producer consumer is done succesffully
    int other;
    other=(1-process);
    interested[process]=TRUE;
    turn=process;
    int flag=0;

    while(turn==process && interested[other==true]) {
        //printf("WAITING\n");
    }
    flag=1;
    return flag;
    
}
void leave_region(int process) {
    interested[process]=FALSE;
}

void producer() {
    /*for(int i=0;i<5;i++)*/
    while(true) {
        exit_counter++;
        //enter_region(0);
        //if you could not enter the region, try again
        if(enter_region(0)==1) {
            printf("PRODUCER ENTERED TO CRITIC REGION\n");
            sleep();
            if(count<N) {
                int item=produce_item();
                printf("PRODUCER PRODUCED\n");
                insert_item(item);
                count+=1;          
            }
            else {
                //consumer();
            }
            leave_region(0);
            printf("PRODUCER LEAVED FROM CRITIC REGION\n");
        }
        else {
            //consumer();
        }
        sleep();
        if(exit_counter==150) {
            printf("END OF PRODUCER\n");
            taskManager.ExitTask();            
            break;
        }        
    }
    printf("END OF PRODUCER\n");
    taskManager.ExitTask();

}
void consumer() {
    for(int i=0;i<500000;i++)
    /*while(true)*/ {
        exit_counter++;
        //enter_region(1);
        //if you could not enter the region, try it
        if(enter_region(1)==1) {
            printf("CONSUMER ENTERED TO CRITIC REGION\n"); 
            sleep();    
            if(count>0) {
                int item = remove_item();
                printf("CONSUMER CONSUMED\n");
                consume_item(item);
                count = count - 1;
            }
            else {
                //producer();
            }
            leave_region(1);
            printf("CONSUMER LEAVED FROM CRITIC REGION\n");
        }
        else {
            //producer();
        }
        sleep();
        if(exit_counter==150) {
            printf("END OF CONSUMER\n");
            taskManager.ExitTask();            
            break;
        }       
    }
    printf("END OF CONSUMER\n");   
    taskManager.ExitTask();

}



void taskA()
{
    for(int i=0;i<50;i++) {
        printf("A");
        sleep();
    }
    taskManager.ExitTask();
}
void taskB()
{
    for(int i=0;i<50;i++) {
        printf("B");
        sleep();        
        if(i==25) {
            taskManager.JoinTask();
        }         
    }
    taskManager.ExitTask();    
}

void taskC() {
    for(int i=0;i<50;i++) {
        printf("C");
        sleep();        
        if(i==25) {
            taskManager.YieldTask();
        }

    } 
    taskManager.ExitTask();       
}

void taskD() {
    for(int i=0;i<50;i++) {
        printf("D");
        sleep();        
    }    
    taskManager.ExitTask();    
}

void taskE() {
    for(int i=0;i<50;i++) {     
        printf("E");
        sleep();        
    }    
    taskManager.ExitTask();    
}

int create_thread(Task* task) {
    return taskManager.AddTask(task);
}

#endif