

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include "tlpi_hdr.h"
#include <semaphore.h>

#define SERVER_FIFO ""
                                /* Well-known name for server's FIFO */
#define CLIENT_FIFO_TEMPLATE "seqnum_cl.%ld"
                                /* Template for building client FIFO name */
#define CLIENT_FIFO_NAME_LEN (sizeof(CLIENT_FIFO_TEMPLATE) + 20)
                                /* Space required for client FIFO pathname
                                  (+20 as a generous allowance for the PID) */

struct request {                /* Request (client --> server) */
    pid_t pid;                  /* PID of client */
    int matrix_entry;
    int row;
};

struct response {               /* Response (server --> client) */
    int invertible;
};

struct worker {
    int client_id;
    int row_count;
    int pid;
    int available;
    int pipe_read_fd;
    int fifo_write_fd;
    int pipe_write_fd;
};

struct worker_z {
    int client_id;
    int row_count;
    int pid;
    int available;
};

typedef struct shared_memory {
    char queue[MAX_BLKSIZE][MAX_BLKSIZE];
    int cursor;
    int last;
    int pool_size;
    int working_worker;
    int handled;
    sem_t empty;
    sem_t full;
    sem_t lock;
}shared_memory;
