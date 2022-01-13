%{
#include <stdio.h>
#include <string.h>
#include "gpp_interpreter.h"
extern FILE *yyin;
typedef struct yy_buffer_state * YY_BUFFER_STATE;
extern int yyparse();
extern YY_BUFFER_STATE yy_scan_string(char * str);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);

/*needed functions to handle things*/
void print_array(int*);
int* concat_array(int*, int*);
int* append_array(int*, int);
int power_function(int, int);
int error=0;

%}
/*union for identifier*/
%union{
    char id[20];
    int ival;
    int *ivals;
    char*string;
}

/*start symbol and tokens*/
%start INPUT
%token COMMENT OP_PLUS OP_MINUS OP_DIV OP_MULT OP_OP OP_CP OP_DBLMULT OP_OC OP_TR OP_COMMA KW_AND KW_OR KW_NOT KW_EQUAL KW_LESS
KW_NIL KW_LIST KW_APPEND KW_CONCAT KW_SET KW_DEFFUN KW_FOR KW_WHILE KW_IF KW_EXIT
KW_LOAD KW_DISP KW_TRUE KW_FALSE NEWLINE KW_DEFVAR

/*attribitued tokens*/
%token <ival> VALUE
%token <id> ID
%token <string> STRING

/*attributed symbols*/
%type <ival> INPUT
%type <ival> EXPI
%type <ival> EXPB
%type <ivals> VALUES
%type <ivals> EXPLISTI
%type <ivals> LISTVALUE
%type <ivals> IDLIST

%%


INPUT:
    EXPI { $$=$1; if(error==-1) {printf("SYNTAX ERROR\n");} else { printf("SYNTAX OK. \nResult = %d\n", $1);} error=0; }    /*INPUT -> EXPI*/
    |
    EXPLISTI {if(error==-1) {printf("SYNTAX ERROR\n");} else {if($1!=NULL) {printf("SYNTAX OK. \nResult = \n"); print_array($1);} } error=0;  }   /*INPUT -> EXPLISTI */
    |
    EXPB  {if(error==-1) {printf("SYNTAX ERROR\n");} else {printf("SYNTAX OK. \nResult = %d\n", $1);} error=0; } /*INPUT *> EXPB */
    |
    COMMENT{printf("SYNTAX OK. COMMENT\n");}    /*INPUT -> COMMENT */
    |
    OP_OP KW_EXIT OP_CP {$$ = 0; printf("EXITING\n"); exit(0);}     /*INPUT -> (exit) */
    ;

