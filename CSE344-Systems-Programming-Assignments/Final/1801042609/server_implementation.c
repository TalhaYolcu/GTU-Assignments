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
#include "structs.h"

#define FILE_NAME_LEN 30
#define MAX_BLKSIZE 1024
#define MAX_THREAD 256


//todo
//bütün sigint leri kontrol et
//eğer available servant yoksa -1 döndür



int number_of_threads=0;        //number of threads
char port_number_char[FILE_NAME_LEN];   //port number of socket
sig_atomic_t terminate_flag=0;          //sigint flag
int port_number=0;
pthread_mutex_t mutex;
fake_servant* servants;
int servant_counter=0;
pthread_cond_t cond;
Queue* my_q;
int handled_requests=0;
pthread_mutex_t m_servant_ctr;

int check_input_validity(int argc,char const *argv[]);
void* run_thread(void*arg);
void handler(int signal_number);

//returns time as a string without \n
char* get_time(char* time) {
    char* my_time=(char*)malloc(sizeof(char)*512);
    memset(my_time,0,512);
    strncpy(my_time,time,strlen(time)-1);
    return my_time;
}



// function to create a queue
// of given capacity.
// It initializes size of queue as 0
struct Queue* createQueue(unsigned capacity)
{
    struct Queue* queue = (struct Queue*)malloc(
        sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
 
    // This is important, see the enqueue
    queue->rear = capacity - 1;
    queue->array = (int*)malloc(
        queue->capacity * sizeof(int));
    return queue;
}
 
// Queue is full when size becomes
// equal to the capacity
int isFull(struct Queue* queue)
{
    return (queue->size == queue->capacity);
}
 
// Queue is empty when size is 0
int isEmpty(struct Queue* queue)
{
    return (queue->size == 0);
}
 
// Function to add an item to the queue.
// It changes rear and size
void enqueue(struct Queue* queue, int item)
{
    if (isFull(queue))
        return;


    pthread_mutex_lock(&mutex);
    queue->rear = (queue->rear + 1)
                  % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
    //printf("%d enqueued to queue\n", item);
    pthread_mutex_unlock(&mutex);
}
 
// Function to remove an item from queue.
// It changes front and size
int dequeue(struct Queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;

    
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1)
                   % queue->capacity;
    queue->size = queue->size - 1;
    //printf("%d dequeued from queue\n",item);
    return item;
}
 
// Function to get front of queue
int front(struct Queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    return queue->array[queue->front];
}
 
// Function to get rear of queue
int rear(struct Queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    return queue->array[queue->rear];
}


//signal handler, if it receives a sigint, sets flag to 1
void handler(int signal_number) {
    if(signal_number==SIGINT) {
        terminate_flag=1;
    }
}


int check_input_validity(int argc,char const *argv[]) {
    
    //./server -p 33000 -t 11 &
    
    if(argc<5 || argc>6) {
        return -1;
    }

    int port_ok=0;
    int thread_num_ok=0;


    for(int i=1;i<argc;i++) {
        //port
        if(argv[i][0]=='-' && argv[i][1]=='p') {
            port_ok=1;
        }   
        //thread_num
        else if(argv[i][0]=='-' && argv[i][1]=='t')  {
            thread_num_ok=1;
        }   

    } 
    if(port_ok==1 && thread_num_ok==1) {
        return 0;
    }
    return -1;  
}

void send_kill_signal_to_servants() {
    for(int i=0;i<servant_counter;i++) {
        kill(servants[i].pid,SIGINT);
    }
}

