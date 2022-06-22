#include <stdio.h>
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
#include "structs.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <limits.h>

int sock=0;
int client_fd=0;
int number_of_threads=0;        //number of threads
char port_number_char[FILE_NAME_LEN];   //port number of socket
sig_atomic_t terminate_flag=0;          //sigint flag
struct dirent** namelist;
int number_of_subdir=0;
servant my_servant;
int start_port_number=16000;
int server_fd=0;
struct node* root=NULL;
int handled_request=0;

int check_input_validity(int argc,char const *argv[]);
void* run_thread(void*arg);
void handler(int signal_number);
int comp(const void*e1,const void* e2);
void scan_directories(char* directory_path);

void take_date(char*date1,int*d,int*m,int*y) {
    char buf[20];
    memset(buf,0,20);

    strcpy(buf,date1);
    char*remained;
    char*tok=strtok_r(buf,"-",&remained);
    *d=atoi(tok);
    
    char*remained2;
    char*tok2=strtok_r(remained,"-",&remained2);
    *m=atoi(tok2);

    *y=atoi(remained2);
}


int compare_dates(char*date1,char*date2) {
    int y1,m1,d1;
    int y2,m2,d2;
    
    take_date(date1,&d1,&m1,&y1);
    take_date(date2,&d2,&m2,&y2);

    if(y1==y2) {
        if(m1==m2) {
            if(d1==d2) {
                //printf("%s and %s are same\n",date1,date2);
                return 0;
            }
            else if(d1>d2) {
                //printf("%s is later than %s",date1,date2);
                return 1;
            }
            else {
                //printf("%s is earlier than %s",date1,date2);
                return -1;
                
            }
        }
        else if(m1>m2) {
            //printf("%s is later than %s",date1,date2);
            return 1;
        }
        else {
           //printf("%s is earlier than %s",date1,date2); 
           return -1;
        }
    }
    else if(y1>y2) {
        //printf("%s is later than %s",date1,date2);
        return 1;
    }
    else {
        //printf("%s is earlier than %s",date1,date2); 
        return -1;
    }
        
}

// A utility function to create a new BST node
struct node* newNode(file_entry* item)
{
    struct node* temp
        = (struct node*)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}
 
// A utility function to do inorder traversal of BST
void inorder(struct node* root)
{
    if (root != NULL) {
        inorder(root->left);
        printf("%s \n", root->key->date);
        inorder(root->right);
    }
}
 
/* A utility function to insert
   a new node with given key in
 * BST */
struct node* insert(struct node* node, file_entry* key)
{
    /* If the tree is empty, return a new node */
    if (node == NULL)
        return newNode(key);
 
    
    /* Otherwise, recur down the tree */
    if (compare_dates(node->key->date,key->date)<=0)
        node->left = insert(node->left, key);
    else if (compare_dates(node->key->date,key->date)>0)
        node->right = insert(node->right, key);
 
    /* return the (unchanged) node pointer */
    return node;
}


//signal handler, if it receives a sigint, sets flag to 1
void handler(int signal_number) {
    if(signal_number==SIGINT) {
        terminate_flag=1;
    }
}


int check_input_validity(int argc,char const *argv[]) {
    
    //./servant -d directoryPath -c 10-19 -r IP -p PORT
    
    if(argc!=9) {
        return -1;
    }

    int port_ok=0;
    int directory_path_ok=0;
    int interval_ok=0;
    int ip_address_ok=0;

    for(int i=1;i<argc;i++) {
        //port
        if(argv[i][0]=='-' && argv[i][1]=='d') {
            directory_path_ok=1;
        }   
        //interval
        else if(argv[i][0]=='-' && argv[i][1]=='c')  {
            interval_ok=1;
        }   
        //ip address
        else if(argv[i][0]=='-' && argv[i][1]=='r')  {
            ip_address_ok=1;
        }  
        //port number
        else if(argv[i][0]=='-' && argv[i][1]=='p')  {
            port_ok=1;
        }          
    } 
    if(port_ok==1 && directory_path_ok==1 && interval_ok==1 && ip_address_ok==1) {
        return 0;
    }
    return -1;  
}




