# Midterm Notes

## Week 1 Summary

RT Sistemler 2 şekilde inceleniyor:

- Timeliness → işi zamanında yapma
- Throughput → yeterince çok iş yapma

### What is System?

Mapping of inputs into outputs

### What is Response Time?

Time interval between presentation of inputs and realization of outputs

### What is Failed System?

System cannot satisfy requirements

### What is Real Time System?

1. Must satisfy bounded response time constraints or risk severe consequences including failure
2. Logical correctness is based on the both correctness of the outputs and their timelines
3. Timeliness : Produce output at the right time
4. Predictability : Able to predict future consequences of current action
5. Testability : Requirements should be verified
6. Cost Optimality : Energy consumption, memory, CPU
7. Maintability : Easy to modify, extend, fix
8. Robustness : Handle peak loads, exception
9. Fault Tolerance : System should not crash

### Predictability Explained

For static systems, we can predict %100, but for dynamic system we can’t know the exact future

### What is Deadline?

Given time after a triggered event by which a response has to be completed

Real Time Systems are classifed into three based on their timing requirements

- Hard RTS
- Firm RTS
- Soft RTS

### Hard RTS

- Missing a deadline is catastrophic, can lead to a system failure or loss of a life
- Correctness is completely dependent on the timely completion of the tasks
- Ex : flight, medical equipments etc..

### Firm RTS

- Expected to meet deadlines most of the time, occasional misses are tolerable
- Ex: multimedia systems

### Soft RTS

- System is expected to produce results as soon as possible but missing a deadline is tolerable.
- Ex: video conferencing, file sharing

### What is Deterministic System?

For each possible state and each set of inputs, outputs and next state can be determined

### What is Event Determinism?

Next states and outputs are known for each set of inputs that trigger events

### What is Event?

Any occurence that causes the program counter to change non-sequentially

|  | Periodic | Aperiodic | Sporadic |
| --- | --- | --- | --- |
| Sync Event | Cyclic code | Conditional branch | Divide-by-zero |
| Async Event | Clock interrupt | Regular, but not fixed period | Power-loss |

Sporadic : reoccur that any random instant and have hard deadline, All critical tasks are sporadic.

### What is Arrival Time - Release Time

Time when a task becomes ready for execution

### What is Worst Case Execution Time

Time necesarry for completion of a task in the worst case scenario

### What is Task Period

Time interval between release time of periodic tasks

Period is actually deadline, we dont need any worst case exec time

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled.png)

Real time Systems are fast systems, there is no just one solution of them, each problem has its own solution. There is no more a need to build a RTOS, many exists

### What are Challenges?

- Impossible to know worst exec. time
- Cache, pipeline
- DMA stealing a CPU cycle
- Interrupt handling delay
- Priority inversion
- Dynamic memory management
- Communication Delays
- Potential Deadlocks, race conditions

## Week 2 Summary

Sistem tasarımlarını Soft Real time tarafına çekmeye çalışabiliriz

Hardware hakkında bilgi sahibi olmalıyız çünkü sistem dizayn ediyoruz, yazılım dizayn etmiyoruz

Strict timing ve latency requirementlarına uymak için inputtan outputa kadar delay pathlerini anlamalıyız

Time delayleri ikiye ayrılır

- Presentation of the input : Keyboard etc. → Excitation
- Generation of the input : → Response

An event starts from physical world, comes to the device driver, and then goes to the CPU, CPU makes request to the RAM, then CPU continues its job, then when data is ready, CPU uses it and if necesarry sends it to the device driver.

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%201.png)

### Von Neumann Arch

Inside CPU, there are Control Unit and ALU

Near the CPU, there is a memory unit.

And outside, there are input and output devices

### Instruction Processing

- Fetch : Read instruction from memory
- Decode : Interpret instruction
- Load : Fetch operands → read from memory
- Execute : Execute ALU function
- Store : Store result → write to the memory

Two different approaches to design the CPU

### Microprogramming

- Sequence of micro instructions stored in memory
- Each micro instruction corresponds to a specific operation that the control unit needs to perform, read - write memory
- Flexible and easier to modify

### Hardwired Logic

