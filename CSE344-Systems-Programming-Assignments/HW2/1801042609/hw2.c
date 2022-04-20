#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <errno.h>
#include <math.h>
#include "defines.h"

/*
int kill(pid_t pid, int sig);
Returns 0 on success, and -1 on error and sets errno.
*/

/*
TODO ------>
If P receives SIGINT, it will forward the signal to all of its children, free all of its resources,
close open files, and remove the output file, clean-up after its children and terminate. When
the children receive the forwarded signal, they will terminate after freeing their resources as
well. Be careful with the signal handler, remember what I told you during the lectures. Use
the polling based paradigm I showed you for graceful exiting

1-Eger parent SIGINT alırsa, childlara ilet
2-Childlar SIGINT alırsa free ve close yap
3-Parentta Eger senin bi child ın SIGINT ile dönerse free ve close yap, output dosyasını sil
4-Signal handlerda sadece flag i ayarla


*/

//prototypes of functions
void handler(int signa_number);
void print_usage_and_exit();
int start_reading_file(char* inputfile,char* outputfile);
void print_points(point pt[POINT_SIZE],int pt_count);
int start_reading_output_file(char* outputfile,int process_count);
float calculate_frobenius_norm(float matrix[ROW_COUNT][COLUMN_COUNT]);
int calculate_difference(norm* matrices,int process_count,char* out);
int read_process_number(int* fd);
float calculate_frobenius_norm(float matrix[ROW_COUNT][COLUMN_COUNT]);
void print_the_matrice(int p1,int p2,char* outputfile);

sig_atomic_t flag=0;

void handler(int signal_number) {
    if(signal_number==SIGINT || signal_number==SIGHUP || signal_number==SIGPIPE || signal_number==SIGQUIT || signal_number==SIGTERM || signal_number==SIGTSTP || signal_number==SIGUSR1 || signal_number==SIGUSR2) {
        flag=1;
    }
}

