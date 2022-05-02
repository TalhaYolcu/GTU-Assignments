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
#include <semaphore.h>
#include <errno.h>

#include "unnamed_header.h"

int number_of_desserts; 
int terminate_flag=0;
shared_memory* shared_ptr=NULL;




void handler(int signal_number,siginfo_t* siginfo,void*fd) {
    if(signal_number==SIGUSR1) {
        //wholesaler sent SIGUSR1 signal to the chef
        //terminate the chef
        //return number of dessert
        terminate_flag=1;
    }

}
void print_usage_and_exit() {
    perror("Error, invalid argument");
    fprintf(stdout,"Usage: ./hw3named -i inputFilePath -n name for named");
    fprintf(stdout,"./hw3unnamed -i inputFilePath for unnamed\n");
    exit(0);
}

int check_arguments(int argc, char const *argv[]) {
    int i=0;

    if(argc!=3) {
        return -1;
    }

    int input_file_ok=0;
    for(i=1;i<argc;i++) {
        if(argv[i][0]=='-' && argv[i][1]=='i' && i!=(argc-1)) {
            input_file_ok=1;
        }                   
    } 
    if(input_file_ok==1) {
        return 0;
    }
    return -1;
}

int create_shared_memory(int* fd,size_t size) {


    *fd = shm_open(MEMORY_NAME, (O_RDWR | O_CREAT), 0777);
    if (*fd == -1) {
        perror("shm_open error");
        return -1;
    }

    if (ftruncate(*fd, size) == -1) {
        perror("ftruncate error");
        return -1;
    }

    shared_ptr = (shared_memory*)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, *fd, 0);
    if (shared_ptr == MAP_FAILED) {
        perror("mmap error"); 
        return -1;
    }

    if(sem_init(&shared_ptr->flour,1,0)==-1) {
        perror("Sem init error flour");
        return -1;
    }
    if(sem_init(&shared_ptr->sugar,1,0)==-1) {
        perror("Sem init error sugar");
        return -1;
    }
    if(sem_init(&shared_ptr->wallnut,1,0)==-1) {
        perror("Sem init error wallnut");
        return -1;
    }
    if(sem_init(&shared_ptr->milk,1,0)==-1) {
        perror("Sem init error milk");
        return -1;
    }
    sem_init(& shared_ptr->agentSem,1,0);
    sem_init(& shared_ptr->sugar,1,0);
    sem_init(& shared_ptr->flour,1,0);
    sem_init(& shared_ptr->milk,1,0);
    sem_init(& shared_ptr->m,1,0);
    sem_init(& shared_ptr->wallnut,1,0);
    sem_init(& shared_ptr->fm,1,0);
    sem_init(& shared_ptr->sf,1,0);
    sem_init(& shared_ptr->sm,1,0);
    sem_init(& shared_ptr->sw,1,0);
    sem_init(& shared_ptr->fw,1,0);
    sem_init(& shared_ptr->mw,1,0);

    shared_ptr->isflour=0;
    shared_ptr->ismilk=0;
    shared_ptr->issugar=0;
    shared_ptr->iswallnut=0;
    memset(shared_ptr->queue,0,(2)*sizeof(char));


    return 0;
}

