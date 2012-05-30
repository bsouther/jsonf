#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*  Globals */
int  level = -1; 
int  last  = -1;
bool instr = false;
bool inesc = false;

/* Handles each character in the stream */
void process_char(int c){

    /* escape */
    if(instr && c == '\\'){
        if(inesc){
            inesc = false;
            printf("%c",c);
            last = c;
            return;
        }else{
            inesc = true;
            printf("%c",c);
            last = c;
            return;
        }
    }// \


    if(inesc){
        inesc = false;
        if('"' == c){
            printf("\"");
            last = '1';
            return;
        }
    }else{
        /* Ignore white space if not in string */
        if(!instr){
            if(' ' == c || '\t' == c || '\r' == c || '\n' == c){
                return;
            }
        }

        /* quote */
        if(last =='"'){
            instr = !instr;
        }
        
        if(!instr){

            if(last == '{' || last == '['){
                level++;
                printf("\n");
                padLine();
            }else if(last == ','){
                printf("\n");
                padLine();
            }

            if(c == '}' || c == ']'){
                if(level > 0){
                    level--;
                }
                printf("\n");
                padLine();
            }else if(c == '{' || c == '['){
                if(last != ',' && last != '[' && last != '{'){
                    printf("\n");
                    padLine();
                }
            }
        }//!instr
    }//insec


    printf("%c", c);
    last = c;
}//process


int padLine(){
    int lvl = level;
    int i = 0;
    int padlen = 4;
    lvl = lvl * padlen;
    for(; i < lvl; i++){
        printf(" ");
    }
}


/* The entry point for the program */
int main(int argc, char *argv[]){

    int c;
    level = 0;
    c     = -1;
    instr = 0;
    inesc = 0;
    last  = -1;

    if(2 == argc){
        /* Work from a file */
        FILE *fp;
        fp = fopen(argv[1], "r");

        if(NULL == fp){
            printf("Unable to open file: %s\n", argv[1]);
            return 1;
        }

        while((c = fgetc(fp)) != EOF){
           process_char(c);
        }
        fclose(fp);
    }else{
        /* Work from stdin */
        while((c = getc(stdin)) != EOF){
            process_char(c);
        } 
    }
    printf("\n");
    return 0;
}//main