void print_usage_and_exit() {
    printf("Program usage is: ./processP -i inputFilePath -o outputFilePath\n");
    printf("Exiting...\n");
    exit(0);
}
void print_points(point pt[POINT_SIZE],int pt_count) {
    //print the points
    int i=0;
    for(i=0;i<pt_count;i++) {
        printf("(%d, %d, %d)",pt[i].x,pt[i].y,pt[i].z);
        if(i!=(pt_count-1)) {
            printf(",");
        }
    }
}
int start_reading_file(char* inputfile,char* outputfile) {
    
    printf("\nThis is process:%d\n",getpid());
    
    //sleep(10);

    if(flag==1) {
        return 0;
    }

    printf("Process P reading %s\n",inputfile);
    //OPEN FILE WITH O_RDWR
    int fd=open(inputfile,READ_FLAGS,0777);
    if(fd==-1) {
        return -1;
    }

    if(flag==1) {
        close(fd);
        return 0;
    }

    size_t offset=0;
    size_t bytes_read;
    unsigned char buffer[READ_BUFFER_SIZE];
    memset(buffer,'\0',READ_BUFFER_SIZE);

    point points[POINT_SIZE];
    memset(points,'0',POINT_SIZE*sizeof(point));
    int point_counter=0;
    int process_counter=1;

    parentp parent;
    memset(parent.childpids,0,MAX_PROCESS*sizeof(int));
    parent.childpcount=0;
    parent.process_id=getpid();

    do {
        //read the input file
        bytes_read=read(fd,buffer,sizeof(buffer));
        //In case of error, return -1
        if(bytes_read<0) {
            close(fd);
            return -1;
        }
        //set x y and z of the point
        points[point_counter].x=buffer[0];
        points[point_counter].y=buffer[1];
        points[point_counter].z=buffer[2];
        offset+=bytes_read;
        //increment point counter
        point_counter++;

        if(flag==1) {
            close(fd);
            return 0;
        }


        if(point_counter==POINT_SIZE) {   
            //10 points found, create child process      
            printf("Created R_%d with ",process_counter);
            print_points(points,point_counter);     
            printf("\n");     
            //create child process  
            int pid=fork();
            //create command line arguments and environment variables
            char* program="./ProcessR_i";
            char**cmdarguments=(char**)malloc(sizeof(char*)*4);
            char**env=(char**)malloc(sizeof(char*)*(POINT_SIZE+1));

            int z=0;
            for(z=0;z<4;z++) {
                cmdarguments[z]=(char*)malloc(sizeof(char)*WRITE_BUFFER_SIZE);
                memset(cmdarguments[z],0,WRITE_BUFFER_SIZE);
            }
            for(z=0;z<POINT_SIZE+1;z++) {
                env[z]=(char*)malloc(sizeof(char)*WRITE_BUFFER_SIZE);
                memset(env[z],0,WRITE_BUFFER_SIZE);
            }
            if(pid!=0) {
                //parent process
                if(flag==1) {
                    int child_traverse=0;
                    for(child_traverse=0;child_traverse<parent.childpcount;child_traverse++) {
                        if(kill(parent.childpids[child_traverse],SIGINT)==-1) {
                            perror("Error:Cant send kill signal to the child");
                        }
                    }
                    //free resources
                    int i=0;
                    for(i=0;i<4;i++) {
                        free(cmdarguments[i]);
                    }
                    for(i=0;i<POINT_SIZE+1;i++) {
                        free(env[i]);
                    }
                    free(cmdarguments);
                    free(env);
                    close(fd);

                    unlink(outputfile);
                    return 0;

                }
                process_counter++;  
            }
            else {
                //child process
                char buffer[WRITE_BUFFER_SIZE];
                memset(buffer,0,WRITE_BUFFER_SIZE);
                parent.childpids[parent.childpcount]=pid;
                parent.childpcount++;

                //set environment variables and command line arguments
                int pt_ctr=0;
                for(pt_ctr=0;pt_ctr<POINT_SIZE;pt_ctr++) {
                    sprintf(buffer,"%d %d %d",points[pt_ctr].x,points[pt_ctr].y,points[pt_ctr].z);
                    strncpy(env[pt_ctr],buffer,strlen(buffer));
                    memset(buffer,0,WRITE_BUFFER_SIZE);
                }
                env[pt_ctr]=NULL;
                cmdarguments[0]=strrchr(program,'/');
                if(cmdarguments[0]!=NULL) {
                    cmdarguments[0]++;
                }
                strncpy(cmdarguments[1],outputfile,strlen(outputfile));
                sprintf(cmdarguments[2],"%d",process_counter);
                cmdarguments[3]=NULL;
                //execute the new program with environment variables
                execve(program,cmdarguments,env);                   
            }
            //free resources
            int i=0;
            for(i=0;i<4;i++) {
                free(cmdarguments[i]);
            }
            for(i=0;i<POINT_SIZE+1;i++) {
                free(env[i]);
            }
            free(cmdarguments);
            free(env);
            //reset point counter to reach 10
            point_counter=0;
        }
    }
    while(bytes_read==sizeof(buffer));

    //end of file is reached

    //wait for childs to finish their jobs
    int process_traverse=0;
    for(process_traverse=0;process_traverse<process_counter;process_traverse++) {
        int childpid=wait(NULL);
        if(childpid==-1) {
            if(errno==ECHILD) {
                printf("No more children - bye\n");
                break;
            }
            else {
                printf("Waiting for child to finish...\n");
            }
        }
    }

    if(flag==1) {
        close(fd);
        unlink(outputfile);
        return 0;        
    }

    //close file and return
    close(fd);
    printf("\nReached EOF, collecting outputs from %s\n",outputfile);

    return process_counter;
}

float calculate_frobenius_norm(float matrix[ROW_COUNT][COLUMN_COUNT]) {
    //calculate square, sum each row and then sum each
    int i=0;
    int j=0;
    float row_sum=0;
    for(i=0;i<ROW_COUNT;i++) {
        float column_sum=0;
        for(j=0;j<COLUMN_COUNT;j++) {
            float square=matrix[i][j]*matrix[i][j];
            column_sum+=square;
        }
        row_sum+=column_sum;
    }
    //return square root of hte sum
    return sqrt(row_sum);

}

int read_process_number(int* fd) {
    //read process number
    char read_char='0';
    char process_num_str[6];
    memset(process_num_str,'\0',6);
    int i=0;
    while(read_char!='\n') {
        //read one byte
        int bytes_read=read(*fd,&read_char,1);
        if(read_char=='\n') {
            break;
        }
        //in case of error, return -1
        if(bytes_read==-1) {
            return -1;
        }
        process_num_str[i]=read_char;
        i++;
    }
    //new line is reached, scan from the buffer
    //get the child number and return it
    int process_number=0;
    sscanf(process_num_str,":%d",&process_number);
    return process_number;
}

