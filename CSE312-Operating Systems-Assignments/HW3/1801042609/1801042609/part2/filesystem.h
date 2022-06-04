#ifndef __1801042609_fs
#define __1801042609_fs

#include <stdint.h>

#define ONE_KILOBYTE (1024)
#define ONE_MEGABYTE (1024*ONE_KILOBYTE)
#define DIRECT_COUNT (8)
#define INDEX1_COUNT (1)
#define INDEX2_COUNT (1)
#define INDEX3_COUNT (1)
#define ADDR_SIZE (sizeof(uint16_t))
#define FILE_NAME_LEN (30)
#define FILE_TYPE (0)
#define DIR_TYPE (1)

#define GET_BIT(a,n) (((a)[(n)/8] >> (7 - ((n)%8))) & 1)
#define SET_BIT(a,n) ((a)[(n)/8] |= 1 << (7 - ((n)%8)))
#define CLEAR_BIT(a,n) ((a)[(n)/8] &= ~(1 << (7 - ((n)%8))))

typedef struct File {
    uint16_t inode;
    char name[FILE_NAME_LEN];
}File;

typedef struct Inode {
    uint8_t link_count;
    uint8_t type;
    uint32_t size;
    int32_t last_access_time;
    uint16_t direct[DIRECT_COUNT];
    uint16_t singleI[INDEX1_COUNT];
    uint16_t doubleI[INDEX2_COUNT];
    uint16_t tripleI[INDEX3_COUNT];
}Inode;

typedef struct SuperBlock {
    uint16_t block_size;
    uint16_t block_count;
    uint16_t inode_count;
    uint16_t file_count;
    uint32_t first_block_address;
    uint32_t first_inode_address;
    uint8_t block_bitmap[128];
}SuperBlock;

#endif