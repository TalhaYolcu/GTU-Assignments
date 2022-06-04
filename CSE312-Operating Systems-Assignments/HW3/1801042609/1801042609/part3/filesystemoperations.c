#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>

#include "filesystem.h"

uint8_t filesystem[16*ONE_MEGABYTE] = {0};

void print_information_about_system(uint8_t *fs, uint16_t *counts, uint8_t *vMap,  Inode *inode)
{
    counts[inode->type]++;
     File *file = NULL;
    if (DIR_TYPE != inode->type) {
        return;
    }
    uint64_t num = inode->size / sizeof( File);
    for (uint64_t i = 2; i < num; ++i) {
        file = get_file_in_directory(fs, inode, i);
        if (!GET_BIT(vMap, file->inode)) {
            SET_BIT(vMap, file->inode);
            print_inode(fs, file->inode);
            print_information_about_system(fs, counts, vMap, get_inode(fs, file->inode));
        }
    }
}

void print_inode(uint8_t *fs, uint16_t num)
{
    printf("--- --- --- --- ---\n");
    printf("Inode:\t%4u %3s\n", num, GET_TYPE(get_inode(fs, num)->type));
     SuperBlock *s = ( SuperBlock *)fs;
    printf("Names:\t");
    for (uint16_t i = 0; i < s->inode_count; ++i) {
         Inode *inode = get_inode(fs, i);
        if (0 == inode->link_count || DIR_TYPE != inode->type) {
            continue;
        }
        uint64_t count = inode->size / sizeof( File);
        for (uint64_t j = 2; j < count; ++j) {
             File *file = get_file_in_directory(fs, inode, j);
            if (file->inode == num) {
                printf("%s, ", file->name);
            }
        }
    }
    printf("\nBlocks:\t");
     Inode *inode = get_inode(fs, num);
    uint64_t blockCount = (inode->size + (s->block_size*ONE_KILOBYTE) - 1) / (s->block_size * ONE_KILOBYTE);
    for (uint64_t i = 0; i < blockCount; ++i) {
        uint16_t res[4] = {0};
        uint16_t cnt = get_file_block_number(fs, inode, i, res);
        for (uint16_t j = 0; j < cnt; ++j) {
            printf("%u, ", res[j]);
        }
    }
    printf("\n");
}

Inode *get_inode(uint8_t *fs, uint16_t num)
{
    SuperBlock *s = ( SuperBlock *)fs;
    uint32_t place = num * sizeof( Inode);
    return ( Inode *)(fs + s->first_inode_address + place);
}

uint8_t *get_block(uint8_t *fs, uint16_t num)
{
    SuperBlock *s = ( SuperBlock *)fs;
    uint32_t place = num * s->block_size * ONE_KILOBYTE;
    return (uint8_t *)(fs + s->first_block_address + place);
}

uint16_t get_first_empty_block(uint8_t *fs)
{
    SuperBlock *s = ( SuperBlock *)fs;
    for (size_t i = 0; i < s->block_count; ++i) {
        if (0 == GET_BIT(s->block_bitmap, i)) {
            return i;
        }
    }
    perror("Error, cant find empty block");
    exit(0);
}

uint16_t get_first_empty_inode(uint8_t *fs)
{
     SuperBlock *s = ( SuperBlock *)fs;
    for (size_t i = 0; i < s->inode_count; ++i) {
        if (0 == get_inode(fs, i)->link_count) {
            return i;
        }
    }
    perror("Error, cant find empty inode");
    exit(0);
}

