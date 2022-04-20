#include <signal.h>
#include <errno.h>
#include <stdio.h>
#include "fifo_seqnum.h"
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <pthread.h>
#include<sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int flag=0;
int sigusr1flag=0;
int worker_can_read=0;
int sigusr2flag=0;
shared_memory shared;
shared_memory* shared_ptr;
shared_memory temp;
int total_request,invertible_request;
struct worker_z * workers;
int pool_size_z=0;

void handler(int signal_number,siginfo_t* siginfo,void*fd) {
    if(signal_number==SIGINT) {
        flag=1;
    }
    if(signal_number==SIGUSR1) {
        sigusr1flag=1;
    }
    if(signal_number==SIGUSR2) {
        sigusr2flag=1;
    }
}

void print_time_stamp() {
    struct timeval tv;
    time_t t;
    struct tm *info;

    gettimeofday(&tv, NULL);
    t = tv.tv_sec;

    info = localtime(&t);

    char* temp=(char*)malloc(sizeof(char)*MAX_BLKSIZE);
    memset(temp,0,MAX_BLKSIZE);

    strncpy(temp,asctime (info),strlen(asctime(info)));

    temp[strlen(temp)-1]=' ';

    printf("%s => ",temp); 

    free(temp);   
}

void print_when_sigint_received() {
    print_time_stamp();
    printf("Z:SIGINT received, exiting server Z, Total request handled %d, %d invertible, %d not.\n",total_request,invertible_request,total_request-invertible_request);
}

void getCofactor(int** mat, int** temp, int p,int q, int n){
    int i = 0, j = 0;
 
    // Looping for each element of the matrix
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            //  Copying into temporary matrix only those
            //  element which are not in given row and
            //  column
            if (row != p && col != q)
            {
                temp[i][j++] = mat[row][col];
 
                // Row is filled, so increase row index and
                // reset col index
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}
 
/* Recursive function for finding determinant of matrix.
   n is current dimension of mat[][]. */
int determinantOfMatrix(int** mat, int n){
    int D = 0; // Initialize result
 
    //  Base case : if matrix contains single element
    if (n == 1)
        return mat[0][0];
 
    int** temp; // To store cofactors
    temp=(int**)malloc(sizeof(int*)*n);
    int i;
    for(i=0;i<n;i++) {
        temp[i]=(int*)malloc(sizeof(int));
    }
 
    int sign = 1; // To store sign multiplier
 
    // Iterate for each element of first row
    for (int f = 0; f < n; f++)
    {
        // Getting Cofactor of mat[0][f]
        getCofactor(mat, temp, 0, f, n);
        D += sign * mat[0][f]
             * determinantOfMatrix(temp, n - 1);
 
        // terms are to be added with alternate sign
        sign = -sign;
    }
    for(i=0;i<n;i++) {
        free(temp[i]);
    }
    free(temp);
    return D;
}


int is_invertible(int** matrix,int row) {
    int determinant=determinantOfMatrix(matrix, row);
    //printf("Determinant of the matrix is : %d\n",determinant);
    //if determinant = 0 , not invertible
    //if determinant!= 0 , invertible
    
    if(determinant!=0) {
        return 1;
    }
    else {
        return 0;
    }
}

void display(int** mat, int row, int col)
{
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++) {
            //fprintf(stdout,"%d ", mat[i][j]);
        }
        //fprintf(stdout,"\n");
    }
}