int find_with_city(struct node* node,char*t_type,char* date1,char*date2,char*city) {
    int result=0;
    if(terminate_flag==1) {
        return 0;
    }
    if(node==NULL) {
        return 0;
    }

    if(strcmp(city,node->key->city_name)!=0) {
        result+=find_with_city(node->left,t_type,date1,date2,city);
        if(terminate_flag==1) {
            return 0;
        }
        result+=find_with_city(node->right,t_type,date1,date2,city);
        if(terminate_flag==1) {
            return 0;
        }
    }
    else {
        //if date1 > .date => 1 else 0
        int comp_result_left=compare_dates(node->key->date,date1);
        
        //if .date > date2 => 1 else 0
        int comp_result_right=compare_dates(date2,node->key->date);


        if(comp_result_left>=0 && comp_result_right>=0) {
            if(strcmp(t_type,node->key->type_real_estate)==0) {
                result++;
            }
        }
        result+=find_with_city(node->left,t_type,date1,date2,city);
        if(terminate_flag==1) {
            return 0;
        }
        result+=find_with_city(node->right,t_type,date1,date2,city);
        if(terminate_flag==1) {
            return 0;
        }
    }
    return result;    
}

int find_without_city(struct node* node,char*t_type,char* date1,char*date2) {
    
    int result=0;
    if(terminate_flag==1) {
        return 0;
    }
    if(node==NULL) {
        return 0;
    }

    //if date1 > .date => 1 else 0
    int comp_result_left=compare_dates(node->key->date,date1);
    
    //if .date > date2 => 1 else 0
    int comp_result_right=compare_dates(date2,node->key->date);

    if(comp_result_left>=0 && comp_result_right>=0) {
        if(strcmp(t_type,node->key->type_real_estate)==0) {
            result++;
        }
    }
    result+=find_without_city(node->left,t_type,date1,date2);
    if(terminate_flag==1) {
        return 0;
    }
    result+=find_without_city(node->right,t_type,date1,date2);
    if(terminate_flag==1) {
        return 0;
    }
    return result;
}

void* run_thread(void*arg) {
    int thread_index=*(int*)arg;
    free(arg);


    //printf("This is thread number %d\n",thread_index);

    char* alinan_veri=(char*)malloc(sizeof(char)*512);
    memset(alinan_veri,0,512);

    int veri_boyutu = recv(thread_index, alinan_veri, 512, 0);
    if(terminate_flag==1) {
        //close(thread_index);
        return NULL;
    }
    if(veri_boyutu < 0){
        perror("Error on receive");
        //close(thread_index);
        return NULL;
    }
    if(alinan_veri==NULL) {
        //close(thread_index);
        return NULL;
    }
    if(strlen(alinan_veri)==0)  {
        //close(thread_index);
        free(alinan_veri);
        return NULL;
    }
    //fprintf(stdout, "Received data: %s\n", alinan_veri);

    char* my_buf=(char*)malloc(sizeof(char)*512);
    memset(my_buf,0,512);

    strncpy(my_buf,alinan_veri,512);

    char*buf=my_buf;


    char* nulls=strtok_r(buf," ",&buf);
    nulls[0]='\0';
    char* transaction_type=strtok_r(buf," ",&buf);
    char* date1=strtok_r(buf," ",&buf);
    char* date2=strtok_r(buf," ",&buf);
    char* city=strtok_r(buf," ",&buf);
    int result=0;

    if(terminate_flag==1) {
        //close(thread_index);
        free(alinan_veri);
        free(my_buf);
        return NULL;
    }
    //search
    if(city==NULL) {
        result=find_without_city(root,transaction_type,date1,date2);
    }
    else {
        result=find_with_city(root,transaction_type,date1,date2,city);
    }


    if(terminate_flag==1) {
        //close(thread_index);
        free(alinan_veri);
        free(my_buf);

        return NULL;
    }


    char* response=(char*)malloc(sizeof(char)*512);
    memset(response,0,512);

    snprintf(response,512,"%d",result);
    if(send(thread_index,response,512,0)<0) {
        perror("Error on send");
        free(my_buf);

        free(response);
        free(alinan_veri);
        //close(thread_index);
        return NULL;
    }
    handled_request++;


    if(terminate_flag==1) {
        free(my_buf);

        free(response);
        free(alinan_veri);
        //close(thread_index);
        return NULL;
    }       
    //send response
    free(my_buf);

    close(thread_index);
    free(response);
    free(alinan_veri);

    return NULL;
}

int comp(const void*e1,const void* e2) {

    struct dirent* const name1=*(struct dirent**)e1;
    struct dirent* const name2=*(struct dirent**)e2;


    int result = strcmp(name1->d_name,name2->d_name);
    return result;    

}

