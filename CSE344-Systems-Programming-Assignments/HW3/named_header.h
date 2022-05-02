#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <pthread.h>
#include <sys/wait.h>
#include <semaphore.h>

#ifndef MY_HEADER_NAMED
#define MY_HEADER_NAMED



#define MAX_BLKSIZE 1024
#define NUMBER_OF_CHEF 6
#define ENDLESS_SUPPLY 2
#define TOTAL_INGREDIENTS 4
#define TOTAL_CHILD (NUMBER_OF_CHEF + TOTAL_INGREDIENTS)
#define MEMORY_NAME "memory_name"

typedef struct shared_memory {
    char queue[2];
    int ismilk;
    int issugar;
    int isflour;
    int iswallnut;    
}shared_memory;

void handler(int signal_number,siginfo_t* siginfo,void*fd);

int create_shared_memory(int* fd, size_t size,char memory_name[MAX_BLKSIZE]);

void print_usage_and_exit();

#endif