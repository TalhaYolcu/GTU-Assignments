#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>

#include "filesystem.h"

uint8_t filesystem[16*ONE_MEGABYTE] = {0};


int main(int argc, char *argv[])
{

    if(argc!=4) {
        perror("Error with arguments");
        return 0;
    }


    uint16_t block_size = atoi(argv[1]);
    uint16_t inode_count = atoi(argv[2]) + 1; //for root inode

    char file_name[30];
    memset(file_name,0,30);

    //take argument
    strcpy(file_name,argv[3]);

    //compare needed space and our limited space (16 MB)
    if (ONE_KILOBYTE * (block_size + 1) + inode_count * sizeof(Inode) >= 16*ONE_MEGABYTE ) {
        perror("16 MB space is not enough for these numbers");
        return 0;
    }

    //calculate bytes left for file operations-blocks
    size_t bytes_left_for_operation = 16*ONE_MEGABYTE;
    bytes_left_for_operation -= sizeof(SuperBlock);
    bytes_left_for_operation -= inode_count * sizeof( Inode);


    //prepare super block which keeps block size, block count, inode count and file count etc
    SuperBlock *super_block = (SuperBlock *)filesystem;
    super_block->block_size = block_size;
    super_block->block_count = bytes_left_for_operation / (block_size * ONE_KILOBYTE);
    super_block->inode_count = inode_count;
    super_block->file_count = block_size * (ONE_KILOBYTE / sizeof(File));
    super_block->first_block_address = 16*ONE_MEGABYTE - (super_block->block_count * super_block->block_size * ONE_KILOBYTE);
    super_block->first_inode_address = super_block->first_block_address - (inode_count * sizeof(Inode));
    SET_BIT(super_block->block_bitmap, 0);

    //prepare root inode which has access all inodes
    Inode *root_inode = (Inode *)(filesystem + super_block->first_inode_address);
    root_inode->link_count = 1;
    root_inode->type = DIR_TYPE;
    root_inode->size = 2 * sizeof(File);
    root_inode->last_access_time = (int32_t)time(NULL);
    root_inode->direct[0] = 0;

    //prepare root directory and set its current directory
    File *file = (File *)(filesystem + super_block->first_block_address);
    file->inode = 0;
    strcpy(file->name, ".");
    file++;
    file->inode = 0;
    strcpy(file->name, "..");

    //write filesystem to a file
    FILE *fp;
    fp = fopen(file_name, "wb+");
    if (fp==NULL) {
        perror("fopen error to write file");
        return 0;
    }
    if (fwrite(filesystem, 16*ONE_MEGABYTE, 1, fp)!=1) {
        perror("Error on fwrite");
        return 0;
    }
    fclose(fp);


    size_t size_of_Inode=sizeof(Inode);
    size_t size_of_superblock=sizeof(SuperBlock);
    size_t size_of_one_block=super_block->block_size;
    size_t size_of_memory=16*ONE_MEGABYTE;
    size_t size_of_all_inodes=size_of_Inode*super_block->inode_count;
    size_t size_of_all_blocks=size_of_one_block*super_block->block_count*ONE_KILOBYTE;
    size_t remained_space=size_of_memory-size_of_all_inodes-size_of_all_blocks;

    printf("Size of superblock:%ld\n",size_of_superblock);
    printf("Size of 1 inode:%ld Size of inodes:%ld\n",size_of_Inode,size_of_all_inodes);
    printf("Size of 1 block:%ld Size of blocks:%ld\n",size_of_one_block,size_of_all_blocks);
    printf("Remained empty space:%ld\n",remained_space);


    return 0;
}