void send_response(int** matrix,int row_count,int client_temp_fd,int client_pid,int sleep_time) {
    shared_ptr->handled++;
    struct response resp;
    //int request_pid=client_pid;
        if(flag==1) {
            return;
        } 
    int invertible=is_invertible(matrix,row_count);
    resp.invertible=invertible;
    if(flag==1) {
        return;
    } 
    if(invertible==1) {
        print_time_stamp();
        printf("Z:Worker PID#%d responding to client PID#%d: the matrix IS invertible.\n",(int)getpid(),client_pid);
    }
    else {
        print_time_stamp();
        printf("Z:Worker PID#%d responding to client PID#%d: the matrix IS NOT invertible.\n",(int)getpid(),client_pid);
    }

    if(flag==1) {
        return;
    } 
    display(matrix,row_count,row_count);

    //printf("\n----\n%d\n----\n",resp.invertible);


    char clientFifo[CLIENT_FIFO_NAME_LEN];
    memset(clientFifo,0,CLIENT_FIFO_NAME_LEN);
        if(flag==1) {
            return;
        } 
    snprintf(clientFifo, CLIENT_FIFO_NAME_LEN, CLIENT_FIFO_TEMPLATE,(long) client_pid);
        if(flag==1) {
            return;
        } 
    client_temp_fd = open(clientFifo, O_WRONLY);

    //printf("Z:Client fifo:%s\n",clientFifo);
    //printf("Z:Worker sleeps %d seconds\n",sleep_time);

    sleep(sleep_time);   

    /* Send response and close FIFO */
    if (write(client_temp_fd, &resp, sizeof(resp))!= sizeof(struct response)){
        print_time_stamp();
        fprintf(stderr, "Z:Error writing to FIFO %s\n", clientFifo);
        if(flag==1) {
            return;
        }            
    }            
    if (close(client_temp_fd) == -1){
        perror("close error");
        if(flag==1) {
            return;
        }            
    }  


    if(invertible==1) {
        int write_result_fd;
        write_result_fd=open("result2.txt",(O_RDWR | O_APPEND | O_CREAT),0777);
        if(write_result_fd==-1) {
            print_time_stamp();
            perror("Error open write results");
            return;
        }
        struct flock lock;
        memset(&lock,0,sizeof(lock));
        lock.l_type=F_WRLCK;  
        int result_of_fcntl=fcntl(write_result_fd,F_SETLKW,&lock);
        if(result_of_fcntl==-1) {
            perror("Error getting lock");
            close(write_result_fd);
            return;
        }

        char n='1';
        write(write_result_fd,&n,1);

        lock.l_type=F_UNLCK;
        result_of_fcntl=fcntl(write_result_fd,F_SETLKW,&lock);

        close(write_result_fd); 
    }
    
     
}

void parse_buffer(char* buffer,int sleep_time,int pool_size) {
    char* buffer2=buffer; 
    int row_count;
    char n2;
    if(flag==1) {       
        return;
    }
    int index=sscanf(buffer,"%d%c",&row_count,&n2);
    buffer+=index;
    if(flag==1) {       
        return;
    }
    int** matrix=(int**)malloc(sizeof(int)*row_count);
    int client_pid;
    int fdd;

    for(int i=0;i<row_count;i++) {
        matrix[i]=(int*)malloc(sizeof(int));
    }
    if(flag==1) {       
        return;
    }

    char* token=strtok(buffer,"\n");
    int my_counter=0;
    while(token!=NULL) {  
    if(flag==1) {  
        for(int i=0;i<row_count;i++) {
            free(matrix[i]);
        }
        free(matrix);               
        return;
    }            
        //printf("%s\n",token);
        if(my_counter<3) {
            for(int i=0;i<row_count;i++) {
                if(i==(row_count-1)) {
                    //int matris_ent;
    if(flag==1) {  
        for(int i=0;i<row_count;i++) {
            free(matrix[i]);
        }
        free(matrix);               
        return;
    }
                    int index=sscanf(token,"%d",&matrix[my_counter][i]);
                    token+=index;
    if(flag==1) {  
        for(int i=0;i<row_count;i++) {
            free(matrix[i]);
        }
        free(matrix);               
        return;
    }
                    //printf("%d\n",matris_ent);
                }
                else {
                    //int matris_ent;
                    char e;
    if(flag==1) {  
        for(int i=0;i<row_count;i++) {
            free(matrix[i]);
        }
        free(matrix);               
        return;
    }
                    int index=sscanf(token,"%d%c",&matrix[my_counter][i],&e);
    if(flag==1) {  
        for(int i=0;i<row_count;i++) {
            free(matrix[i]);
        }
        free(matrix);               
        return;
    }
                    token+=index;
                    //printf("%d ",matris_ent);
                }
            }
        }
        else {
            char first[MAX_BLKSIZE];
            //char second[MAX_BLKSIZE];
            memset(first,0,MAX_BLKSIZE);
            int cnt=0;
            int first_cnt=0;
            //int second_cnt=0;
            while(1) {
                if(token[cnt]=='\n' || token[cnt]=='\0') {
                    break;
                }
                first[first_cnt++]=token[cnt++];
            }

            if(my_counter==3) {
                client_pid=atoi(first);
            }
            else {
                fdd=atoi(first);
            }
        }
        my_counter++;
    if(flag==1) {  
        for(int i=0;i<row_count;i++) {
            free(matrix[i]);
        }
        free(matrix);               
        return;
    }
        token=strtok(NULL,"\n"); 
    if(flag==1) {  
        for(int i=0;i<row_count;i++) {
            free(matrix[i]);
        }
        free(matrix);               
        return;
    }
    }

    if(flag==1) {  
        for(int i=0;i<row_count;i++) {
            free(matrix[i]);
        }
        free(matrix);               
        return;
    }

    //int number_of_available_worker=0;
    print_time_stamp();
    printf("Z:Worker PID#%d is handling client PID#%d, matrix size %dx%d, pool busy%d/%d\n",getpid(),client_pid,row_count,row_count,shared_ptr->working_worker,pool_size);
    //printf("Z:Worker parsed the buffer\n");
    buffer=buffer2;
   
    //printf("Z:Worker will send the response\n");
    if(flag==1) {  
        for(int i=0;i<row_count;i++) {
            free(matrix[i]);
        }
        free(matrix);               
        return;
    }
    send_response(matrix,row_count,fdd,client_pid,sleep_time);

    if(flag==1) {  
        for(int i=0;i<row_count;i++) {
            free(matrix[i]);
        }
        free(matrix);               
        return;
    }

    for(int i=0;i<row_count;i++) {
        free(matrix[i]);
    }
    free(matrix);    
}

