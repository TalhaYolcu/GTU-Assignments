#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <ctype.h>


/*
valgrind --leak-check=full ./hw1 "/str[12]/Linux/i" input3.txt
*/


#define BLKSIZE 1024
#define _zero 48
#define _nine 57
#define CAPITAL_A 65
#define CAPITAL_Z 90
#define little_a 97
#define little_z 122
#define READ_FLAGS O_RDWR
#define WRITE_FLAGS (O_WRONLY | O_TRUNC | O_CREAT)

typedef struct match_case{
    bool start_line;
    bool end_line;
    bool case_sensitive;
}match_case;

typedef struct word {
    bool at_end_of_line;
    bool at_start_of_the_line;
    char* string;
}word;

typedef struct match_situation {
    int start_index;
    int end_index;
}match_situation;

void print_usage_and_exit();
char return_insensitive(char c);
bool detect_start_line(const char* match_command);
int check_input_validity(const char* match_command);
bool detect_end_line(const char* match_command,int len);
void determine_cases(const char*match_command,match_case* m);
bool detect_case_sensitive(const char* match_command,int len);
void substring(const char *source,char target[], int start, int end);
int seperate_slashes(int length_of_input,char* match_command,const char* pathname,match_case* m);
void traverse(word* word1,char* first_word,char* second_word,int first_word_counter,int second_word_counter,bool endline,bool startline,bool case_sensitive);
int do_matching(const char* pathname,char* first_word,char* second_word,int first_word_counter,int second_word_counter,match_case* m,char* match_command);



int check_input_validity(const char* match_command) {
    int length_of_input=strlen(match_command);    
    if(length_of_input<5) {
        print_usage_and_exit();
    }
    else if(match_command[0]!='/') {
        print_usage_and_exit();
    }
    else if(match_command[1]=='*') {
        print_usage_and_exit();
    }
    else if(match_command[length_of_input-1]!='/')  {
        if(match_command[length_of_input-2]!='/') {
            print_usage_and_exit();
        }
        if(match_command[length_of_input-1]!='i') {
            print_usage_and_exit();
        }
    }
    else {
        int i=0;
        int op=0;
        int cp=0;
        int number_of_slash=0;
        for(i=0;i<length_of_input;i++) {
            if(match_command[i]=='/') {
                number_of_slash++;
            }
            else if(match_command[i]=='[') {
                if(match_command[i+1]==']') {
                    print_usage_and_exit();
                }
                op++;
            }
            else if(match_command[i]==']') {
                cp++;
            }
        }
        if(op!=cp) {
            print_usage_and_exit();
        }
        else if(number_of_slash%3!=0) {
            print_usage_and_exit();
        }
    }
    return 0;

}

void print_usage_and_exit() {
    char usage[]="Usage:To change str1 to str2, enter that command\n./hw1 \"/str1/str2/\" inputfilepath\n";
    printf("%s",usage);
    exit(-1);
}

bool detect_start_line(const char* match_command) {
    if(match_command[1]=='^') {
        return true;
    }
    else {
        return false;
    }
}

bool detect_end_line(const char* match_command,int len) {
    int i=1;
    bool end_line=false;
    while(i<(len-1) || match_command[i]!='/') {
        if(match_command[i]=='$') {
            end_line=true;
        }
        i++;
    }
    return end_line;
}

bool detect_case_sensitive(const char* match_command,int len) {
    if(match_command[len-1]!='/')  {
        if(match_command[len-2]!='/') {
            print_usage_and_exit();
        }
        if(match_command[len-1]!='i') {
            print_usage_and_exit();
        }
        return false; //case insensitive
    }
    else {
        return true;
    }  
}

void determine_cases(const char*match_command,match_case* m) {
    int length_of_input=strlen(match_command);
    m->case_sensitive=detect_case_sensitive(match_command,length_of_input);
    m->start_line=detect_start_line(match_command);  
    m->end_line=detect_end_line(match_command,length_of_input); 
}

void substring(const char *source,char target[], int start, int end) {
   int c = 0;  
   while (c <= end) {
      target[c] = source[start+c];
      c++;
   }
   target[c] = '\0';
}

char return_insensitive(char c) {
    if(c>=_zero && c<=_nine) {
        return c;
    }
    if(c>=CAPITAL_A && c<=CAPITAL_Z) {
        return c+(little_a-CAPITAL_A);
    }    
    else {
        return c-(little_a-CAPITAL_A);
    }
}