uint8_t *get_file_block(uint8_t *fs,  Inode *inode, uint64_t num)
{
    SuperBlock *s = ( SuperBlock *)fs;
    uint8_t *block = NULL;
    uint64_t iC = (s->block_size * ONE_KILOBYTE) / ADDR_SIZE;
    uint64_t single_count = iC;
    uint64_t double_count = single_count * iC;
    uint64_t triple_count = double_count * iC;
    uint64_t capacity = DIRECT_COUNT + single_count*INDEX1_COUNT + double_count*INDEX2_COUNT + triple_count*INDEX3_COUNT;
    if (capacity <= num) {
        perror("Inode capacity full");
        exit(0);
    }
    capacity -= triple_count * INDEX3_COUNT;
    if (capacity <= num) {
        num -= capacity;
        block = get_block(fs, inode->tripleI[num/triple_count]);
        num %= triple_count;
    }
    capacity -= double_count * INDEX2_COUNT;
    if (capacity <= num || block != NULL) {
        if (NULL == block) {
            num -= capacity;
            block = get_block(fs, inode->doubleI[num/double_count]);
        }
        else {
            uint16_t *shifter = (uint16_t *)block;
            shifter += num / double_count;
            block = get_block(fs, *shifter);
        }
        num %= double_count;
    }
    capacity -= single_count * INDEX1_COUNT;
    if (capacity <= num || block != NULL) {
        if (NULL == block) {
            num -= capacity;
            block = get_block(fs, inode->singleI[num/single_count]);
        }
        else {
            uint16_t *shifter = (uint16_t *)block;
            shifter += num / single_count;
            block = get_block(fs, *shifter);
        }
        num %= single_count;
    }
    if (NULL == block) {
        block = get_block(fs, inode->direct[num]);
    }
    else {
        uint16_t *shifter = (uint16_t *)block;
        shifter += num;
        block = get_block(fs, *shifter);
    }
    return block;
}

uint8_t get_file_block_number(uint8_t *fs,  Inode *inode, uint64_t num, uint16_t *res)
{
     SuperBlock *s = ( SuperBlock *)fs;
    uint8_t cnt = 0;
    uint8_t *block = NULL;
    uint64_t iC = (s->block_size * ONE_KILOBYTE) / ADDR_SIZE;
    uint64_t single_count = iC;
    uint64_t double_count = single_count * iC;
    uint64_t triple_count = double_count * iC;
    uint64_t capacity = DIRECT_COUNT + single_count*INDEX1_COUNT + double_count*INDEX2_COUNT + triple_count*INDEX3_COUNT;
    if (capacity <= num) {
        perror("Inode capacity full");
        exit(0);
    }
    capacity -= triple_count * INDEX3_COUNT;
    if (capacity <= num) {
        num -= capacity;
        block = get_block(fs, inode->tripleI[num/triple_count]);
        if (0 == num % triple_count) {
            res[cnt++] = inode->tripleI[num/triple_count];
        }
        num %= triple_count;
    }
    capacity -= double_count * INDEX2_COUNT;
    if (capacity <= num || block != NULL) {
        if (NULL == block) {
            num -= capacity;
            block = get_block(fs, inode->doubleI[num/double_count]);
            if (0 == num % double_count) {
                res[cnt++] = inode->doubleI[num/double_count];
            }
        }
        else {
            uint16_t *shifter = (uint16_t *)block;
            shifter += num / double_count;
            block = get_block(fs, *shifter);
            if (0 == num % double_count) {
                res[cnt++] = *shifter;
            }
        }
        num %= double_count;
    }
    capacity -= single_count * INDEX1_COUNT;
    if (capacity <= num || block != NULL) {
        if (NULL == block) {
            num -= capacity;
            block = get_block(fs, inode->singleI[num/single_count]);
            if (0 == num % single_count) {
                res[cnt++] = inode->singleI[num/single_count];
            }
        }
        else {
            uint16_t *shifter = (uint16_t *)block;
            shifter += num / single_count;
            block = get_block(fs, *shifter);
            if (0 == num % single_count) {
                res[cnt++] = *shifter;
            }
        }
        num %= single_count;
    }
    if (NULL == block) {
        res[cnt++] = inode->direct[num];
    }
    else {
        uint16_t *shifter = (uint16_t *)block;
        shifter += num;
        res[cnt++] = *shifter;
    }
    return cnt;
}

 File *getFile(uint8_t *fs,  Inode *inode, char *name)
{
     File *file = NULL;
    uint64_t num = inode->size / sizeof( File);
    for (uint64_t i = 0; i < num; ++i) {
        file = get_file_in_directory(fs, inode, i);
        if (!strcmp(file->name, name)) {
            return file;
        }
    }
    return NULL;
}

