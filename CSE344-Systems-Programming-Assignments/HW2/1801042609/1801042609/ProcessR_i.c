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

extern char **environ;


//prototypes of functions
void handler(int signal_number);
void calculate_mean(point points[POINT_SIZE],int pt_count,double* xmean,double *ymean, double* zmean);
double calculate_cov(point points[POINT_SIZE],int pt_count,double fmean,double smean,char f,char s);
int generate_matrix(point points[POINT_SIZE],int pt_count,const char* outputfilePath,int process_num);

sig_atomic_t flag=0;
void handler(int signal_number) {
    if(signal_number==SIGINT || signal_number==SIGHUP || signal_number==SIGPIPE || signal_number==SIGQUIT || signal_number==SIGTERM || signal_number==SIGTSTP || signal_number==SIGUSR1 || signal_number==SIGUSR2) {
        flag=1;
    }
}

void calculate_mean(point points[POINT_SIZE],int pt_count,double* xmean,double *ymean, double* zmean) {
    //calculate the means of the x y and z coordinates
    int i=0;
    for(i=0;i<pt_count;i++) {
        (*xmean)+=points[i].x;
        (*ymean)+=points[i].y;
        (*zmean)+=points[i].z;
    }
    (*xmean)/=pt_count;
    (*ymean)/=pt_count;
    (*zmean)/=pt_count;
}

double calculate_cov(point points[POINT_SIZE],int pt_count,double fmean,double smean,char f,char s) {
    //calculate the covariance matrix with given parameters
    double cov=0;

    if(f==s) {
        if(f=='x') {
            //cov xx
            int i=0;
            for(i=0;i<pt_count;i++) {
                cov+=((points[i].x-fmean)*(points[i].x-smean));
            }
            cov/=pt_count;

        }
        else if(f=='y') {
            //cov yy
            int i=0;
            for(i=0;i<pt_count;i++) {
                cov+=((points[i].y-fmean)*(points[i].y-smean));
            }
            cov/=pt_count;
        }
        else {
            //cov zz
            int i=0;
            for(i=0;i<pt_count;i++) {
                cov+=((points[i].z-fmean)*(points[i].z-smean));
            }
            cov/=pt_count;
        }
    }
    else if(f=='x' && s=='y') {
        //covxy
        int i=0;
        for(i=0;i<pt_count;i++) {
            cov+=((points[i].x-fmean)*(points[i].y-smean));
        }
        cov/=pt_count;
    }
    else if(f=='x' && s=='z') {
            //covxz
            int i=0;
            for(i=0;i<pt_count;i++) {
                cov+=((points[i].x-fmean)*(points[i].z-smean));
            }
            cov/=pt_count;
    }
    else if(f=='y' && s=='z') {
            //covyz
            int i=0;
            for(i=0;i<pt_count;i++) {
                cov+=((points[i].y-fmean)*(points[i].z-smean));
            }
            cov/=pt_count;
    }
    return cov;   
}

int generate_matrix(point points[POINT_SIZE],int pt_count,const char* outputfilePath,int process_num) {
    double xmean=0,ymean=0,zmean=0;
    //calculate the means of the x y and z coordinats
    calculate_mean(points,pt_count,&xmean,&ymean,&zmean);

    /*
    MATRIX IS 

    [cov(x,x)  cov(x,y)  cov(x,z)]

    [cov(y,x)  cov(y,y)  cov(y,z)]

    [cov(z,x)  cov(z,y)  cov(z,z)]

    */

    float covxx=0,covyy=0,covzz=0,covxy=0,covxz=0,covyz=0;
    covxx=calculate_cov(points,pt_count,xmean,xmean,'x','x');
    covyy=calculate_cov(points,pt_count,ymean,ymean,'y','y');
    covzz=calculate_cov(points,pt_count,zmean,zmean,'z','z');
    covxy=calculate_cov(points,pt_count,xmean,ymean,'x','y');
    covxz=calculate_cov(points,pt_count,xmean,zmean,'x','z');
    covyz=calculate_cov(points,pt_count,ymean,zmean,'y','z');

    char buffer[WRITE_BUFFER_SIZE];
    memset(buffer,0,WRITE_BUFFER_SIZE);

    //open the output file to write with
    //(O_RDWR | O_APPEND | O_CREAT) flags
    int fd=open(outputfilePath,WRITE_FLAGS,0777);
    if(fd==-1) {
        perror("Error: Couldnt open outputfile");
        return -1;
    }
    int pid=process_num;
    sprintf(buffer,":%d\n%.3f %.3f %.3f\n%.3f %.3f %.3f\n%.3f %.3f %.3f\n",pid,covxx,covxy,covxz,covxy,covyy,covyz,covxz,covyz,covzz);
    int i=0;
    while(buffer[i]!='\0') {
        i++;
    }

    //lock the file to ensure that nobody else using the file
    struct flock lock;
    int result_of_fcntl;

    //lock
    memset(&lock,0,sizeof(lock));
    lock.l_type=F_WRLCK;  
    result_of_fcntl=fcntl(fd,F_SETLKW,&lock);


    if(result_of_fcntl==-1) {
        close(fd);
        perror("Error:Couldnt lock the file");
        return -1;
    }

    //write to file

    int catch=write(fd,buffer,i);
    if(catch==-1) {
        perror("Error COULDNT WROTE TO FILE:");
    }

    //release unlock
    lock.l_type=F_UNLCK;
    result_of_fcntl=fcntl(fd,F_SETLKW,&lock);

    if(result_of_fcntl==-1) {
        close(fd);
        perror("Error couldnt RELEASE LOCK:");
        return -1;
    }
    close(fd);


    if(flag==1) {
        printf("SIGINT ARRIVED\n");
        return 0;          
    }    
    return 0;
}

int main(int argc, char const *argv[]) {
    struct sigaction sa;

    //printf("\n%d\n",getpid());
    memset(&sa,0,sizeof(sa));
    sa.sa_handler=&handler;
    sigaction(SIGINT,&sa,NULL);

    //sleep(10);
 
    //this is child process and started by execve
    int point_counter=0;
    point points[POINT_SIZE];
    memset(points,0,POINT_SIZE*sizeof(point));

    printf("\nThis is process:%d\n",getpid());
    //sleep(10);
    //get the environment variables
    for(point_counter=0;point_counter<POINT_SIZE;point_counter++) {
        int x=0,y=0,z=0;
        sscanf(environ[point_counter],"%d %d %d",&x,&y,&z);
        points[point_counter].x=(unsigned char)x;
        points[point_counter].y=(unsigned char)y;
        points[point_counter].z=(unsigned char)z;

    }


    int process_num=0;
    sscanf(argv[2],"%d",&process_num);
    //generate the matrix with given points
    generate_matrix(points,POINT_SIZE,argv[1],process_num);
    printf("Exiting from child... %d\n",process_num);




    exit(0);
    return 0;
}