int pusher(int pusherindex) {

    while(terminate_flag==0) {
        switch (pusherindex)
        {
            case 0:
                if(sem_wait(& shared_ptr->milk)==-1) {
                    return -1;
                }
                if(terminate_flag==1) {
                    break;
                }  
                sem_wait(& shared_ptr->m);
                if(terminate_flag==1) {
                    break;
                }     
                if(shared_ptr->issugar==1) {
                    shared_ptr->issugar=0;
                    sem_post(& shared_ptr->fw);                  
                    if(terminate_flag==1) {
                        break;
                    }                         
                }
                else if(shared_ptr->isflour==1) {
                    shared_ptr->isflour=0;
                    sem_post(& shared_ptr->sw);
                    if(terminate_flag==1) {
                        break;
                    } 
                }
                else if(shared_ptr->iswallnut==1) {
                    shared_ptr->iswallnut=0;
                    sem_post(& shared_ptr->sf);

                    if(terminate_flag==1) {
                        break;
                    }                     
                }
                else {
                    shared_ptr->ismilk=1;
                }
                if(terminate_flag==1) {
                    break;
                } 

                sem_post(& shared_ptr->m);
                
                if(terminate_flag==1) {
                    break;
                }                 
                break;
            
            case 1:

                sem_wait(& shared_ptr->flour);
                if(terminate_flag==1) {
                    break;
                } 
                sem_wait(& shared_ptr->m);
                if(terminate_flag==1) {
                    break;
                } 
                if(shared_ptr->issugar==1) {
                    shared_ptr->issugar=0;
                    sem_post(& shared_ptr->mw);
                    if(terminate_flag==1) {
                        break;
                    }                     
                }
                else if(shared_ptr->ismilk==1) {
                    shared_ptr->ismilk=0;
                    sem_post(& shared_ptr->sw);
                    if(terminate_flag==1) {
                        break;
                    }  
                }
                else if(shared_ptr->iswallnut==1) {
                    shared_ptr->iswallnut=0;
                    sem_post(& shared_ptr->sm);

                    if(terminate_flag==1) {
                        break;
                    }  
                }                
                else {
                    shared_ptr->isflour=1;
                    if(terminate_flag==1) {
                        break;
                    }  
                }
                if(terminate_flag==1) {
                    break;
                }  
                sem_post(& shared_ptr->m);
                if(terminate_flag==1) {
                    break;
                }                  
                break;

            case 2:

                sem_wait(& shared_ptr->sugar);
                if(terminate_flag==1) {
                    break;
                }   

                sem_wait(& shared_ptr->m);
                if(terminate_flag==1) {
                    break;
                }   
                if(shared_ptr->ismilk==1) {
                    shared_ptr->ismilk=0;
                    sem_post(& shared_ptr->fw);

                    if(terminate_flag==1) {
                        break;
                    }                     
                }
                else if(shared_ptr->isflour==1) {
                    shared_ptr->isflour=0;
                    sem_post(& shared_ptr->mw);
                    if(terminate_flag==1) {
                        break;
                    } 
                }
                else if(shared_ptr->iswallnut==1) {
                    shared_ptr->iswallnut=0;
                    sem_post(& shared_ptr->fm);

                    if(terminate_flag==1) {
                        break;
                    } 
                }                
                else {
                    shared_ptr->issugar=1;
                    if(terminate_flag==1) {
                        break;
                    } 
                }
                if(terminate_flag==1) {
                    break;
                } 
                sem_post(& shared_ptr->m);
                if(terminate_flag==1) {
                    break;
                }                 
                break;

            case 3:

                sem_wait(& shared_ptr->wallnut);
                if(terminate_flag==1) {
                    break;
                }   

                sem_wait(& shared_ptr->m);
                if(terminate_flag==1) {
                    break;
                }   
                if(shared_ptr->issugar==1) {
                    shared_ptr->issugar=0;

                    sem_post(& shared_ptr->fm);
                    if(terminate_flag==1) {
                        break;
                    }                     
                }
                else if(shared_ptr->isflour==1) {
                    shared_ptr->isflour=0;
                    sem_post(& shared_ptr->sm);


                    if(terminate_flag==1) {
                        break;
                    } 
                }
                else if(shared_ptr->ismilk==1){
                    shared_ptr->ismilk=0;
                    sem_post(& shared_ptr->sf);
                    if(terminate_flag==1) {
                        break;
                    } 
                }
                else {
                    shared_ptr->iswallnut=1;
                    if(terminate_flag==1) {
                        break;
                    }                     
                }
                if(terminate_flag==1) {
                    break;
                } 

                sem_post(& shared_ptr->m);
                if(terminate_flag==1) {
                    break;
                }                 
                break;

            default:

                break;
        }
        if(terminate_flag==1) {
            break;
        }         
    }

    return 0;

}

void print_array() {
    fprintf(stdout,"%c%c\n",shared_ptr->queue[0],shared_ptr->queue[1]);
}