void scan_directories(char* directory_path) {
    DIR*dirp=opendir(directory_path);
    while(dirp) {
        errno=0;
        struct dirent* dp;
        if((dp=readdir(dirp))!=NULL) {
            //printf("%s\n",dp->d_name);
            number_of_subdir++;
        }
        else {
            break;
        }
    }
    seekdir(dirp,0);
    number_of_subdir-=2;
    
    namelist=(struct dirent**)malloc(number_of_subdir*sizeof(struct dirent*));
    for(int i=0;i<number_of_subdir;i++) {
        namelist[i]=(struct dirent*)malloc(sizeof(struct dirent));
        memset(namelist[i],0,sizeof(struct dirent));
    }
    int subdir_counter=0;

    for(int i=0;i<number_of_subdir+2;i++) {
        struct dirent* dp=readdir(dirp);
        if(strcmp(dp->d_name,"..")==0 || strcmp(dp->d_name,".")==0) {}
        else {
            strcpy(namelist[subdir_counter]->d_name,dp->d_name);
            namelist[subdir_counter]->d_type=dp->d_type;
            subdir_counter++; 
        }    
    }
    closedir(dirp);
    qsort(namelist,number_of_subdir,sizeof(struct dirent*),comp);
    
}

void read_until_newline(int fd,char*buffer) {
    int read_byte=0;
    char read_char='\0';
    int buffer_counter=0;
    while(1) {
        read_byte=read(fd,&read_char,1);
        if(read_byte==-1) {
            perror("Error on read");
            return;
        }
        if(read_byte==0) {
            break;
        }
        if(read_char=='\n') {
            break;
        }
        buffer[buffer_counter++]=read_char;
    }
}

void read_date_file(char*path,int city_index,int file_index) {
    int date_fd=open(path,(O_RDONLY),0777);
    if(date_fd==-1) {
        perror("Error opening date file");
        return;
    }
    int read_byte=0;
    char read_char='\0';
    int file_entry_counter=0;
    while(1) {
        read_byte=read(date_fd,&read_char,1);
        if(read_byte==-1) {
            perror("Error read date file");
            return;
        }
        if(read_byte==0) {
            break;
        }
        if(read_char=='\n') {
            file_entry_counter++;
        }
    }
    close(date_fd);
    my_servant.cities[city_index].files[file_index].entries=(file_entry*)malloc(sizeof(file_entry)*file_entry_counter);
    memset(my_servant.cities[city_index].files[file_index].entries,0,file_entry_counter*sizeof(file_entry));
    my_servant.cities[city_index].files[file_index].number_of_entry=file_entry_counter;

    
    date_fd=open(path,(O_RDONLY),0777);
    if(date_fd==-1) {
        perror("Error opening date file");
        return;
    }

    for(int i=0;i<file_entry_counter;i++) {

        my_servant.cities[city_index].files[file_index].entries[i].name_of_street=(char*)malloc(sizeof(char)*FILE_NAME_LEN);
        memset(my_servant.cities[city_index].files[file_index].entries[i].name_of_street,0,FILE_NAME_LEN);

        my_servant.cities[city_index].files[file_index].entries[i].type_real_estate=(char*)malloc(sizeof(char)*FILE_NAME_LEN);
        memset(my_servant.cities[city_index].files[file_index].entries[i].type_real_estate,0,FILE_NAME_LEN);

        my_servant.cities[city_index].files[file_index].entries[i].city_name=(char*)malloc(sizeof(char)*FILE_NAME_LEN);
        memset(my_servant.cities[city_index].files[file_index].entries[i].city_name,0,FILE_NAME_LEN);

        my_servant.cities[city_index].files[file_index].entries[i].date=(char*)malloc(sizeof(char)*FILE_NAME_LEN);
        memset(my_servant.cities[city_index].files[file_index].entries[i].date,0,FILE_NAME_LEN);        

        strcpy(my_servant.cities[city_index].files[file_index].entries[i].city_name,my_servant.cities[city_index].city_name);
        strcpy(my_servant.cities[city_index].files[file_index].entries[i].date,my_servant.cities[city_index].files[file_index].file_name);
   

        char* buffer=(char*)malloc(sizeof(char)*MAX_BLKSIZE);
        memset(buffer,0,MAX_BLKSIZE);
        read_until_newline(date_fd,buffer);

        //printf("%s\n",buffer);

        char* strtok_buf=buffer;

        char* first_token=strtok_r(strtok_buf," ",&strtok_buf);
        char* second_token=strtok_r(strtok_buf," ",&strtok_buf);
        char* third_token=strtok_r(strtok_buf," ",&strtok_buf);
        char* fourth_token=strtok_r(strtok_buf," ",&strtok_buf);
        char* fifth_token=strtok_r(strtok_buf," ",&strtok_buf);
                
        strcpy(my_servant.cities[city_index].files[file_index].entries[i].type_real_estate,second_token);
        strcpy(my_servant.cities[city_index].files[file_index].entries[i].name_of_street,third_token);
        my_servant.cities[city_index].files[file_index].entries[i].transaction_id=atoi(first_token);
        my_servant.cities[city_index].files[file_index].entries[i].surface=atoi(fourth_token);
        my_servant.cities[city_index].files[file_index].entries[i].price=atoi(fifth_token);
        free(buffer);
    }
    close(date_fd);
}