void read_memory(int sleep_time,int pool_size) {

    char* my_buffer=(char*)malloc(sizeof(char)*MAX_BLKSIZE);
    memset(my_buffer,0,MAX_BLKSIZE);

    //printf("Z:Before sem wait at read memory\n");
    if(flag==1) {
        free(my_buffer);
        return;
    }
    sem_wait(&(shared_ptr->full));
    if(flag==1) {
        free(my_buffer);        
        return;
    }
    sem_wait(&(shared_ptr->lock));
    if(flag==1) {
        free(my_buffer);        
        return;
    }
    //printf("Z:After sem wait at read memory\n");

    //printf("Size of shared_ptr=>%ld\n",sizeof(*shared_ptr));
    
    //printf("In queue:%s\n",shared_ptr->queue[shared_ptr->cursor]);
    if(shared_ptr->cursor <= shared_ptr->last) {
        strncpy(my_buffer,shared_ptr->queue[shared_ptr->cursor],MAX_BLKSIZE);
        if(flag==1) {
            free(my_buffer);        
            return;
        }
        shared_ptr->cursor=(shared_ptr->cursor+1)%MAX_BLKSIZE;
    }
    //printf("Z:Before sem post at read memory\n");
    if(flag==1) {
        free(my_buffer);        
        return;
    }
    shared_ptr->working_worker++;

    sem_post(&(shared_ptr->lock));
    if(flag==1) {
        free(my_buffer);        
        return;
    }
    sem_post(&(shared_ptr->empty));
    if(flag==1) {
        free(my_buffer);        
        return;
    }
    //printf("Z:After sem post at read memory\n");

    parse_buffer(my_buffer,sleep_time,pool_size);
    if(flag==1) {
        free(my_buffer);        
        return;
    }
    free(my_buffer);
}

void run_worker(/*struct worker_z* worker,*/int sleep_time,int pool_size) {
    if(flag==1) {
        return;
    }    
    while(flag==0) {
        if(flag==1) {
            return;
        }        
        //printf("Z:Worker will read the memory\n");

        //read data
        read_memory(sleep_time,pool_size);

        if(flag==1) {
            return;
        }
        //printf("Z:Worker has read the memory and sent the response\n");
        shared_ptr->working_worker--;
        if(flag==1) {
            return;
        }
    }
}


