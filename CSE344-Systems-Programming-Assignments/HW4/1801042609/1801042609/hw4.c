#include <stdio.h>
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
#include "implementation.c"
#include "header.h"
//./hw4 -C 10 -N 5 -F input.txt



int main(int argc, char const *argv[])
{   
    //cancel buffering
    if(setvbuf (stdout, NULL, _IONBF, 0)!=0) {
        perror("Error on cancel buffering");
        exit(-1);
    }
    //signal stuff
    struct sigaction sa; 
    memset(&sa,0,sizeof(sa));
    sa.sa_flags=SA_SIGINFO;
    if(sigemptyset(&sa.sa_mask)!=0) {
        perror("Error on sigemptyset");
        exit(-1);
    }
    sa.sa_sigaction=handler;
    if(sigaction(SIGINT,&sa,NULL)!=0) {
        perror("Error on sigaction");
        exit(-1);
    }


    //initialize arguments
    memset(count_arg,0,MAX_BLKSIZE);
    memset(number_arg,0,MAX_BLKSIZE);
    memset(inputfile_arg,0,MAX_BLKSIZE);

    //check argument validity
    if(check_arguments(argc,argv)!=0) {
        perror("Error with arguments");
        print_usage_end_exit();
    }

    int i=0;
    //take arguments
    for(i=1;i<argc;i++) {
        if(argv[i][0]=='-' && argv[i][1]=='C') {
            strncpy(count_arg,argv[i+1],strlen(argv[i+1]));
        }
        else if(argv[i][0]=='-' && argv[i][1]=='N') {
            strncpy(number_arg,argv[i+1],strlen(argv[i+1]));
        }  
        else if(argv[i][0]=='-' && argv[i][1]=='F') {
            strncpy(inputfile_arg,argv[i+1],strlen(argv[i+1]));
        }                           
    }     


    loop_n=atoi(number_arg);
    consumer_size=atoi(count_arg);

    //more argument check
    if(consumer_size<=4 || loop_n<=1) {
        perror("Error with arguments");
        print_usage_end_exit();
    }

    //create semaphores
    union semun arg;
    unsigned short values[2]={0,0};

    arg.array=values;

    int nsems=2;
    semid=semget(IPC_PRIVATE,nsems, S_IRUSR | S_IWUSR);
    if(semid==-1) {
        perror("Error on semget 1");
        exit(-1);
    }

    int ignore=0;
    //initialize them to 0
    if(semctl(semid,ignore,SETALL,arg)==-1) {
        perror("Error on semctl while initializing to 0");
        exit(-1);
    }

    //create supplier thread
    pthread_t supplier;
    consumers=(pthread_t*)malloc(sizeof(pthread_t)*consumer_size);
    void* nullptr=NULL;
    int error_s=pthread_create(&supplier,NULL,supplier_thread,nullptr);
    if(error_s==-1) {
        perror("Error on pthread create supplier");
        exit(-1);
    }

    //detach it
    int error_detach=pthread_detach(supplier);
    if(error_detach==-1) {
        perror("Error while making detach supplier");
        pthread_exit(NULL);
    }

    //create consumer threads
  
    for(i=0;i<consumer_size;i++) {
        //it will be freed in the thread
        int* index=(int*)malloc(sizeof(int));
        *index=i;
        //send thread number as an argument
        int error_c=pthread_create(&consumers[i],NULL,consumer_threads,index);
        if(error_c==-1) {
            perror("Error on pthread create consumer");
            pthread_exit(NULL);
        }
    }


    //join consumer threads
    for(i=0;i<consumer_size;i++) {
        void*  nullptr; 
        int error_jc=pthread_join(consumers[i],&nullptr);
        if(terminate_flag==1) {

        }        
        if(error_jc!=0) {
            perror("Error on pthread join");
            pthread_exit(NULL);
        }
    }   
    free(consumers);
    //remove the semaphores 
    remove_semaphores();
    pthread_exit(NULL);

}