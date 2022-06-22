#include "common.c"

void insertion_ex(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
 
        // Move elements of arr[0..i-1], 
        // that are greater than key, to one
        // position ahead of their
        // current position
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void insertionSort(my_program*p,int arr[], int n){
    int i, key, j;
    for (i = 1; i < n; i++){
        key=(*(reference_memory(p,arr,i)));
        j = i - 1;
        while (j >= 0 && (*reference_memory(p,arr,j)) > key){
            *(reference_memory(p,arr,j+1))=(*reference_memory(p,arr,j));
            j = j - 1;
        }
        *reference_memory(p,arr,j+1)=key;
    }
}

void insertion_operation(my_program* p,int*array) {
    printf("INSERTION OPERATION\n");
    insertionSort(p,array,DISK_ARRAY_SIZE);
    write_back_to_disk(p,array);
}