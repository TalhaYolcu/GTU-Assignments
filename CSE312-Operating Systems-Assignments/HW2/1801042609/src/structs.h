#ifndef MY_PAGE
#define MY_PAGE


#define VIRTUAL_ADDRESS_SPACE 64 //2^6
#define PAGE_SIZE 16 //2^4
#define NUMBER_OF_PAGE 4 //2^2
#define DISK_ARRAY_SIZE 128 


typedef struct Page
{
    int index;
    int array[PAGE_SIZE];
    int load_time;
    int last_reference_time;
    int R_bit;
    int M_bit;
    int second_chance;
}Page;


typedef struct pagetable {
    Page pages[NUMBER_OF_PAGE];
}pagetable;


typedef struct my_program {
    pagetable table;
}my_program;

#endif