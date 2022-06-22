#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef _1801042609_final_structs
#define _1801042609_final_structs

#define FILE_NAME_LEN 30
#define MAX_BLKSIZE 1024
#define MAX_THREAD 256

typedef struct file_entry {
    int transaction_id;
    char* type_real_estate;
    char* name_of_street;
    int surface;
    int price;
    char* date;
    char* city_name;
}file_entry;

typedef struct date_file {
    char* file_name;
    file_entry* entries;
    int number_of_entry;
}date_file;

typedef struct city{
    date_file* files;
    char* city_name;
    int number_of_file;
}city;

typedef struct servant {
    city* cities;
    int number_of_city;
    int start_index;
    int end_index;
    int port_number;
}servant;

typedef struct fake_servant {
    char* start_city;
    char* end_city;
    char* ip_address;
    int port_number;
    int pid;
    int fd;
    int socket_num;

}fake_servant;

struct node {
    file_entry *key;
    struct node *left, *right;
};

typedef struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
}Queue;
 



#endif