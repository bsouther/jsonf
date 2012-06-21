#include <stdio.h>

int padLine(int level){
    int i;
    printf("\n");
    for(i=0; i < level; i++) 
        printf("    ");
}

void process_fp(FILE *fp) {

    int level=0;
    int last=-1;
    int c;
    int instr=0;
    int inesc=0;

    while ((c=fgetc(fp))!=EOF){
        if(instr && c == '\\'){    /* escape */
            inesc=!inesc;
        }else if (inesc){
            inesc = 0;
            if ('"' == c){
                printf("\"");
                last = '1';
                continue;
            }
        }else{
            if(last =='"')    
                instr=!instr;    /* quote */

            if(!instr && last==':') 
                printf(" ");

            if(!instr) {
                if (last == '{' || last == '[')    
                    padLine(++level);
                else if (last == ',')
                    padLine(level);

                if (c == '}' || c == ']') {
                    if (level > 0)
                        level--;    
                    padLine(level);
                }else if (c == '{' || c == '[') {
                    if (last != ',' && last != '[' && last != '{') 
                        padLine(level);
                }
            }
        }


        last=c;
        if (instr || !(' ' == c || '\t' == c || '\r' == c || '\n' == c)){ 
            printf("%c",c);
        }
        
        /* Should the end of the JSON document. Flush stdout */
        if(level <= 0 && (c == '}' || c == ']' )){
            fflush(stdout);
        }  
    }
}

int main(int argc, char *argv[]){
    FILE *fp = stdin;

    if (2 == argc){            /* Work from a file */
        fp = fopen(argv[1], "r");
        if (!fp){
            fprintf(stderr, "Unable to open file: %s\n", argv[1]);
            return 1;
        }
    }

    process_fp(fp);
    if (fp!=stdin) 
        fclose(fp);
    printf("\n");
    return 0;
}




















