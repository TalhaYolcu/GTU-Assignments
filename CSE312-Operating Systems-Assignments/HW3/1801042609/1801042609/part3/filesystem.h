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
#define SYM_TYPE (2)
#define GET_TYPE(t) (FILE_TYPE==(t) ? "FIL" : (DIR_TYPE==(t) ? "DIR" : (SYM_TYPE==(t) ? "SYM" : "NIL")))

#define GET_BIT(a,n) (((a)[(n)/8] >> (7 - ((n)%8))) & 1)
#define SET_BIT(a,n) ((a)[(n)/8] |= 1 << (7 - ((n)%8)))
#define CLEAR_BIT(a,n) ((a)[(n)/8] &= ~(1 << (7 - ((n)%8))))

typedef struct File {
    uint16_t inode;
    char name[FILE_NAME_LEN];
}File;

typedef struct  Inode {
    uint8_t link_count;
    uint8_t type;
    uint32_t size;
    int32_t last_access_time;
    uint16_t direct[DIRECT_COUNT];
    uint16_t singleI[INDEX1_COUNT];
    uint16_t doubleI[INDEX2_COUNT];
    uint16_t tripleI[INDEX3_COUNT];
}Inode;

typedef struct  SuperBlock {
    uint16_t block_size;
    uint16_t block_count;
    uint16_t inode_count;
    uint16_t file_count;
    uint32_t first_block_address;
    uint32_t first_inode_address;
    uint8_t block_bitmap[128];
}SuperBlock;


Inode *get_inode(uint8_t *, uint16_t);
uint8_t *get_block(uint8_t *, uint16_t );
uint16_t get_first_empty_block(uint8_t *);
uint16_t get_first_empty_inode(uint8_t *);
File *get_file_in_directory(uint8_t *,  Inode *, uint64_t);
File *get_first_empty_place(uint8_t *,  Inode *);
File *get_last_nonempty_place(uint8_t *,  Inode *);
uint8_t *get_file_block(uint8_t *,  Inode *, uint64_t);
uint8_t get_file_block_number(uint8_t *,  Inode *, uint64_t, uint16_t *);
void find_parent_direcotry(char *, char *);
File *getFile(uint8_t *,  Inode *, char *);
Inode *find_inode_of_path(uint8_t *, char *);
size_t get_length_until_path(char *);
void free_file_block(uint8_t *,  File *);
uint16_t emptyblock_count(uint8_t *);
uint16_t emptyinode_count(uint8_t *);
void check_available(uint8_t *, uint8_t, uint8_t);

void print_information_about_system(uint8_t *, uint16_t *, uint8_t *,  Inode *);
void print_inode(uint8_t *, uint16_t);

void dir_command(uint8_t *, char *);
void mkdir_command(uint8_t *, char *);
void rmdir_command(uint8_t *, char *);
void dumpe2fs_command(uint8_t*);

#endif