EXPI:
    OP_OP OP_PLUS EXPI EXPI OP_CP  {$$=$3+$4;} /* (+ EXPI EXPI) */
    |
    OP_OP OP_MINUS EXPI EXPI OP_CP {$$=$3-$4;} /* (- EXPI EXPI) */
    |
    OP_OP OP_MULT EXPI EXPI OP_CP  {$$=$3*$4;} /* (* EXPI EXPI) */
    |
    OP_OP OP_DIV EXPI EXPI OP_CP   {$$=$3/$4;} /* (/ EXPI EXPI) */
    |
    OP_OP OP_DBLMULT EXPI EXPI OP_CP {$$ = power_function($3, $4);}   /*(** EXPI EXPI) */
    |
    ID {$$ = get_entry($1);}    /*ID*/
    |
    VALUE {$$ = $1;}    /*VALUE*/
    |
    OP_OP KW_SET ID EXPI OP_CP {put_entry($3, $4); $$ = $4; }/* (set Id EXPI) */
    |
    OP_OP KW_IF EXPB EXPI OP_CP {$$ = (1 == $3) ? $4: 0;} /* (if EXPB EXPI) */
    |
    OP_OP KW_FOR OP_OP ID EXPI EXPI OP_CP EXPLISTI OP_CP{print_array($8); $$=get_entry($4);} /* (for (Id EXPI EXPI) EXPLISTI)*/
    |
    OP_OP KW_IF EXPB EXPI EXPI OP_CP {$$ = (1 == $3) ? $4: $5;} /* (if EXPB EXPI EXPI) */
    |
    OP_OP KW_DISP EXPI OP_CP { $$ = $3; printf("Print: %d\n", $3);} /*(disp EXPI)*/
    |
    OP_OP ID EXPLISTI OP_CP {  print_array($3);} /*(ID EXPLISTI) */
    |
    OP_OP KW_DEFFUN ID OP_OP IDLIST OP_CP EXPLISTI OP_CP {print_array($7); $$=get_entry($3);} /*(DEFFUN ID IDLIST EXPLISTI) function definition*/
    |
    OP_OP KW_IF EXPB EXPLISTI OP_CP {if(1==$3) {print_array($4);$$=1;}else {$$=0;}} /*(IF EXPB EXPLISTI)*/
    |
    OP_OP KW_IF EXPB EXPLISTI EXPLISTI OP_CP {if(1==$3) {print_array($4);$$=1;}else {print_array($5); $$=0;}} /*(IF EXPB EXPLISTI)*/
    |
    OP_OP KW_WHILE OP_OP EXPB OP_CP EXPLISTI OP_CP {$$=0; if (1==$4) {print_array($6); $$=1;}} /*(WHILE (EXPB) EXPLISTI)*/
    |
    OP_OP KW_DEFVAR ID EXPI OP_CP {if(search_entry($3,$4)>0) {printf("SYNTAX ERROR, CANT DECLARE THIS VARIABLE AGAIN\n"); error=-1;} else {$$ = $4; put_entry($3,$4);} } /*(defvar ID EXPI) defining a variable*/ 
    |
    OP_OP KW_LOAD STRING OP_CP   /*(load "helloworld.g++")*/{
        int i=0;
        char*temp=$3;
        /*find size of name*/
        while(temp[i]!='\0') {
            i++;
        }
        char*temp2=(char*)malloc(sizeof(char)*i);
        int k=0;
        int z=0;
        /*remove "" 's */
        for(k=0;k<i;k++) {
            if(temp[k]!='\"') {
                temp2[z]=temp[k];
                z++;
            }
        }
        FILE* fp2 = fopen(temp2, "r");
        if(fp2 == NULL) {
            printf("A file with name %s does not exist\n",temp2); $$=0; 
        }

		else{
            /*open file and read input*/
			printf("Loaded file %s\n", temp2);
            FILE*fp4=fopen(temp2,"r");
            $$=0;
            FILE* current_state = yyin;
            while(!feof(fp4)) {
                char line[128];
                fgets(line, sizeof(line), fp4);
                printf(">%s\n",line);
                YY_BUFFER_STATE buffer = yy_scan_string(line);
                $$=yyparse();
                yy_delete_buffer(buffer);
            }
            fclose(fp2);
            fclose(fp4);
            yyin=current_state;
		}
    }   
    ;

EXPB:
    OP_OP KW_AND EXPB EXPB OP_CP {$$ = $3 && $4;}   /* (and EXPB EXPB) */
    |
    OP_OP KW_OR EXPB EXPB OP_CP  {$$ = $3 || $4;}    /* (or EXPB EXPB) */
    |
    OP_OP KW_NOT EXPB OP_CP  {$$ = ! ($3);}      /* (not EXPB) */
    |
    OP_OP KW_EQUAL EXPI EXPI OP_CP {$$ = ($3 == $4);}  /* (equal EXPI EXPI) */  
    |  
    OP_OP KW_EQUAL EXPB EXPB OP_CP {$$ = ($3 == $4);}  /* (equal EXPB EXPB) */
    |
    OP_OP KW_LESS EXPI EXPI OP_CP { $$ = $3 < $4; } /* (less EXPI EXPI) */
    |
    KW_TRUE  { $$ = 1; }   /* true */
    |
    KW_FALSE   { $$ = 0; } /* false */
    | 
    OP_OP KW_DISP EXPB OP_CP { $$ = $3; printf("Print: %s\n", ($3 ? "true":"false"));} /*EXPI -> (disp EXPB) */
    ;

EXPLISTI:
    OP_OP KW_CONCAT OP_TR EXPLISTI OP_TR EXPLISTI OP_CP {$$ = concat_array($4, $6);} /*EXPLISTI -> (concat 'EXPLISTI 'EXPLISTI) */
    |
    OP_OP KW_APPEND EXPI OP_TR EXPLISTI OP_CP {$$ = append_array($5, $3);} /*EXPLISTI -> (append EXPI 'EXPLISTI) */
    |
    OP_TR OP_OP KW_LIST VALUES OP_CP {$$ = $4;} /*EXPLISTI ->  '(list VALUES) */
    |
    LISTVALUE  {$$ = $1;} /*EXPLISTI ->  LISTVALUE */
    |
    OP_OP KW_DISP LISTVALUE OP_CP { if($3==NULL) {printf("NULL\n"); $$=$3;} else {$$ = $3; printf("Print: "); print_array($3);} } /*EXPLISTI -> (disp LISTVALUE) */
    |
    OP_TR OP_OP VALUES OP_CP {$$ = $3;} /*EXPLISTI -> '(VALUES) */
    ;
    

