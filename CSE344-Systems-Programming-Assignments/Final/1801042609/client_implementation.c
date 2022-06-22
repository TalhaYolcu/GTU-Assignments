
#define FILE_NAME_LEN 30
#define MAX_BLKSIZE 1024
#define MAX_THREAD 256

#include <stdio.h>
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
#include <sys/socket.h>
#include <arpa/inet.h>

int arrived=0;                  //number of arrived thread
pthread_cond_t condition;       //condition variable for synchronization barrier
pthread_mutex_t mutex;          //mutex for synchronization barrier
int number_of_threads=0;        //number of threads
char port_number_char[FILE_NAME_LEN];   //port number of socket
char ip_address[FILE_NAME_LEN];         //ip address of socket
sig_atomic_t terminate_flag=0;          //sigint flag
char** read_buffer=NULL;

int port_number=33000;
int unique_port_number=0;


int check_input_validity(int argc,char const *argv[]);
void* run_thread(void*arg);
void handler(int signal_number);


//signal handler, if it receives a sigint, sets flag to 1
void handler(int signal_number) {
    if(signal_number==SIGINT) {
        terminate_flag=1;
    }
}


int check_input_validity(int argc,char const *argv[]) {
    
    //./client -r requestFile -q PORT -s IP
    
    if(argc!=7) {
        return -1;
    }

    int req_file_ok=0;
    int port_ok=0;
    int ip_ok=0;


    for(int i=1;i<argc;i++) {
        //req_file
        if(argv[i][0]=='-' && argv[i][1]=='r') {
            req_file_ok=1;
        }
        //port
        else if(argv[i][0]=='-' && argv[i][1]=='q') {
            port_ok=1;
        }   
        //ip
        else if(argv[i][0]=='-' && argv[i][1]=='s')  {
            ip_ok=1;
        }   

    } 
    if(req_file_ok==1 && port_ok==1 && ip_ok==1) {
        return 0;
    }
    return -1;  
}

void* run_thread(void*arg) {
    int thread_index=*(int*)arg;
    free(arg);
    int sock=0;
    //printf("This is thread number %d\n",thread_index);
    fprintf(stdout,"Client-Thread-%d: Thread-%d has been created\n",thread_index,thread_index);


    pthread_mutex_lock(&mutex);
    if(terminate_flag==1) {
        pthread_mutex_unlock(&mutex);
    }
    ++arrived;   
    //synchronization barrier
    while(arrived<number_of_threads) {   
        if(terminate_flag==1) {
            break;
        }   
        pthread_cond_wait(&condition,&mutex);  
        if(terminate_flag==1) {
            break;
        }       
    }    
    pthread_cond_broadcast(&condition);
    pthread_mutex_unlock(&mutex);
    //after barrier    

    if(terminate_flag==1) {
        return NULL;
    }

    //printf("Threads have passed the barrier\n");


    //connect to socket

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if(sock<0) {
        perror("Error on socket");
        return 0;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port_number);

    if(inet_pton(AF_INET,ip_address,&serv_addr.sin_addr)<0) {
        perror("Error on inet pton");
        return 0;
    }    

    // Sunucuya bağlanma
    int client_fd=connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if(client_fd< 0 ){
        perror("Error on connect");
        return NULL;
    }
    char* msg=(char*)malloc(sizeof(char)*512);
    memset(msg,0,512);

    if(read_buffer[thread_index][strlen(read_buffer[thread_index])-1]==' ') {
        read_buffer[thread_index][strlen(read_buffer[thread_index])-1]='\0';
    }

    sprintf(msg,"CLIENT %s",read_buffer[thread_index]);

    fprintf(stdout,"Client-Thread-%d: I am requesting \"%s\"\n",thread_index,read_buffer[thread_index]);


    if(send(sock,msg,512,0)<0) {
        perror("Error on send");
        return NULL;
    }
    free(msg);

   //wait for response
    //receive
    char incoming_response[512];
    memset(incoming_response,0,512);

    if(read(sock,incoming_response,512)<0) {
        perror("Error on receive");
    }
    if(terminate_flag==1) {
        close(sock);
        return NULL;
    }
    close(sock); 


    int response=atoi(incoming_response);

    if(response==-1) {
        fprintf(stdout,"Error-Client-Thread-%d: The server’s response to \"%s\" is %d - There is no servant responsible\n",thread_index,read_buffer[thread_index],response);

    }
    else {
        fprintf(stdout,"Client-Thread-%d: The server’s response to \"%s\" is %d\n",thread_index,read_buffer[thread_index],response);
    }
    
    fprintf(stdout,"Client-Thread-%d: Terminating\n",thread_index);

    //close(client_fd);
    return NULL;
}