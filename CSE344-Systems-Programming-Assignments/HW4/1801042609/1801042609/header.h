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
#include <sys/sem.h>

#ifndef _HW4_HEADER_YTY
#define _HW4_HEADER_YTY

#define MAX_BLKSIZE 256
union semun {                   /* Used in calls to semctl() */
    int val;
    struct semid_ds * buf;
    unsigned short * array;
#if defined(__linux__)
    struct seminfo * __buf;
#endif
};


void handler(int signal_number,siginfo_t* siginfo,void*fd);
int check_arguments(int argc, char const *argv[]);
char* get_time(char* time);
void remove_semaphores();
void* supplier_thread(void*arg);
void* consumer_threads(void*arg);





#endif