#include "header.h"
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

//sigint flag
int terminate_flag=0;
//string contains -C argument
char count_arg[MAX_BLKSIZE];
//string contains -N argument
char number_arg[MAX_BLKSIZE];
//string contains -F argument
char inputfile_arg[MAX_BLKSIZE];
//loop time
int loop_n=0;
//number of consumers
int consumer_size=0;
//semaphore id
int semid=0;

pthread_t* consumers;

//./hw4 -C 10 -N 5 -F input.txt

//signal handler, if it receives a sigint, sets flag to 1
void handler(int signal_number,siginfo_t* siginfo,void*fd) {
    if(signal_number==SIGINT) {
        terminate_flag=1;
    }
}
//checks arguments
int check_arguments(int argc, char const *argv[]) {
    int i=0;

    if(argc!=7) {
        return -1;
    }

    int count_ok=0;
    int number_ok=0;
    int file_ok=0;

    for(i=1;i<argc;i++) {
        //consumer count
        if(argv[i][0]=='-' && argv[i][1]=='C') {
            count_ok=1;
        }
        //loop time
        else if(argv[i][0]=='-' && argv[i][1]=='N') {
            number_ok=1;
        }   
        //filepath
        else if(argv[i][0]=='-' && argv[i][1]=='F')  {
            file_ok=1;
        }                
    } 
    if(file_ok==1 && count_ok==1 && number_ok==1) {
        return 0;
    }
    return -1;
}

void print_usage_end_exit() {
    fprintf(stdout,"Usage:./hw4 -C 10 -N 5 -F input.txt\n");
    exit(-1);
}

//returns time as a string without \n
char* get_time(char* time) {
    int len=strlen(time);
    time[len-1]='\0';
    return time;
}

//removes the semaphores
void remove_semaphores() {
    if (semctl(semid, 0, IPC_RMID) == -1) {    
        perror("semctl-removing");
        return;
    }  
}
void cancel_threads() {
   // printf("Canceling threads\n");
    for(int i=0;i<consumer_size;i++) {
        pthread_cancel(consumers[i]);
    }
    //printf("Canceling ended\n");
}

void* supplier_thread(void*arg) {

    if(terminate_flag==1) {      
        pthread_exit(NULL);
    }

    char read_char='\0';

    //open input file
    int read_input_fd=open(inputfile_arg,(O_RDONLY),0777);
    if(read_input_fd==-1) {
        perror("Error open to input file");
        pthread_exit(NULL);
    }

    if(terminate_flag==1) {       
        close(read_input_fd);
        pthread_exit(NULL);
    }

    while(1) {
        //sleep(1);
        //read 1 byte
        int read_byte=read(read_input_fd,&read_char,1);
        if(terminate_flag==1) {  
            cancel_threads();     
            close(read_input_fd);
            pthread_exit(NULL);
        }        
        if(read_byte==-1) {
            perror("Error on read");
            close(read_input_fd);
            pthread_exit(NULL);
        }
        if(read_byte==0) {
            break;
        }
        if(read_char=='1') {
            union semun getvalues;
            unsigned short values[2]={0,0};
            getvalues.array=values;
            //get the semaphore values to print
            if (semctl(semid, 0, GETALL, getvalues) == -1) {
                perror("semctl-GETALL");         
                close(read_input_fd);
                pthread_exit(NULL);                 
            }
            if(terminate_flag==1) {       
                close(read_input_fd);
                pthread_exit(NULL);
            }              
            time_t curtime;

            time(&curtime);

            fprintf(stdout,"%s => Supplier: read from input a ‘1’. Current amounts: %d x ‘1’, %d x ‘2’.\n",get_time(ctime(&curtime)),getvalues.array[0],getvalues.array[1]);
            //post first semaphore
            struct sembuf sops;
            sops.sem_flg=0;
            sops.sem_num = 0;
            sops.sem_op = 1;
            if(semop(semid, &sops, 1)==-1) {
                perror("Error on semop 1");       
                close(read_input_fd);
                pthread_exit(NULL);   
            }
            if(terminate_flag==1) {  
                            cancel_threads();        
                close(read_input_fd);
                pthread_exit(NULL);
            }           
            //get the semaphore values to print   
            if (semctl(semid, 0, GETALL, getvalues) == -1) {
                perror("semctl-GETALL");        
                close(read_input_fd);
                pthread_exit(NULL);   
            }
            if(terminate_flag==1) {  
                            cancel_threads();        
                close(read_input_fd);
                pthread_exit(NULL);
            }   
            time(&curtime);
                       
            fprintf(stdout,"%s => Supplier: delivered a ‘1’. Post-delivery amounts: %d x ‘1’, %d x ‘2’.\n",get_time(ctime(&curtime)),getvalues.array[0],getvalues.array[1]);            
        }
        if(read_char=='2') {
            union semun getvalues;
            unsigned short values[2]={0,0};
            getvalues.array=values;
            //get the semaphore values to print
            if (semctl(semid, 0, GETALL, getvalues) == -1) {
                perror("semctl-GETALL");          
                close(read_input_fd);
                pthread_exit(NULL);   
            }
            if(terminate_flag==1) {  
                            cancel_threads();        
                close(read_input_fd);
                pthread_exit(NULL);
            }   
            time_t curtime;

            time(&curtime);            
            fprintf(stdout,"%s => Supplier: read from input a ‘2’. Current amounts: %d x ‘1’, %d x ‘2’.\n",get_time(ctime(&curtime)),getvalues.array[0],getvalues.array[1]);            
            //post second semaphore
            struct sembuf sops;
            sops.sem_flg=0;
            sops.sem_num = 1;
            sops.sem_op = 1;
            if(semop(semid, &sops, 1)==-1) {
                perror("Error on semop 2");       
                close(read_input_fd);
                pthread_exit(NULL);   
            }
            if(terminate_flag==1) {       
                close(read_input_fd);
                cancel_threads();
                pthread_exit(NULL);
            }   
            //get the semaphre values to print
            if (semctl(semid, 0, GETALL, getvalues) == -1) {
                perror("semctl-GETALL");    
                close(read_input_fd);
                pthread_exit(NULL);    
            }
            if(terminate_flag==1) {   
                cancel_threads();
                close(read_input_fd);
                pthread_exit(NULL);
            }   
            time(&curtime);
            fprintf(stdout,"%s => Supplier: delivered a ‘2’. Post-delivery amounts: %d x ‘1’, %d x ‘2’.\n",get_time(ctime(&curtime)),getvalues.array[0],getvalues.array[1]);   
            //sleep(1);
        }
    }


    if(close(read_input_fd)==-1) {
        perror("Error on close input file");
    }   
    time_t curtime;

    time(&curtime);  
    fprintf(stdout,"%s => The Supplier has left.\n",get_time(ctime(&curtime))); 
    pthread_exit(NULL);   

}

