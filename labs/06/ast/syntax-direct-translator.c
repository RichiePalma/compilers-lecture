#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LINE_LENGTH 255

/***************************
Grammar:
    E ->  int | ( E ) | E + E | E - E | E * E

Example:
    5 + (2 - 3)
    5 + (2 * (2+4))
    (3+1)

***************************/

char l;
char line[LINE_LENGTH];
char graphviz[LINE_LENGTH];
char epsilon = '\n';
FILE *fp;
int i;

bool E();
bool E_1();
bool E_2();

bool A();
bool A_1();
bool A_2();

bool B();
bool B_1();
bool B_2();

bool C();
bool C_1();
bool C_2();
bool match(char t)
{
    if (l == t)
    {
        switch (l)
        {
        case '+':
            printf("add ");
            break;
        case '-':
            printf("sub ");
            break;
        case '*':
            printf("mul ");
            break;
        case '/':
            printf("div ");
            break;
        case ')':
            printf("acum\n");
            break;
        case '(':
            printf("&acum\n");
            break;
        case '\n':
            //printf("acum\n");
            break;
        default:
            printf("%c,",l);
            break;
        }
        i++;
        l = line[i];
        return true;
    }
    return false;
}

//E -> int A B C | (E) A B C
bool E(){
        if(E_1() || E_2()){
            return true;
        }
}

//E -> int A B C
bool E_1(){
    if(isdigit(l)){
        //printf("%c ",l);
        if(match(l) && A() && B() && C()){
            return true;
        }
    }
}

// E -> (E) A B C
bool E_2(){
    if(l == '('){
        //printf(",acum ");
        if(match('(') && E() && match(')') && A() && B() && C()){
            return true;
        }
    }
}

// A -> +E A B C | B C
bool A(){
    if(A_1() || A_2()){
        return true;
    }
}

// A -> +E A B C
bool A_1(){
    //printf("add ");
    if(match('+') && E() && A() && B() && C()){
        return true;
    }
}

// A -> BC
bool A_2(){
    if(B() && C()){
        return true;
    }
}

// B -> -E A B C | C
bool B(){
    if(B_1() || B_2()){
        return true;
    }
}

// B -> -E A B C
bool B_1(){
    if(l == '-'){
        //printf("sub ");
        if(match('-') && E() && A() && B() && C()){
            return true;
        }
    }
}

// B -> C
bool B_2(){
    if(C()){
        return true;
    }
}

// C -> *E A B C | epsilon
bool C(){
    if(C_1() || C_2()){
        return true;
    }
}

// C -> *E A B C
bool C_1(){
    if(l == '*'){
        if(match('*') && E() && A() && B() && C()){
            return true;
        }
    }
}

// C -> epsilon
bool C_2(){
    if(l == epsilon){
        return true;
    }
}

// https://stackoverflow.com/questions/1726302/removing-spaces-from-a-string-in-c
void remove_spaces(char* s) {
    const char* d = s;
    do {
        while (*d == ' ') {
            ++d;
        }
    } while (*s++ = *d++);
}

int main()
{

    fp = fopen("codefile.txt", "r");
    while (fgets(line, LINE_LENGTH, fp))
    {
        i = 0;
        remove_spaces(line);
        do
        {
            l = line[i];
            // E is a start symbol.
            if (E())
            {
                printf("\nParsing Successful: %s", line);
                break;
            }
            else
            {
                printf("\nError %s", line);
                break;
            }
        } while (l != '\n' && l != EOF);
    }

    printf("\n");
    fclose(fp);
}