- Fixed set of electronic circuits, logic gates. Circuits are wired together in a specific way to produce the desired behavior.
- Control unit is determined at the time of design and cannot be changed without physically rewiring circuits
- Faster and more efficient

### What is peripheral device?

Peripheral device. An input/output unit of a system that feeds data into and/or receives data from the central processing unit of a digital device.

Two design approach for CPU to communicate with memory

### Memory Mapped IO

- Peripheral devices are mapped to CPU’s address space
- CPU can read - write data them using memory access instructions
- Treats the IO devices as if they are a part of the memory, access through memory address
- Simpler and more efficient

 

### Programmed IO

- CPU uses specialized input and output instructions to communicate.
- CPU uses special registers for these operations
- Finer control

between CPU and memory → fast bus speed

between CPU and IO → slow bus speed

Interrupt geldiğinde instruction ı bitirince program counter ve status register stack’e konulur.

Program counter, Interrupt Service Routine in başlangıc registerına eşitlenir.

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%202.png)

- Interrupts checked at the end of each instruction
- Response delay is not still predictable.
- Unexpected or variable delays may happen in the preempted task, Interrupt Service Routine is inside drivers, not in the OS.
- **Maskable interrupt :** can be temporarily disabled by the CPU. CPU can choose to ignore these interrupts if it is busy executing a critical section of code like OS kernel.
- **Nonmaskable interrupt :** interrupts that cannot be disabled or ignored. Power failure or hardware error. CPU must stop and handle interrupt.

Software interrupt : system call

### Dynamic RAM

- Requires periodic refreshing to maintain the charge on the capacitors.
- Simple and cheap to manufacture, provide high memory density, slow,higher power consumption
- Small size

### Static RAM

- Flip - flop circuit, faster than DRAM, lower power consumption.
- Expensive, lower memory density
- Big size

### Cache Hierarchy

Store data in DRAM → controlled by OS and apps

Store temporary copies of data into SRAM → controlled by processor hardware, more likely to used data is stored here

Temporal locality : Same region is going to be used soon → for loop iterator

Spatial locality : Close region is going to be used soon → array in a for loop

### Direct Mapped Cache

Each block of main memory is mapped to a unique location in the cache. Set of address bits from memory address is used.

Advantage : Simple, low hardware cost.

Disadvantage :  If two memory blocks are mapped to the same block in the cache, cache thrashing will happen.

Set associative caches can be used.

N- way set associate cache, cache N tane kümeye bölünüyor ve her seferinde adresi gruplardan bi tanesine atabiliyoruz.

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%203.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%204.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%205.png)

In Real Time Systems, there are drawbacks

- High miss rate degrades performance
- Effective Access time not deterministic
- Frequent switching among tasks violate locality principle

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%206.png)

Right one is better for spatial locality. It holds pointers

Prefetch  + Limited Cache = Infinite cache

Prefetch : predict and prevent cache miss

## Week 3 Summary

Data bustan hem instruction hem veriler geliyor

Von neumannda fetch - load - store birbirine bağlı, aynı bus ı kullanırlar, pipelining için uygun değil

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%207.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%208.png)

### Harvard Arch

- Require more physical space - two seperate bus
- DSP lerde kullanılır , Digital Signal Processor

There is Harvard Arch. inside CPU, Von Neumann Arch. outside CPU

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%209.png)

This ensures

- Better CPU utilization → overhead is : delay because of buffers between stages
- Unexpected jumps, external interrupts causes pipeline flushing

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2010.png)

### Branch Predictors

- Static : Based on the instruction only → branch will be or not be taken at compile time
- Dynamic : Based on the history of the instruction → Gather info about taken and not taken branches
- Random : Guarantee %50 prediction

### Dynamic Branch Predictors

- Local : keep history of each instruction
- Global : Keep a common history for all branch instruction

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2011.png)

random : 160ms

nonrandom : 15ms

### Why Multi-Core processors?

When Clock rate is > 3 GHz

- Higher power consumption
- High heat generation
- Difficult data sync

When Clock rate is < 3 GHz

- Increasing number of gate in the chip is not hard
- number of cores can increase

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2012.png)

