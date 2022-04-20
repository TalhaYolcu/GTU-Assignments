/*
./serverY -s pathToServerFifo -o pathToLogFile –p poolSize -r poolSize2 -t 2
where
where
-s: denotes the path (relative or absolute) of the server fifo
-o: denotes the path (relative or absolute) of the log file to record all server output/errors
-p: denotes the pool size of serverY (p >= 2)
-r: denotes the pool size of serverZ (r >= 2)
-t: denotes the sleep duration (in seconds)

*/


#include <signal.h>
#include <errno.h>
#include <stdio.h>
#include "fifo_seqnum.h"
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include<sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "become_daemon.h"

int flag=0;
int sigusr1flag=0;
int worker_can_read=0;
int sigusr2flag=0;
int pool_size_Y=0;
int process_id_z;

char serverFifo[MAX_BLKSIZE];
char logfile[MAX_BLKSIZE];
char datafile[MAX_BLKSIZE];


struct worker* workers;
int total_request,invertible_request,forwarded_request;
int available_child_pid=-1;
int number_of_available_worker=0;

void getCofactor(int** mat, int** temp, int p,int q, int n);
int determinantOfMatrix(int** mat, int n);
int is_invertible(int** matrix,int row);
void send_response(int** matrix,int row_count,int client_temp_fd,int client_pid,int sleep_time);
void handler(int signal_number,siginfo_t* siginfo,void*fd);
void display(int** mat, int row, int col);
void writer(int**matrix,int row_count,int fd,int pid,int clientwritefd);
void reader(int fd,int sleep_time);