void traverse(word* word1,char* first_word,char* second_word,int first_word_counter,int second_word_counter,bool endline,bool startline,bool case_sensitive) {      
    if((endline==word1->at_end_of_line && startline==word1->at_start_of_the_line) || (word1->at_end_of_line==true && word1->at_start_of_the_line==true) || (endline==startline)) {

        int word1_traverser=0;
        int word1_traverser_end=0;
        int first_word_traverser=0;
        int match_situation_traverser=0;
        bool switch_word=false;
        match_situation* matches=(match_situation*)malloc(sizeof(match_situation)*50);
        int match_situation_counter=0;

        //check each symbol of the first word

        while(word1->string[word1_traverser]!='\0') {
            if(word1_traverser>=strlen(word1->string)) {
                break;
            }

            word1_traverser_end=word1_traverser;
            first_word_traverser=0;
            while(word1->string[word1_traverser_end]!='\0') {


                bool continue_machine=true;
                bool match_found=false;

                if(word1_traverser_end>=strlen(word1->string)) {
                    //continue_machine=false;
                    break;
                }
                //finite state machine
                while(1) {      
                    int selectable_counter=0;     
                    char selectables[first_word_counter*2];        
                    if(first_word_traverser>=first_word_counter) {
                        
                        if(word1->string[word1_traverser_end]!='\0' && endline==true) {
                            break;
                        }
                        

                        matches[match_situation_counter].start_index=word1_traverser;
                        matches[match_situation_counter].end_index=word1_traverser_end;
                        match_situation_counter++;
                        match_found=true;
                        break;
                    }       
                    if(first_word[first_word_traverser]=='^') {
                        first_word_traverser++;
                        //this is start line, do nothing
                    }
                    else if(first_word[first_word_traverser]=='$') {
                        first_word_traverser++;
                        //this is end line, do nothing
                    }
                    else if(first_word[first_word_traverser]=='\0') {
                        matches[match_situation_counter].start_index=word1_traverser;
                        matches[match_situation_counter].end_index=word1_traverser_end;
                        match_situation_counter++;
                        match_found=true;
                        break;
                        //end of the first word, matching is OK.
                    }
                    else if(first_word[first_word_traverser]=='[') {
                        //selectable letters start
                        first_word_traverser++;
                        int selectable_traverser=0;
                        bool selectable_in_here=false;

                        while(1) {
                            if(first_word[first_word_traverser]==']') {
                                break;
                            }
                            if(case_sensitive==false) {
                                if(first_word[first_word_traverser]>=_zero && first_word[first_word_traverser]<=_nine) {
                                    //this is a digit, dont take insensitive of it
                                }
                                else {
                                    selectables[selectable_counter++]=return_insensitive(first_word[first_word_traverser]);
                                    first_word_traverser++;
                                }
                            }
                            selectables[selectable_counter++]=first_word[first_word_traverser];
                            first_word_traverser++;
                        }
                        if(first_word[first_word_traverser+1]=='*') {
                            //TODO ----->
                            if(case_sensitive==false) {
                                for(selectable_traverser=0;selectable_traverser<selectable_counter;selectable_traverser++) {
                                    if((selectables[selectable_traverser]==word1->string[word1_traverser_end]) ||
                                    (return_insensitive(selectables[selectable_traverser])==word1->string[word1_traverser_end])) {
                                        //selectable found
                                        word1_traverser_end++;
                                        selectable_in_here=true;
                                        break;
                                    }
                                }
                                if(selectable_in_here==true) {
                                    while((word1->string[word1_traverser_end]==selectables[selectable_traverser]) ||
                                    (return_insensitive(selectables[selectable_traverser])==word1->string[word1_traverser_end]) ) {
                                        word1_traverser_end++;
                                    }
                                }
                            }
                            else {
                                for(selectable_traverser=0;selectable_traverser<selectable_counter;selectable_traverser++) {
                                    if(selectables[selectable_traverser]==word1->string[word1_traverser_end]) {
                                        //selectable found
                                        word1_traverser_end++;
                                        selectable_in_here=true;
                                        break;
                                    }
                                }
                                if(selectable_in_here==true) {
                                    while(word1->string[word1_traverser_end]==selectables[selectable_traverser]) {
                                        word1_traverser_end++;
                                    }
                                }
                            }
                        }
                        else {
                            for(selectable_traverser=0;selectable_traverser<selectable_counter;selectable_traverser++) {
                                if(selectables[selectable_traverser]==word1->string[word1_traverser_end]) {
                                    //selectable found
                                    word1_traverser_end++;
                                    selectable_in_here=true;
                                    break;
                                }
                            }
                            //selectable_counter=0;
                            if(selectable_in_here==true) {
                                first_word_traverser++;
                            }
                            else {
                                continue_machine=false;
                                break;
                            }
                        }                        
                    }
                    else {
                        if(case_sensitive==false) {
                            if(first_word[first_word_traverser]>=_zero && first_word[first_word_traverser]<=_nine) {
                                //this is a digit dont need to take insensitive of it

                                if(first_word[first_word_traverser+1]=='*') {
                                    while(word1->string[word1_traverser_end]==first_word[first_word_traverser]) {
                                        word1_traverser_end++;
                                    }
                                    first_word_traverser+=2;
                                }
                                else {
                                    if(word1->string[word1_traverser_end]!=first_word[first_word_traverser]) {
                                        continue_machine=false;
                                        break;
                                    }
                                    else {
                                        first_word_traverser++;
                                        word1_traverser_end++;
                                        continue_machine=true;
                                    } 
                                }                               
                            }
                            else {

                                if(first_word[first_word_traverser+1]=='*') {
                                    while((word1->string[word1_traverser_end]==first_word[first_word_traverser])
                                    || (return_insensitive(first_word[first_word_traverser])==word1->string[word1_traverser_end])) {          
                                        word1_traverser_end++;
                                    }
                                    first_word_traverser+=2;
                                }
                                else {
                                    if(word1->string[word1_traverser_end]==first_word[first_word_traverser] || word1->string[word1_traverser_end]==return_insensitive(first_word[first_word_traverser])) {
                                        first_word_traverser++;
                                        word1_traverser_end++;
                                        continue_machine=true;  
                                    }
                                    else {
                                        continue_machine=false;
                                        break;                            
                                    }
                                }

                            }
                        }
                        else {
                            if(first_word[first_word_traverser+1]=='*') {
                                while(word1->string[word1_traverser_end]==first_word[first_word_traverser]) {  
                                    word1_traverser_end++;
                                }
                                first_word_traverser+=2;                                
                            }
                            else {
                                if(word1->string[word1_traverser_end]!=first_word[first_word_traverser]) {
                                    continue_machine=false;
                                    break;
                                }
                                else {
                                    first_word_traverser++;
                                    word1_traverser_end++;
                                    continue_machine=true;
                                }
                            }

                        }

                    }
                }

                if(continue_machine!=true) {
                    break;
                }
                if(match_found==true) {
                    switch_word=true;
                    break;
                }
            }
            //increment the word1_traverser
            if(startline==true && word1_traverser==0 && switch_word==false) {
                break;
            }
            word1_traverser++;
        }
        if(switch_word==true) {
            for(match_situation_traverser=0;match_situation_traverser<match_situation_counter;match_situation_traverser++) {
                int lenword=strlen(word1->string);
                char tempword[lenword];
                strcpy(tempword,word1->string);  
                word1->string=NULL;
                word1->string=(char*)malloc(sizeof(100));
                int i=0;
                for(i=0;i<=matches[match_situation_traverser].start_index;i++) {
                    word1->string[i]=tempword[i];
                }
                int k=0;
                for(i=matches[match_situation_traverser].start_index;i<matches[match_situation_traverser].start_index+second_word_counter;i++) {
                    word1->string[i]=second_word[k];
                    k++;
                }
                k=0;
                for(i=matches[match_situation_traverser].end_index;i<lenword;i++) {
                    word1->string[k+matches[match_situation_traverser].start_index+second_word_counter]=tempword[i];
                    k++;
                }
                if(match_situation_counter>0) {
                    matches[match_situation_traverser+1].start_index+=(strlen(second_word)-(matches[match_situation_traverser].end_index-matches[match_situation_traverser].start_index));
                    matches[match_situation_traverser+1].end_index+=(strlen(second_word)-(matches[match_situation_traverser].end_index-matches[match_situation_traverser].start_index));
                }
            }
        }
        free(matches);
    }
}
      
