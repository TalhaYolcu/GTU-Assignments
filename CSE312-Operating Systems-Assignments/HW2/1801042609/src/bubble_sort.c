#ifndef MY_BUBBLE
#define MY_BUBBLE

#include "common.c"
#include "structs.h"
 
void bubble_ex(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++) {
        // Last i elements are already in place
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void bubbleSort(my_program*p,int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            int* arrj=reference_memory(p,arr,j);
            int* arrjp=reference_memory(p,arr,j+1);
            if((*arrj)>(*arrjp)) {
                swap(arrj,arrjp);
            }
        }
    }
}
void bubble_operation(my_program* p,int*array) {
    printf("BUBBLE OPERATION\n");
    bubbleSort(p,array,DISK_ARRAY_SIZE);
    write_back_to_disk(p,array);
}

#endif