int chef(char endless_supply[2],char needed_supply[2],int chef_number) {
    
    int count_dessert=0;
    char ingredient1[MAX_BLKSIZE];
    memset(ingredient1,0,MAX_BLKSIZE);
    char ingredient2[MAX_BLKSIZE];
    memset(ingredient2,0,MAX_BLKSIZE);

    if(needed_supply[0]=='S') {
        strncpy(ingredient1,"sugar",strlen("sugar"));
    }
    if(needed_supply[0]=='F') {
        strncpy(ingredient1,"flour",strlen("flour"));
    }
    if(needed_supply[0]=='M') {
        strncpy(ingredient1,"milk",strlen("milk"));
    }
    if(needed_supply[0]=='W') {
        strncpy(ingredient1,"wallnut",strlen("wallnut"));
    }
    if(needed_supply[1]=='S') {
        strncpy(ingredient2,"sugar",strlen("sugar"));
    }
    if(needed_supply[1]=='F') {
        strncpy(ingredient2,"flour",strlen("flour"));
    }
    if(needed_supply[1]=='M') {
        strncpy(ingredient2,"milk",strlen("milk"));
    }
    if(needed_supply[1]=='W') {
        strncpy(ingredient2,"wallnut",strlen("wallnut"));
    }                     
                           
    while(terminate_flag==0) {
        fprintf(stdout,"chef%d (pid %d) is waiting for %s and %s => array:",chef_number,getpid(),ingredient1,ingredient2);
        print_array();

        if(terminate_flag==1) {
            break;
        }

        switch (chef_number)
        {
        case 0:

            //WS

            sem_wait(& shared_ptr->fm);
            if(terminate_flag==1) {
                break;
            }
            if(shared_ptr->queue[0]=='W') {
                shared_ptr->queue[0]='\0';
                fprintf(stdout,"chef%d (pid %d) has taken the %s => array:",chef_number,getpid(),ingredient1);
                print_array();

                shared_ptr->queue[1]='\0';
                fprintf(stdout,"chef%d (pid %d) has taken the %s => array:",chef_number,getpid(),ingredient2);  
                print_array();                                  
            }
            else {
                shared_ptr->queue[0]='\0';
                fprintf(stdout,"chef%d (pid %d) has taken the %s => array:",chef_number,getpid(),ingredient2);
                print_array();                     

                shared_ptr->queue[1]='\0';
                fprintf(stdout,"chef%d (pid %d) has taken the %s => array:",chef_number,getpid(),ingredient1);             
                print_array();                            

            }
        
            break;
        
        case 1:
            //WF
            sem_wait(& shared_ptr->sm);
            if(terminate_flag==1) {
                break;
            }

            if(shared_ptr->queue[0]=='W') {
                shared_ptr->queue[0]='\0';
                fprintf(stdout,"chef%d (pid %d) has taken the %s => array:",chef_number,getpid(),ingredient1);
                print_array();

                shared_ptr->queue[1]='\0';
                fprintf(stdout,"chef%d (pid %d) has taken the %s => array:",chef_number,getpid(),ingredient2);  
                print_array();                                  
            }
            else {
                shared_ptr->queue[0]='\0';
                fprintf(stdout,"chef%d (pid %d) has taken the %s => array:",chef_number,getpid(),ingredient2);
                print_array();                     

                shared_ptr->queue[1]='\0';
                fprintf(stdout,"chef%d (pid %d) has taken the %s => array:",chef_number,getpid(),ingredient1);             
                print_array();                            

            }
            break;

        case 2:
            //SF
            sem_wait(& shared_ptr->mw);
            
            if(terminate_flag==1) {
                break;
            }

            if(shared_ptr->queue[0]=='S') {
                shared_ptr->queue[0]='\0';
                fprintf(stdout,"chef%d (pid %d) has taken the %s => array:",chef_number,getpid(),ingredient1);
                print_array();

                shared_ptr->queue[1]='\0';
                fprintf(stdout,"chef%d (pid %d) has taken the %s => array:",chef_number,getpid(),ingredient2);  
                print_array();                                  
            }
            else {
                shared_ptr->queue[0]='\0';
                fprintf(stdout,"chef%d (pid %d) has taken the %s => array:",chef_number,getpid(),ingredient2);
                print_array();                     

                shared_ptr->queue[1]='\0';
                fprintf(stdout,"chef%d (pid %d) has taken the %s => array:",chef_number,getpid(),ingredient1);             
                print_array();                            

            }
            break;

        case 3:
            //FM
            sem_wait(& shared_ptr->sw);
            
            if(terminate_flag==1) {
                break;
            }

            if(shared_ptr->queue[0]=='F') {
                shared_ptr->queue[0]='\0';
                fprintf(stdout,"chef%d (pid %d) has taken the %s => array:",chef_number,getpid(),ingredient1);
                print_array();

                shared_ptr->queue[1]='\0';
                fprintf(stdout,"chef%d (pid %d) has taken the %s => array:",chef_number,getpid(),ingredient2);  
                print_array();                                  
            }
            else {
                shared_ptr->queue[0]='\0';
                fprintf(stdout,"chef%d (pid %d) has taken the %s => array:",chef_number,getpid(),ingredient2);
                print_array();                     

                shared_ptr->queue[1]='\0';
                fprintf(stdout,"chef%d (pid %d) has taken the %s => array:",chef_number,getpid(),ingredient1);             
                print_array();                            

            }
            break;

        case 4:
            //MW
            sem_wait(& shared_ptr->sf);
            
            if(terminate_flag==1) {
                break;
            }

            if(shared_ptr->queue[0]=='M') {
                shared_ptr->queue[0]='\0';
                fprintf(stdout,"chef%d (pid %d) has taken the %s => array:",chef_number,getpid(),ingredient1);
                print_array();

                shared_ptr->queue[1]='\0';
                fprintf(stdout,"chef%d (pid %d) has taken the %s => array:",chef_number,getpid(),ingredient2);  
                print_array();                                  
            }
            else {
                shared_ptr->queue[0]='\0';
                fprintf(stdout,"chef%d (pid %d) has taken the %s => array:",chef_number,getpid(),ingredient2);
                print_array();                     

                shared_ptr->queue[1]='\0';
                fprintf(stdout,"chef%d (pid %d) has taken the %s => array:",chef_number,getpid(),ingredient1);             
                print_array();                            

            }

            break;

        case 5:
            //MS
            sem_wait(& shared_ptr->fw);
            
            if(terminate_flag==1) {
                break;
            }

            if(shared_ptr->queue[0]=='M') {
                shared_ptr->queue[0]='\0';
                fprintf(stdout,"chef%d (pid %d) has taken the %s => array:",chef_number,getpid(),ingredient1);
                print_array();

                shared_ptr->queue[1]='\0';
                fprintf(stdout,"chef%d (pid %d) has taken the %s => array:",chef_number,getpid(),ingredient2);  
                print_array();                                  
            }
            else {
                shared_ptr->queue[0]='\0';
                fprintf(stdout,"chef%d (pid %d) has taken the %s => array:",chef_number,getpid(),ingredient2);
                print_array();                     

                shared_ptr->queue[1]='\0';
                fprintf(stdout,"chef%d (pid %d) has taken the %s => array:",chef_number,getpid(),ingredient1);             
                print_array();                            

            }

            break;

                        

        default:
            perror("In chef, switch caase error");
            break;
        }


        if(terminate_flag==1) {
            break;
        }
            

        fprintf(stdout,"chef%d (pid %d) is preparing the dessert => array:",chef_number,getpid());
        print_array();
        sem_post(& shared_ptr->agentSem);

        fprintf(stdout,"chef%d (pid %d) has delivered the desserts => array:",chef_number,getpid());
        print_array();        

        count_dessert++;
    }

    fprintf(stdout,"chef%d (pid %d) is exiting with desert %d => array:",chef_number,getpid(),count_dessert);
    print_array();

    return count_dessert;
}

