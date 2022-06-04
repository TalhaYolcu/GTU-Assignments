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
#include <stdint.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <pthread.h>
#include <sys/wait.h>
#include <math.h>

//inputfilepath1
char input1[MAX_BLKSIZE];
char input2[MAX_BLKSIZE];   //inputfilepath2
char output[MAX_BLKSIZE];   //outputfilepath
char narg[MAX_BLKSIZE];     //argument after -n
char marg[MAX_BLKSIZE];     //argument after -m
int n_int=0;                //int representation of n
int m_int=0;                //int representation of m
int matrix_size_for_thread=0;   //2^n
int** matrix1;                  //read matrix1
int** matrix2;                  //read matrix2
int** result_matrix;            //result of multiplication of matrices
double** dft_matrix_r;          //real part of dft
double** dft_matrix_i;          //imaginary part of dft
pthread_t* threads;             //threads
int arrived=0;                  //number of arrived thread
pthread_cond_t condition;       //condition variable for synchronization barrier
pthread_mutex_t mutex;          //mutex for synchronization barrier

//./hw5 -i filePath1 -j filePath2 -o output -n 4 -m 2

//sigint flag
sig_atomic_t terminate_flag=0;

//signal handler, if it receives a sigint, sets flag to 1
void handler(int signal_number) {
    if(signal_number==SIGINT) {
        terminate_flag=1;
    }
}
//checks arguments
int check_arguments(int argc, char const *argv[]) {
    int i=0;

    if(argc!=11) {
        return -1;
    }

    int input1_ok=0;
    int input2_ok=0;
    int output_ok=0;
    int n_ok=0;
    int m_ok=0;

    for(i=1;i<argc;i++) {
        //input1
        if(argv[i][0]=='-' && argv[i][1]=='i') {
            input1_ok=1;
        }
        //input2
        else if(argv[i][0]=='-' && argv[i][1]=='j') {
            input2_ok=1;
        }   
        //output
        else if(argv[i][0]=='-' && argv[i][1]=='o')  {
            output_ok=1;
        }   
        //n  
        else if(argv[i][0]=='-' && argv[i][1]=='n')  {
            n_ok=1;
        }   
        //m
        else if(argv[i][0]=='-' && argv[i][1]=='m')  {
            m_ok=1;
        }   

    } 
    if(input1_ok==1 && input2_ok==1 && output_ok==1 && n_ok==1 && m_ok==1) {
        return 0;
    }
    return -1;
}

void print_usage_end_exit() {
    fprintf(stdout,"Usage:./hw5 -i filePath1 -j filePath2 -o output -n 4 -m 2\n");
    exit(-1);
}

void print_matrix(int size,int** matrix) {
    fprintf(stdout,"--------\n");
    for(int i=0;i<size;i++) {
        for(int k=0;k<size;k++) {
            fprintf(stdout,"%d ",matrix[i][k]);
        }
        fprintf(stdout,"\n");
    }
}
void print_matrix_double(int size,double** matrix) {
    fprintf(stdout,"--------\n");
    for(int i=0;i<size;i++) {
        for(int k=0;k<size;k++) {
            fprintf(stdout,"%.4lf ",matrix[i][k]);
        }
        fprintf(stdout,"\n");
    }
}

void free_resources() {
    free(threads);

    for(int i=0;i<matrix_size_for_thread;i++) {
        free(matrix1[i]);
        free(matrix2[i]);
        free(result_matrix[i]);
        free(dft_matrix_i[i]);
        free(dft_matrix_r[i]);
    }

    free(matrix1);
    free(matrix2);
    free(result_matrix);
    free(dft_matrix_i);
    free(dft_matrix_r);
}

//returns time as a string without \n
char* get_time(char* time) {
    int len=strlen(time);
    time[len-1]='\0';
    return time;
}