void print_the_matrice(int p1,int p2,char* outputfile) {
    printf("\n");
    int fd=open(outputfile,READ_FLAGS,0777);
    char buf[5];
    int found_counter=0;
    memset(buf,'\0',5*sizeof(char));
    char p;
    if(fd==-1) {
        perror("Error:Couldnt open output file");
        exit(1);
    }
    while(1) {
        int x=read(fd,&p,1);
        if(p==EOF) {
            close(fd);
            break;
        }
        if(x==-1 || x==0) {
            close(fd);
            break;
        }
        
        if(p==':') {
            int ct=0;
            while(p!='\n') {
                int err=read(fd,&p,1);
                if(err==-1) {
                    close(fd);
                    perror("Error:");
                    exit(0);
                }
                buf[ct++]=p;
            }
            int read_int=0;
            sscanf(buf,"%d",&read_int);
            memset(buf,'\0',5);
            if(read_int==p1 || read_int==p2) {
                found_counter++;
                int line_ct=0;
                for(line_ct=0;line_ct<COLUMN_COUNT;line_ct++) {
                    p=0;
                    while(p!='\n') {
                        int err2=read(fd,&p,1);
                        if(err2==-1) {
                            close(fd);
                            perror("Error:");
                            exit(1);
                        }
                        printf("%c",p);
                    }
                }
                printf("\n");
            }

        }
        if(found_counter==2) {
            close(fd);
            break;
        }
    }

}

int calculate_difference(norm* matrices,int process_count,char* outputfile) {
    int i=0;
    int j=0;
    int p1=0;
    int p2=1;
    float difference=fabs(matrices[0].distance-matrices[1].distance);
    for(i=0;i<(process_count-1);i++) {
        for(j=i+1;j<(process_count-1);j++) {
            float temp_difference=fabs(matrices[i].distance-matrices[j].distance);
            if(temp_difference<difference) {
                difference=temp_difference;
                p1=matrices[i].process_number;
                p2=matrices[j].process_number;
            }
        }
    }
    printf("The closest matrices are %d and %d and their distance is %.3f.\n",p1,p2,difference);
    print_the_matrice(p1,p2,outputfile);
    printf("Terminating the program...\n");
    return 0;
}


int start_reading_output_file(char* outputfile,int process_count) {
    //open file to read outpuf file
    //return -1 in case of error
    int fd=open(outputfile,READ_FLAGS,777);
    if(fd==-1) {
        perror("Error:cant open outputfile");
        return -1;
    }
    //size_t offset=0;
    size_t bytes_read;
    char buffer='0';
    norm matrices[process_count];
    memset(matrices,'0',process_count*sizeof(norm));
    int current_process=0;

    if(process_count<=1) {
        printf("There is less than 2 matrices, can't calculate difference, terminating...");
        return 0;
    }
    while(1){

        //ensure that end of file is not reached
        char x='0';
        int res=read(fd,&x,1);
        if(res==0) {
            break;
        }
        //in case of error return -1
        if(res==-1) {
            perror("Error:cant read input file");
            close(fd);
            return -1;
        }
        //if end of file is reached get out of the loop
        if(x=='\n' || x==EOF) {
            break;
        }
        else {
            //we are not reached the EOF yet, we read the 1 byte
            //So, move cursor to the previous index
            lseek(fd,-1,SEEK_CUR);
        }
        //first read process number        
        int result_of_reading_process=read_process_number(&fd);
        if(result_of_reading_process==-1) {
            perror("Error:cant read process number");
            close(fd);
            return -1;
        }
        //save the process number into matrices
        matrices[current_process].process_number=result_of_reading_process;
        int line_traverse=0;
        float matrix[ROW_COUNT][COLUMN_COUNT];
        int cc=0;
        int rc=0;
        for(cc=0;cc<COLUMN_COUNT;cc++) {
            for(rc=0;rc<ROW_COUNT;rc++) {
                memset(matrix,0,sizeof(float));
            }
        }
        //read three line
        for(line_traverse=0;line_traverse<COLUMN_COUNT;line_traverse++) {
            char matrix_row[36];
            memset(matrix_row,'\0',36);
            int matrix_row_traverser=0;
            //read line by line
            while(buffer!='\n' || bytes_read!=0) {
                bytes_read=read(fd,&buffer,1);
                if(bytes_read==-1) {
                    //in case of error, return -1
                    close(fd);
                    perror("Error:cant read the line");
                    return -1;
                }
                if(buffer=='\n' || bytes_read==0) {
                    break;
                }
                //save the line to the matrix string
                matrix_row[matrix_row_traverser++]=buffer;
            }
            //save the matrix entries to the table
            sscanf(matrix_row,"%f %f %f",&matrix[line_traverse][0],&matrix[line_traverse][1],&matrix[line_traverse][2]);
        }    

        //calculate the frobenius norm of the matrix
        float frobenius_norm=calculate_frobenius_norm(matrix);   
        //save to the table
        matrices[current_process].distance=frobenius_norm;
        //printf("NORM OF %d. matrix is: %.3f\n",matrices[current_process].process_number,frobenius_norm); 
        current_process++;
    }
    close(fd);

    if(flag==1) {
        printf("SIGINT SIGNAL ARRIVED");
        unlink(outputfile);     
    }

    //find the closest two matrises
    return calculate_difference(matrices,process_count,outputfile);

}