int do_matching(const char*pathname,char* first_word,char* second_word,int first_word_counter,int second_word_counter,match_case* m,char* match_command) {


    struct flock lock;
    int fd=open(pathname,READ_FLAGS);

    if(fd==-1) {
        perror("Error:");
        exit(-1);
    }
    //lock
    memset(&lock,0,sizeof(lock));
    lock.l_type=F_WRLCK;  
    int result_of_fcntl=fcntl(fd,F_SETLKW,&lock);

    if(result_of_fcntl==-1) {
        close(fd);
        perror("Error:");
        exit(-1);
    }
    char* buffer=(char*)malloc(sizeof(char)*BLKSIZE);
    if(buffer==NULL) {
        close(fd);
        perror("Error:");
        lock.l_type=F_UNLCK;
        result_of_fcntl=fcntl(fd,F_SETLKW,&lock); 
        exit(-1);       
    }
    size_t bytes_read;
    while(1) {
        bytes_read=read(fd,buffer,BLKSIZE);
        if(bytes_read==sizeof(buffer)) {
            //buffer is full
            break;
        }
        else if(bytes_read==0) {
            //end of file reached
            break;
        }
        else if(bytes_read==-1) {
            lock.l_type=F_UNLCK;
            result_of_fcntl=fcntl(fd,F_SETLKW,&lock);
            close(fd);
            perror("Error:");
            return -1;
        }
    }

    //unlock
    lock.l_type=F_UNLCK;
    result_of_fcntl=fcntl(fd,F_SETLKW,&lock);

    close(fd);

    int size_of_buffer=strlen(buffer);
    word* words=(word*)malloc(sizeof(word)*BLKSIZE);
    if(words==NULL) {
        perror("Error:");
        exit(-1);
    }
    int i=0;
    for(i=0;i<BLKSIZE;i++) {
        words[i].string=(char*)malloc(sizeof(char)*BLKSIZE);
        words[i].at_end_of_line=false;
        words[i].at_start_of_the_line=false;
        if(words[i].string==NULL) {
            perror("Error:");
            return -1;
        }
    }
    i=0;
    int word_counter=0;
    int letter_counter=0;
    while(i<=size_of_buffer) {
        if(i==0) {
            words[word_counter].at_start_of_the_line=true;
        }
        if(buffer[i]=='\n') {
            words[word_counter].string[letter_counter]='\0';
            words[word_counter].at_end_of_line=true;
            word_counter++;
            if(buffer[i+1]>0) {
                words[word_counter].at_start_of_the_line=true;
            }
            letter_counter=0;
        }
        else if(buffer[i]==' ') {
            words[word_counter].at_end_of_line=false;            
            words[word_counter].string[letter_counter]='\0';
            word_counter++;
            letter_counter=0;
        }
        else {
            words[word_counter].string[letter_counter]=buffer[i];
            letter_counter++;
        }
        i++;
    }

    int k=0;
    printf("\n----WORDS----\n");
    for(i=0;i<word_counter;i++) {
        printf("%d)-",i+1);
        for(k=0;words[i].string[k]!='\0';k++) {
            printf("%c",words[i].string[k]);
        }
        printf("\n");
    }   
    printf("----\n");
 
    i=0;
    for(i=0;i<word_counter;i++) {
        traverse(&words[i],first_word,second_word,first_word_counter,second_word_counter,m->end_line,m->start_line,m->case_sensitive);
    }  
    printf("\n----CHANGED WORDS----\n");
    for(i=0;i<word_counter;i++) {
        printf("%d)-",i+1);
        for(k=0;words[i].string[k]!='\0';k++) {
            printf("%c",words[i].string[k]);
        }
        printf("\n");
    }   

    int fd2=open(pathname,WRITE_FLAGS);
    if(fd2==-1) {
        perror("Error:");
        exit(-1);
    }

    //lock
    memset(&lock,0,sizeof(lock));
    lock.l_type=F_WRLCK;  
    result_of_fcntl=fcntl(fd2,F_SETLKW,&lock);

    if(result_of_fcntl==-1) {
        perror("Error:");
        close(fd2);
        exit(-1);
    }

    for(i=0;i<word_counter;i++) {
        size_t length=strlen(words[i].string);
        int write_ret=write(fd2,words[i].string,length);
        if(write_ret==-1) {
            perror("Error: ");
            close(fd2);
            lock.l_type=F_UNLCK;
            result_of_fcntl=fcntl(fd2,F_SETLKW,&lock);
            exit(-1);
        }
        else if(words[i].at_end_of_line==true) {
            write_ret=write(fd2,"\n",1);
        }
        else {
            write_ret=write(fd2," ",1);            
        }
        if(write_ret==-1) {
            perror("Error: ");
            close(fd2);
            lock.l_type=F_UNLCK;
            result_of_fcntl=fcntl(fd2,F_SETLKW,&lock);
            exit(-1);
        }
    }    
    printf("\n");

    //unlock
    lock.l_type=F_UNLCK;
    result_of_fcntl=fcntl(fd2,F_SETLKW,&lock);
    close(fd2);
    for(i=0;i<BLKSIZE;i++) {
        free(words[i].string);
    }
    free(words);
    free(buffer);
    return 0;
}
int seperate_slashes(int length_of_input,char* match_command,const char* pathname,match_case* m) {
    char* first_word=(char*)malloc(sizeof(char)*length_of_input);
    if(first_word==NULL) {
        perror("Error:");
        exit(-1);
    }
    char* second_word=(char*)malloc(sizeof(char)*length_of_input);
    if(second_word==NULL) {
        perror("Error:");
        exit(-1);
    }
    int i=1;
    int second_word_counter=0;
    int first_word_counter=0;

    while(match_command[i]!='/') {
        first_word[first_word_counter++]=match_command[i++];
    }
    i++;
    while(match_command[i]!='/') {
        second_word[second_word_counter++]=match_command[i++];
    }

    if(do_matching(pathname,first_word,second_word,first_word_counter,second_word_counter,m,match_command)==-1) {
        perror("Error:");
        exit(-1);
    }
    free(first_word);
    free(second_word);
    return 0;
}