int multiply_two_matrices(int size,int** matrix1,int** matrix2,int** result_matrix,int index) {
    
    int start_point=index*size/m_int;
    int end_point=(index+1)*size/m_int;
    
    int i=0;
    int j=0;
    int k=0;
    for(i=0;i<size;i++){    
        for(j=start_point;j<end_point;j++){       
            for(k=0;k<size;k++){    
                result_matrix[i][j]+=matrix1[i][k]*matrix2[k][j];   
                if(terminate_flag==1) {
                    return -1;
                }                 
            }    
        }    
    } 
    return 0;       
}

double get_one_over_mn() {
    return 1.0/(matrix_size_for_thread*matrix_size_for_thread);
}

int calculate_2d_dft(int size,int** matrix1,double** real,double** imaginary,int index) {
    
    int start_point=index*size/m_int;
    int end_point=(index+1)*size/m_int;
    int k=0;
    int m=0;
    int n=0;
    int l=0;
    //cos (2*pi*((k*m)/M + l*n/N))-jsin(2*pi*((k*m)/M + l*n/N))
    for(k=0;k<size;k++) {
        for(l=start_point;l<end_point;l++) {
            for(m=0;m<size;m++) {
                for(n=0;n<size;n++) {
                    //cofactor+=((cos(2*M_PI*((double)(k*m/size) + (double)(l*n/size))-sin(2*M_PI*((double)(k*m/size) + (double)(l*n/size)))))*matrix1[m][n]);
                    //cofactor+=(((exp(2*M_PI*(k*m/size + l*n/size))))*matrix1[m][n]);
                    double mult1=(-2.0*M_PI*(double)k*(double)m/(double)size);
                    double mult2=(-2.0*M_PI*(double)l*(double)n/(double)size);
                    real[k][l]+=((double)matrix1[m][n]*1.0*(cos(mult1+mult2)));
                    imaginary[k][l]+=((double)matrix1[m][n]*1.0*(sin(mult1+mult2)));
                    if(terminate_flag==1) {
                        return -1;
                    }
                }
            }
            //real[k][l]/=get_one_over_mn();
            //imaginary[k][l]/=get_one_over_mn();
        }        
    }
    return 0;
}

