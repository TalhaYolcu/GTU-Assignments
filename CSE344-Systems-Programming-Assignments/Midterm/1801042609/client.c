/*
./client -s pathToServerFifo -o pathToDataFile

where
-s: the path (relative or absolute) of the server fifo
-o: the path (relative or absolute) of the data file to be processed by the server.
*/

/*
1,0,-1
4,5,4
7,8,7


*/

#include "fifo_seqnum.h"
#include<errno.h>
#include<stdio.h>
#include <time.h>

static char clientFifo[CLIENT_FIFO_NAME_LEN];

/* Invoked on exit to delete client FIFO */
static void removeFifo(void){
    unlink(clientFifo);
}

void display(int** mat, int row, int col)
{
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++) {
            fprintf(stdout,"%d ", mat[i][j]);
        }
        fprintf(stdout,"\n");
    }
}

void print_usage_exit() {
    //print_time_stamp();
    printf("Usage:./client -s serverfifo -o input2.csv\n");
    perror("Error, missing cmd arguments");
    exit(0);
}

int main(int argc, char *argv[]) {
    int serverFd, clientFd;
    struct request req;
    struct response resp;
    int row_count=0;
    int column_count=1;

    if(argc!=5) {
        print_usage_exit();
    }

    char* datafile=(char*)malloc(sizeof(char)*MAX_BLKSIZE);
    char* fifofile=(char*)malloc(sizeof(char)*MAX_BLKSIZE);
    memset(datafile,0,sizeof(char)*MAX_BLKSIZE);
    memset(fifofile,0,sizeof(char)*MAX_BLKSIZE);

    int i;
    for(i=1;i<argc;i++) {
        if(argv[i][0]=='-' && argv[i][1]=='o') {
            int len=strlen(argv[i+1]);
            strncpy(datafile,argv[i+1],len);
        }
        else if(argv[i][0]=='-' && argv[i][1]=='s') {
            int len=strlen(argv[i+1]);
            strncpy(fifofile,argv[i+1],len);
        }
    }

    int fd=open(datafile,O_RDONLY);
    if(fd==-1) {
        perror("Open error\n");
        exit(1);
    }

    char read_until_new_line='0';
    while(1) {
        int bytes_read=read(fd,&read_until_new_line,1);
        if(bytes_read==-1) {
            perror("Read error");
            break;
        }
        if(bytes_read==0) {
            //fprintf(stdout,"Eof reached...\n");
            break;
        }
        if(read_until_new_line=='\0') {
            //fprintf(stdout,"Eof reached...\n");
            break;            
        }   
        if(read_until_new_line==',') {
            column_count++;
        }     
        if(read_until_new_line=='\n') {
            break;
        }
    }
    if(close(fd)==-1) {
        perror("Error close");
        exit(1);
    } 

    fd=open(datafile,O_RDONLY);
    if(fd==-1) {
        perror("Open error\n");
        exit(1);
    }


    int matrix[column_count][column_count];
    row_count=column_count;
    char int_buffer[12];
    memset(int_buffer,'\0',sizeof(char)*12);
    char read_byte='0';


    int buffer_counter=0;
    int row=0;
    int column=0;

    while(1) {

        int bytes_read=read(fd,&read_byte,1);
        if(bytes_read==-1) {
            perror("Read error");
            break;
        }
        if(bytes_read==0) {
            //fprintf(stdout,"Eof reached...1\n");
            if(column!=column_count) {
                //printf("%s\n",int_buffer);
                sscanf(int_buffer,"%d",&matrix[row][column]);
                column++;

                buffer_counter=0;
                memset(int_buffer,0,sizeof(char)*12);
            }            
            break;
        }
        if(read_byte=='\0') {
            if(row!=column) {
                //printf("%s\n",int_buffer);
                sscanf(int_buffer,"%d",&matrix[row][column]);
                column++;

                buffer_counter=0;
                memset(int_buffer,0,sizeof(char)*12);
            }
            //fprintf(stdout,"Eof reached...2\n");
            break;            
        }
        if(read_byte==',') {
            //printf("%s\n",int_buffer);
            //integer is in int_buffer
            //after taking integer clean the buffer

            sscanf(int_buffer,"%d",&matrix[row][column]);
            column++;

            buffer_counter=0;
            memset(int_buffer,0,sizeof(char)*12);
        }
        else if(read_byte=='\n') {
            //printf("%s\n",int_buffer);

            //new line, next row is coming

            sscanf(int_buffer,"%d",&matrix[row][column]);
            column=0;
            row++;
            memset(int_buffer,0,sizeof(char)*12);
            buffer_counter=0;            
        }
        else {
            int_buffer[buffer_counter++]=read_byte;
        }
    }



    if(close(fd)) {
        perror("Close error\n");
        //free resources
        exit(1);
    }

    int** matrixv2=(int**)malloc(sizeof(int*)*column_count);
    for(i=0;i<column_count;i++) {
        matrixv2[i]=(int*)malloc(sizeof(int)*column_count);
    }

    for(i=0;i<column_count;i++) {
        int k;
        for(k=0;k<column_count;k++) {
            matrixv2[i][k]=matrix[i][k];
        }
    }

    //display(matrixv2,row_count,column_count);
    //add timestamp
    printf("Client PID#%d (%s) is submitting %dx%d matrix\n",getpid(),datafile,row_count,row_count);

    time_t submit_time=time(NULL);


    /* Create our FIFO (before sending request, to avoid a race) */




    umask(0);                   /* So we get the permissions we want */
    snprintf(clientFifo, CLIENT_FIFO_NAME_LEN, CLIENT_FIFO_TEMPLATE,(long) getpid());
    if (mkfifo(clientFifo, 0777) == -1 && errno != EEXIST)
        errExit("mkfifo %s", clientFifo);

    if (atexit(removeFifo) != 0)
        errExit("atexit");

    /* Construct request message, open server FIFO, and send message */

    serverFd = open(fifofile, O_WRONLY);
    if (serverFd == -1)
        errExit("open %s", fifofile);


    i=0;
    int k=0;
    for(i=0;i<column_count;i++) {
        for(k=0;k<row_count;k++) {
            req.matrix_entry=matrixv2[i][k];
            req.pid=getpid();
            req.row=row_count;
            int r1=sizeof(struct request);
            int r2=write(serverFd,&req,sizeof(struct request));
            if(r1!=r2) {
                perror("Can't write to server");
                exit(1);
            }
        }
    }

    /*if(close(serverFd)==-1) {
        perror("Error close fifo");
        free(datafile);
        free(fifofile);        
        exit(-1);
    }*/

    resp.invertible=0;

    /* Open our FIFO, read and display response */

    clientFd = open(clientFifo, O_RDONLY);
    if (clientFd == -1)
        perror("open clientfd error");

    if (read(clientFd, &resp, sizeof(int))
            != sizeof(int))
        perror("Can't read response from server");

    /*if(close(clientFd)==-1) {
        perror("Error close fifo");
        free(datafile);
        free(fifofile);        
        exit(-1);
    }*/
/*
    
Client PID#667: the matrix is invertible, total time 2.25 seconds, goodbye.

*/  

    time_t receive_time=time(NULL);
    //printf("%ld %ld\n",submit_time,receive_time);
    double duration=receive_time-submit_time;

   
    if(resp.invertible==0) {
        printf("Client PID#%d: the matrix is not invertible, total time %.2lf seconds, goodbye.\n",getpid(),duration);
    }
    else {
        printf("Client PID#%d the matrix is invertible, total time %.2lf seconds, goodbye.\n",getpid(),duration);
    }

    removeFifo();


    free(datafile);
    free(fifofile);


    exit(EXIT_SUCCESS);
}