int main(int argc, char const *argv[]) {
    //argument number is less than 3
    if (argc!=3) {
        print_usage_and_exit();
    }
    int length_of_input=strlen(argv[1]);
    const char* match_command=argv[1];
    const char* pathname=argv[2];



    if(strstr(match_command,";")==NULL) {
        //only 1 match
        match_case* m=(match_case*)malloc(sizeof(match_case));
        if(m==NULL) {
            perror("Error:");
            exit(-1);
        }
        int input_valid=check_input_validity(match_command);
        if(input_valid==0) {
            printf("%s is valid\n",match_command);
        }
        else {
            print_usage_and_exit();
        }
        determine_cases(match_command,m);
        char* copy_of_match_command=(char*)malloc(sizeof(char)*strlen(match_command));
        strcpy(copy_of_match_command,match_command);
        int res=seperate_slashes(length_of_input,copy_of_match_command,pathname,m);
        if(res==-1) {
            perror("Error: ");
            exit(-1);
        }
        free(m);
        free(copy_of_match_command);
    }
    else {
        //more than 1 match
        int i=0;
        char** inputs=(char**)malloc(length_of_input*sizeof(char*));
        if(inputs==NULL) {
            perror("Error:");
            exit(-1);
        }
        for(i=0;i<length_of_input;i++) {
            inputs[i]=malloc(sizeof(char)*length_of_input);
            if(inputs[i]==NULL) {
                perror("Error:");
                exit(-1);
            }
        }
        i=0;
        int match_counter=0;
        const char token[2]=";";
        char* first_token;
        char* copy_of_match_command=(char*)malloc(sizeof(char)*strlen(match_command));
        strcpy(copy_of_match_command,match_command);
        first_token=strtok(copy_of_match_command,token);
        while(first_token!=NULL) {
            int input_valid=check_input_validity(first_token);
            if(input_valid==0) {
                printf("%s is valid\n",first_token);
            }
            else {
                print_usage_and_exit();
            }
            inputs[match_counter++]=first_token;
            first_token=strtok(NULL,token);
        }

        match_case* m=(match_case*)malloc(sizeof(match_case)*match_counter);
        if(m==NULL) {
            perror("Error:");
            exit(-1);
        }
        i=0;
        for(i=0;i<match_counter;i++) {
            determine_cases(inputs[i],&m[i]);
            int res=seperate_slashes(strlen(inputs[i]),inputs[i],pathname,&m[i]);
            if(res==-1) {
                perror("Error: ");
                exit(-1);
            }
        }
        free(m); 
        //when I uncomment that, it gives seg fault
        /*for(i=0;i<length_of_input;i++) {
            free(inputs[i]);
        }*/
        free(inputs); 
        free(copy_of_match_command); 

    }
    return 0;
}
