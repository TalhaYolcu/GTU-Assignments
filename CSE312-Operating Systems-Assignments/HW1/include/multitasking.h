 
#ifndef __MYOS__MULTITASKING_H
#define __MYOS__MULTITASKING_H

#include <common/types.h>
#include <gdt.h>

extern "C" int int_bottom();


namespace myos
{
    #define BLOCKED_T 1
    #define READY_T 0
    #define FINISHED_T 2
    
    struct CPUState
    {
        common::uint32_t eax;
        common::uint32_t ebx;
        common::uint32_t ecx;
        common::uint32_t edx;

        common::uint32_t esi;
        common::uint32_t edi;
        common::uint32_t ebp;

        /*
        common::uint32_t gs;
        common::uint32_t fs;
        common::uint32_t es;
        common::uint32_t ds;
        */
        common::uint32_t error;

        common::uint32_t eip;
        common::uint32_t cs;
        common::uint32_t eflags;
        common::uint32_t esp;
        common::uint32_t ss;        
    } __attribute__((packed));
    
    
    class Task
    {
    friend class TaskManager;
    private:
        common::uint8_t stack[4096]; // 4 KiB
        CPUState* cpustate;
        int taskState=READY_T;


    public:
        Task(GlobalDescriptorTable *gdt, void entrypoint());
        ~Task();    
            
    };
    
    
    class TaskManager
    {
    private:
        Task* tasks[256];
        int numTasks=0;//number of tasks
        int currentTask;//curent task id
        int yielded=-1;//yielded task is
        int joined=-1;//joined task id

    public:
        TaskManager();
        ~TaskManager();
        bool TerminateTask(Task* task);
        bool AddTask(Task* task);
        bool YieldTask(Task* task);
        bool YieldTask();
        bool JoinTask();
        bool JoinTask(Task* task);        
        bool ExitTask();
        int getnumTask();

        CPUState* Schedule(CPUState* cpustate);
    };
    
    
    
}


#endif