void* run_thread(void*arg) {
    //int thread_index=*(int*)arg;
    free(arg);

    while(terminate_flag==0) {

        pthread_mutex_lock(&mutex);
        while(terminate_flag==0 && my_q->size<1) {
            pthread_cond_wait(&cond,&mutex);
        }

        if(terminate_flag==1) {
            pthread_mutex_unlock(&mutex);
            pthread_cond_broadcast(&cond);
            pthread_mutex_unlock(&m_servant_ctr);

            send_kill_signal_to_servants();
            return NULL;
        }
        int request_fd=dequeue(my_q);
        pthread_mutex_unlock(&mutex);

        char* request=(char*)malloc(sizeof(char)*512);
        memset(request,0,512);

        //receive data
        int veri_boyutu = read(request_fd, request, 512);
        //fprintf(stderr,"Incoming:%s\n",request);
        if(terminate_flag==1) {
            close(request_fd);
            send_kill_signal_to_servants();
            free(request);
            return NULL;
        }
        if(veri_boyutu < 0){
            perror("Error on receive reading request");
            close(request_fd);
            free(request);
            send_kill_signal_to_servants();
            return NULL;
        }
        //fprintf(stdout, "Received data: %s\n",request);
        if(request==NULL) {
            send_kill_signal_to_servants();
            close(request_fd);
            free(request);
            return NULL;            
        }
        if(strlen(request)==0) {
            send_kill_signal_to_servants();
            close(request_fd);
            free(request);
            return NULL;
        }

        char* copy_of_request=(char*)malloc(sizeof(char)*512);
        memset(copy_of_request,0,512);
        strncpy(copy_of_request,request,512);

        char*buf=copy_of_request;
        char*first_token=strtok_r(buf," ",&buf);

        const char* cl="CLIENT";
        const char* srvnt="SERVANT";

        if(strncmp(first_token,cl,strlen(cl))==0) {
            
            int result=0;
            char*null=strtok_r(buf," ",&buf);
            null[0]='\0';
            char* transaction_type=strtok_r(buf," ",&buf);
            char* date1=strtok_r(buf," ",&buf);
            char* date2=strtok_r(buf," ",&buf);
            //printf("%s %s %s\n",transaction_type,date1,date2);
            char* city=strtok_r(buf," ",&buf);

            time_t curtime;
            time(&curtime);

            

            if(city==NULL) {
                //run all servants

                char* my_time=get_time(ctime(&curtime));

                fprintf(stdout,"%s => Contacting ALL servants\n",my_time);
                free(my_time);

                pthread_mutex_lock(&m_servant_ctr);
                int servant_ctr_loop=servant_counter;
                pthread_mutex_unlock(&m_servant_ctr);

                for(int i=0;i<servant_ctr_loop;i++) {
                    char* msg=(char*)malloc(sizeof(char)*512);
                    memset(msg,0,512);
                    sprintf(msg,"transactionCount %s %s %s",transaction_type,date1,date2);

                    time(&curtime);
                    char* stamp=get_time(ctime(&curtime));
                    fprintf(stdout,"%s => Request arrived \"transactionCount %s %s %s\"\n",stamp,transaction_type,date1,date2);
                    free(stamp);

                    //socket i sadece haberleşeceğin zaman aç
                    struct sockaddr_in serv_addr;
                    memset(&serv_addr, 0, sizeof(serv_addr));
                    int sock = socket(AF_INET, SOCK_STREAM, 0);

                    if(sock<0) {
                        perror("Error on socket");
                        free(copy_of_request);
                        free(request);
                        free(msg);
                        send_kill_signal_to_servants();
                        close(request_fd);
                        return NULL;
                    }
                    serv_addr.sin_family = AF_INET;
                    serv_addr.sin_port = htons(servants[i].port_number);

                    if(terminate_flag==1) {
                        send_kill_signal_to_servants();
                        free(copy_of_request);
                        free(request);
                        free(msg);
                        close(request_fd);
                        close(sock);

                        return NULL;
                    }
                    if(inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr)<0) {
                        perror("Error on inet pton");
                        send_kill_signal_to_servants();
                        free(copy_of_request);
                        free(request);
                        free(msg);
                        close(request_fd);
                        close(sock);

                        return 0;
                    } 
                    int servant_fd=0;
                    // Sunucuya bağlanma
                    servant_fd=connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
                    if(servant_fd< 0 ){
                        perror("Error on connect to servant a servant");
                        send_kill_signal_to_servants();
                        free(copy_of_request);
                        free(request);
                        free(msg);
                        close(request_fd);
                        close(sock);
                        return NULL;

                    }
                    if(terminate_flag==1) {
                        send_kill_signal_to_servants();
                        free(msg);
                        free(copy_of_request);
                        free(request);
                        close(request_fd);
                        close(sock);
                        //close(servant_fd);

                        return NULL;
                    }

                    servants[i].fd=servant_fd;
                    servants[i].socket_num=sock;
                    if(send(servants[i].socket_num,msg,512,0)<0) {
                        perror("Error on send");
                        send_kill_signal_to_servants();
                        free(copy_of_request);
                        free(request);
                        free(msg);
                        close(request_fd);
                        close(servants[i].socket_num);
                        //close(servant_fd);

                        return NULL;
                    }

                    char* recv_servant=(char*)malloc(sizeof(char)*512);
                    memset(recv_servant,0,512);

                    int veri_boyutu = read(servants[i].socket_num, recv_servant, 512);
                    if(veri_boyutu < 0){
                        perror("Error on receive reading a servant response");
                        free(msg);
                        free(recv_servant);
                        free(copy_of_request);
                        free(request);
                        send_kill_signal_to_servants();
                        close(request_fd);
                        close(servants[i].socket_num);
                        //close(servant_fd);

                        return NULL;
                    }  

                    close(servants[i].socket_num);
                    result+=atoi(recv_servant);

                    if(terminate_flag==1) {
                        free(copy_of_request);
                        free(request);
                        send_kill_signal_to_servants();
                        free(msg);
                        free(recv_servant); 
                        close(request_fd);      
                        //close(servant_fd);

                        return NULL;                 
                    }
                    free(msg);
                    free(recv_servant);
                    //close(servant_fd);

                }
                char client_response_buf[512];
                memset(client_response_buf,0,512);

                sprintf(client_response_buf,"%d",result);
                if(send(request_fd,client_response_buf,512,0)<0) {
                    perror("Error on send");
                    free(copy_of_request);
                    free(request);
                    send_kill_signal_to_servants();
                    close(request_fd);
                    return NULL;
                } 

                handled_requests++;
                time(&curtime);
                char* stamp=get_time(ctime(&curtime));                
                fprintf(stdout,"%s => Response received: %d, forwarded to client\n",stamp,result);
                free(stamp);
                if(terminate_flag==1) {
                    send_kill_signal_to_servants();
                    free(copy_of_request);
                    free(request);       
                    close(request_fd); 
                    return NULL;            
                }
            }
            else {
                //find servant
                int flag=0;
                pthread_mutex_lock(&m_servant_ctr);
                int temp_serv_ctr=servant_counter;
                pthread_mutex_unlock(&m_servant_ctr);
                for(int i=0;i<temp_serv_ctr;i++) {
                    
                    if(terminate_flag==1) {
                        free(copy_of_request);
                        free(request);
                        return NULL;
                    }

                    if(city==NULL) {
                        perror("city is NULL");
                        return NULL;
                    }
                    if(servants[i].start_city==NULL) {
                        //fprintf(stderr,"servant index:%d\n",i);
                        //fprintf(stderr,"Servant pid:%d\n",servants[i].pid);
                        //fprintf(stderr,"Servant port:%d\n",servants[i].port_number);
                        //fprintf(stderr,"Servant counter:%d\n",servant_counter);
                        perror("Servant start city is NULL");
                        free(copy_of_request);
                        free(request);
                        return NULL;
                    }
                    if(servants[i].end_city==NULL) {
                        perror("Servant end city NULL");
                        return NULL;
                    }

                    if(strncmp(city,servants[i].start_city,strlen(servants[i].start_city))>=0 && strncmp(city,servants[i].end_city,strlen(servants[i].end_city))<=0) {
                        time(&curtime);
                        char* my_time=get_time(ctime(&curtime));
                        
                        fprintf(stdout,"%s => Contacting servant %d\n",my_time,servants[i].pid);
                        free(my_time);
                        
                        flag=1;
                        char* msg=(char*)malloc(sizeof(char)*512);
                        memset(msg,0,512);
                        sprintf(msg,"transactionCount %s %s %s %s",transaction_type,date1,date2,city);
                        time(&curtime);
                        my_time=get_time(ctime(&curtime));

                        fprintf(stdout,"%s => Request arrived \"transactionCount %s %s %s %s\"\n",my_time,transaction_type,date1,date2,city);
                        free(my_time);

                        //socket i sadece haberleşeceğin zaman aç
                        struct sockaddr_in serv_addr;
                        memset(&serv_addr, 0, sizeof(serv_addr));
                        int sock = socket(AF_INET, SOCK_STREAM, 0);

                        if(sock<0) {
                            perror("Error on socket");
                            free(msg);
                            free(copy_of_request);
                            free(request);
                            close(request_fd);
                            close(sock);
                            return NULL;
                        }
                        serv_addr.sin_family = AF_INET;
                        serv_addr.sin_port = htons(servants[i].port_number);

                        if(servants[i].ip_address==NULL) {
                            free(msg);
                            free(copy_of_request);
                            free(request);
                            return NULL;
                        }

                        if(inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr)<0) {
                            perror("Error on inet pton");
                            free(msg);
                            free(copy_of_request);
                            free(request);   
                            close(request_fd); 
                            close(sock);                        
                            return NULL;
                        }

                        
                        int servant_fd=0;
                        // Sunucuya bağlanma
                        servant_fd=connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
                        if( servant_fd< 0 ){
                            perror("Error on connect to specific servant");
                            free(msg);
                            free(copy_of_request);
                            free(request);
                            close(sock);
                            close(request_fd);
                            return NULL;
                        }

                        servants[i].fd=servant_fd;
                        servants[i].socket_num=sock;

                        if(terminate_flag==1) {
                            free(msg);
                            free(copy_of_request);
                            free(request);
                            //close(servant_fd);

                            close(sock);
                            close(request_fd);
                            send_kill_signal_to_servants();
                            return NULL;
                        }


                        if(send(servants[i].socket_num,msg,512,0)<0) {
                            perror("Error on send");
                            send_kill_signal_to_servants();
                            free(msg);
                            free(copy_of_request);
                            free(request);
                            close(sock);
                            close(request_fd);
                            //close(servant_fd);

                            return NULL;
                        }

                        char* servant_response=(char*)malloc(sizeof(char)*512);
                        memset(servant_response,0,512);

                        int veri_boyutu = read(servants[i].socket_num, servant_response, 512);
                        if(veri_boyutu < 0){
                            perror("Error on receive reading specific server response");
                            free(msg);
                            free(copy_of_request);
                            free(request);
                            free(servant_response);
                            close(request_fd);
                            //close(servant_fd);

                            close(sock);
                            send_kill_signal_to_servants();
                            return NULL;
                        }  

                        if(terminate_flag==1) {
                            free(msg);
                            free(copy_of_request);
                            free(request);
                            free(servant_response);
                            close(request_fd);
                            //close(servant_fd);

                            close(sock);
                            send_kill_signal_to_servants();
                            return NULL;
                        }
                        close(servants[i].socket_num);

                        if(send(request_fd,servant_response,512,0)<0) {
                            perror("Error on send");
                            free(msg);
                            free(copy_of_request);
                            free(request);
                            //close(servant_fd);

                            free(servant_response);
                            close(request_fd);
                            send_kill_signal_to_servants();
                            return NULL;
                        }     

                        handled_requests++;

                        result=atoi(servant_response);
                        time(&curtime);
                        my_time=get_time(ctime(&curtime));

                        

                        fprintf(stdout,"%s => Response received: %d, forwarded to client\n",my_time,result);
                        free(my_time);

                        if(terminate_flag==1) {
                            send_kill_signal_to_servants();
                            free(msg);
                            free(copy_of_request);
                            free(request);
                            free(servant_response);
                            //close(servant_fd);

                            close(request_fd);
                            return NULL;
                        }
                        free(servant_response);
                        free(msg);
                        //close(servant_fd);

                        break;
                    }
                }

                if(flag==0) {
                    //perror("Error could not find the available servant");
                    char* response_to_client=(char*)malloc(sizeof(char)*512);
                    memset(response_to_client,0,512);

                    sprintf(response_to_client,"-1");

                    if(send(request_fd,response_to_client,512,0)<0) {
                        perror("Error on send");
                        free(response_to_client);
                        free(request);
                        free(copy_of_request);
                        close(request_fd);
                        send_kill_signal_to_servants();
                        return NULL;
                    }     
                    free(response_to_client);
                }
            }
        }
        else if(strncmp(first_token,srvnt,strlen(srvnt))==0) {
            //fprintf(stderr,"servant tanitma buf :%s\n",buf);
            char* pid_char=strtok_r(buf," ",&buf);
            char* port_char=strtok_r(buf," ",&buf);
            char* ip_address_of_servant=strtok_r(buf," ",&buf);
            char* first_city=strtok_r(buf," ",&buf);
            char* last_city=strtok_r(buf," ",&buf);

            pthread_mutex_lock(&m_servant_ctr);
            int temp_serv_ctr=servant_counter;
            pthread_mutex_unlock(&m_servant_ctr);

            servants[temp_serv_ctr].pid=atoi(pid_char);
            servants[temp_serv_ctr].port_number=atoi(port_char);
            
            servants[temp_serv_ctr].start_city=(char*)malloc(sizeof(char)*512);
            servants[temp_serv_ctr].end_city=(char*)malloc(sizeof(char)*512);
            servants[temp_serv_ctr].ip_address=(char*)malloc(sizeof(char)*512);

            memset(servants[temp_serv_ctr].start_city,0,512);
            memset(servants[temp_serv_ctr].end_city,0,512);
            memset(servants[temp_serv_ctr].ip_address,0,512);

            if(first_city==NULL) {
                perror("Error, first city is NULL");
                close(request_fd);
                return NULL;
            }
            if(last_city==NULL) {
                perror("Error, last city is NULL");
                close(request_fd);

                return NULL;
            }
            if(ip_address_of_servant==NULL) {
                perror("Error, ip address is NULL");
                close(request_fd);

                return NULL;
            }

            strncpy(servants[temp_serv_ctr].start_city,first_city,strlen(first_city));
            strncpy(servants[temp_serv_ctr].end_city,last_city,strlen(last_city));
            strncpy(servants[temp_serv_ctr].ip_address,ip_address_of_servant,strlen(ip_address_of_servant));


            if(servants[temp_serv_ctr].start_city==NULL) {
                perror("Error, Servant start city is NULL when know servant");
                close(request_fd);

                return NULL;
            }

            //printf("SERVANT: %d %d %s %s %s\n",servants[servant_counter].pid,servants[servant_counter].port_number,servants[servant_counter].ip_address,servants[servant_counter].start_city,servants[servant_counter].end_city);
            time_t curtime;
            time(&curtime);
            char* my_time=get_time(ctime(&curtime));

            fprintf(stdout,"%s => Servant %d present at port %d handling cities %s-%s\n",my_time,servants[servant_counter].pid,servants[servant_counter].port_number,servants[servant_counter].start_city,servants[servant_counter].end_city);
            free(my_time);

            pthread_mutex_lock(&m_servant_ctr);            
            servant_counter++;
            pthread_mutex_unlock(&m_servant_ctr);

            if(terminate_flag==1) {
                send_kill_signal_to_servants();
                free(request);
                free(copy_of_request);
                close(request_fd);
                return NULL;
            }

        }
        
        else {
            perror("Error, unknown data");
            free(request);
            free(copy_of_request);            
            send_kill_signal_to_servants();
            close(request_fd);
            return NULL;
        }
        
        free(request);
        free(copy_of_request);
        close(request_fd);

    }

    return NULL;
}