LISTVALUE:  /* LISTVALUE -> '( VALUES ) | '() | nil */
    OP_OP VALUES OP_CP {$$ = $2;} /*LISTVALUE -> '( VALUES )*/
    |
    OP_OP OP_CP { $$= NULL; } /*LISTVALUE -> '()*/
    |
    KW_NIL { $$ = NULL;} /*LISTVALUE -> nil*/
    ;

VALUES:
    VALUES VALUE  {$$ = append_array($1, $2);} /*VALUES -> VALUES VALUE*/
    |
    VALUE {$$ = NULL; $$ = append_array($$, $1);} /*VALUES -> VALUE */
    ;
IDLIST: /*IDLIST -> (ID IDLIST) | ID */
    IDLIST ID {}
    |
    ID {}
    ;


%%

/*WHEN SYNTAX ERROR IS COME */
int yyerror(char *s) {
    fprintf(stderr, "SYNTAX ERROR. \n");
}

/*prints the given array*/
void print_array(int*arr) {
    int i=0;
    for(i=0;arr[i]!=-1;i++) {
        printf("%d ",arr[i]);
    }
    printf("\n");
}

/*concatanates the given 2 array*/
int* concat_array(int*arr1, int*arr2) {
    int size1=0, size2=0;

    int *temp = arr1;
    if(temp!=NULL) {
        while(*temp != -1){
            size1++;
            temp++;
        }
    }

    
    printf("%d\n", size1);

    temp = arr2;
    if(temp!=NULL) {
        while(*temp != -1){
            size2++;
            temp++;
        }
    }


    printf("%d\n", size1+size2);

    temp = (int *) malloc(sizeof(int) * (size1 + size2) + 2);

    int i=0;
    for(i;i<size1;++i) // copy arr1.
        temp[i] = arr1[i];
    
    int j=0;
    for(j;j<size2; ++j) // copy arr2.
        temp[i++] = arr2[j]; 

    temp[i] = -1;
    free(arr1);
    free(arr2);
    return temp;    
}

/*appends sth to array*/
int* append_array(int*arr, int num) {
    if(arr == NULL){ // create new arr.
        arr = (int *)malloc(sizeof(int)*2);
        arr[0] = num;
        arr[1] = -1;
    } 
    else{ // expand the old arr.
        int *temp = arr;
        int size = 0;

        while(*temp != -1){
            ++temp;
            ++size;
        }

        temp = arr;
        arr = (int*)(malloc(sizeof(int)*(size+2)));

        int i=0;
        for(i;i<size;++i)
            arr[i] = temp[i]; // copy old array.
        arr[i] = num; // add the item.
        arr[i+1] = -1; // new size.
        free(temp);
    } 

    return arr;    
}
/*my own power function*/
int power_function(int a, int b) {
    int i=0;
    if(b==0) {
        return 1;
    }
    else if(b==1) {
        return a;
    }
    else {
        int result=1;
        for(i=0;i<b;i++) {
            result=result*a;
        }
        return result;
    }
}
/*needed gpp interpreter function this function select reading input from terminal or read input from file*/
void gpp_interpreter() {
	FILE *fp;
	char *filename,*st;
    int i=0;
    int k=0;
	
	filename = (char*) malloc(sizeof(char));
	st = (char*) malloc(sizeof(char));

	scanf("%c",&st[i]);//get the command if the interprter takes the code from terminal of from file. 
	
    /*scan the g++*/
	while(st[i] !='\n'){
		if(st[i] != ' ' && st[i] != '$' && st[i] != 'g' && st[i] != '+'){
			filename[k] = st[i];
			k++;
		}
		i++;
		scanf("%c",&st[i]);
	}
    /*read from terminal*/
    if(st[4] =='\n'){//if interpreter takes input from terminal
        printf(">>");
        yyin=stdin;
        while(yyparse()==0) {}
		
	}
	else{//input from .txt files
		FILE*fp2;
        fp2=fopen(filename,"r");
		fp=fopen(filename,"r");
        yyin=fp;
        while(yyparse()==0) {
            char line[128];
            fgets(line, sizeof(line), fp2);
            printf(">%s\n",line);
        }
        fclose(fp);
        fclose(fp2);
	}

}
int main(int argc, char **argv)
{
    ++argv, --argc;
    init_table();
    gpp_interpreter();	
    return 0;
}

