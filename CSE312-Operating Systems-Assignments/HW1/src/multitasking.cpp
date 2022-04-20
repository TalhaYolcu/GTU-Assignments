
#include <multitasking.h>
//#include "mythread.cpp"

using namespace myos;
using namespace myos::common;

extern "C" int int_bottom();
void printfHex(uint8_t key);
void printf(char* buf);

Task::Task(GlobalDescriptorTable *gdt, void entrypoint())
{
    cpustate = (CPUState*)(stack + 4096 - sizeof(CPUState));
    
    cpustate -> eax = 0;
    cpustate -> ebx = 0;
    cpustate -> ecx = 0;
    cpustate -> edx = 0;

    cpustate -> esi = 0;
    cpustate -> edi = 0;
    cpustate -> ebp = 0;
    
    /*
    cpustate -> gs = 0;
    cpustate -> fs = 0;
    cpustate -> es = 0;
    cpustate -> ds = 0;
    */
    
    // cpustate -> error = 0;    
   
    // cpustate -> esp = ;
    cpustate -> eip = (uint32_t)entrypoint;
    cpustate -> cs = gdt->CodeSegmentSelector();
    // cpustate -> ss = ;
    cpustate -> eflags = 0x202;

    //procedure=&Task::exec;
    //calling=entrypoint;
    //cpustate->eip=(uint32_t)entrypoint;

    //this->id=id;


    
}

Task::~Task()
{
}


        
TaskManager::TaskManager()
{
    numTasks = 0;
    currentTask =-1;
}

TaskManager::~TaskManager()
{
}

bool TaskManager::AddTask(Task* task)
{
    if(numTasks >= 256)
        return false;
    tasks[numTasks++] = task;
    return true;
}

bool TaskManager::TerminateTask(Task* task) {
    //set state as finished
    task->taskState=FINISHED_T;

    printf("TERMINATED\n");  
    //call interrupt
    //this function does not return back  
    int_bottom();

}

bool TaskManager::ExitTask() {
    return TerminateTask(tasks[currentTask]);
}

bool TaskManager::YieldTask(Task* task) {
    //set yielded task id
    yielded=currentTask;
    

    //int_bottom();
}
bool TaskManager::YieldTask() { 
    printf("\nTASK YIELDED\n");
    YieldTask(tasks[currentTask]);
    
    //int_bottom();
    //printf("GG");
}

bool TaskManager::JoinTask() {
    JoinTask(tasks[currentTask]);
}
bool TaskManager::JoinTask(Task* task) {
    printf("\nTASK JOINED\n");
    //set joined task id
    joined=currentTask;
    //int_bottom();
}

int TaskManager::getnumTask() {
    return numTasks;
}


CPUState* TaskManager::Schedule(CPUState* cpustate)
{   
    
    //printf("\nINTERRUPT HAPPENED\n");
    if(numTasks <= 0) {
        return cpustate;
    }
    if(currentTask >= 0) {
        tasks[currentTask]->cpustate = cpustate;
    }

    //remove finished tasks from array
    for(int i=0;i<numTasks;i++) {
        if(tasks[i]->taskState==FINISHED_T) {
            int index_s=i;
            for(index_s=i;index_s<(numTasks-1);index_s++) {
                tasks[index_s]=tasks[index_s+1];
            }
            numTasks--;
            //set the order
            currentTask--;
        }
    } 
    //continue execution I could not do other than that, It never execute the current task again, I had to execute it again so.
    if(yielded!=-1) {     
        currentTask=yielded-1;
        yielded=-1;

    }
    //Continue its execution
    if(joined!=-1) {
        currentTask=joined-1;
        joined=-1;
    }
    if(++currentTask >= numTasks) {
        currentTask %= numTasks;
    }
    return tasks[currentTask]->cpustate;

}

    