### CPU vs GPU

CPU

- Optimized for sequential processing with less than 10 cores

GPU

- Optimized for parallel processing with more than 1000 cores
- Smaller cores for simpler tasks
- Hard to design parallel algos

### FPGA

Field Programmable Gate Array

We design the circuit and program it with VHDL or Verilog

We design CPU or download

It has fast response times

CPU to communicate with peripheral devices in 3 ways

IO bound → CPU az kullanır, IO yu çok kullanır

CPU bound → CPU yu çok kullanır, bırakmaz istemez, IO kullanmaz

### Polled IO

- Periodically check the status of the IO devices to determine if any data is available for processing. CPU cycles wasted for nonexisting input
- Sync IO

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2013.png)

### Interrupt Driven IO

- Input checking without CPU cycle waste
- Async IO
- Better response time, sleep not more than necesarry
- interrupted by the I/O device when data is available for processing.
- Read from device to CPU registers
- Write from CPU registers to memory
- Inefficent for large volume of data

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2014.png)

### DMA

Remove CPU from the copying process, Device reads - writes memory without CPU intervention

Burst Mode : CPU cannot access memory, but proceed with local cache - unpredictable stalls

Cycle - Stealing mode : CPU and Device time - share the bus -DMA takes longer but CPU does not stall

### Synchronous DMA

- Driver allocates DMA buffer and instructs IO device
- Device copies data using DMA
- Interrupt : Copy complete
- Process uses data

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2015.png)

### Asynchronous DMA

- IO device raises interrupt for requesting DMA
- Driver allocate DMA buffer and instructs IO device
- Device copies data using DMA
- Interrupt  : copy complete
- Process uses data

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2016.png)

Undersampling : az örnekleyerek frekansı kaybetme

Oversampling : gereğinden fazla örnekleme

## Week 4 Summary

Callbacks : Provides a mechanism to connect independently developed classes

For ex :

Class A is designed to detect an event

Class B is designed to process an event

There should not be dependency between classes so that each class can be reused seperately in another project

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2017.png)

What is functor : Sınıf () operatörünü override ediyosa bu sınıf bir functordur

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2018.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2019.png)

function 2 deki c stackte, ve m_bell.generatesound function2 bittikten çok daha sonra çağrılacak ve lambda functordaki int c nin referansı çoktan gitmiş olacak

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2020.png)

### Hardware wise storages

- Registers
- Cache (inside and outside of the CPU)
- Memory Hardware

### Software wise storage

- Stack → function calls, local vars
- Data segment → global and statics
- Heap → dynamic memory in C
- Free Store → dynamic memory inc C++

we have make_unique and make_shared instead of new, delete, malloc, calloc, and free

Stack and global → variable declared by the programmer, allocation made by the compiler

### Free Store

Stack and global allocations are fast, high chance of cache hit

A drawback : size needs to be known at compile time

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2021.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2022.png)

Second owner might want to delete pointer second time, double delete

What if we want to change owner of the pointer?

Owner cant be copied

We have move pointer

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2023.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2024.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2025.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2026.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2027.png)

function1(s) calls first one

function1(std::move) and function1(Sound()) calls second one

in move constructor we have to make the old one nullptr

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2028.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2029.png)

shared_ptr keeps count that how many owners are there

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2030.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2031.png)

When delete head, all linked list will be deleted.

To delete all of the double linked list, having a weak pointer is best. We could start from n3 and delete all.

If program is inefficient, if your program does not use usually IO, it is because of unnecesarry memory allocations

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2032.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2033.png)

make_unique : find a spare place in free store, we could have so many cache misses

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2034.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2035.png)

red and green ones are entities, with that way we can efficient program

Instead of next to each other pointers, have next to each other objects.

## Week 5 Summary

Concurrency : two or more threads running at the same time

### Seperation of concerns

Group related code together and keep code apart, make code easier to understand and test

### Performance

Parallel processing on multiple cores

**Task parallelism :** Divide a single task into parts and run each in parallel, reduce total running time

**Data parallelism :** Perform the same task on multiple sets of data concurrently

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2036.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2037.png)

