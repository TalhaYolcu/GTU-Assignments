#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>

#include "filesystem.h"
#include "filesystemoperations.c"




int main(int argc, char *argv[])
{


    if(argc<3 || argc>5) {
        perror("Error, arguments are not valid");
        return 0;
    }


    char file_name[30];
    memset(file_name,0,30);

    char command[30];
    memset(command,0,30);



    strcpy(file_name,argv[1]);

    FILE* fp=fopen(file_name,"rb");
    if(fp==NULL) {
        perror("Error, file could not opened");
        return 0;
    }

    if (fread(filesystem, 16*ONE_MEGABYTE, 1, fp)!=1) {
        perror("Error on fread");
        return 0;
    }
    fclose(fp);

    strcpy(command,argv[2]);

    if(argc==5) {

        char other_file[30];
        memset(other_file,0,30);

        char path1[30];
        memset(path1,0,30);

        strcpy(other_file,argv[4]);
        strcpy(path1,argv[3]);


        if(strcmp(command,"write")==0) {
            printf("Not implemented\n");
            return 0;
        }
        else if(strcmp(command,"read")==0) {
            printf("Not implemented\n");
            return 0;            
        }
        else {
            perror("Error, wrong command");
            return 0;
        }

    }
    else if(argc==4) {
        char path1[30];
        memset(path1,0,30);
        strcpy(path1,argv[3]); 

        if(strcmp(command,"mkdir")==0) {
            mkdir_command(filesystem,path1);
        }
        else if(strcmp(command,"rmdir")==0) {
            rmdir_command(filesystem,path1);
        }
        else if(strcmp(command,"dir")==0) {
            dir_command(filesystem,path1);
        }
        else if(strcmp(command,"del")==0) {
            printf("Not implemented\n");
            return 0;
        }
        else {
            perror("Error, wrong command");
            return 0;
        }      
    }
    else if(argc==3){
        if(strcmp(command,"dumpe2fs")==0) {
            dumpe2fs_command(filesystem);
        }
        else {
            perror("Error, wrong command");
            return 0;
        }
    }
    else {
        perror("Error, wrong argument");
        return 0;
    }
    fp = fopen(file_name, "wb+");
    if (fp==NULL) {
        perror("Error on fopen to write");
        return 0;
    }
    if (fwrite(filesystem, 16*ONE_MEGABYTE, 1, fp)!=1) {
        perror("Error on fwrite");
        return 0;
    }
    fclose(fp);
    return 0;;
}

