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

#include "named_header.h"

shared_memory* shared_ptr=NULL;
sem_t* agentSem;
sem_t* sugar;
sem_t* flour;
sem_t* milk;
sem_t* wallnut;
sem_t* m;
sem_t* sf;
sem_t* sm;
sem_t* sw;
sem_t* fm;
sem_t* fw;
sem_t* mw;
int number_of_desserts; 
int terminate_flag=0;


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
int destroy_semaphore_for_child() {

    if(sem_close(agentSem)==-1) {
        perror("Error closing agentsem semaphore");
        return -1;
    }
    if(sem_close(sugar)==-1) {
        perror("Error closing sugar semaphore");
        return -1;
    }
    if(sem_close(flour)==-1) {
        perror("Error closing flour semaphore");
        return -1;        
    }
    if(sem_close(wallnut)==-1) {
        perror("Error closing wallnut semaphore");
        return -1;        
    }
    if(sem_close(milk)==-1) {
        perror("Error closing milk semaphore");
        return -1;        
    }  
    if(sem_close(m)==-1) {
        perror("Error closing m semaphore");
        return -1;
    }
    if(sem_close(sf)==-1) {
        perror("Error closing sf semaphore");
        return -1;
    }
    if(sem_close(sw)==-1) {
        perror("Error closing sw semaphore");
        return -1;
    }
    if(sem_close(fm)==-1) {
        perror("Error closing fm semaphore");
        return -1;
    }
    if(sem_close(fw)==-1) {
        perror("Error closing fw semaphore");
        return -1;
    }
    if(sem_close(mw)==-1) {
        perror("Error closing mw semaphore");
        return -1;
    }
    if(sem_close(sm)==-1) {
        perror("Error closing sm semaphore");
        return -1;
    }                            
    return 0;
}
int pusher(int pusherindex) {

    while(terminate_flag==0) {
        switch (pusherindex)
        {
            case 0:
                if(sem_wait(milk)==-1) {
                    return -1;
                }
                if(terminate_flag==1) {
                    break;
                }  
                sem_wait(m);
                if(terminate_flag==1) {
                    break;
                }     
                if(shared_ptr->issugar==1) {
                    shared_ptr->issugar=0;
                    sem_post(fw);
                  
                    if(terminate_flag==1) {
                        break;
                    }                         
                }
                else if(shared_ptr->isflour==1) {
                    shared_ptr->isflour=0;
                    sem_post(sw);                   
                    
                    if(terminate_flag==1) {
                        break;
                    } 
                }
                else if(shared_ptr->iswallnut==1) {
                    shared_ptr->iswallnut=0;
                    sem_post(sf);

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

                sem_post(m);
                
                if(terminate_flag==1) {
                    break;
                }                 
                break;
            
            case 1:

                sem_wait(flour);
                if(terminate_flag==1) {
                    break;
                } 
                sem_wait(m);
                if(terminate_flag==1) {
                    break;
                } 
                if(shared_ptr->issugar==1) {
                    shared_ptr->issugar=0;
                    sem_post(mw);
                   
                    if(terminate_flag==1) {
                        break;
                    }                     
                }
                else if(shared_ptr->ismilk==1) {
                    shared_ptr->ismilk=0;
                    sem_post(sw);
                

                    if(terminate_flag==1) {
                        break;
                    }  
                }
                else if(shared_ptr->iswallnut==1) {
                    shared_ptr->iswallnut=0;
                    sem_post(sm);
                
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
                sem_post(m);
                if(terminate_flag==1) {
                    break;
                }                  
                break;

            case 2:

                sem_wait(sugar);
                if(terminate_flag==1) {
                    break;
                }   

                sem_wait(m);
                if(terminate_flag==1) {
                    break;
                }   
                if(shared_ptr->ismilk==1) {
                    shared_ptr->ismilk=0;
                    sem_post(fw);
                  
                    if(terminate_flag==1) {
                        break;
                    }                     
                }
                else if(shared_ptr->isflour==1) {
                    shared_ptr->isflour=0;
                    sem_post(mw);

                    if(terminate_flag==1) {
                        break;
                    } 
                }
                else if(shared_ptr->iswallnut==1) {
                    shared_ptr->iswallnut=0;
                    sem_post(fm);

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

                sem_post(m);
                if(terminate_flag==1) {
                    break;
                }                 
                break;

            case 3:

                sem_wait(wallnut);
                if(terminate_flag==1) {
                    break;
                }   

                sem_wait(m);
                if(terminate_flag==1) {
                    break;
                }   
                if(shared_ptr->issugar==1) {
                    shared_ptr->issugar=0;

                    sem_post(fm);                    

                    if(terminate_flag==1) {
                        break;
                    }                     
                }
                else if(shared_ptr->isflour==1) {
                    shared_ptr->isflour=0;
                    sem_post(sm);

                    if(terminate_flag==1) {
                        break;
                    } 
                }
                else if(shared_ptr->ismilk==1){
                    shared_ptr->ismilk=0;
                    sem_post(sf);

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

                sem_post(m);
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

int chef(char endless_supply[ENDLESS_SUPPLY],char needed_supply[TOTAL_INGREDIENTS-ENDLESS_SUPPLY],int chef_number) {
    
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
            sem_wait(fm);
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
            sem_wait(sm);
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
            sem_wait(mw);
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
            sem_wait(sw);
            
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
            sem_wait(sf);
            
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
            sem_wait(fw);
            
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
        sem_post(agentSem);

        fprintf(stdout,"chef%d (pid %d) has delivered the desserts => array:",chef_number,getpid());
        print_array();        

        count_dessert++;
    }

    fprintf(stdout,"chef%d (pid %d) is exiting with desert %d => array:",chef_number,getpid(),count_dessert);
    print_array();
    return count_dessert;
}
int increment_ingredients(char needed_supply[TOTAL_INGREDIENTS-ENDLESS_SUPPLY]) {

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
        sem_post(wallnut);
        sem_post(sugar);

    }
    else if((needed_supply[0]=='F' && needed_supply[1]=='W') || (needed_supply[1]=='F' && needed_supply[0]=='W')) {
        sem_post(wallnut);
        sem_post(flour);

    }
    else if((needed_supply[0]=='S' && needed_supply[1]=='F') || ((needed_supply[1]=='S' && needed_supply[0]=='F'))) {
        sem_post(sugar);
        sem_post(flour);
        
    }
    else if((needed_supply[0]=='M' && needed_supply[1]=='F') || ((needed_supply[1]=='M' && needed_supply[0]=='F'))) {
        sem_post(flour);
        sem_post(milk);

    }
    else if((needed_supply[0]=='M' && needed_supply[1]=='W') || ((needed_supply[1]=='M' && needed_supply[0]=='W'))) {
        sem_post(wallnut);
        sem_post(milk);
        
    }
    else if((needed_supply[0]=='S' && needed_supply[1]=='M') || (needed_supply[1]=='S' && needed_supply[0]=='M')) {
        sem_post(sugar);
        sem_post(milk);

    }
    fprintf(stdout,"the wholesaler (pid %d) is waiting for the dessert\n",getpid());

    sem_post(m);

    sem_wait(agentSem);

    fprintf(stdout,"the wholesaler (pid %d) has obtained the dessert and left\n",getppid());

    return 0;
}
int check_arguments(int argc, char const *argv[]) {
    int i=0;

    if(argc!=5) {
        return -1;
    }

    int input_file_ok=0;
    int name_ok=0;

    for(i=1;i<argc;i++) {
        if(argv[i][0]=='-' && argv[i][1]=='i' && i!=(argc-1)) {
            input_file_ok=1;
        }
        else if(argv[i][0]=='-' && argv[i][1]=='n') {
            name_ok=1;
        }                    
    } 
    if(input_file_ok==1 && name_ok==1) {
        return 0;
    }
    return -1;
}

int create_shared_memory(int* fd,size_t size,char semaphore_name[MAX_BLKSIZE]) {


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

    sem_unlink("sugarname");
    sem_unlink("flourname");
    sem_unlink("wallnutname");
    sem_unlink("milkname");
    sem_unlink("m");
    sem_unlink("sf");
    sem_unlink("mw");
    sem_unlink(semaphore_name);
    sem_unlink("sm");
    sem_unlink("sw");
    sem_unlink("fw");
    sem_unlink("fm");


    sugar=sem_open("sugarname",O_CREAT | O_EXCL,0777,0);
    if(errno==EEXIST) {

        fprintf(stdout,"sugarname already exists\n");
        return -1;
    }
    else if(sugar==SEM_FAILED) {
        perror("Error opening semaphore sugar");
        return -1;
    }
    flour=sem_open("flourname",O_CREAT | O_EXCL,0777,0);
    if(errno==EEXIST) {

        fprintf(stdout,"flourname already exists\n");
        return -1;        

    }
    else if(flour==SEM_FAILED) {
        perror("Error opening semaphore flour");
        return -1;    
    }
    wallnut=sem_open("wallnutname",O_CREAT | O_EXCL,0777,0);
    if(errno==EEXIST) {

        fprintf(stdout,"wallnutname already exists\n");
        return -1;
    }
    else if(wallnut==SEM_FAILED) {
        perror("Error opening semaphore wallnut");
        return -1;
    }
    milk=sem_open("milkname",O_CREAT | O_EXCL,0777,0);
    if(errno==EEXIST) {

        fprintf(stdout,"milkname already exists\n");
        return -1;
    }
    else if(milk==SEM_FAILED) {
        perror("Error opening semaphore milk");
        return -1;
    }
    agentSem=sem_open(semaphore_name,O_CREAT | O_EXCL,0777,0);
    if(errno==EEXIST) {

        fprintf(stdout,"%s already exists\n",semaphore_name);
        return -1;
    }
    else if(agentSem==SEM_FAILED) {
        perror("Error opening semaphore agentsem");
        return -1;
    }
    m=sem_open("m",O_CREAT | O_EXCL,0777,0);
    if(errno==EEXIST) {

        fprintf(stdout,"m already exists\n");
        return -1;
    }
    else if(m==SEM_FAILED) {
        perror("Error opening semaphore m");
        return -1;
    }
    sf=sem_open("sf",O_CREAT | O_EXCL,0777,0);
    if(errno==EEXIST) {

        fprintf(stdout,"sf already exists\n");
        return -1;
    }
    else if(sf==SEM_FAILED) {
        perror("Error opening semaphore sf");
        return -1;
    }
    sm=sem_open("sm",O_CREAT | O_EXCL,0777,0);
    if(errno==EEXIST) {

        fprintf(stdout,"agentsem already exists\n");
        return -1;
    }
    else if(sm==SEM_FAILED) {
        perror("Error opening semaphore sm");
        return -1;
    }
    sw=sem_open("sw",O_CREAT | O_EXCL,0777,0);
    if(errno==EEXIST) {

        fprintf(stdout,"sw already exists\n");
        return -1;
    }
    else if(sw==SEM_FAILED) {
        perror("Error opening semaphore sw");
        return -1;
    }
 
    fm=sem_open("fm",O_CREAT | O_EXCL,0777,0);
    if(errno==EEXIST) {

        fprintf(stdout,"fm already exists\n");
        return -1;
    }
    else if(fm==SEM_FAILED) {
        perror("Error opening semaphore fm");
        return -1;
    }
    fw=sem_open("fw",O_CREAT | O_EXCL,0777,0);
    if(errno==EEXIST) {

        fprintf(stdout,"fw already exists\n");
        return -1;
    }
    else if(fw==SEM_FAILED) {
        perror("Error opening semaphore fw");
        return -1;
    }
    mw=sem_open("mw",O_CREAT | O_EXCL,0777,0);
    if(errno==EEXIST) {

        fprintf(stdout,"mw already exists\n");
        return -1;
    }
    else if(mw==SEM_FAILED) {
        perror("Error opening semaphore mw");
        return -1;
    }

    memset(shared_ptr->queue,0,(2)*sizeof(char));
    return 0;
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

int destroy_semaphores(char semaphore_name[MAX_BLKSIZE]) {

    if(sem_close(sugar)==-1 || sem_unlink("sugarname")==-1) {
        perror("Error closing sugar semaphore");
        return -1;
    }
    if(sem_close(flour)==-1 || sem_unlink("flourname")==-1 ) {
        perror("Error closing flour semaphore");
        return -1;        
    }
    if(sem_close(wallnut)==-1 || sem_unlink("wallnutname")==-1 ) {
        perror("Error closing wallnut semaphore");
        return -1;        
    }
    if(sem_close(milk)==-1 || sem_unlink("milkname")==-1) {
        perror("Error closing milk semaphore");
        return -1;        
    }  

    if(sem_close(agentSem)==-1 || sem_unlink(semaphore_name)==-1) {
        perror("Error closing agentsem semaphore");
        return -1;
    }
    if(sem_close(m)==-1 || sem_unlink("m")==-1) {
        perror("Error closing m semaphore");
        return -1;        
    }
    if(sem_close(sf)==-1 || sem_unlink("sf")==-1) {
        perror("Error closing sf semaphore");
        return -1;        
    }
    if(sem_close(sw)==-1 || sem_unlink("sw")==-1) {
        perror("Error closing sw semaphore");
        return -1;        
    }
    if(sem_close(fm)==-1 || sem_unlink("fm")==-1) {
        perror("Error closing fm semaphore");
        return -1;        
    }
    if(sem_close(fw)==-1 || sem_unlink("fw")==-1) {
        perror("Error closing fw semaphore");
        return -1;        
    }
    if(sem_close(mw)==-1 || sem_unlink("mw")==-1) {
        perror("Error closing mw semaphore");
        return -1;        
    }
    if(sem_close(sm)==-1 || sem_unlink("sm")==-1) {
        perror("Error closing sm semaphore");
        return -1;        
    }
    return 0;
}

int destroy_shared_memory(int memory_fd) {
    close(memory_fd);
    return shm_unlink(MEMORY_NAME);
}