becomes

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2038.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2039.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2040.png)

Detached thread should not use main threads fields

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2041.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2042.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2043.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2044.png)

### Race Condition

Thread1s timing causes undesired behavior in Thread2

Occur where completing an operation requires modification of two or more distinct pieces of data

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2045.png)

### How to avoid race conditions

- Protect invariants with locks
- Lock free programming
- Programming with transactions

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2046.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2047.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2048.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2049.png)

Operations are embedded inside atomic transactions

- BeginTransaction(), add,delete,update, CommitTransaction()

Commit one is built as thread safe

### All solutions introduce overhead

- Lock : Threads waiting for others, OS keeps track of synchronozation among threads
- Lock - free programming : Atomic operations inhibitng certain compiler and CPU optimizations
- Programming with transaction : Queueing

### Condition variables

std::condition_variable can wait() and notify(_all)

Acts with a mutex

### Signaling thread

1. Hold the mutex, operate on shared data
2. Call notify(_all)
3. Release mutex

### Waiting thread

1. Hold mutex, operate on shared data
2. Call wait(lock that owns mutex)
3. Mutex is automatically released upon wait and held again when wait returns
4. Consider spurious wakeups

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2050.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2051.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2052.png)

### RTOS

Provide basic support for

- Scheduling
- Resource Management
- Sync
- Communication
- Precise Timing
- IO

### Tasks as processes

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2053.png)

Threads sharing process space

Procceses as system level multitasking

Threads as process level multitasking

### Kernel Threads

Schedulable threads by OS

Processes have at least one main thread

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2054.png)

### What does kernel do?

- Scheduling
- Dispatching
- Interprocess communication

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2055.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2056.png)

Advantages :

- One CPU dedicated to a high speed input channel

Disadvantages:

- CPU cycle wasted
- Hard to implement complex system

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2057.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2058.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2059.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2060.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2061.png)

## Week 6 Summary

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2062.png)

Eğer packet_here flagini hemen birisi hazır hale getirmesin diye uğraşırsak delay var kullanabiliriz

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2063.png)

### Preemptive Priority Systems

One of scheduling algorihms that OS uses. Each process is assigned a priority level based on its importance.

### Rate Monotonic System

Higher execution rate: higher priority

- Task exec. with 10ms period : highest priority
- Task exec. with 1 sec period : lowest priority

### How process yields CPU?

- thread_yield
- mutex_lock
- sleep
- cond var wait

Bunlar dışında CPU task ı bitirmeden başka bir task çalıştırdıysa, bu CPU preemptive dir.

Scheduler : devide which task to execute next

Dispatcher : Put the scheduled task into the CPU

Task states : Executing, ready, suspended (blocked), dormant (some linux versions)

### TCB

Task Control Block Model

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2064.png)

### Hybrid Scheduling Systems

- FIFO
- Round Robin
- Earliest - deadline - first
- Noraml
- Batch

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2065.png)

### Pre-runtime Scheduling

- Guarantee execution order of tasks
- Prevent conflicting access to shared resources
- Optimize context switching overhead
- Kim ne zaman çalışacak belli
- 

### Runtime Scheduling

- Fixed or dynamic properties assigned to tasks
- Resources are allocated on this priority basis during runtime
- Complex runtime mechanism for tasks synchronizaation
- Kim ne zaman çalışacak belli değil
- Performans analizi istatistiksel

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2066.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2067.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2068.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2069.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2070.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2071.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2072.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2073.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2074.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2075.png)

Compiler işlem sırasını değiştirebilir

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2076.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2077.png)

Relaxed memory model → atomic but order can change

what if process_data takes longer time to execute?

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2078.png)

double buffering → opengl, directx

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2079.png)

read, write from/to queue