void write_to_memory(char buffer[MAX_BLKSIZE]) {
    //printf("Inside write to memory\n");

    //printf("Z:Before sem_wait at write memory\n");

    sem_wait(&(shared_ptr->empty));
    if(flag==1) {
        return;
    }
    sem_wait(&(shared_ptr->lock));
    if(flag==1) {
        return;
    }
    //printf("Z:After sem_wait at write memory\n");

    strncpy(shared_ptr->queue[shared_ptr->last],buffer,MAX_BLKSIZE);    
    if(flag==1) {
        return;
    }
    //memcpy(shared.queue[shared.last],&buffer,MAX_BLKSIZE);
    shared_ptr->last= (shared_ptr->last+1) % MAX_BLKSIZE;
    if(flag==1) {
        return;
    }
    //printf("Z:ServerZ Written to the memory\n");
    //printf("Z:ServerZ has written:%s\n",buffer);
    if(flag==1) {
        return;
    }
    sem_post(&(shared_ptr->lock));
    if(flag==1) {
        return;
    }
    sem_post(&(shared_ptr->full));
}

void create_shared_memory(size_t size,int pool_size) {
    int fd;
    void *addr;

    /* Create shared memory object and set its size */

    fd = shm_open("memory_name", (O_RDWR | O_CREAT), 0777);
    if (fd == -1) {
        print_time_stamp();
        perror("shm_open error");
    }

    if (ftruncate(fd, size) == -1) {
        print_time_stamp();
        perror("ftruncate error");
    }



    temp.cursor=0;
    temp.last=0;
    temp.working_worker=0;
    temp.pool_size=pool_size;
    temp.handled=0;

    sem_init(&(temp.empty),1,MAX_BLKSIZE);
    sem_init(&(temp.full),1,0);
    sem_init(&(temp.lock),1,1);

    memset(temp.queue,0,MAX_BLKSIZE*MAX_BLKSIZE);

    /* Map shared memory object */

    addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED)
        perror("mmap error"); 
    
    memcpy(addr,&temp,size);
    shared_ptr=(shared_memory*)addr;

}

void send_kill_signal() {
    int read_invertible=0;    
    //read pipes takes results
    //printf("In send kill signal Z %d pool_size\n",pool_size_z);

    
    for(int i=0;i<pool_size_z;i++) {
        if(kill(workers[i].pid,SIGINT)==-1) {
            //printf("Child#%d",workers[i].pid);
            print_time_stamp();
            perror("Error send kill signal");
        }
    }

   int process_traverse=0;
    for(process_traverse=0;process_traverse<pool_size_z;process_traverse++) {
        int childpid=wait(NULL);
        if(childpid==-1) {
            if(errno==ECHILD) {
                //printf("No more children - bye\n");
                break;
            }
            else {
                //printf("Waiting for child to finish...\n");
            }
        }
    }    

    int read_result_fd=open("result2.txt",O_RDONLY);
    if(read_result_fd==-1) {
        print_time_stamp();
        perror("Error open to read read result");
        return;
    }
/*
    struct flock lock;
    memset(&lock,0,sizeof(lock));
    lock.l_type=F_WRLCK;  
    int result_of_fcntl=fcntl(read_result_fd,F_SETLKW,&lock);
*/
    while(1) {
        char n;
        int bytes_read=read(read_result_fd,&n,1);
        if(bytes_read==-1) {
            print_time_stamp();
            perror("Read error");
            break;
        }
        if(n=='1') {
            read_invertible++;
        }
        if(bytes_read==0) {
            break;
        }
    }
/*
    lock.l_type=F_UNLCK;
    result_of_fcntl=fcntl(read_result_fd,F_SETLKW,&lock);
*/
    close(read_result_fd); 


    invertible_request=(--read_invertible);

    total_request=shared_ptr->handled;
}



