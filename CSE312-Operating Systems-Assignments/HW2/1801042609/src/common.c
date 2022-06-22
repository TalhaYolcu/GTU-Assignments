#ifndef COMMON
#define COMMON


#include "structs.h"
#include <common/types.h>
#include <gdt.h>
#include <memorymanagement.h>
#include <hardwarecommunication/interrupts.h>
#include <hardwarecommunication/pci.h>
#include <drivers/driver.h>
#include <drivers/keyboard.h>
#include <drivers/mouse.h>
#include <drivers/vga.h>
#include <gui/desktop.h>
#include <gui/window.h>
#include <multitasking.h>
#include <time.h>


int fifo_flag=1;
int second_chance_flag=0;
int lru_flag=0;
int current_clock=0;
int hit_counter=0;
int miss_counter=0;
int loaded_page=0;
int written_page=0;


        typedef char                     int8_t;
        typedef unsigned char           uint8_t;
        typedef short                   int16_t;
        typedef unsigned short         uint16_t;
        typedef int                     int32_t;
        typedef unsigned int           uint32_t;
        typedef long long int           int64_t;
        typedef unsigned long long int uint64_t;
    
        typedef const char*              string;
        typedef uint32_t                 size_t;

void printf(char* str)
{
    static uint16_t* VideoMemory = (uint16_t*)0xb8000;

    static uint8_t x=0,y=0;

    for(int i = 0; str[i] != '\0'; ++i)
    {
        switch(str[i])
        {
            case '\n':
                x = 0;
                y++;
                break;
            default:
                VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | str[i];
                x++;
                break;
        }

        if(x >= 80)
        {
            x = 0;
            y++;
        }

        if(y >= 25)
        {
            for(y = 0; y < 25; y++)
                for(x = 0; x < 80; x++)
                    VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';
            x = 0;
            y = 0;
        }
    }
}

void printfHex(uint8_t key)
{
    char* foo = "00";
    char* hex = "0123456789ABCDEF";
    foo[0] = hex[(key >> 4) & 0xF];
    foo[1] = hex[key & 0xF];
    printf(foo);
}



int calculate_digit(int num) {
    //calculate number of digit
    if((num)<10) {
        return 1;
    }
    int div=(num)/10;
    int digit=calculate_digit(div);
    return (digit+1);
}
void toChar(char buf[50],int num) {
    //write number into the buffer

    char buf2[50];
    for(int i=0;i<50;i++) {
        buf[i]='\0';
        buf2[i]='\0';
    }      
    int digit=calculate_digit(num);
    for(int i=0;i<digit;i++) {
        int div=(num)/10;
        int mod=(num)%10;
        buf2[i]=mod+'0';
        (num)=div;
    }
    for(int i=0;i<digit;i++) {
        buf[i]=buf2[digit-i-1];
    }
}

void print_hit() {
    //printf("HIT\n");
    hit_counter++;
}
void print_miss() {
    //printf("MISS\n");
    miss_counter++;
}

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
 
/* Function to print an array */
void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++) {
        char buf[50];      
        toChar(buf,(arr[i]));
        printf(buf);
        printf(" ");
    }
    printf("\n");
}

int my_pow(int base,int exp) {
    int res=1;
    for(int i=0;i<exp;i++) {
        res=res*base;
    }
    return res;
}

int my_log2(int base) {
    int res=base;
    int i=0;
    for(i=0;res>1;i++) {
        res/=2;
    }
    return i;
}
void fifo_replacement(my_program*p,int arr_index,int*arr) {
    int min_load_time=current_clock;
    int page_index=0;
    int page_i=0;
    for(int i=0;i<NUMBER_OF_PAGE;i++) {
        if(p->table.pages[i].load_time<min_load_time) {
            page_i=i;
            page_index=p->table.pages[i].index;
            min_load_time=p->table.pages[i].load_time;
        }
    }
    int needed_start_index=(arr_index/PAGE_SIZE)*PAGE_SIZE;
    for(int i=needed_start_index;i<(needed_start_index+PAGE_SIZE);i++) {
        p->table.pages[page_i].array[i%PAGE_SIZE]=arr[i];
    }
    p->table.pages[page_i].index=needed_start_index/PAGE_SIZE;
    p->table.pages[page_i].last_reference_time=current_clock;
    p->table.pages[page_i].load_time=current_clock++;
    p->table.pages[page_i].M_bit=0;
    p->table.pages[page_i].R_bit=0;
    p->table.pages[page_i].second_chance=0;
}


