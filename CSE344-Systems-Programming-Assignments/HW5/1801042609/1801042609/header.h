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

#ifndef _HW5_HEADER_YTY
#define _HW5_HEADER_YTY

#define MAX_BLKSIZE 256

void handler(int signal_number);
int check_arguments(int argc, char const *argv[]);
void print_usage_end_exit();
void print_matrix(int size,int** matrix);
void print_matrix_double(int size,double** matrix);
void free_resources();
char* get_time(char* time);
int multiply_two_matrices(int size,int** matrix1,int** matrix2,int** result_matrix,int index);
double get_one_over_mn();
int calculate_2d_dft(int size,int** matrix1,double** real,double** imaginary,int index);
void* run_thread(void* arg);
void wait_for_threads();
int run_the_process(int argc, char const *argv[]);


#endif