File *get_file_in_directory(uint8_t *fs,  Inode *inode, uint64_t num)
{
     SuperBlock *s = ( SuperBlock *)fs;
    uint8_t *block = NULL;
    uint64_t iC = (s->block_size * ONE_KILOBYTE) / ADDR_SIZE;
    uint64_t c = s->file_count;
    uint64_t single_count = c * iC;
    uint64_t double_count = single_count * iC;
    uint64_t triple_count = double_count * iC;
    uint64_t capacity = c*DIRECT_COUNT + single_count*INDEX1_COUNT + double_count*INDEX2_COUNT + triple_count*INDEX3_COUNT;
    if (capacity <= num) {
        perror("There is no capacity on inode");
        exit(0);
    }
    capacity -= triple_count * INDEX3_COUNT;
    if (capacity <= num) {
        num -= capacity;
        block = get_block(fs, inode->tripleI[num/triple_count]);
        num %= triple_count;
    }
    capacity -= double_count * INDEX2_COUNT;
    if (capacity <= num) {
        if (NULL == block) {
            num -= capacity;
            block = get_block(fs, inode->doubleI[num/double_count]);
        }
        else {
            uint16_t *shifter = (uint16_t *)block;
            shifter += num / double_count;
            block = get_block(fs, *shifter);
        }
        num %= double_count;
    }
    capacity -= single_count * INDEX1_COUNT;
    if (capacity <= num) {
        if (NULL == block) {
            num -= capacity;
            block = get_block(fs, inode->singleI[num/single_count]);
        } else {
            uint16_t *shifter = (uint16_t *)block;
            shifter += num / single_count;
            block = get_block(fs, *shifter);
        }
        num %= single_count;
    }
    if (NULL == block) {
        block = get_block(fs, inode->direct[num/c]);
    }
    else {
        uint16_t *shifter = (uint16_t *)block;
        shifter += num / c;
        block = get_block(fs, *shifter);
    }
    num %= c;
    File *file = ( File *)(block + num*sizeof( File));
    return file;
}

File *get_first_empty_place(uint8_t *fs,  Inode *inode)
{
    uint64_t num = inode->size / sizeof( File);
     SuperBlock *s = ( SuperBlock *)fs;
    uint8_t *block = NULL;
    uint64_t iC = (s->block_size * ONE_KILOBYTE) / ADDR_SIZE;
    uint64_t c = s->file_count;
    uint64_t single_count = c * iC;
    uint64_t double_count = single_count * iC;
    uint64_t triple_count = double_count * iC;
    uint64_t capacity = c*DIRECT_COUNT + single_count*INDEX1_COUNT + double_count*INDEX2_COUNT + triple_count*INDEX3_COUNT;
    if (capacity <= num) {
        perror("Inode capacity full");
        exit(0);
    }
    capacity -= triple_count * INDEX3_COUNT;
    if (capacity <= num) {
        num -= capacity;
        if (0 == num % triple_count) {
            inode->tripleI[num/triple_count] = get_first_empty_block(fs);
            SET_BIT(s->block_bitmap, inode->tripleI[num/triple_count]);
        }
        block = get_block(fs, inode->tripleI[num/triple_count]);
        num %= triple_count;
    }
    capacity -= double_count * INDEX2_COUNT;
    if (capacity <= num) {
        if (NULL == block) {
            num -= capacity;
            if (0 == num % double_count) {
                inode->doubleI[num/double_count] = get_first_empty_block(fs);
                SET_BIT(s->block_bitmap, inode->doubleI[num/double_count]);
            }
            block = get_block(fs, inode->doubleI[num/double_count]);
        } else {
            uint16_t *shifter = (uint16_t *)block;
            shifter += num / double_count;
            if (0 == num % double_count) {
                *shifter = get_first_empty_block(fs);
                SET_BIT(s->block_bitmap, *shifter);
            }
            block = get_block(fs, *shifter);
        }
        num %= double_count;
    }
    capacity -= single_count * INDEX1_COUNT;
    if (capacity <= num) {
        if (NULL == block) {
            num -= capacity;
            if (0 == num % single_count) {
                inode->singleI[num/single_count] = get_first_empty_block(fs);
                SET_BIT(s->block_bitmap, inode->singleI[num/single_count]);
            }
            block = get_block(fs, inode->singleI[num/single_count]);
        } else {
            uint16_t *shifter = (uint16_t *)block;
            shifter += num / single_count;
            if (0 == num % single_count) {
                *shifter = get_first_empty_block(fs);
                SET_BIT(s->block_bitmap, *shifter);
            }
            block = get_block(fs, *shifter);
        }
        num %= single_count;
    }
    if (NULL == block) {
        if (0 == num % c) {
            inode->direct[num/c] = get_first_empty_block(fs);
            SET_BIT(s->block_bitmap, inode->direct[num/c]);
        }
        block = get_block(fs, inode->direct[num/c]);
    } else {
        uint16_t *shifter = (uint16_t *)block;
        shifter += num / c;
        if (0 == num % c) {
            *shifter = get_first_empty_block(fs);
            SET_BIT(s->block_bitmap, *shifter);
        }
        block = get_block(fs, *shifter);
    }
    num %= c;
     File *file = ( File *)(block + num*sizeof( File));
    return file;
}

