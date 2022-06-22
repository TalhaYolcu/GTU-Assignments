#include <stdio.h>
#include "client_implementation.c"
#include <sys/types.h>
#include <fcntl.h>
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


int main(int argc, char const *argv[]){
    
    //./client -r requestFile -q PORT -s IP

    if(check_input_validity(argc,argv)!=0) {
        perror("Error, there is a problem with arguemnts");
        fprintf(stdout,"Usage:./client -r requestFile -q PORT -s IP\n");
        return 0;
    }

    char req_file[FILE_NAME_LEN];

    //signal stuff
    struct sigaction sa; 
    memset(&sa,0,sizeof(sa));
    if(sigemptyset(&sa.sa_mask)!=0) {
        perror("Error on sigemptyset");
        exit(-1);
    }
    //sa.sa_sigaction=handler;
    sa.sa_handler=&handler;
    if(sigaction(SIGINT,&sa,NULL)!=0) {
        perror("Error on sigaction");
        exit(-1);
    }



    memset(req_file,0,FILE_NAME_LEN);
    memset(port_number_char,0,FILE_NAME_LEN);
    memset(ip_address,0,FILE_NAME_LEN);

    for(int i=1;i<argc;i++) {
        //req_file
        if(argv[i][0]=='-' && argv[i][1]=='r') {
            strcpy(req_file,argv[i+1]);
        }
        //port
        else if(argv[i][0]=='-' && argv[i][1]=='q') {
            strcpy(port_number_char,argv[i+1]);

        }   
        //ip
        else if(argv[i][0]=='-' && argv[i][1]=='s')  {
            strcpy(ip_address,argv[i+1]);
        }          
    }

    port_number=atoi(port_number_char);

    //printf("File:%s\nPort:%d\nIP address:%s\n",req_file,port_number,ip_address);

    int req_file_fd=open(req_file,(O_RDONLY),0777);

    if(req_file_fd==-1) {
        perror("Error, could not open file");
        return 0;
    }

    int bytes_read=0;
    char read_char='\0';

    while(1) {
        bytes_read=read(req_file_fd,&read_char,1);
        if(bytes_read==-1) {
            perror("Error on read");
            close(req_file_fd);
            return 0;
        }
        if(bytes_read==0) {
            //end of file
            break;
        }
        if(read_char=='\n') {
            number_of_threads++;
        }
    }
    //printf("Number of threads:%d\n",number_of_threads);

    read_buffer=(char**)malloc(number_of_threads*sizeof(char*));
    for(int i=0;i<number_of_threads;i++) {
        read_buffer[i]=(char*)malloc(MAX_BLKSIZE*sizeof(char));
        memset(read_buffer[i],0,MAX_BLKSIZE);
    }
    int buffer_counter=0;
    int char_counter=0;
    close(req_file_fd);

    req_file_fd=open(req_file,(O_RDONLY),0777);
    if(req_file_fd==-1) {
        perror("Error, could not open file");
        return 0;
    }

    while(1) {
        bytes_read=read(req_file_fd,&read_char,1);
        if(bytes_read==-1) {
            perror("Error on read");
            close(req_file_fd);
            return 0;
        }
        if(bytes_read==0) {
            //end of file
            break;
        }
        if(read_char!='\n') {
            read_buffer[buffer_counter][char_counter++]=read_char;
        }
        if(read_char=='\n') {
            if(char_counter!=0) {
                char_counter=0;
                buffer_counter++;
            }
        }
    }   
    close(req_file_fd);

    if(terminate_flag==1) {
        return 0;
    }

    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&condition,NULL);

    int prev_number_of_threads=number_of_threads;
    number_of_threads=buffer_counter;
    pthread_t threads[number_of_threads];
    //create threads

    fprintf(stdout,"Client:I have loaded %d requests and I'm creating %d threads\n",number_of_threads,number_of_threads);

    for(int i=0;i<number_of_threads;i++) {
        int*index=(int*)malloc(sizeof(int));
        *index=i;
        if(pthread_create(&threads[i],NULL,run_thread,(void*)index)!=0) {
            perror("Error on pthread_create");
            return 0;
        }
    }
    //wait for threads

    for(int i=0;i<number_of_threads;i++) {
        if(pthread_join(threads[i],NULL)!=0) {
            perror("Error on pthread join");
            return 0;
        }
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condition);

    fprintf(stdout,"Client: All threads have terminated, goodbye.\n");


    for(int i=0;i<prev_number_of_threads;i++) {
        free(read_buffer[i]);
    }
    free(read_buffer);

    return 0;
}
