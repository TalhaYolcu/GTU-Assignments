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
#include "server_implementation.c"
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[])
{
    //./server -p 33000 -t 11 &
    if(check_input_validity(argc,argv)!=0) {
        perror("Error, there is a problem with arguemnts");
        fprintf(stdout,"Usage:./server -p 33000 -t 11 &\n");
        return 0;
    }
    pthread_cond_init(&cond,NULL);
    pthread_mutex_init(&mutex,NULL);
    pthread_mutex_init(&m_servant_ctr,NULL);

    memset(port_number_char,0,FILE_NAME_LEN);
    char thread_num_char[FILE_NAME_LEN];
    memset(thread_num_char,0,FILE_NAME_LEN);

    //signal stuff
    struct sigaction sa; 
    memset(&sa,0,sizeof(sa));
    if(sigemptyset(&sa.sa_mask)!=0) {
        perror("Error on sigemptyset");
        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&cond);
        exit(-1);
    }
    //sa.sa_sigaction=handler;
    
    sa.sa_handler=&handler;
    if(sigaction(SIGINT,&sa,NULL)!=0) {
        perror("Error on sigaction");
        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&cond);
        exit(-1);
    }

    for(int i=1;i<argc;i++) {
        //port
        if(argv[i][0]=='-' && argv[i][1]=='p') {
            strcpy(port_number_char,argv[i+1]);
        }   
        //thread_num
        else if(argv[i][0]=='-' && argv[i][1]=='t')  {
            strcpy(thread_num_char,argv[i+1]);
        }   
    }
    my_q=createQueue(512);

    //printf("Port number:%s\n",port_number_char);
    number_of_threads=atoi(thread_num_char);

    if(number_of_threads<5) {
        perror("Error, number of threads should be greater than 5");
        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&cond);
        free(my_q);
        free(my_q->array);
        return 0;
    }

    //printf("Thread count:%d\n",number_of_threads);
    port_number=atoi(port_number_char);

    int server_fd=socket(AF_INET,SOCK_STREAM,0);

    if(server_fd<0) {
        perror("Error on first socket");
        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&cond);
        free(my_q->array);
        free(my_q);
        
        return 0;
    }

    struct sockaddr_in address;
    int addrlen=sizeof(address);
    memset(&address,0,sizeof(address));
    address.sin_family=AF_INET;
    address.sin_addr.s_addr=INADDR_ANY;
    address.sin_port=htons(port_number);



    if(bind(server_fd,(struct sockaddr*)&address,(socklen_t)addrlen)<0) {
        perror("Error on bind");
        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&cond);
        free(my_q->array);
        free(my_q);
        close(server_fd);
        return 0;
    }

    if(listen(server_fd,512)<0) {
        perror("Error on listen");
        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&cond);
        free(my_q->array);
        free(my_q);
        close(server_fd);
        return 0;
    }


    pthread_t threads[number_of_threads];
    //create threads


    for(int i=0;i<number_of_threads;i++) {
        int*index=(int*)malloc(sizeof(int));
        *index=i;

        if(pthread_create(&threads[i],NULL,run_thread,(void*)index)!=0) {
            perror("Error on pthread_create");
            pthread_mutex_destroy(&mutex);
            pthread_cond_destroy(&cond);
            free(my_q->array);
            free(my_q);
            close(server_fd);
            return 0;
        }
    }
    
    servants=(fake_servant*)malloc(sizeof(fake_servant)*number_of_threads);
    memset(servants,0,sizeof(fake_servant)*number_of_threads);

    int client_fd=0;
    struct sockaddr_in client_addr;
    socklen_t client_addr_size=sizeof(client_addr);
    while(1) {
        if(terminate_flag==1) {
            pthread_cond_broadcast(&cond);
            break;
        }
        client_fd=accept(server_fd,(struct sockaddr*)&client_addr,(socklen_t*)&client_addr_size);
        //printf("NEW ACCEPT\n");
        if(terminate_flag==1) {
            pthread_cond_broadcast(&cond);
            break;
        }
        if(client_fd==-1) {
            perror("Error while accepting");
            break;
        }
        if(terminate_flag==1) {
            pthread_cond_broadcast(&cond);        
            break;
        }
        enqueue(my_q,client_fd);
        client_fd=0;
        pthread_cond_signal(&cond);
    }

    send_kill_signal_to_servants();



    //wait for threads

    for(int i=0;i<number_of_threads;i++) {
        if(pthread_join(threads[i],NULL)!=0) {
            perror("Error on pthread join");
            return 0;
        }
    } 
    close(server_fd);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&m_servant_ctr);

    time_t curtime;
    time(&curtime);
    char* my_time=get_time(ctime(&curtime));
    fprintf(stdout,"%s => SIGINT has been received. I handled a total of %d requests. Goodbye.\n",my_time,handled_requests);
    free(my_time);
    for(int i=0;i<servant_counter;i++) {
        free(servants[i].end_city);
        free(servants[i].ip_address);
        free(servants[i].start_city);
        close(servants[i].socket_num);
    }
    free(servants);

    int size=my_q->size;

    for(int i=0;i<size;i++) {
        int temp_fd=dequeue(my_q);
        close(temp_fd);
    }

    free(my_q->array);
    free(my_q);

    return 0;
}