void handler(int signal_number,siginfo_t* siginfo,void*fd) {
    if(signal_number==SIGINT) {
        flag=1;
    }
    if(signal_number==SIGUSR1) {
        sigusr1flag=1;
        available_child_pid=siginfo->si_pid;
        //number_of_available_worker++;
        //printf("\n+++%d+++%d\n",available_child_pid,getpid());
    }
    if(signal_number==SIGUSR2) {
        number_of_available_worker++;
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
    printf("SIGINT received, exiting server Y, Total request handled %d, %d invertible, %d not.\n",total_request,invertible_request,total_request-invertible_request);
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

void writer(int**matrix,int row_count,int fd,int pid,int clientwritefd) {

    char* buffer=(char*)malloc(sizeof(char)*MAX_BLKSIZE);
    memset(buffer,0,MAX_BLKSIZE);
    char* buffer2=buffer;

    int index=sprintf(buffer,"%d\n",row_count);
    buffer+=index;

    for(int i=0;i<row_count;i++) {
        for(int k=0;k<row_count;k++) {
            if(k==(row_count-1)) {
                if(flag==1) {
                    free(buffer);
                    return;
                }                
                int index=sprintf(buffer,"%d\n",matrix[i][k]);
                buffer+=index;
            }
            else {
                if(flag==1) {
                    free(buffer);
                    return;
                }                
                int index=sprintf(buffer,"%d ",matrix[i][k]);
                if(flag==1) {
                    free(buffer);
                    return;
                }                
                buffer+=index;                
            }
        }
    }
    if(flag==1) {
        free(buffer);
        return;
    }

    index=sprintf(buffer,"%d\n",pid);
     if(flag==1) {
        free(buffer);
        return;
    }
    buffer+=index;
    index=sprintf(buffer,"%d\n",clientwritefd);
     if(flag==1) {
        free(buffer);
        return;
    }
    buffer+=index;


    buffer=buffer2;

    //printf("Written pipe buffer:\n%s\n",buffer);


    if(write(fd,buffer,MAX_BLKSIZE)==-1) {
        perror("Writer error\n");
        if(flag==1) {
            free(buffer);
            return;
        }        
    }

    free(buffer);
}

void send_response(int** matrix,int row_count,int client_temp_fd,int client_pid,int sleep_time) {
    struct response resp;

    int invertible=is_invertible(matrix,row_count);
    resp.invertible=invertible;

    if(invertible==1) {
        print_time_stamp();        
        printf("Worker PID#%d responding to client PID#%d: the matrix IS invertible.\n",(int)getpid(),client_pid);
    }
    else {
        printf("Worker PID#%d responding to client PID#%d: the matrix IS NOT invertible.\n",(int)getpid(),client_pid);
    }

    if(flag==1) {
        return;
    }

    display(matrix,row_count,row_count);

    //printf("\n----\n%d\n----\n",resp.invertible);


    char clientFifo[CLIENT_FIFO_NAME_LEN];
    memset(clientFifo,0,CLIENT_FIFO_NAME_LEN);
    snprintf(clientFifo, CLIENT_FIFO_NAME_LEN, CLIENT_FIFO_TEMPLATE,(long) client_pid);
    client_temp_fd = open(clientFifo, O_WRONLY);

/*
    printf("Client fifo:%s\n",clientFifo);
    printf("Worker sleeps %d seconds\n",sleep_time);
*/
    sleep(sleep_time);   

    /* Send response and close FIFO */
    if (write(client_temp_fd, &resp, sizeof(resp))!= sizeof(struct response)){
        print_time_stamp();
        fprintf(stderr, "Error writing to FIFO %s\n", clientFifo);
        if(flag==1) {
            return;
        }            
    }            
    if (close(client_temp_fd) == -1){
        perror("close client temp fd error");
        if(flag==1) {
            return;
        }            
    }    

    int write_result_fd;
    write_result_fd=open("result.txt",(O_RDWR | O_APPEND | O_CREAT),0777);
    if(write_result_fd==-1) {
        perror("Error open write results");
        return;
    }
    struct flock lock;
    memset(&lock,0,sizeof(lock));
    lock.l_type=F_WRLCK;  
    int result_of_fcntl=fcntl(write_result_fd,F_SETLKW,&lock);

    if(result_of_fcntl==-1) {
        perror("Lock error");
        close(write_result_fd);
        return;
    }


    char n='1';
    write(write_result_fd,&n,1);

    lock.l_type=F_UNLCK;
    result_of_fcntl=fcntl(write_result_fd,F_SETLKW,&lock);

    close(write_result_fd);


    //write result to file
    //lock file

    //unlock file

}

void reader(int fd,int sleep_time) {

    
    char* buffer=(char*)malloc(sizeof(char)*MAX_BLKSIZE);
    memset(buffer,0,MAX_BLKSIZE);
    char* buffer2=buffer;

//    printf("Worker will read the pipe in reader\n");

    if(flag==1) {
        free(buffer);
        return;
    }

    read(fd,buffer,MAX_BLKSIZE);

    if(flag==1) {
        free(buffer);
        return;
    }


//    printf("Worker read all\n");

//    printf("Worker read this\n%s\n",buffer);
    int row_count=0;
    char n2;
    int index=sscanf(buffer,"%d%c",&row_count,&n2);
    buffer+=index;

    if(flag==1) {
        free(buffer);
        return;
    }

    int** matrix=(int**)malloc(sizeof(int)*row_count);
    int client_pid;
    int fdd;

    for(int i=0;i<row_count;i++) {
        matrix[i]=(int*)malloc(sizeof(int));
    }

    if(flag==1) {
        free(buffer);
        for(int i=0;i<row_count;i++) {
            free(matrix[i]);
        }
        free(matrix);
        return;
    }

    char* token=strtok(buffer,"\n");
    int my_counter=0;
    while(token!=NULL) {        
        //printf("%s\n",token);
        if(my_counter<3) {
            for(int i=0;i<row_count;i++) {
                if(i==(row_count-1)) {
                    int index=sscanf(token,"%d",&matrix[my_counter][i]);
                    token+=index;
                    //printf("%d\n",matris_ent);
                }
                else {
                    char e;
                    int index=sscanf(token,"%d%c",&matrix[my_counter][i],&e);
                    token+=index;
                    //printf("%d ",matris_ent);
                }
            }
        }
        else {
            char first[MAX_BLKSIZE];
            memset(first,0,MAX_BLKSIZE);
            int cnt=0;
            int first_cnt=0;
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
        token=strtok(NULL,"\n");
        
    }
    if(flag==1) {
        free(buffer);
        for(int i=0;i<row_count;i++) {
            free(matrix[i]);
        }
        free(matrix);
        return;
    }


    buffer=buffer2;
   
    free(buffer);
    
//    printf("Worker will send the response\n");

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



void display(int** mat, int row, int col)
{
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++) {
            //fprintf(stdout,"%d ", mat[i][j]);
        }
        //fprintf(stdout,"\n");
    }
}


void run_worker(struct worker* workers,int fd0,int sleep_time) {
    
    while(1) {
        
        //printf("Child with id %d sends I am available signal to the parent with id:%d\n",getpid(),getppid());
        kill(getppid(),SIGUSR1);
        //printf("Worker will read the pipe\n");

        if(flag==1) {
            return;
        }

        //read data
        reader(fd0,sleep_time);

        if(flag==1) {
            return;
        }
        //printf("Worker has read the pipe and sent the response\n");

        kill(getppid(),SIGUSR2);
    }
}



void send_kill_signal() {

    unlink("double_instant");
    int read_invertible=0;    
    //read pipes takes results

    //printf("In send kill signal Y %d\n",pool_size_Y);

    if(kill(process_id_z,SIGINT)==-1) {
        perror("Error send kill signal to Z");
    }
    
    for(int i=0;i<pool_size_Y;i++) {
        if(kill(workers[i].pid,SIGINT)==-1) {
            //printf("Child#%d",workers[i].pid);
            perror("Error send kill signal");
        }
    }



    int process_traverse=0;
    for(process_traverse=0;process_traverse<(pool_size_Y);process_traverse++) {
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
    //wait(NULL);




    int read_result_fd=open("result.txt",O_RDONLY,0777);
    if(read_result_fd==-1) {
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
        int bytes_read=read(read_result_fd,&n,sizeof(char));
        if(bytes_read==-1) {
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

    read_invertible--;
/*
    lock.l_type=F_UNLCK;
    result_of_fcntl=fcntl(read_result_fd,F_SETLKW,&lock);
*/
    close(read_result_fd); 

    int read_result_fd2=open("result2.txt",O_RDONLY);
    if(read_result_fd2==-1) {
        perror("Error open to read read result");
        return;
    }
/*    
    struct flock lock2;
    memset(&lock2,0,sizeof(lock2));
    lock2.l_type=F_WRLCK;  
    result_of_fcntl=fcntl(read_result_fd2,F_SETLKW,&lock2);
*/

    while(1) {
        char n;
        int bytes_read=read(read_result_fd2,&n,sizeof(char));
        if(bytes_read==-1) {
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

    read_invertible--;

    read_invertible--;

/*    lock2.l_type=F_UNLCK;
    result_of_fcntl=fcntl(read_result_fd2,F_SETLKW,&lock2);
*/
    close(read_result_fd2); 

    unlink("result2.txt");
    unlink("result.txt");
    invertible_request=read_invertible;
}

void print_usage_exit() {
    print_time_stamp();
    printf("Usage:./serverY -s serverfifo -o logfile -p 2 -r 3 -t 5\n");
    perror("Error, missing cmd arguments");
    exit(0);
}

int main(int argc, char *argv[]) {
    total_request=0;
    invertible_request=0;
    becomeDaemon(0);

    if(argc!=11) {
        print_usage_exit();
    }

    int try_double_ins=0;
    try_double_ins=open("double_instant",(O_CREAT | O_EXCL));
    if(try_double_ins==-1) {
        perror("Double instant");
        unlink("double_instant");
        return 0;
    }

    close(try_double_ins);

    //unlink("double_instant");
   
    struct sigaction sa; 
    memset(&sa,0,sizeof(sa));
    sa.sa_flags=SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    //sa.sa_handler=&handler;
    sa.sa_sigaction=handler;
    sigaction(SIGINT,&sa,NULL);  
    sigaction(SIGUSR1,&sa,NULL);
    sigaction(SIGUSR2,&sa,NULL);

    struct timeval tv;
    time_t t;
    struct tm *info;

    int read_result_fd2=open("result2.txt",(O_WRONLY | O_TRUNC | O_CREAT)  );
    if(read_result_fd2==-1) {
        //perror("Error open to read read result");
        return 0;
    }

    close(read_result_fd2);
      
    read_result_fd2=open("result.txt",(O_WRONLY | O_TRUNC | O_CREAT)  );
    if(read_result_fd2==-1) {
        perror("Error open to read read result");
        return 0;
    }

    close(read_result_fd2);

    available_child_pid=-1;

    int sleep_time=0;   

    int pool_size_Z=0;   
    int serverFd=0, dummyFd=0, clientFd=0;  
    char clientFifo[CLIENT_FIFO_NAME_LEN];     

    struct request req;
    memset(datafile,0,sizeof(char)*MAX_BLKSIZE);
    memset(serverFifo,0,sizeof(char)*MAX_BLKSIZE);
    memset(logfile,0,sizeof(char)*MAX_BLKSIZE);
    memset(clientFifo,0,CLIENT_FIFO_NAME_LEN);

/*
./serverY -s pathToServerFifo -o pathToLogFile –p poolSize -r poolSize2 -t 2
where
where
-s: denotes the path (relative or absolute) of the server fifo
-o: denotes the path (relative or absolute) of the log file to record all server output/errors
-p: denotes the pool size of serverY (p >= 2)
-r: denotes the pool size of serverZ (r >= 2)
-t: denotes the sleep duration (in seconds)

*/

    int i;



    for(i=1;i<argc;i++) {
        if(argv[i][0]=='-' && argv[i][1]=='s') {
            int len=strlen(argv[i+1]);
            strncpy(serverFifo,argv[i+1],len);
        }
        else if(argv[i][0]=='-' && argv[i][1]=='o') {
            int len=strlen(argv[i+1]);
            strncpy(logfile,argv[i+1],len);
        }
        else if(argv[i][0]=='-' && argv[i][1]=='p') {
            sscanf(argv[i+1],"%d",&pool_size_Y);
        }
        else if(argv[i][0]=='-' && argv[i][1]=='r') {
            sscanf(argv[i+1],"%d",&pool_size_Z);
        }
        else if(argv[i][0]=='-' && argv[i][1]=='t') {
            sscanf(argv[i+1],"%d",&sleep_time);
        }                       
    }
    int fds_z[2];
    //create z pipe
    if(pipe(fds_z)==-1){
        print_time_stamp();
        perror("Pipe create error");
        exit(0);
    }

    
    int forkz=fork();
    process_id_z=forkz;
    if(forkz==-1) {
        perror("Fork error z");
        exit(0);
    }
    else if(forkz==0) {
        close(fds_z[1]);
        //execve
        //serverfifo
        //logfile
        //poolz
        //sleep time
        int number_of_argument=5;
        char buffer[MAX_BLKSIZE];
        memset(buffer,0,MAX_BLKSIZE);

        char* program="./serverZ";

        //char cmdarguments[number_of_argument+1][MAX_BLKSIZE];
        char** cmdarguments=(char**)malloc(sizeof(char*)*(number_of_argument+2));
        for(int i=0;i<number_of_argument+2;i++) {
            cmdarguments[i]=(char*)malloc(sizeof(char)*MAX_BLKSIZE);
        }

        /*cmdarguments[0]=strrchr(program,'/');
        if(cmdarguments[0]!=NULL) {
            cmdarguments[0]++;
        }*/
        strncpy(cmdarguments[0],program,MAX_BLKSIZE);
        strncpy(cmdarguments[1],serverFifo,MAX_BLKSIZE);
        strncpy(cmdarguments[2],logfile,MAX_BLKSIZE);
        snprintf(cmdarguments[3],MAX_BLKSIZE,"%d",pool_size_Z);
        snprintf(cmdarguments[4],MAX_BLKSIZE,"%d",sleep_time);
        snprintf(cmdarguments[5],MAX_BLKSIZE,"%d",fds_z[0]);
        cmdarguments[6]=NULL;


        //execute the new program with environment variables
        //printf("Execve is gonna work\n");
        int ret=execv(program,cmdarguments);
        //printf("RET:%d\n",ret);
        if(ret==-1){
            print_time_stamp();            
            perror("Error");
        } 
        print_time_stamp();     
        printf("This should not be worked\n");
        exit(0);
    }

    close(fds_z[0]);
    process_id_z=forkz;

    int temp_out=open(logfile,O_RDWR|O_CREAT|O_TRUNC,0777);
    close(temp_out);


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

    //puts("doing an ls or something now");

/*  bring out back
    fflush(stdout); close(out);
    fflush(stderr); close(err);

    dup2(save_out, fileno(stdout));
    dup2(save_err, fileno(stderr));

    close(save_out);
    close(save_err);

    puts("back to normal output");
*/
    gettimeofday(&tv, NULL);
    t = tv.tv_sec;

    info = localtime(&t);
    printf("%s",asctime (info));

    printf("\nServer Fifo: %s\n",serverFifo);
    printf("%sLog file: %s\n",asctime (info),logfile);
    printf("%sPool Size Y: %d\n",asctime (info),pool_size_Y);
    printf("%sPool Size Z: %d\n",asctime (info),pool_size_Z);


    printf("%sServer Y (%s, p=%d, t=%d) started\n",asctime (info),logfile,pool_size_Y,sleep_time);
    printf("%sInstantiated server Y\n",asctime(info));
    /* Create well-known FIFO, and open it for reading */

    umask(0);                           /* So we get the permissions we want */
    if (mkfifo(/*SERVER_FIFO*/serverFifo, 0777) == -1 && errno != EEXIST){
        print_time_stamp();
        perror("mkfifo");
        exit(0);
    }
    if(flag==1) {
        print_when_sigint_received();
        //unlink(serverFifo);
        exit(0); 
    }   
    serverFd = open(serverFifo, O_RDONLY);
    if(flag==1) {
        print_when_sigint_received();
        //unlink(serverFifo);
        exit(0);   
    }
    if (serverFd == -1){
        print_time_stamp();
        perror("open serverfd error");
        //unlink(serverFifo);
        exit(0); 
    }
    if(flag==1) {
        print_when_sigint_received();
        //unlink(serverFifo);
        exit(0);
    }  
    /* Open an extra write descriptor, so that we never see EOF */

    dummyFd = open(serverFifo, O_WRONLY);
    if (dummyFd == -1){
        print_time_stamp();
        perror("open dummyfd error");
        print_when_sigint_received();
        //unlink(serverFifo);
        exit(0);   
    }
    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR){
        print_time_stamp();
        perror("signal error");
        print_when_sigint_received();
        //unlink(serverFifo);
        exit(0);      
    }

    if(flag==1) {
        print_when_sigint_received();
        //unlink(serverFifo);
        exit(0);
    }

    //child - okuyan
    //write end i kapatıcak yani 1'i
    //read end i açıcak yani 0 ' ı

    //parent - yazan
    //write end i açıcak yani 1'i
    //read end i kapatıcak yani 0'ı

    number_of_available_worker=pool_size_Y;
    total_request=0;
    workers=(struct worker*)malloc(sizeof(struct worker)*pool_size_Y);
    memset(workers,0,pool_size_Y*sizeof(struct worker));
    int fds[pool_size_Y][2];


    for(int i=0;i<pool_size_Y;i++) {
        if(pipe(fds[i])==-1) {
            print_time_stamp();
            perror("Pipe create error");
            free(workers);
            exit(0);
        }
        workers[i].available=1;
        workers[i].pipe_read_fd=fds[i][0];
        workers[i].pipe_write_fd=fds[i][1];
        
    }

    if(flag==1) {
        print_when_sigint_received();
        //unlink(serverFifo);
        free(workers);
        exit(0);
    }

    for(int i=0;i<pool_size_Y;i++) {      
        int forkpid=fork();
        if(forkpid==-1) {
            print_time_stamp();
            perror("Fork error");
            exit(0);
        }
        else if(forkpid==0) {
            //child process
            close(fds[i][1]);
            workers[i].pid=getpid();
            run_worker(&workers[i],fds[i][0],sleep_time);
            free(workers);
            return 0;
        }
        else {
            //parent process
            close(fds[i][0]);            
            workers[i].pid=forkpid;
        }
    }

    if(flag==1) {

        send_kill_signal();

        print_when_sigint_received();
        //unlink(serverFifo);
        free(workers);
        return 0;
    }

    number_of_available_worker=pool_size_Y;    

    for (;;) {  
        /* Read requests and send responses */
        //sleep(10);
        int r1=read(serverFd, &req, sizeof(struct request)); 

        if(flag==1) {

            send_kill_signal();

            print_when_sigint_received();
            //unlink(serverFifo);
            free(workers);
            return 0;
        }

        if(r1==-1) {
            continue;

        }
        if(flag==1) {

            send_kill_signal();         

            print_when_sigint_received();
            //unlink(serverFifo);
            free(workers);
            return 0;
        }

        int r2=sizeof(struct request);

        if (r1 != r2) {
            send_kill_signal(); 
            print_time_stamp();
            fprintf(stderr, "Error reading request; discarding\n");
                            /* Either partial read or error */
            print_when_sigint_received();
            //unlink(serverFifo);
            free(workers);
            return 0;       
        }
        if(flag==1) {

            send_kill_signal();  

            print_when_sigint_received();
            //unlink(serverFifo);
            free(workers);
            return 0;
        }

        int i=0;
        int k=0;
        int row_count=0;
        row_count=req.row;
        int** matrix;
        matrix=(int**)malloc(sizeof(int*)*row_count);
        for(i=0;i<row_count;i++) {
            matrix[i]=(int*)malloc(sizeof(int)*row_count);
        }

        matrix[0][0]=req.matrix_entry;
        if(flag==1) {

            send_kill_signal();  

            print_when_sigint_received();
            //unlink(serverFifo);
            free(workers);
            for(int i=0;i<row_count;i++) {
                free(matrix[i]);
            }
            free(matrix);
            return 0;
        }
        for(i=0;i<row_count;i++) {
            if(i==0) {
                for(k=1;k<row_count;k++) {
                    if(flag==1) {
                        
                        send_kill_signal();

                        print_when_sigint_received();
                        //unlink(serverFifo);
                        free(workers);
                        for(int i=0;i<row_count;i++) {
                            free(matrix[i]);
                        }
                        free(matrix);
                        return 0;
                    }                    
                    read(serverFd,&req,sizeof(struct request));
                    if(flag==1) {
                        send_kill_signal();                          
                        print_when_sigint_received();
                        //unlink(serverFifo);
                        free(workers);
                        for(int i=0;i<row_count;i++) {
                            free(matrix[i]);
                        }
                        free(matrix);
                        return 0;
                    }                    
                    matrix[i][k]=req.matrix_entry;
                }
            }
            else {
                for(k=0;k<row_count;k++) {
                    if(flag==1) {
                        send_kill_signal();                          
                        print_when_sigint_received();
                        //unlink(serverFifo);
                        free(workers);
                        for(int i=0;i<row_count;i++) {
                            free(matrix[i]);
                        }
                        free(matrix);
                        return 0;
                    }                     
                    read(serverFd,&req,sizeof(struct request));
                    if(flag==1) {
                        send_kill_signal();                          
                        print_when_sigint_received();
                        //unlink(serverFifo);
                        free(workers);
                        for(int i=0;i<row_count;i++) {
                            free(matrix[i]);
                        }
                        free(matrix);
                        return 0;
                    }                     
                    matrix[i][k]=req.matrix_entry;
                }
            }
            
        }
        if(flag==1) {
            send_kill_signal();                          
            print_when_sigint_received();
            //unlink(serverFifo);
            free(workers);
            for(int i=0;i<row_count;i++) {
                free(matrix[i]);
            }
            free(matrix);
            return 0;
        } 

        //printf("Matris is read from fifo\n");


        int available_found=0;
        int available_one=-1;

        while(available_child_pid==-1) {

        }
        if(flag==1) {
            send_kill_signal();                          
            print_when_sigint_received();
            //unlink(serverFifo);
            free(workers);
            for(int i=0;i<row_count;i++) {
                free(matrix[i]);
            }
            free(matrix);
            return 0;
        } 
        if(sigusr1flag==2) {
            for(int i=0;i<pool_size_Y;i++) {
                if(workers[i].pid==available_child_pid) {
                    workers[i].available=1;
                }
            }
        }

        for(int i=0;i<pool_size_Y;i++) {
            if(workers[i].available==1) {
                available_one=i;
                available_found=1;
                break;
            }
        }

            total_request++;


        if(available_found==1) {

            number_of_available_worker--;
            //printf("Number of available worker:%d\n",number_of_available_worker);
            //number_of_available_worker%=pool_size_Y;
            print_time_stamp();
            printf("Worker PID#%d is handling client PID#%d, matrix size %dx%d, pool busy %d/%d\n",workers[available_one].pid,req.pid,row_count,row_count,(pool_size_Y-number_of_available_worker),pool_size_Y);

            workers[available_one].available=0;

            //printf("Available worker found at this index:%d\n",available_one);

            /* Open client FIFO (previously created by client) */

            snprintf(clientFifo, CLIENT_FIFO_NAME_LEN, CLIENT_FIFO_TEMPLATE,(long) req.pid);
            if(flag==1) {
                send_kill_signal();                          

                print_when_sigint_received();
                //unlink(serverFifo);
                free(workers);
                for(int i=0;i<row_count;i++) {
                    free(matrix[i]);
                }
                free(matrix);
                return 0;
            } 
            clientFd = open(clientFifo, O_WRONLY);
            if(flag==1) {
                send_kill_signal(); 
                print_when_sigint_received();
                //unlink(serverFifo);
                free(workers);
                for(int i=0;i<row_count;i++) {
                    free(matrix[i]);
                }
                free(matrix);
                return 0;
            } 
            //printf("ServerY has client fd:%d\n",clientFd);

            if (clientFd == -1) {           /* Open failed, give up on client */
                perror("open clientfifo");
                send_kill_signal(); 
                //unlink(serverFifo);
                free(workers);
                for(int i=0;i<row_count;i++) {
                    free(matrix[i]);
                }
                free(matrix);
                return 0;
            }

            if(flag==1) {
                send_kill_signal(); 
                print_when_sigint_received();
                //unlink(serverFifo);
                free(workers);
                for(int i=0;i<row_count;i++) {
                    free(matrix[i]);
                }
                free(matrix);
                return 0;
            } 

            //send matrix as in pipe
            //
            //open in write mode

            //printf("Writing to the pipe\n");
            //number_of_available_worker--;
            //write matrix to the pipe
            writer(matrix,row_count,fds[available_one][1],(int)req.pid,clientFd);

            if(flag==1) {
                send_kill_signal(); 
                print_when_sigint_received();
                //unlink(serverFifo);
                free(workers);
                for(int i=0;i<row_count;i++) {
                    free(matrix[i]);
                }
                free(matrix);
                return 0;
            } 

            //printf("Written to pipe\n");


            //close pipe
            //close available child pipe

    
        }
        else {
            print_time_stamp();
            printf("Forwarding request of client PID#%d to serverZ, matrix size %dx%d, pool busy %d/%d\n",req.pid,row_count,row_count,(pool_size_Y-number_of_available_worker),pool_size_Y);
            //start serverZ
            //printf("Start server Z");

            snprintf(clientFifo, CLIENT_FIFO_NAME_LEN, CLIENT_FIFO_TEMPLATE,(long) req.pid);

            if(flag==1) {
                send_kill_signal(); 
                print_when_sigint_received();
                //unlink(serverFifo);
                free(workers);
                for(int i=0;i<row_count;i++) {
                    free(matrix[i]);
                }
                free(matrix);
                return 0;
            } 

            clientFd = open(clientFifo, O_WRONLY);

            if(flag==1) {
                send_kill_signal(); 
                print_when_sigint_received();
                //unlink(serverFifo);
                free(workers);
                for(int i=0;i<row_count;i++) {
                    free(matrix[i]);
                }
                free(matrix);
                return 0;
            } 

            //printf("ServerY has client fd:%d\n",clientFd);

            if (clientFd == -1) {           /* Open failed, give up on client */
                send_kill_signal(); 
                print_time_stamp();
                perror("open clientfd error");
                //unlink(serverFifo);
                free(workers);
                for(int i=0;i<row_count;i++) {
                    free(matrix[i]);
                }
                free(matrix);
                return 0;
            }
            if(flag==1) {
                send_kill_signal(); 
                print_when_sigint_received();
                //unlink(serverFifo);
                free(workers);
                for(int i=0;i<row_count;i++) {
                    free(matrix[i]);
                }
                free(matrix);
                return 0;
            } 
            //send matrix as in pipe
            //
            //open in write mode

            //printf("Writing to the pipe\n");
            //number_of_available_worker--;
            //write matrix to the pipe
            writer(matrix,row_count,fds_z[1],(int)req.pid,clientFd);

            if(flag==1) {
                send_kill_signal(); 
                print_when_sigint_received();
                //unlink(serverFifo);
                free(workers);
                for(int i=0;i<row_count;i++) {
                    free(matrix[i]);
                }
                free(matrix);
                return 0;
            } 


            //printf("Written to pipe\n");


            //close pipe
            //close available child pipe

        }

        for(i=0;i<row_count;i++) {
            free(matrix[i]);
        }
        free(matrix);
    }
}