int destroy_semaphore_for_child() {
    sem_destroy(& shared_ptr->agentSem);
    sem_destroy(& shared_ptr->sugar);
    sem_destroy(& shared_ptr->flour);
    sem_destroy(& shared_ptr->milk);
    sem_destroy(& shared_ptr->m);  
    sem_destroy(& shared_ptr->sf);  
    sem_destroy(& shared_ptr->sm);  
    sem_destroy(& shared_ptr->sw);  
    sem_destroy(& shared_ptr->fm);  
    sem_destroy(& shared_ptr->fw);  
    sem_destroy(& shared_ptr->mw);  

    return 0;
}
int destroy_semaphores() {
    sem_destroy(& shared_ptr->agentSem);
    sem_destroy(& shared_ptr->sugar);
    sem_destroy(& shared_ptr->flour);
    sem_destroy(& shared_ptr->milk);
    sem_destroy(& shared_ptr->m);    
    sem_destroy(& shared_ptr->sf);  
    sem_destroy(& shared_ptr->sm);  
    sem_destroy(& shared_ptr->sw);  
    sem_destroy(& shared_ptr->fm);  
    sem_destroy(& shared_ptr->fw);  
    sem_destroy(& shared_ptr->mw);     
    
    return 0;   
}

int destroy_shared_memory(int memory_fd) {
    close(memory_fd);
    return shm_unlink(MEMORY_NAME);
}

