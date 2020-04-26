#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 255

/***************************

Example:
abbbbbc
abbbb
abc
abcbcbcc
ac

Grammar:
S -> aBc
B -> bc | b

Graphiz web page: 
http://www.webgraphviz.com/
***************************/

char l;
char line[LINE_LENGTH];
char graphviz[LINE_LENGTH];
FILE *fp;
int i;

bool B();
bool B_1();
bool B_2();

void error()
{
    printf("Error\n");
    exit(-1);
}

// Match function
bool match(char t)
{
    if (l == t)
    {
        i++;
        l = line[i];
        return true;
    }
    return false;
    //error();
}

//  B -> bc | b
bool B()
{
    if (B_1() || B_2())
    {
        return true;
    }
}

// B -> b
bool B_2()
{
    if (l == 'b')
        return match('b');
    return false;
}

// B -> bc
bool B_1()
{
    if (l == 'b')
    {
        if (match('b') && match('c'))
        {
            return true;
        }
    }
    return false;
}

// S -> aBc
bool S()
{
    if (l == 'a')
    {
        if (match('a') && B() && (l == '\n' || match('c')))
        {
            return true;
        }
        return false;
    }
    else
    {
        printf("%s Error\n", line);
        return false;
        //error();
    }
}

int main()
{

    fp = fopen("tokens.txt", "r");
    while (fgets(line, LINE_LENGTH, fp))
    {
        i = 0;
        do
        {
            l = line[i];
            // S is a start symbol.

            if (S())
            {
                printf("%s Parsing Successful\n", line);
                if (strcmp(line, "abc\n") == 0)
                {
                    strcat(graphviz, "digraph G {\n");
                    strcat(graphviz, "\tS -> a\n");
                    strcat(graphviz, "\tS -> B\n");
                    strcat(graphviz, "\tB -> b\n");
                    strcat(graphviz, "\tS -> c\n");
                    strcat(graphviz, "}");
                    printf("%s\n", graphviz);
                    *graphviz = '\0';
                }
                else
                {
                    strcat(graphviz, "digraph G {\n");
                    strcat(graphviz, "\tS -> a\n");
                    strcat(graphviz, "\tS -> B\n");
                    strcat(graphviz, "\tB -> b\n");
                    strcat(graphviz, "\tB -> c\n");
                    strcat(graphviz, "\tS -> c\n");
                    strcat(graphviz, "}");
                    printf("%s\n", graphviz);
                    *graphviz = '\0';
                }
            }
            else
            {
                printf("%s Error\n", line);
                break;
            }
        } while (l != '\n' && l != EOF);
    }

    fclose(fp);
    /* if (l == '\n')
        printf("Parsing Successful\n");*/
}