File *get_last_nonempty_place(uint8_t *fs,  Inode *inode)
{
    uint64_t num = inode->size / sizeof( File);
    if (0 == num) {
        perror("Inode error");
        exit(0);
    }
    return get_file_in_directory(fs, inode, num-1);
}

void find_parent_direcotry(char *dest, char *src)
{
    strcpy(dest, src);
    size_t i = strlen(dest) - 1;
    if ('/' == dest[i]) {
        perror("Path is invalid\n");
        exit(0);
    }
    for (; 0 < i; --i) {
        if ('/' != dest[i]) {
            dest[i] = '\0';
        } else {
            dest[i] = '\0';
            break;
        }
    }
    if (FILE_NAME_LEN <= strlen(src)-strlen(dest)) {
        perror( "File name is long");
        exit(0);
    }
}

Inode *find_inode_of_path(uint8_t *fs, char *path)
{
    if ('/' != path[0]) {
        perror( "Path not found");
        exit(0);
    }
    path++;
    char name[ONE_KILOBYTE];
    uint16_t inodeNum = 0;
    Inode *inode = get_inode(fs, inodeNum);
    File *file = NULL;
    while (strlen(path)) {
        size_t keylen = get_length_until_path(path);
        if (FILE_NAME_LEN <= keylen) {
            perror( "File name is long");
            exit(0);
        }
        switch (inode->type) {
            case FILE_TYPE:
                perror( "Could not find path");
                exit(0);
                break;
            case DIR_TYPE:
                strncpy(name, path, keylen);
                name[keylen] = '\0';
                file = getFile(fs, inode, name);
                if (NULL == file) {
                    perror( "Could not find path");
                    exit(0);
                }
                inodeNum = file->inode;
                break;
            default:
                perror( "Unknown file type\n");
                exit(0);
        }
        inode = get_inode(fs, inodeNum);
        path += keylen;
        if (0 < strlen(path)) {
            path++;
        }
    }
    return inode;
}

size_t get_length_until_path(char *path)
{
    size_t len = 0;
    while ('/' != path[len] && '\0' != path[len])
    {
        ++len;
    }
    return len;
}