int wait_for_child(int childpid) {
    int status=0;
    if(waitpid(childpid,&status,0)==-1) {
        perror("Error waiting child");
        return -1;
    }
    int return_value = WEXITSTATUS(status);    
    return return_value;
}

int send_terminate_signal_to_the_child(int childpid) {
    if(kill(childpid,SIGUSR1)==-1) {
        perror("Error send sigusr1 signal to the child");
        return -1;
    }
    return 0;
}

int increment_ingredients(char needed_supply[2]) {

    char ingredient1[MAX_BLKSIZE];
    memset(ingredient1,0,MAX_BLKSIZE);
    char ingredient2[MAX_BLKSIZE];
    memset(ingredient2,0,MAX_BLKSIZE);

    if(needed_supply[0]=='S') {
        strncpy(ingredient1,"sugar",strlen("sugar"));
    }
    if(needed_supply[0]=='F') {
        strncpy(ingredient1,"flour",strlen("flour"));
    }
    if(needed_supply[0]=='M') {
        strncpy(ingredient1,"milk",strlen("milk"));
    }
    if(needed_supply[0]=='W') {
        strncpy(ingredient1,"wallnut",strlen("wallnut"));
    }
    if(needed_supply[1]=='S') {
        strncpy(ingredient2,"sugar",strlen("sugar"));
    }
    if(needed_supply[1]=='F') {
        strncpy(ingredient2,"flour",strlen("flour"));
    }
    if(needed_supply[1]=='M') {
        strncpy(ingredient2,"milk",strlen("milk"));
    }
    if(needed_supply[1]=='W') {
        strncpy(ingredient2,"wallnut",strlen("wallnut"));
    }                     
                          

    fprintf(stdout,"the wholesaler (pid %d) delivers %s and %s\n",getpid(),ingredient1,ingredient2);

    /*
    0=>ws
    1=>fw
    2=>sf
    3=>mf
    4=>mw
    5=>sm
    */

    if((needed_supply[0]=='W' && needed_supply[1]=='S') || (needed_supply[1]=='W' && needed_supply[0]=='S')) {
        sem_post(&shared_ptr->wallnut);
        sem_post(&shared_ptr->sugar);
    }
    else if((needed_supply[0]=='F' && needed_supply[1]=='W') || (needed_supply[1]=='F' && needed_supply[0]=='W')) {
        sem_post(&shared_ptr->wallnut);
        sem_post(&shared_ptr->flour);
    }
    else if((needed_supply[0]=='S' && needed_supply[1]=='F') || ((needed_supply[1]=='S' && needed_supply[0]=='F'))) {
        sem_post(&shared_ptr->sugar);
        sem_post(&shared_ptr->flour);        
    }
    else if((needed_supply[0]=='M' && needed_supply[1]=='F') || ((needed_supply[1]=='M' && needed_supply[0]=='F'))) {
        sem_post(&shared_ptr->flour);
        sem_post(&shared_ptr->milk);
    }
    else if((needed_supply[0]=='M' && needed_supply[1]=='W') || ((needed_supply[1]=='M' && needed_supply[0]=='W'))) {
        sem_post(&shared_ptr->wallnut);
        sem_post(&shared_ptr->milk);       
    }
    else if((needed_supply[0]=='S' && needed_supply[1]=='M') || (needed_supply[1]=='S' && needed_supply[0]=='M')) {
        sem_post(&shared_ptr->sugar);
        sem_post(&shared_ptr->milk);
    }

    fprintf(stdout,"the wholesaler (pid %d) is waiting for the dessert\n",getpid());

    sem_post(& shared_ptr->m);

    sem_wait(& shared_ptr->agentSem);

    fprintf(stdout,"the wholesaler (pid %d) has obtained the dessert and left\n",getppid());

    return 0;
}
