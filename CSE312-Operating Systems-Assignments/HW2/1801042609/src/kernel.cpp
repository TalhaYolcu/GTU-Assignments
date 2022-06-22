
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
#include "structs.h"
#include "common.c"
#include "insertion_sort.c"
#include "bubble_sort.c"
#include "quick_sort.c"
// #define GRAPHICSMODE


using namespace myos;
using namespace myos::common;
using namespace myos::drivers;
using namespace myos::hardwarecommunication;
using namespace myos::gui;






class PrintfKeyboardEventHandler : public KeyboardEventHandler
{
public:
    void OnKeyDown(char c)
    {
        char* foo = " ";
        foo[0] = c;
        printf(foo);
    }
};

class MouseToConsole : public MouseEventHandler
{
    int8_t x, y;
public:
    
    MouseToConsole()
    {
        uint16_t* VideoMemory = (uint16_t*)0xb8000;
        x = 40;
        y = 12;
        VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
                            | (VideoMemory[80*y+x] & 0xF000) >> 4
                            | (VideoMemory[80*y+x] & 0x00FF);        
    }
    
    virtual void OnMouseMove(int xoffset, int yoffset)
    {
        static uint16_t* VideoMemory = (uint16_t*)0xb8000;
        VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
                            | (VideoMemory[80*y+x] & 0xF000) >> 4
                            | (VideoMemory[80*y+x] & 0x00FF);

        x += xoffset;
        if(x >= 80) x = 79;
        if(x < 0) x = 0;
        y += yoffset;
        if(y >= 25) y = 24;
        if(y < 0) y = 0;

        VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
                            | (VideoMemory[80*y+x] & 0xF000) >> 4
                            | (VideoMemory[80*y+x] & 0x00FF);
    }
    
};





void taskA()
{
    while(true)
        printf("A");
}
void taskB()
{
    while(true)
        printf("B");
}






typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}



extern "C" void kernelMain(const void* multiboot_structure, uint32_t /*multiboot_magic*/)
{

    GlobalDescriptorTable gdt;
    
    
    uint32_t* memupper = (uint32_t*)(((size_t)multiboot_structure) + 8);
    size_t heap = 10*1024*1024;
    MemoryManager memoryManager(heap, (*memupper)*1024 - heap - 10*1024);
    
    void* allocated = memoryManager.malloc(1024);

    
    TaskManager taskManager;
    /*
    Task task1(&gdt, taskA);
    Task task2(&gdt, taskB);
    taskManager.AddTask(&task1);
    taskManager.AddTask(&task2);
    */
    
    InterruptManager interrupts(0x20, &gdt, &taskManager);
    
    
    #ifdef GRAPHICSMODE
        Desktop desktop(320,200, 0x00,0x00,0xA8);
    #endif
    
    DriverManager drvManager;
    
        #ifdef GRAPHICSMODE
            KeyboardDriver keyboard(&interrupts, &desktop);
        #else
            PrintfKeyboardEventHandler kbhandler;
            KeyboardDriver keyboard(&interrupts, &kbhandler);
        #endif
        drvManager.AddDriver(&keyboard);
        
    
        #ifdef GRAPHICSMODE
            MouseDriver mouse(&interrupts, &desktop);
        #else
            MouseToConsole mousehandler;
            MouseDriver mouse(&interrupts, &mousehandler);
        #endif
        drvManager.AddDriver(&mouse);
        
        PeripheralComponentInterconnectController PCIController;
        PCIController.SelectDrivers(&drvManager, &interrupts);

        VideoGraphicsArray vga;
        
        drvManager.ActivateAll();
        

    #ifdef GRAPHICSMODE
        vga.SetMode(320,200,8);
        Window win1(&desktop, 10,10,20,20, 0xA8,0x00,0x00);
        desktop.AddChild(&win1);
        Window win2(&desktop, 40,15,30,30, 0x00,0xA8,0x00);
        desktop.AddChild(&win2);
    #endif




 


    int disk_array[DISK_ARRAY_SIZE];
    int insertion_sort_array[DISK_ARRAY_SIZE];
    int bubble_sort_array[DISK_ARRAY_SIZE];
    int quick_sort_array[DISK_ARRAY_SIZE];
    for(int i=0;i<DISK_ARRAY_SIZE;i++) {
        disk_array[i]=DISK_ARRAY_SIZE-i;
        
        
        
        
        insertion_sort_array[i]=disk_array[i];
        bubble_sort_array[i]=disk_array[i];
        quick_sort_array[i]=disk_array[i];
        char buf[50];      
        toChar(buf,(disk_array[i]));
        printf(buf);
        printf(" ");
    }

    my_program p;

    //page index = DISK ARRAY SIZE / NUMBER OF PAGE
    
    for(int i=0;i<NUMBER_OF_PAGE;i++) {
        p.table.pages[i].last_reference_time=0;
        p.table.pages[i].load_time=i;
        p.table.pages[i].M_bit=0;
        p.table.pages[i].R_bit=0;
        p.table.pages[i].second_chance=0;
        p.table.pages[i].index=i;
        loaded_page++;
        for(int j=0;j<PAGE_SIZE;j++) {
            p.table.pages[i].array[j]=disk_array[i*PAGE_SIZE+j];
        }
    }



    fifo_flag=0;
    lru_flag=0;
    second_chance_flag=1;    
    if(lru_flag==1) {
        printf("\nLRU ALGORITHM\n");
    }
    else if(second_chance_flag==1) {
        printf("\nSECOND CHANCE ALGORITHM\n");
    }
    else if(fifo_flag==1) {
        printf("\nFIFO ALGORITHM\n");
    }   
    //bubble_operation(&p,bubble_sort_array);
    insertion_operation(&p,insertion_sort_array);
    //quick_operation(&p,quick_sort_array);

    

























































    for(int i=0;i<DISK_ARRAY_SIZE;i++) {
        insertion_sort_array[i]=disk_array[i];
        bubble_sort_array[i]=disk_array[i];
        quick_sort_array[i]=disk_array[i];        
    }

    bubble_ex(bubble_sort_array,DISK_ARRAY_SIZE);
    insertion_ex(insertion_sort_array,DISK_ARRAY_SIZE);
    quick_ex(quick_sort_array,0,DISK_ARRAY_SIZE-1);

    print_array(bubble_sort_array,insertion_sort_array,quick_sort_array,disk_array,DISK_ARRAY_SIZE);


	
    interrupts.Activate();
    
    while(1)
    {
        #ifdef GRAPHICSMODE
            desktop.Draw(&vga);
        #endif
    }
}