void* run_thread(void* arg) {
    //take thread index
    int thread_index=*(int*)arg;
    double time_passed=0;
    //ree(arg);

    if(terminate_flag==1) {
        pthread_cond_broadcast(&condition);
        pthread_mutex_unlock(&mutex);
        return NULL;
    }

    struct timespec ts;

    //start to measure time
    double first_time=0;
    if (clock_gettime (CLOCK_MONOTONIC, &ts) == 0) {
        first_time=(double) (ts.tv_sec+ts.tv_nsec/(pow(10.0,9.0)));
    } 
    else {
        perror("Error on clock get time");
        return NULL;
    }

    if(terminate_flag==1) {
        pthread_cond_broadcast(&condition);
        pthread_mutex_unlock(&mutex);
        return NULL;
    }

    if(multiply_two_matrices(matrix_size_for_thread,matrix1,matrix2,result_matrix,thread_index)!=0) {
        pthread_cond_broadcast(&condition);
        pthread_mutex_unlock(&mutex);
        return NULL;
    }
    if(terminate_flag==1) {
        pthread_cond_broadcast(&condition);
        pthread_mutex_unlock(&mutex);
        return NULL;
    }
    //measure time
    double second_time=0;
    if (clock_gettime (CLOCK_MONOTONIC, &ts) == 0) {
        second_time=(double) (ts.tv_sec+ts.tv_nsec/(pow(10.0,9.0)));
    }
       
    else {
        perror("Error on clock get time");
        return NULL;
    }
    if(terminate_flag==1) {
        pthread_cond_broadcast(&condition);
        pthread_mutex_unlock(&mutex);
        return NULL;
    }        
    time_passed=second_time-first_time;
    time_t curtime;
    time(&curtime);
    fprintf(stdout,"%s => Thread %d has reached the rendezvous point in %.4lf seconds.\n",get_time(ctime(&curtime)),thread_index,time_passed);
    pthread_mutex_lock(&mutex);
    ++arrived;   
    //synchronization barrier
    while(arrived<m_int) {   
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
    time(&curtime);
    fprintf(stdout,"%s => Thread %d is advancing to the second part\n",get_time(ctime(&curtime)),thread_index);
    time_passed=0;

    //do dft

    first_time=0;
    if (clock_gettime (CLOCK_MONOTONIC, &ts) == 0) {
        first_time=(double) (ts.tv_sec+ts.tv_nsec/(pow(10.0,9.0)));
    }
        
    else {
        perror("Error on clock get time");
        return NULL;
    }
    if(terminate_flag==1) {
        return NULL;
    }
    if(calculate_2d_dft(matrix_size_for_thread,result_matrix,dft_matrix_r,dft_matrix_i,thread_index)!=0) {
        return NULL;
    }
    if(terminate_flag==1) {
        return NULL;
    }
    second_time=0;
    if (clock_gettime (CLOCK_MONOTONIC, &ts) == 0) {
        second_time=(double) (ts.tv_sec+ts.tv_nsec/(pow(10.0,9.0)));
    }    
    else {
        perror("Error on clock get time");
        return NULL;
    }
        
    time(&curtime);
    time_passed=second_time-first_time;
    fprintf(stdout,"%s => Thread %d has finished the second part in %.4lf seconds.\n",get_time(ctime(&curtime)),thread_index,time_passed);

    return NULL;
}

void wait_for_threads() {
    /*for(int i=0;i<m_int;i++) {
        void**retval=NULL;
        if(pthread_join(threads[i],retval)!=0) {}
    }*/
}

int run_the_process(int argc, char const *argv[]) {

    memset(input1,0,MAX_BLKSIZE);
    memset(input2,0,MAX_BLKSIZE);
    memset(output,0,MAX_BLKSIZE);
    memset(narg,0,MAX_BLKSIZE);
    memset(marg,0,MAX_BLKSIZE);          

    int i=0;
    //take arguments
    for(i=1;i<argc;i++) {
        if(argv[i][0]=='-' && argv[i][1]=='i') {
            strncpy(input1,argv[i+1],strlen(argv[i+1]));
        }
        else if(argv[i][0]=='-' && argv[i][1]=='j') {
            strncpy(input2,argv[i+1],strlen(argv[i+1]));
        }  
        else if(argv[i][0]=='-' && argv[i][1]=='o') {
            strncpy(output,argv[i+1],strlen(argv[i+1]));
        }   
        else if(argv[i][0]=='-' && argv[i][1]=='n') {
            strncpy(narg,argv[i+1],strlen(argv[i+1]));
        } 
        else if(argv[i][0]=='-' && argv[i][1]=='m') {
            strncpy(marg,argv[i+1],strlen(argv[i+1]));
        }                                         
    }     

    n_int=atoi(narg);
    m_int=atoi(marg);
    //initiliaze condition variable and mutex
    pthread_cond_init(&condition,NULL);
    pthread_mutex_init(&mutex,NULL);

    //take matrix size
    int matrix_size=(int)(pow(2.0,(double)n_int));
    matrix_size_for_thread=matrix_size;

    if(n_int<=2) {
        perror("Error with argument n");
        pthread_cond_destroy(&condition);
        pthread_mutex_destroy(&mutex);
        return -1;
    }
    if(m_int<2 && m_int%2!=0) {
        perror("Error with argument m");
        pthread_cond_destroy(&condition);
        pthread_mutex_destroy(&mutex);
        return -1;
    }    
    //open input file 1
    int fd_input1=open(input1,(O_RDONLY),0777);
    if(fd_input1==-1) {
        perror("Error on first input file");
        pthread_cond_destroy(&condition);
        pthread_mutex_destroy(&mutex);
        return -1;
    }

    matrix1=(int**)malloc(sizeof(int*)*matrix_size);
    matrix2=(int**)malloc(sizeof(int*)*matrix_size);
    result_matrix=(int**)malloc(sizeof(int*)*matrix_size);
    dft_matrix_i=(double**)malloc(sizeof(double*)*matrix_size);
    dft_matrix_r=(double**)malloc(sizeof(double*)*matrix_size);

    for(int i=0;i<matrix_size;i++) {
        matrix1[i]=(int*)malloc(sizeof(int)*matrix_size);
        matrix2[i]=(int*)malloc(sizeof(int)*matrix_size);
        result_matrix[i]=(int*)malloc(sizeof(int)*matrix_size);
        dft_matrix_i[i]=(double*)malloc(sizeof(double)*matrix_size);
        dft_matrix_r[i]=(double*)malloc(sizeof(double)*matrix_size);

        memset(matrix1[i],0,sizeof(int)*matrix_size);
        memset(matrix2[i],0,sizeof(int)*matrix_size);
        memset(result_matrix[i],0,sizeof(int)*matrix_size);      
        memset(dft_matrix_i[i],0,sizeof(double)*matrix_size);
        memset(dft_matrix_r[i],0,sizeof(double)*matrix_size);

    }

    threads=(pthread_t*)malloc(sizeof(pthread_t)*m_int);
    memset(threads,0,sizeof(pthread_t)*m_int);

    int read_file_1_count=0;
    int read_file_2_count=0;
    int row_count=0;
    int column_count=0;

    struct timespec ts;

    double first_time=0;
    if (clock_gettime (CLOCK_MONOTONIC, &ts) == 0) {
        first_time=(double) (ts.tv_sec+ts.tv_nsec/(pow(10.0,9.0)));
    }
        
    else {
        close(fd_input1);
        free_resources();
        pthread_cond_destroy(&condition);
        pthread_mutex_destroy(&mutex);
        return -1;
    }


    while(1) {
        char read_char='\0';
        int read_byte=read(fd_input1,&read_char,1);

        if(terminate_flag==1) {
            close(fd_input1);
            free_resources();
            pthread_cond_destroy(&condition);
            pthread_mutex_destroy(&mutex);

            return -1;            
        }

        if(read_byte==-1) {
            perror("Error on read");
            close(fd_input1);
            free_resources();
            pthread_cond_destroy(&condition);
            pthread_mutex_destroy(&mutex);            
            return -1;
        }

        if(read_char=='\0' || read_file_1_count==(matrix_size*matrix_size)) {
            //eof reached
            break;
        }
        int read_int=(int)read_char;

        matrix1[row_count][column_count++]=read_int;
        if(column_count==matrix_size) {
            column_count=0;
            row_count++;
        }
        //printf("%d %d\n",read_file_1_count,matrix_size*matrix_size);        
        read_file_1_count++;
    }
    if(read_file_1_count<(matrix_size*matrix_size)) {
        perror("FATAL ERROR, input file 1 have insufficient content");
        close(fd_input1);
        free_resources();        
        return -1;
    }

    row_count=0;
    column_count=0;
    if(close(fd_input1)!=0) {
        perror("Error closing input file 1");
        free_resources();
        pthread_cond_destroy(&condition);
        pthread_mutex_destroy(&mutex); 
        return -1;
    }

    int fd_input2=open(input2,(O_RDONLY),0777);
    if(fd_input2==-1) {
        perror("Error opening input file 2");
        pthread_cond_destroy(&condition);
        pthread_mutex_destroy(&mutex); 
        free_resources();
        return -1;      
    }
    
    while(1) {
        char read_char='\0';
        int read_byte=read(fd_input2,&read_char,1);
        if(read_byte==-1) {
            perror("Error on read");
            close(fd_input2);
            pthread_cond_destroy(&condition);
            pthread_mutex_destroy(&mutex); 
            free_resources();
            return -1;
        }
        if(read_char=='\0' || read_file_2_count==(matrix_size*matrix_size)) {
            //eof reached
            break;
        }
        int read_int=(int)read_char;
        matrix2[row_count][column_count++]=read_int;
        if(column_count==matrix_size) {
            column_count=0;
            row_count++;
        }
        read_file_2_count++;
    }

    if(read_file_2_count<(matrix_size*matrix_size)) {
        perror("FATAL ERROR, input file 2 have insufficient content");
        close(fd_input2);
        pthread_cond_destroy(&condition);
        pthread_mutex_destroy(&mutex); 
        free_resources();
        return -1;
    }
    if(close(fd_input2)!=0) {
        free_resources();
        perror("Error closing input file 2");
        pthread_cond_destroy(&condition);
        pthread_mutex_destroy(&mutex); 
        return -1;
    }

    time_t curtime;
    time(&curtime);

    int index_numbers[m_int];
    memset(index_numbers,0,m_int*sizeof(int));


    for(int i=0;i<m_int;i++) {
        //int* index=(int*)malloc(sizeof(int));
        //*index=i;
        index_numbers[i]=i;
        void*pointer=&index_numbers[i];


        if(pthread_create(&(threads[i]),NULL,&run_thread,/*(void*)index*/pointer)!=0) {
            perror("Error on create thread");
            pthread_cond_destroy(&condition);
            pthread_mutex_destroy(&mutex); 
            free_resources();
            return -1;
        }
    }
    fprintf(stdout,"%s => Two matrices of size %dx%d have been read. The number of threads is %d\n",get_time(ctime(&curtime)),matrix_size,matrix_size,m_int);

    if(terminate_flag==1) {
        //pthread_cond_broadcast(&condition);
        free_resources();
        pthread_cond_destroy(&condition);
        pthread_mutex_destroy(&mutex); 
        return -1;
    }
    for(int i=0;i<m_int;i++) {
        void**retval=NULL;
        if(pthread_join(threads[i],retval)!=0) {
            perror("Error on pthread join");
            //pthread_cond_broadcast(&condition);
            free_resources();
            pthread_cond_destroy(&condition);
            pthread_mutex_destroy(&mutex); 
            return -1;
        }
    }
    if(terminate_flag==1) {
        free_resources();
        pthread_cond_destroy(&condition);
        pthread_mutex_destroy(&mutex); 
        return -1;
    }

    double second_time=0;
    if (clock_gettime (CLOCK_MONOTONIC, &ts) == 0) {
        second_time=(double) (ts.tv_sec+ts.tv_nsec/(pow(10.0,9.0)));
    }
        
    else {
        perror("Error on clock get time");
        free_resources();
        pthread_cond_destroy(&condition);
        pthread_mutex_destroy(&mutex); 
        return -1;
    }
    double time_passed=second_time-first_time;

    time(&curtime);

    fprintf(stdout,"%s => Total time spent:%.3lf\n",get_time(ctime(&curtime)),time_passed);

    int out_fd=open(output,O_RDWR | O_TRUNC | O_CREAT,0777);

    if(terminate_flag==1) {
        close(out_fd);
        free_resources();
        pthread_cond_destroy(&condition);
        pthread_mutex_destroy(&mutex); 
        return -1;
    }

    if(out_fd==-1) {
        perror("Error on open output file");
        close(out_fd);
        free_resources();
        pthread_cond_destroy(&condition);
        pthread_mutex_destroy(&mutex); 
        return -1;
    }
    for(int i=0;i<matrix_size;i++) {
        for(int k=0;k<matrix_size;k++) {
            dprintf(out_fd,"%.3lf + (%.3lf j) ",dft_matrix_r[i][k],dft_matrix_i[i][k]);
            if(k!=(matrix_size-1)) {
                dprintf(out_fd,",");
            }
            if(terminate_flag==1) {
                close(out_fd);
                free_resources();
                pthread_cond_destroy(&condition);
                pthread_mutex_destroy(&mutex); 
                return -1;                
            }
        }
        dprintf(out_fd,"\n");
    }
    if(close(out_fd)!=0) {
        perror("Error on close output file");
        free_resources();
        pthread_cond_destroy(&condition);
        pthread_mutex_destroy(&mutex); 
        return -1;
    }
    time(&curtime);
    fprintf(stdout,"%s => The process has written the output file.\n",get_time(ctime(&curtime)));
    free_resources();   
    pthread_cond_destroy(&condition);
    pthread_mutex_destroy(&mutex);
    return 0;
}