void scan_city_directory(char* city_name,char* directory_path,int index,int interval_low) {

    char* full_path=(char*)malloc(sizeof(char)*MAX_BLKSIZE);
    memset(full_path,0,MAX_BLKSIZE);
    strcat(full_path,directory_path);
    strcat(full_path,"/");
    strcat(full_path,city_name);

    int number_of_file_entry=0;

    DIR*dirp=opendir(full_path);
    while(dirp) {
        errno=0;
        struct dirent* dp;
        if((dp=readdir(dirp))!=NULL) {
            //printf("%s\n",dp->d_name);
            number_of_file_entry++;
        }
        else {
            break;
        }
    }
    seekdir(dirp,0);
    number_of_file_entry-=2;
    my_servant.cities[index-interval_low].number_of_file=number_of_file_entry;
    my_servant.cities[index-interval_low].files=(date_file*)malloc(sizeof(date_file)*number_of_file_entry);
    memset(my_servant.cities[index-interval_low].files,0,sizeof(date_file)*number_of_file_entry);
    int date_file_counter=0;
    //printf("CITY:%s\n",city_name);
    for(int i=0;i<number_of_file_entry+2;i++) {
        struct dirent* dp=readdir(dirp);
        if(strcmp(dp->d_name,"..")==0 || strcmp(dp->d_name,".")==0) {}
        else {
            my_servant.cities[index-interval_low].files[date_file_counter].file_name=(char*)malloc(sizeof(char)*FILE_NAME_LEN);
            memset(my_servant.cities[index-interval_low].files[date_file_counter].file_name,0,FILE_NAME_LEN);
            strcpy(my_servant.cities[index-interval_low].files[date_file_counter].file_name,dp->d_name);
            //printf("%s\n",dp->d_name);
            char* date_file_full_path=(char*)malloc(sizeof(char)*MAX_BLKSIZE);
            memset(date_file_full_path,0,MAX_BLKSIZE);
            strcpy(date_file_full_path,full_path);
            strcat(date_file_full_path,"/");
            strcat(date_file_full_path,dp->d_name);
            read_date_file(date_file_full_path,index-interval_low,date_file_counter);

            free(date_file_full_path);
            date_file_counter++;
        }    
    }
    closedir(dirp);

    //printf("------\n");
    free(full_path);
}

void free_tree(struct node* root) {
    if(root==NULL) {
        return;
    }
    free_tree(root->left);
    free(root->left);
    free_tree(root->right);
    free(root->right);
}

void free_resources() {


    for(int i=0;i<my_servant.number_of_city;i++) {
        for(int k=0;k<my_servant.cities[i].number_of_file;k++) {
            for(int j=0;j<my_servant.cities[i].files[k].number_of_entry;j++) {
                free(my_servant.cities[i].files[k].entries[j].name_of_street);
                free(my_servant.cities[i].files[k].entries[j].type_real_estate);
                free(my_servant.cities[i].files[k].entries[j].city_name);
                free(my_servant.cities[i].files[k].entries[j].date);
            }
            free(my_servant.cities[i].files[k].entries);
            free(my_servant.cities[i].files[k].file_name);
        }
        free(my_servant.cities[i].files);
        free(my_servant.cities[i].city_name);
    }
    free(my_servant.cities);
    for(int i=0;i<number_of_subdir;i++) {
        free(namelist[i]);
    }
    free(namelist);
}