void kill_others(int index) {
    for(int i=0;i<consumer_size;i++) {
        if(i!=index) {
            pthread_cancel(consumers[i]);
        }
    }
}

void* consumer_threads(void*arg) {
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

    //consumer number
    int consumer_number=*(int*)arg;
    free(arg);

    int i=0;
    for(i=0;i<loop_n;i++) {
        //sleep(1);
        if(terminate_flag==1) { 
            kill_others(consumer_number);      
            pthread_exit(NULL);
        } 
        //adjust wait values
        struct sembuf sops[2];
        sops[0].sem_num = 0;
        sops[0].sem_op = -1;
        sops[0].sem_flg=0;

        sops[1].sem_num = 1;
        sops[1].sem_op = -1;
        sops[1].sem_flg=0;

        union semun getvalues;
        unsigned short values[2]={0,0};
        getvalues.array=values;
        //get the semaphore values to print
        if (semctl(semid, 0, GETALL, getvalues) == -1) {
            perror("semctl-GETALL 1 in consumer");  
            pthread_exit(NULL);    
        }
        if(terminate_flag==1) { 
            kill_others(consumer_number);      
            pthread_exit(NULL);
        }  
        time_t curtime;

        time(&curtime);           
        fprintf(stdout,"%s => Consumer-%d at iteration %d (waiting). Current amounts: %d x '1', %d x '2'.\n",get_time(ctime(&curtime)),consumer_number,i,getvalues.array[0],getvalues.array[1]);

        //wait both of the semaphores just 1 time
        if(semop(semid, sops, 2) == -1) {
            if (terminate_flag==1) {
                kill_others(consumer_number);
                pthread_exit(NULL);
            }            
            perror("Error on semop waiting on 1 and 2");

            pthread_exit(NULL);
        }

        if (terminate_flag==1) {
            kill_others(consumer_number);
            perror("GG\n");
            pthread_exit(NULL);
        }
        //get semaphore values to print
        if (semctl(semid, 0, GETALL, getvalues) == -1) {
            perror("semctl-GETALL 2 in consumer"); 
            pthread_exit(NULL);
        }
        if(terminate_flag==1) {  
            kill_others(consumer_number);     
            pthread_exit(NULL);
        }  
        time(&curtime);           
       
        fprintf(stdout,"%s => Consumer-%d at iteration %d (consumed). Post-consumption amounts: %d x '1', %d x '2'.\n",get_time(ctime(&curtime)),consumer_number,i,getvalues.array[0],getvalues.array[1]);

        //sleep(1);
    }
    time_t curtime;

    time(&curtime);    
    fprintf(stdout,"%s => Consumer-%d has left.\n",get_time(ctime(&curtime)),consumer_number);
    return NULL;
}