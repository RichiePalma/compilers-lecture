%{
    #include <stdio.h>
    FILE *yyin;
%}
%%
[0-9]+  {printf("inum");}
[0-9]+\.[0-9]+ {printf("fnum");}
f   {printf("floatdlc");}
i   {printf("intdlc");}
p   {printf("print");}
[a-eg-hj-oq-z]+ {printf("id");}
= {printf("assign");}
\+ {printf("plus");}
\- {printf("minus");}
\/{1} {printf("div");}
\/{2}.* ;
\* {printf("times");}
%%

void main(int argc,char **argv){
    yyin = fopen(argv[1],"r");
    yylex();
    fclose(yyin);
}