void free_file_block(uint8_t *fs,  File *file)
{
    SuperBlock *s = (SuperBlock *)fs;
    Inode *delInode = get_inode(fs, file->inode);
    uint64_t iC = (s->block_size * ONE_KILOBYTE) / ADDR_SIZE;
    uint64_t blockCount = (delInode->size + (s->block_size*ONE_KILOBYTE) - 1) / (s->block_size * ONE_KILOBYTE);
    for (uint64_t i = 0; i < DIRECT_COUNT && 0 < blockCount; ++i) {
        CLEAR_BIT(s->block_bitmap, delInode->direct[i]);
        blockCount--;
    }
    for (uint64_t i = 0; i < INDEX1_COUNT && 0 < blockCount; ++i) {
        uint16_t *sAddr = (uint16_t *)get_block(fs, delInode->singleI[i]);
        for (uint64_t j = 0; j < iC && 0 < blockCount; ++j) {
            CLEAR_BIT(s->block_bitmap, *sAddr);
            blockCount--;
            sAddr++;
        }
        CLEAR_BIT(s->block_bitmap, delInode->singleI[i]);
    }
    for (uint64_t i = 0; i < INDEX2_COUNT && 0 < blockCount; ++i) {
        uint16_t *dAddr = (uint16_t *)get_block(fs, delInode->doubleI[i]);
        for (uint64_t j = 0; j < iC && 0 < blockCount; ++j) {
            uint16_t *sAddr = (uint16_t *)get_block(fs, *dAddr);
            for (uint64_t k = 0; k < iC && 0 < blockCount; ++k) {
                CLEAR_BIT(s->block_bitmap, *sAddr);
                blockCount--;
                sAddr++;
            }
            CLEAR_BIT(s->block_bitmap, *dAddr);
            dAddr++;
        }
        CLEAR_BIT(s->block_bitmap, delInode->doubleI[i]);
    }
    for (uint64_t i = 0 ; i < INDEX3_COUNT && 0 < blockCount; ++i) {
        uint16_t *tAddr = (uint16_t *)get_block(fs, delInode->tripleI[i]);
        for (uint64_t j = 0; j < iC && 0 < blockCount; ++j) {
            uint16_t *dAddr = (uint16_t *)get_block(fs, *tAddr);
            for (uint64_t k = 0; k < iC && 0 < blockCount; ++k) {
                uint16_t *sAddr = (uint16_t *)get_block(fs, *dAddr);
                for (uint64_t m = 0; m < iC && 0 < blockCount; ++m) {
                    CLEAR_BIT(s->block_bitmap, *sAddr);
                    blockCount--;
                    sAddr++;
                }
                CLEAR_BIT(s->block_bitmap, *dAddr);
                dAddr++;
            }
            CLEAR_BIT(s->block_bitmap, *tAddr);
            tAddr++;
        }
        CLEAR_BIT(s->block_bitmap, delInode->tripleI[i]);
    }
    delInode->size = 0;
}

uint16_t emptyblock_count(uint8_t *fs)
{
    SuperBlock *s = (SuperBlock *)fs;
    uint16_t count = s->block_count;
    for (uint16_t i = 0; i < s->block_count; ++i) {
        if (GET_BIT(s->block_bitmap, i)) {
            count--;
        }
    }
    return count;
}

uint16_t emptyinode_count(uint8_t *fs)
{
    SuperBlock *s = (SuperBlock *)fs;
    uint16_t count = s->inode_count;
    for (uint16_t i = 0; i < s->inode_count; ++i) {
        if (0 < get_inode(fs, i)->link_count) {
            count--;
        }
    }
    return count;
}

void check_available(uint8_t *fs, uint8_t checkBlocks, uint8_t checkInodes)
{
    if (emptyblock_count(fs) < checkBlocks) {
        perror( "Cannot find enough empty blocks");
        exit(0);
    }
    if (emptyinode_count(fs) < checkInodes) {
        perror( "Cannot find enough empty inodes");
        exit(0);
    }
}

void dir_command(uint8_t *fs, char *path)
{
    Inode *inode = find_inode_of_path(fs, path);
    if (DIR_TYPE != inode->type) {
        perror( "it is not a directory");
        exit(0);
    }
    File *file = NULL;
    uint64_t num = inode->size / sizeof( File);
    for (uint64_t i = 0; i < num; ++i) {
        file = get_file_in_directory(fs, inode, i);
        Inode *finode = get_inode(fs, file->inode);
        time_t t = (time_t)(finode->last_access_time);
        char *timeStr = asctime(gmtime(&t));
        timeStr[strlen(timeStr)-1] = '\0';
        printf("%3s %7u %s %s\n", GET_TYPE(finode->type), finode->size, timeStr, file->name);
    }
}

void mkdir_command(uint8_t *fs, char *path)
{
    char str[ONE_KILOBYTE];
    find_parent_direcotry(str, path);
    Inode *inode = find_inode_of_path(fs, str);
    path += strlen(str);
    if (strlen(str) != 1) {
        path++;
    }
    if (DIR_TYPE != inode->type) {
        perror( "it is not a directory");
        exit(0);
    }
     SuperBlock *s = ( SuperBlock *)fs;
    if (NULL != getFile(fs, inode, path)) {
        perror( "it is already directory");
        exit(0);
    }
    check_available(fs, 1, 1);
    File *file = ( File *)get_block(fs, inode->direct[0]);
    uint16_t block = get_first_empty_block(fs);
    SET_BIT(s->block_bitmap, block);
    File *newDir = ( File *)get_block(fs, block);
    memset(newDir, '\0', s->block_size*ONE_KILOBYTE);
    strcpy(newDir->name, ".");
    newDir->inode = get_first_empty_inode(fs);
    strcpy((newDir+1)->name, "..");
    (newDir+1)->inode = file->inode;

    file = get_first_empty_place(fs, inode);
    strcpy(file->name, path);
    file->inode = newDir->inode;
    inode->size += sizeof( File);
    inode->last_access_time = (int32_t)time(NULL);

    inode = get_inode(fs, file->inode);
    memset(inode, '\0', sizeof( Inode));
    inode->link_count = 1;
    inode->type = DIR_TYPE;
    inode->size = 2 * sizeof( File);
    inode->last_access_time = (int32_t)time(NULL);
    inode->direct[0] = block;
}