![https://github.com/TalhaYolcu/GTU-Assignments/raw/main/CSE437-Real-Time-Systems-Architecture/notlar/Week%206%203fb521bfbf49493794a1cf02f3ac8f27/Untitled%2031.png](https://github.com/TalhaYolcu/GTU-Assignments/raw/main/CSE437-Real-Time-Systems-Architecture/notlar/Week%206%203fb521bfbf49493794a1cf02f3ac8f27/Untitled%2031.png)

![https://github.com/TalhaYolcu/GTU-Assignments/raw/main/CSE437-Real-Time-Systems-Architecture/notlar/Week%206%203fb521bfbf49493794a1cf02f3ac8f27/Untitled%2032.png](https://github.com/TalhaYolcu/GTU-Assignments/raw/main/CSE437-Real-Time-Systems-Architecture/notlar/Week%206%203fb521bfbf49493794a1cf02f3ac8f27/Untitled%2032.png)

overflow, should notify consumer

### RingBuffer

- One reader one writer sync without lock
- Bost lock free queue : Multiple reader - writer buffer
- Using locks is gets better result

### Sync with locks

Coordinate access to critical sections of the code

- to avoid race conds
- to protect resources

Mutex : binary semaphore

Mutex : Protect critic section of code

Semaphore : Access resources with limited availability

Cond. var. : Signaling among tasks

Without help of OS :

- Spinlock : wait for an event to occur in a loop

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2080.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2081.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2082.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2083.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2084.png)

Starvation is problem in here

## Week 7 Summary

### Mutual Exclusion

Only one process or thread can access a shared resource at a time.

### Hold and Wait

Occur when a process holds a resource and waits for another resource currently being held by another process.

### Circular wait

Occur when a group of processes hold resources and are waiting for resources held by other processes in the group.

### Priority Inversion

Occur when a low priority process holds a resource that a higher priority process needs to access.

### Priority Ceiling Control

Concurrency control mechanism that is used to prevent prevent inversion. High priority task is not blocked by a lower priority task that is holding a shared resource.

Each shared resource is associated with a priority ceiling, highest priority among the processes that can access the resource. Priority is elevated to the ceiling while it is accessing the resource. Ensure that a high priority process cannot be blocked by a lower priority process that holds the resource

If a process attempts to access a shared resource that is already held by a lower-priority process, the priority of the lower-priority process is temporarily raised to the ceiling priority of the shared resource. This ensures that the higher-priority process can access the resource without being blocked by the lower-priority process.

### What is Procedure?

A series of computational steps to be carried out

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2085.png)

### Call by Value

- Parameter copied from caller into procedure’s formal parameter
- Procedure cannot alter callers parameter
- Actual parameter copying into runtime stack

### Call by Reference

- Address of the caller parameter is passed to procedure
- Procedure can alter callers parameter

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2086.png)

Global vars have less overhead but allow unauthorized access to parameters

May introduce bugs that are hard to isolate

we may recursion also.

Allocation of stack and copying parameters into the stack in each recursion step.

Number of recoursion steps is not known during compile time

Use iteration if possible

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2087.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2088.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2089.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2090.png)

### Data Abstraction - Messaging

- Seperate Abstract properties of data and Concrete details of its implementation
- Abstract property: Public
- Concrete detail : Private

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2091.png)

### Polymorphism

Provision of a single interface to entites of different types

### Static Polymorphism

Decide which function to use at compile time

Function overloading

### Dynamic Polymorphism

- Decide which function to use at runtime
- Virtual functions

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2092.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2093.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2094.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2095.png)

### Internal locking

Class contains mutex. Each public function acquires mmutex before processing and release after

### External locking

Caller of each public function associates a mutex with the object, and acquires it before calling a public method, and releases it after

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2096.png)

### Encapsulated Objects

Object is contained in a synchronized class

Object is only accessible through public methods of the synchronized class

No need for synchronization inside encapsulated class

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2097.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2098.png)

![Untitled](Midterm%20Notes%202b44c40f52b94b3a9fb5f72100adf322/Untitled%2099.png)

thread_local static değişken yaratır, global olur

### Objects Migrating betwen threads

- Object owned by a single thread
- No need for sync while accessing the objects, sync necesarry during transfer of ownership

Immutable Object : Require no sync

delete ten sonra nullptr ataması bug tespitini kolaylaştırır

Javada hata yapma imkanı daha az olduğu için C,C++ a göre daha çok tercih ediliyor

Real Time kodlarında Java kullanılmaz çünkü garbage collectiondan dolayı