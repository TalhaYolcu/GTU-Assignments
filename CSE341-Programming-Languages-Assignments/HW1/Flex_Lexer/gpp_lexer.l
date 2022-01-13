%{
int flag = 0;
FILE *output_file;
%}

/*These are regular expressions.*/
COMMENT ";;".*
VALUE [1-9][0-9]*|"0"
IDENTIFIER  [a-zA-Z][a-zA-Z0-9]*
ERROR  [0-9][a-zA-Z0-9]*
EXIT "\n\n"

%%

"and" { fprintf(output_file, "KW_AND\n");}
"or" { fprintf(output_file, "KW_OR\n");}
"not" { fprintf(output_file, "KW_NOT\n");}
"equal" { fprintf(output_file, "KW_EQUAL\n");} 
"less" { fprintf(output_file, "KW_LESS\n");}
"nil" { fprintf(output_file, "KW_NIL\n");}
"list" { fprintf(output_file, "KW_LIST\n");}
"append" { fprintf(output_file, "KW_APPEND\n");}
"concat" { fprintf(output_file, "KW_CONCAT\n");}
"set" { fprintf(output_file, "KW_SET\n");}
"deffun" { fprintf(output_file, "KW_DEFFUN\n");}
"for" { fprintf(output_file, "KW_FOR\n");}
"if" { fprintf(output_file, "KW_IF\n");}
"exit" { fprintf(output_file, "KW_EXIT\n"); return 0;}
"load" { fprintf(output_file, "KW_LOAD\n");}
"disp" { fprintf(output_file, "KW_DISP\n");}
"true" { fprintf(output_file, "KW_TRUE\n");}
"false" { fprintf(output_file, "KW_FALSE\n");}

"+" { fprintf(output_file, "OP_PLUS\n");}
"-" { fprintf(output_file, "OP_MINUS\n");}
"/" { fprintf(output_file, "OP_DIV\n");}
"*" { fprintf(output_file, "OP_MULT\n");}
"(" { fprintf(output_file, "OP_OP\n");}
")" { fprintf(output_file, "OP_CP\n");} 
"**" { fprintf(output_file, "OP_DBLMULT\n");}
"," { fprintf(output_file, "OP_COMMA\n");}

" \" " {    
            if(flag==0) //if flag is 0 then  operator is OC
            {
                fprintf(stdout, "OP_OC\n");
                flag=1;
            }             
            else{  //if flag is 1 operator is CC
                fprintf(stdout, "OP_CC\n");
                flag=0;
            }  
        }



{COMMENT} {fprintf (output_file,"COMMENT\n");}
{VALUE} { fprintf(output_file, "VALUE\n");}
{IDENTIFIER} {fprintf(output_file, "IDENTIFIER\n");}
{ERROR} {fprintf(output_file, "ERROR\n");}
{EXIT} {printf("EXITING...\n");
        fprintf(output_file, "EXITING...\n");
        return 0;}



"\n"|"\t"|" " { }

. { 
    fprintf (output_file,"SYNTAX ERROR %s cannot be tokenized \n",yytext); 
    } 


%%

int yywrap(){
    //intentionally empty
} 

int main(int argc , char** argv){ 
    char my_file[40];
    FILE *fpointer; 
    output_file = fopen("my_parsed_c.txt", "w");

    if (argc < 2){  

        yyin = stdin; 
        yylex();
    }      
    else{  

        fpointer = fopen(argv[1],"r");  
        yyin = fpointer; 
        yylex(); 
    }    
}
