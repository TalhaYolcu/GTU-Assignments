#include <stdio.h>
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
#include <sys/stat.h>
#include <sys/mman.h>
#include <pthread.h>
#include <sys/wait.h>
#include "implementation.c"
#include "header.h"

//./hw5 -i filePath1 -j filePath2 -o output -n 4 -m 2

int main(int argc, char const *argv[])
{
    
    //check argument validity
    if(check_arguments(argc,argv)!=0) {
        perror("Error with arguments");
        print_usage_end_exit();
    }
    
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

    //run process
    if(run_the_process(argc,argv)!=0) {
        return 0;
    }

    
    return 0;
}
