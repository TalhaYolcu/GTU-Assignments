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
#include "unnamed_header.h"
#include "unnamed_implementation.c"

/*
ex input
MS
FM
WS
SM
*/

int main(int argc, char const *argv[]) {
    //check argument validity
   int result_of_arguments=check_arguments(argc,argv);
    if(result_of_arguments==-1) {
        print_usage_and_exit();
    }
    int i;

    char inputfilepath[MAX_BLKSIZE];

    memset(inputfilepath,0,MAX_BLKSIZE*sizeof(char));


    //take argument
    for(i=1;i<argc;i++) {
        if(argv[i][0]=='-' && argv[i][1]=='i' && i!=(argc-1)) {
            strncpy(inputfilepath,argv[i+1],strlen(argv[i+1]));
        }                    
    }     

    struct sigaction sa; 
    memset(&sa,0,sizeof(sa));
    sa.sa_flags=SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction=handler;
    sigaction(SIGUSR1,&sa,NULL);

    int memory_fd=0;
    //create shared memory and initialize semaphores
    if(create_shared_memory(&memory_fd,sizeof(shared_memory))==-1) {
        perror("Error create memory");
        exit(-1);
    }

    int child_number=TOTAL_CHILD;
    //6 chef + 4 pusher
    int childpids[TOTAL_CHILD];
    memset(childpids,0,TOTAL_CHILD*sizeof(int));

    for(int i=0;i<TOTAL_CHILD;i++) {
        int pid=fork();
        if(pid==0) {
            //child

            if(i<TOTAL_INGREDIENTS) {
                pusher(i);
                destroy_semaphore_for_child();
                return 0;
            }
            else {
                char endless_supply[ENDLESS_SUPPLY];
                char needed_supply[TOTAL_INGREDIENTS-ENDLESS_SUPPLY];
                memset(endless_supply,0,sizeof(char)*ENDLESS_SUPPLY);
                memset(needed_supply,0,sizeof(char)*(TOTAL_INGREDIENTS-ENDLESS_SUPPLY));

                if(i==4) {
                    endless_supply[0]='M';
                    endless_supply[1]='F';
                    needed_supply[0]='W';
                    needed_supply[1]='S';
                    number_of_desserts=chef(endless_supply,needed_supply,i-4);
                    if(destroy_semaphore_for_child()==-1) {
                        return -1;
                    }
                    return number_of_desserts;                    
                }
                else if(i==5) {
                    endless_supply[0]='M';
                    endless_supply[1]='S';
                    needed_supply[0]='W';
                    needed_supply[1]='F';
                    number_of_desserts=chef(endless_supply,needed_supply,i-4);
                    if(destroy_semaphore_for_child()==-1) {
                        return -1;
                    }
                    return number_of_desserts;
                }
                else if(i==6) {
                    endless_supply[0]='M';
                    endless_supply[1]='W';
                    needed_supply[0]='S';
                    needed_supply[1]='F';
                    number_of_desserts=chef(endless_supply,needed_supply,i-4);
                    if(destroy_semaphore_for_child()==-1) {
                        return -1;
                    }
                    return number_of_desserts;
                }
                else if(i==7) {
                    endless_supply[0]='S';
                    endless_supply[1]='W';
                    needed_supply[0]='F';
                    needed_supply[1]='M';
                    number_of_desserts=chef(endless_supply,needed_supply,i-4);
                    if(destroy_semaphore_for_child()==-1) {
                        return -1;
                    }
                    return number_of_desserts;
                }
                else if(i==8) {
                    endless_supply[0]='S';
                    endless_supply[1]='F';
                    needed_supply[0]='M';
                    needed_supply[1]='W';
                    number_of_desserts=chef(endless_supply,needed_supply,i-4);
                    if(destroy_semaphore_for_child()==-1) {
                        return -1;
                    }
                    return number_of_desserts;
                }                                                
                else {
                    endless_supply[0]='F';
                    endless_supply[1]='W';
                    needed_supply[0]='M';
                    needed_supply[1]='S';
                    number_of_desserts=chef(endless_supply,needed_supply,i-4);
                    if(destroy_semaphore_for_child()==-1) {
                        return -1;
                    }
                    return number_of_desserts;
                }


            }

        }
        else {
            //parent
            childpids[i]=pid;

        }
    }

    int fd=open(inputfilepath,(O_RDONLY),0777);
    if(fd==-1) {
        perror("Input file open error");
        //send terminate signals to the childs
        for(int i=0;i<child_number;i++){
            if(send_terminate_signal_to_the_child(childpids[i])==-1) {
                perror("Error");
            }
        }
        
    }

    char read_char='\0';
    int read_byte=0;
    int row_count=0;
    char read_ingredients[2];    
    memset(read_ingredients,0,(2)*sizeof(char));


    while(1) {

        read_byte=read(fd,&read_char,1);
        if(read_byte==0) {
            //end of file

            if(read_ingredients[0]=='\0') {
                break;
            }

            strncpy(shared_ptr->queue,read_ingredients,2);
            shared_ptr->queue[0]=read_ingredients[0];
            shared_ptr->queue[1]=read_ingredients[1];            

            if(increment_ingredients(read_ingredients)==-1) {
                perror("Error increment ingredients");
                break;
            }

            row_count=0;
            memset(read_ingredients,0,(2)*sizeof(char));

            break;
        }
        else if(read_byte==-1) {
            perror("Error reading file");
            //send terminate signal to the childs
            for(int i=0;i<child_number;i++){
                if(send_terminate_signal_to_the_child(childpids[i])==-1) {
                    perror("Error");
                }
            }            
            break;
        }
        if(read_char=='\n') {
            //put to the shared memory

            strncpy(shared_ptr->queue,read_ingredients,2);
            shared_ptr->queue[0]=read_ingredients[0];
            shared_ptr->queue[1]=read_ingredients[1];             
           
            if(increment_ingredients(read_ingredients)==-1) {
                perror("Error increment ingredients");
                break;
            }
            row_count=0;
            memset(read_ingredients,0,(2)*sizeof(char));

        }
        else {
            //read next letter
            read_ingredients[row_count]=read_char;
            row_count++;
        }
    }
    //send terminate signal to the childs
    for(int i=0;i<child_number;i++){
        if(send_terminate_signal_to_the_child(childpids[i])==-1) {
            perror("Error");
        }
    }        

    //sum the total desserts
    for(int i=0;i<child_number;i++){
        int result_of_wait=wait_for_child(childpids[i]);
        if(i>=4) {
            if(result_of_wait==-1) {
                perror("Error");
            }
            else {
                number_of_desserts+=result_of_wait;
            }
        }
        else {
            if(result_of_wait==-1) {
                perror("Error");
            } 
        }
    } 

    if(close(fd)==-1) {
        perror("Error close input file");        
    }

    fprintf(stdout,"the wholesaler (pid %d) is done (total desserts: %d)\n",getpid(),number_of_desserts);   


    if(destroy_semaphores()==-1) {
        perror("Error destroying semaphores");
    }
    
    if(destroy_shared_memory(memory_fd)==-1) {
        perror("Error destroying shared memory");
        exit(-1);
    }

    return 0;
}
