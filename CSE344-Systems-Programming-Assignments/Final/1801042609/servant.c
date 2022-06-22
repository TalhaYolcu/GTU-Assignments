#include <stdio.h>
#include "servant_implementation.c"
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
#include <dirent.h>
#include <sys/procfs.h>
#include <sys/signal.h>
#include <sys/syscall.h>
#include <sys/param.h>
#include <sys/socket.h>
#include <arpa/inet.h>

//1-9 arası 0 dan mı başlayacak yoksa 1 den mi başlayacak

int main(int argc, char const *argv[])
{
    //./servant -d directoryPath -c 10-19 -r IP -p PORT
    if(check_input_validity(argc,argv)!=0) {
        perror("Error, there is a problem with arguemnts");
        fprintf(stdout,"Usage:./servant -d directoryPath -c 10-19 -r IP -p PORT\n");
        return 0;
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


    char directory_path[FILE_NAME_LEN];
    char interval_char[FILE_NAME_LEN];
    char ip_address[FILE_NAME_LEN];
    char port_char[FILE_NAME_LEN];

    int stat_fd=open("/proc/self/stat",(O_RDONLY),0777);
    if(stat_fd==-1) {
        perror("Error on open statfd");
        return 0;
    }
    int pid=0;

    char buffer[MAX_BLKSIZE];
    memset(buffer,0,MAX_BLKSIZE);

    if(read(stat_fd,buffer,MAX_BLKSIZE)==-1) {
        perror("Error on read");
        return 0;
    }
    char*buf=buffer;
    char* pid_char=strtok_r(buf," ",&buf);
    pid=atoi(pid_char);

    close(stat_fd);
    //printf("%d\n",pid);

    memset(directory_path,0,FILE_NAME_LEN);
    memset(interval_char,0,FILE_NAME_LEN);
    memset(ip_address,0,FILE_NAME_LEN);
    memset(port_char,0,FILE_NAME_LEN);

    for(int i=1;i<argc;i++) {
        //directory path
        if(argv[i][0]=='-' && argv[i][1]=='d') {
            strcpy(directory_path,argv[i+1]);
        }   
        //interval
        else if(argv[i][0]=='-' && argv[i][1]=='c')  {
            strcpy(interval_char,argv[i+1]);
        }  
        //ip address 
        else if(argv[i][0]=='-' && argv[i][1]=='r')  {
            strcpy(ip_address,argv[i+1]);
        }  
        //port number
        else if(argv[i][0]=='-' && argv[i][1]=='p')  {
            strcpy(port_char,argv[i+1]);
        }          
    } 

    int interval_low=0;
    int interval_high=0;

    char*buf2=interval_char;


    char* interval_low_char=strtok_r(buf2,"-",&buf2);
    interval_low=atoi(interval_low_char)-1;

    interval_high=atoi(buf2)-1;

    int port_number=atoi(port_char);

    //printf("Directory path:%s\nInterval:%d-%d\nIP address:%s\nPort number:%d\n",directory_path,interval_low,interval_high,ip_address,port_number);

    scan_directories(directory_path);

    my_servant.number_of_city=interval_high-interval_low+1;
    my_servant.start_index=interval_low;
    my_servant.end_index=interval_high;
    my_servant.port_number=port_number;
    my_servant.cities=(city*)malloc(sizeof(city)*my_servant.number_of_city);
    memset(my_servant.cities,0,my_servant.number_of_city);

    //printf("-----\n");
    for(int i=interval_low;i<=interval_high;i++) {
        my_servant.cities[i-interval_low].city_name=(char*)malloc(sizeof(char)*FILE_NAME_LEN);
        memset(my_servant.cities[i-interval_low].city_name,0,FILE_NAME_LEN);
        strcpy(my_servant.cities[i-interval_low].city_name,namelist[i]->d_name);
        scan_city_directory(namelist[i]->d_name,directory_path,i,interval_low);
    }


    fprintf(stdout,"Servant %d: loaded dataset, cities %s-%s\n",pid,my_servant.cities[0].city_name,my_servant.cities[my_servant.number_of_city-1].city_name);

    for(int i=0;i<my_servant.number_of_city;i++){
        for(int k=0;k<my_servant.cities[i].number_of_file;k++) {
            for(int j=0;j<my_servant.cities[i].files[k].number_of_entry;j++) {
                root=insert(root,&my_servant.cities[i].files[k].entries[j]);
            }
        }
    }

    if(terminate_flag==1) {
        free_resources();
        free_tree(root);
        free(root);
        return 0;
    }

    int servant_port_number=start_port_number+(int)((interval_low+interval_high)/2);

    //inorder(root);

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if(sock<0) {
        perror("Error on socket");
        free_resources();
        free_tree(root);
        free(root);
        return 0;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port_number);

    if(inet_pton(AF_INET,ip_address,&serv_addr.sin_addr)<0) {
        perror("Error on inet pton");
        free_resources();
        close(sock);
        free_tree(root);
        free(root);
        return 0;
    }    

    // Sunucuya bağlanma
    client_fd=connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if(client_fd< 0 ){
        perror("Error on connect");
        free_resources();
        close(sock);
        free_tree(root);
        free(root);
        return 0;
    }

    char* msg=(char*)malloc(sizeof(char)*512);
    memset(msg,0,512);
    sprintf(msg,"SERVANT %d %d %s %s %s",pid,servant_port_number,ip_address,my_servant.cities[0].city_name,my_servant.cities[my_servant.number_of_city-1].city_name);
    printf("Servant sent:%s\n",msg);
    if(send(sock,(const char*)msg,512,0)<0) {
        perror("Error on send");
        free_resources();
        free(msg);
        close(sock);
        free_tree(root);
        free(root);
        return 0;
    }
    free(msg);
    close(sock);

    struct sockaddr_in address;
    int addrlen=sizeof(address);
    memset(&address,0,sizeof(address));

    address.sin_family=AF_INET;
    address.sin_port=htons(servant_port_number);

    if(inet_pton(AF_INET,ip_address,&address.sin_addr)<0) {
        perror("Error on inet pton");
        free_resources();
        free_tree(root);
        free(root);
        return 0;
    }

    server_fd=socket(AF_INET,SOCK_STREAM,0);

    if(server_fd<0) {
        perror("Error to get-connect");
        free_resources();
        free_tree(root);
        free(root);
        return 0;
    }

    if(bind(server_fd,(struct sockaddr*)&address,(socklen_t)addrlen)<0) {
        perror("Error on bind");
        close(server_fd);
        free_tree(root);
        free(root);
        free_resources();
        return 0;
    }

    if(listen(server_fd,512)<0) {
        perror("Error on listen");
        close(server_fd);
        free_resources();
        free_tree(root);
        free(root);
        return 0;
    }

    fprintf(stdout,"Servant %d: listening at port %d\n",pid,servant_port_number);

    int accept_fds[512];
    memset(accept_fds,-1,512*sizeof(int));
    int accept_fds_counter=0;
    while(1) {
        int new_socket=accept(server_fd,(struct sockaddr*)&address,(socklen_t*)&addrlen);
        if(terminate_flag==1) {
            break;
        }
        if(new_socket<0) {
            perror("Error on accept");
            break;
        }
        pthread_t thread;
        int*index=(int*)malloc(sizeof(int));
        *index=new_socket;
        accept_fds[accept_fds_counter++]=*index;
        
        if(pthread_create(&thread,NULL,run_thread,(void*)index)!=0) {
            perror("Error on pthread create");
            break;
        }
        pthread_detach(thread);
        if(terminate_flag==1) {
            break;
        }        

    }
    fprintf(stdout,"Servant %d: termination message received, handled %d requests in total.\n",pid,handled_request);

    /*for(int i=0;i<accept_fds_counter;i++) {
        close(accept_fds[i]);
    }*/

    free_resources();
    free_tree(root);
    free(root);
    close(server_fd);

    return 0;
}