void rmdir_command(uint8_t *fs, char *path)
{
    char str[ONE_KILOBYTE];
    find_parent_direcotry(str, path);
    Inode *inode = find_inode_of_path(fs, str);
    path += strlen(str);
    if (strlen(str) != 1) {
        path++;
    }
    if (DIR_TYPE != inode->type) {
        perror( "it is not a directory");
        exit(0);
    }
    File *file = (File *)getFile(fs, inode, path);
    if (NULL == file) {
        perror( "it is not found");
        exit(0);
    }
    Inode *delInode = get_inode(fs, file->inode);
    if (DIR_TYPE != delInode->type) {
        perror( "it is not a directory");
        exit(0);
    }
    if (2 * sizeof(File) != delInode->size) {
        perror( "it is not an empty directory");
        exit(0);
    }

    delInode = get_inode(fs, file->inode);
    if (0 == --(delInode->link_count)) {
        free_file_block(fs, file);
        get_inode(fs, file->inode)->link_count = 0;
    }
    File *full = get_last_nonempty_place(fs, inode);
    memcpy(file, full, sizeof(File));
    memset(full, '\0', sizeof(File));
    inode->size -= sizeof(File);
    inode->last_access_time = (uint32_t)time(NULL);
}

void dumpe2fs_command(uint8_t *fs)
{
     SuperBlock *s = ( SuperBlock *)fs;
    uint16_t emptyBlocks = emptyblock_count(fs);
    uint16_t emptyInodes = emptyinode_count(fs);
    printf("Block Size(KB) :   %8u\n", s->block_size);
    printf("Blocks(Free)   :   %8u\n", emptyBlocks);
    printf("Blocks(Total)  :   %8u\n", s->block_count);
    printf("Inodes(Free)   :   %8u\n", emptyInodes);
    printf("Inodes(Total)  :   %8u\n", s->inode_count);

     Inode *root = get_inode(fs, 0);
    printf("--- --- --- --- ---\n");
    printf("Inode:\t%4u %3s\n", 0, GET_TYPE(get_inode(fs, 0)->type));
    printf("Names:\t(root)");
    printf("\nBlocks:\t");
    uint64_t blockCount = (root->size + (s->block_size*ONE_KILOBYTE) - 1) / (s->block_size * ONE_KILOBYTE);
    for (uint64_t i = 0; i < blockCount; ++i) {
        uint16_t res[4] = {0};
        uint16_t cnt = get_file_block_number(fs, root, i, res);
        for (uint16_t j = 0; j < cnt; ++j) {
            printf("%u, ", res[j]);
        }
    }
    printf("\n");

    uint16_t typeCounts[3] = {0};
    uint8_t *visited = (uint8_t *)calloc((s->inode_count+7)/8, sizeof(uint8_t));
    SET_BIT(visited, 0);
    print_information_about_system(fs, typeCounts, visited, root);
    free(visited);
    printf("--- --- --- --- ---\n");
    printf("Files          :   %8u\n", typeCounts[FILE_TYPE]);
    printf("Directories    :   %8u\n", typeCounts[DIR_TYPE]);
    printf("Symbolic Links :   %8u\n", typeCounts[SYM_TYPE]);
    printf("Free Blocks    :   ");
    for (uint16_t i = 0; i < s->block_count; ++i) {
        if (0 == GET_BIT(s->block_bitmap, i)) {
            printf("%u, ", i);
        }
    }
    printf("\nFree Inodes    :   ");
    for (uint16_t i = 0; i < s->inode_count; ++i) {
        if (0 == get_inode(fs, i)->link_count) {
            printf("%u, ", i);
        }
    }
    printf("\n");
}