int main(int argc, char const *argv[])
{

    char serverfifo[MAX_BLKSIZE];
    char logfile[MAX_BLKSIZE];
    memset(serverfifo,0,MAX_BLKSIZE);
    memset(logfile,0,MAX_BLKSIZE);

    struct sigaction sa; 
    memset(&sa,0,sizeof(sa));
    sa.sa_flags=SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    //sa.sa_handler=&handler;
    sa.sa_sigaction=handler;
    sigaction(SIGINT,&sa,NULL);  


    //struct timeval tv;
    //time_t t;
    //struct tm *info;




    int sleep_time=0;

    strncpy(serverfifo,argv[1],strlen(argv[1]));
    strncpy(logfile,argv[2],strlen(argv[2]));

    int pipe_fd_with_y[2];

    pool_size_z=atoi(argv[3]);
    sscanf(argv[4],"%d",&sleep_time);

    pipe_fd_with_y[1]=atoi(argv[5]);


    //int number_of_available_worker=pool_size_z;
    workers=(struct worker_z*)malloc(sizeof(struct worker_z)*pool_size_z);
    //memset(workers,0,pool_size_z*sizeof(struct worker_z));

    //switch out to file
    int out = open(logfile, O_RDWR|O_CREAT|O_APPEND, 0600);
    if (-1 == out) { perror("opening logfile"); return 255; }

    int err = open(logfile, O_RDWR|O_CREAT|O_APPEND, 0600);
    if (-1 == err) { perror(logfile); return 255; }

    int save_out = dup(fileno(stdout));

    if(save_out==-1) {
        perror("Error at savingt stdout");
        exit(0);
    }
    int save_err = dup(fileno(stderr));
    if(save_err==-1) {
        perror("Error saving stderr");
        exit(0);
    }

    if (-1 == dup2(out, fileno(stdout))) { perror("cannot redirect stdout"); return 255; }
    if (-1 == dup2(err, fileno(stderr))) { perror("cannot redirect stderr"); return 255; }   
    
    print_time_stamp();
    printf("Z:Server Z (%s, t=%d, r=%d) started\n",logfile,sleep_time,pool_size_z);

    //number_of_available_worker=pool_size_z;  


    create_shared_memory(sizeof(shared_memory),pool_size_z);

    total_request=0;
    invertible_request=0;



    if(flag==1) {
        print_when_sigint_received();
        free(workers);
        sem_destroy(&(temp.empty));
        sem_destroy(&(temp.full));
        sem_destroy(&(temp.lock));         
        return 0;
    }

    for(int i=0;i<pool_size_z;i++) {      
        int forkpid=fork();
        if(forkpid==-1) {
            perror("Fork error");
        }
        else if(forkpid==0) {
            //child process
            workers[i].pid=getpid();
            run_worker(/*&workers[i],*/sleep_time,pool_size_z);
            free(workers);
            sem_destroy(&(temp.empty));
            sem_destroy(&(temp.full));
            sem_destroy(&(temp.lock));             
            return 0;
        }
        else {
            //parent process         
            workers[i].pid=forkpid;
        }
    }
    if(flag==1) {
        print_when_sigint_received();
        free(workers);
        sem_destroy(&(temp.empty));
        sem_destroy(&(temp.full));
        sem_destroy(&(temp.lock));      
        return 0;  
    }
    for(;;) {

        //read the pipe

        char* buffer=(char*)malloc(sizeof(char)*MAX_BLKSIZE);
        memset(buffer,0,MAX_BLKSIZE);
        //char* buffer2=buffer;
        
        //printf("Z will read the pipe\n");

        if(flag==1) {
            print_when_sigint_received();
            free(workers);
            free(buffer);
            break;
        }

        read(pipe_fd_with_y[1],buffer,MAX_BLKSIZE);

        if(flag==1) {
            send_kill_signal();
            print_when_sigint_received();
            free(workers);
            free(buffer);
            break;
        }

        //printf("Z read all\n");

        //printf("Z read this\n%s\n",buffer);

       // printf("Z:Z should find an available child\n");
        //printf("Z:Buffer before writing:%s\n",buffer);

        write_to_memory(buffer);

        if(flag==1) {
            send_kill_signal();
            print_when_sigint_received();
            free(workers);
            free(buffer);
            break;
        }

        free(buffer);  

        if(flag==1) {
            send_kill_signal();
            print_when_sigint_received();
            free(workers);
            break;
        }


    }

    sem_destroy(&(temp.empty));
    sem_destroy(&(temp.full));
    sem_destroy(&(temp.lock));

    return 0;
}