void least_recently_used(my_program*p,int arr_index,int*arr) {
    int min_ref_time=current_clock;
    int page_index=0;
    int page_i=0;
    for(int i=0;i<NUMBER_OF_PAGE;i++) {
        if(p->table.pages[i].last_reference_time<min_ref_time) {
            page_i=i;
            page_index=p->table.pages[i].index;
            min_ref_time=p->table.pages[i].load_time;
        }
    }
    int needed_start_index=(arr_index/PAGE_SIZE)*PAGE_SIZE;
    for(int i=needed_start_index;i<(needed_start_index+PAGE_SIZE);i++) {
        p->table.pages[page_i].array[i%PAGE_SIZE]=arr[i];
    }
    p->table.pages[page_i].index=needed_start_index/PAGE_SIZE;
    p->table.pages[page_i].last_reference_time=current_clock;
    p->table.pages[page_i].load_time=current_clock++;
    p->table.pages[page_i].M_bit=0;
    p->table.pages[page_i].R_bit=0;
    p->table.pages[page_i].second_chance=0;
}

void second_chance_replacement(my_program*p,int arr_index,int*arr) {
    int page_index=0;
    int page_i=0;
    int flag=0;
    while(!flag) {
        for(int i=0;i<NUMBER_OF_PAGE;i++) {
            if(p->table.pages[i].second_chance==0) {
                page_i=i;
                page_index=p->table.pages[i].index;
                flag=1;
                break;
            }
            else if(p->table.pages[i].second_chance==1) {
                p->table.pages[i].second_chance=0;
            }
        }
    }
    int needed_start_index=(arr_index/PAGE_SIZE)*PAGE_SIZE;
    for(int i=needed_start_index;i<(needed_start_index+PAGE_SIZE);i++) {
        p->table.pages[page_i].array[i%PAGE_SIZE]=arr[i];
    }
    p->table.pages[page_i].index=needed_start_index/PAGE_SIZE;
    p->table.pages[page_i].last_reference_time=
    p->table.pages[page_i].load_time=current_clock++;
    p->table.pages[page_i].M_bit=0;
    p->table.pages[page_i].R_bit=0;
    p->table.pages[page_i].second_chance=0;
}

void replace_page(my_program*p,int arr_index,int*arr) {
    if(fifo_flag==1) {
        fifo_replacement(p,arr_index,arr);
    }
    else if(lru_flag==1) {
        least_recently_used(p,arr_index,arr);
    }
    else if(second_chance_flag==1) {
        second_chance_replacement(p,arr_index,arr);
    }
    else {
        printf("ERROR DETECT TO REPLACEMENT ALGO\n");
    }
    loaded_page++;
    written_page++;
    return;
}



int* reference_memory(my_program*p,int arr[], int index) {
    int needed_page_index=(index/PAGE_SIZE);
    for(int i=0;i<NUMBER_OF_PAGE;i++) {
        if(p->table.pages[i].index==needed_page_index) {
            p->table.pages[i].last_reference_time=current_clock++;
            p->table.pages[i].R_bit=1;
            p->table.pages[i].second_chance=1;
            print_hit();
            return &(p->table.pages[i].array[index%PAGE_SIZE]);
        }
    }
    print_miss();
    replace_page(p,index,arr);
    return reference_memory(p,arr,index);
    
}

void write_back_to_disk(my_program*p,int*array) {
    for(int i=0;i<NUMBER_OF_PAGE;i++) {
        written_page++;
        for(int j=0;j<PAGE_SIZE;j++) {
            array[p->table.pages[i].index*PAGE_SIZE+j]=p->table.pages[i].array[j];
        }
    }
}
























void print_array(int*bubble,int*insertion,int*quick,int*disk,int n) {
    if(disk[0]!=bubble[0]) {
        printArray(bubble,n);
    }
    else if(disk[0]!=insertion[0]) {
        printArray(insertion,n);
    }
    else {
        printArray(quick,n);
    }
    if(miss_counter==0 && hit_counter==0) {

    }
    else {
        printf("TOTAL HIT:");
        char buf[50];      
        toChar(buf,(hit_counter));
        printf(buf);  
        printf("\n");

        printf("TOTAL MISS:");
        toChar(buf,(miss_counter));
        printf(buf);  
        printf("\n");

        printf("LOADED PAGE:");
        toChar(buf,(loaded_page));
        printf(buf);  

        printf("\nWRITTEN PAGE:");
        toChar(buf,(written_page));
        printf(buf);              
    }
}

#endif
 
