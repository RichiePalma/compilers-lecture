%{
 
#include <stdio.h>
#include "y.tab.h"
int c;
extern int yylval;
/*
S -> aBc
B -> bc | b
*/
%}
%%
a   {
    return(TA);
    }
b   {
    return(TB);
    }
c   {
    return(TC);
    }
c$  {
    return(TCE);
    }
.   {
    return 0;
    }
%%
