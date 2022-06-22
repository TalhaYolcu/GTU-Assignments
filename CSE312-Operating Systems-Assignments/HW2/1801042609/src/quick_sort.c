
#include "common.c"
 
int partition_ex (int arr[], int low, int high)
{
    int pivot = arr[high]; // pivot
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far
    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j] < pivot)
        {
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
 
void quick_ex(int arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition_ex(arr, low, high);
 
        // Separately sort elements before
        // partition and after partition
        quick_ex(arr, low, pi - 1);
        quick_ex(arr, pi + 1, high);
    }
}


int partition (my_program*p,int arr[], int low, int high){
    int pivot=(*reference_memory(p,arr,high));
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++){
        if (*reference_memory(p,arr,j) < pivot){
            i++;
            swap(reference_memory(p,arr,i), reference_memory(p,arr,j));
        }
    }
    swap(reference_memory(p,arr,i+1), reference_memory(p,arr,high));
    return (i + 1);
}
void quickSort(my_program*p,int arr[], int low, int high){
    if (low < high){
        int pi = partition(p,arr, low, high);
        quickSort(p,arr, low, pi - 1);
        quickSort(p,arr, pi + 1, high);
    }
}

void quick_operation(my_program* p,int*array) {
    printf("QUICK OPERATION\n");
    quickSort(p,array,0,DISK_ARRAY_SIZE-1);
    write_back_to_disk(p,array);
}