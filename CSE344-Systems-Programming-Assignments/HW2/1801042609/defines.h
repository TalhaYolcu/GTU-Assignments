#ifndef DEFINES
#define DEFINES


#define READ_FLAGS O_RDWR
#define WRITE_FLAGS (O_RDWR | O_APPEND | O_CREAT)
#define CLEAN_WRITE_FLAGS (O_WRONLY | O_TRUNC | O_CREAT)
#define READ_BUFFER_SIZE 3
#define POINT_SIZE 10
#define WRITE_BUFFER_SIZE 100
#define BLKSIZE 1024
#define ROW_COUNT 3
#define COLUMN_COUNT 3
#define MAX_PROCESS 500

typedef struct point {
    unsigned char x;
    unsigned char y;
    unsigned char z;
}point;

typedef struct norm {
    int process_number;
    float distance;
}norm;

typedef struct parentp {
    int process_id;
    int childpids[MAX_PROCESS];
    int childpcount;
}parentp;


#endif
