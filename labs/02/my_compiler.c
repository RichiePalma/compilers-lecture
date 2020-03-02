#include <stdio.h>
#include <stdlib.h>

FILE cleanup(char *filename){ //Cleans up comments and text in quotes for them to be ignored
    char ch;
    char comments;
    FILE *fp, *fp2;
    
    fp = fopen(filename,"r");
    fp2 = fopen("cleaned.txt","w");

    if (fp == NULL || fp2 == NULL){
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
    }
    while((ch = fgetc(fp)) != EOF){
        if(ch == '/'){
            if(comments == '/'){ //Comment detected
                comments = 'c'; // c = comment
                while((ch = fgetc(fp)) != '\n' && (ch = fgetc(fp)) != EOF){
                    //Ignores rest of line
                }
            }
            else{
                comments = '/';
            }
        }
        else if(ch == '*' && comments == '/'){ //Entered multilinear comment
            comments = 'm'; //multilinear state
            while((ch = fgetc(fp)) != EOF){
                if(ch == '*'){
                    comments = 'l'; //need to find another '/' before breaking comment
                }
                else if(ch == '/' && comments == 'l'){
                    break; //found end of multilinear comment
                }
                else{
                    comments = 'm'; //found * but not / so we are still in multilinear state
                }
            }         
        }
        else if(ch =='"'){
            fprintf(fp2,"%c",ch);
            while((ch = fgetc(fp)) != EOF && ch != '"' && ch != '\n'){
                // Ignore text inside quotation marks
            }
            if(ch=='"'){
                fprintf(fp2,"%c",ch);
            }
        }
        else if(ch =='\''){
            fprintf(fp2,"%c",ch);
            while((ch = fgetc(fp)) != EOF && ch != '\'' && ch != '\n'){
                // Ignore text inside quotation marks
            }
            if(ch=='\''){
                fprintf(fp2,"%c",ch);
            }
        }
        else{
            if(comments == '/'){
                fprintf(fp2,"/");
            }
            comments = ' ';
            fprintf(fp2,"%c",ch);
        }
    }

    fclose(fp);
    fclose(fp2);
    return *fp2;
}

void count(){
    FILE *cleaned; 
    cleaned = fopen("cleaned.txt","r");
    int oPars = 0; //Parentheses
    int cPars = 0; 
    int oBrcks = 0; //Brackets
    int cBrcks = 0;
    int oBracs = 0; //Braces
    int cBracs = 0;
    int dQuotes = 0;
    int sQuotes = 0;
    int errors = 0;
    char ch;
    while((ch = fgetc(cleaned)) != EOF){
        switch(ch){
            case '/':
                while((ch = fgetc(cleaned)) != EOF && ch != '\n'){
                    //Ignore line with wrong comment format
                }
                printf("There is a missing /\n");
                break;
            case '(':
                oPars++;
                break;
            case ')':
                cPars++;
                break;
            case '[':
                oBrcks++;
                break;
            case ']':
                cBrcks++;
                break;
            case '{':
                oBracs++;
                break;
            case '}':
                cBracs++;
                break;
            case '"':
                dQuotes++;
                break;
            case '\'':
                sQuotes++;
                break;
        }
    }
    if(oPars>cPars){
        printf("There is a missing )\n");
        errors++;
    }
    else if(oPars<cPars){
        printf("There is a missing (\n");
        errors++;
    }
    if(oBrcks>cBrcks){
        printf("There is a missing ]\n");
        errors++;
    }
    else if(oBrcks<cBrcks){
        printf("There is a missing [\n");
        errors++;
    }
    if(oBracs>cBracs){
        printf("There is a missing }\n");
        errors++;
    }
    else if(oBracs<cBracs){
        printf("There is a missing {\n");
        errors++;
    }
    if(dQuotes%2 != 0){
        printf("There is a missing \"\n");
        errors++;
    }
    if(sQuotes%2 != 0){
        printf("There is a missing '\n");
        errors++;
    }
    if(errors == 0){
        printf("There are no errors\n");
    }
    remove("cleaned.txt");
}

int main(int argc, char **argv){
    cleanup(argv[1]);
    count();
    return 0;
}