int main(int argc, char const *argv[]) {
    //check input validity
    //there should be 5 command line arguments:
    /*
    1)./processP
    2)-i
    3)files/input.dat
    4)-o
    5)files/outputFile.dat
    */
    if(argc!=5) {
        print_usage_and_exit();
    }
    //if there is no -i
    if(strcmp(argv[1],"-i")!=0) {
        print_usage_and_exit();
    }
    //if there is no -o
    if(strcmp(argv[3],"-o")!=0) {
        print_usage_and_exit();
    }

    struct sigaction sa;

    //printf("\n%d\n",getpid());
    memset(&sa,0,sizeof(sa));
    sa.sa_handler=&handler;
    sigaction(SIGINT,&sa,NULL);
    sigaction(SIGHUP,&sa,NULL);
    sigaction(SIGPIPE,&sa,NULL);
    sigaction(SIGQUIT,&sa,NULL);
    sigaction(SIGTERM,&sa,NULL);
    sigaction(SIGTSTP,&sa,NULL);
    sigaction(SIGUSR1,&sa,NULL);
    sigaction(SIGUSR2,&sa,NULL);
   

    //copy the input file path
    char* inputfilepath=(char*)malloc(sizeof(char)*(strlen(argv[2])+1));
    memset(inputfilepath,0,strlen(argv[2])+1);
    strncpy(inputfilepath,argv[2],strlen(argv[2]));

    if(flag==1) {
        free(inputfilepath);
        perror("Error:SIGINT SIGNAL ARRIVED\n");
        exit(0);
    }

    //copy the output file path
    char* outputfilepath=(char*)malloc(sizeof(char)*(strlen(argv[4])+1));
    memset(outputfilepath,0,strlen(argv[4])+1);
    strncpy(outputfilepath,argv[4],strlen(argv[4]));

    //sleep(10);
    if(flag==1) {
        unlink(outputfilepath);
        free(inputfilepath);
        free(outputfilepath);
        printf("SIGINT SIGNAL ARRIVED\n");
        exit(0);        
    }    

    //make sure that output file is clean
    int fd=open(outputfilepath,CLEAN_WRITE_FLAGS,0777);
    if(fd==-1) {
        perror("Error:Couldnt open outputfile");
        free(inputfilepath);
        free(outputfilepath);        
        return -1;        
    }

    close(fd);



    //start to read input file return -1 if there is error
    //this function also creates childs and waits for them to finish their job
    int res=start_reading_file(inputfilepath,outputfilepath);

    //sleep(10);
    if(flag==1) {
        unlink(outputfilepath);
        free(inputfilepath);
        free(outputfilepath); 
        printf("SIGINT SIGNAL ARRIVED\n");
        exit(0);      
    }

    if(res==-1) {
        perror("Error: in start reading file ");
        free(inputfilepath);
        free(outputfilepath);        
        return -1;
    }
    printf("Children wrote to the file successfully...\n");

    //This function reads the output files to calculate frobenius norms and differences
    //If there is error, returns -1
    int res2=start_reading_output_file(outputfilepath,res);
    //printf("\n%d\n",getpid());
    //sleep(10);

    if(flag==1) {
        //make sure that output file is clean
        int fd=open(outputfilepath,CLEAN_WRITE_FLAGS,0777);
        if(fd==-1) {
            perror("Error:Couldnt open outputfile");
            free(inputfilepath);
            free(outputfilepath);        
            return -1;        
        }
        close(fd);        
        unlink(outputfilepath);

        free(inputfilepath);
        free(outputfilepath); 
        printf("SIGINT SIGNAL ARRIVED\n");


        exit(0);        
    }


    if(res2==-1) {
        perror("Error:in start reading output file");
        free(inputfilepath);
        free(outputfilepath);        
        return -1;
    }
    //free resources
    free(inputfilepath);
    free(outputfilepath);
    return 0;
}
