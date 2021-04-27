%{
    #include "IOMngr.h"
    #include "y.tab.h"

    #define YY_INPUT(buf,result,max_size) \
    { int c = getNextSourceChar(); \
    result = (c == EOF) ? YY_NULL : (buf[0] = c, 1); \
    }

%}

letter [A-Za-Z]
digit [0-9]

%%

letter(letter|digit)*     {return Ident;}
[\{](letter[\,])*(letter)?[\}]    {return Set;}
\+                              {return '+';}
\*                              {return '*';}
\=                              {return '=';}
\(                              {return '(';}
\)                              {return ')';}
\;                              {return ';';}
[ ]                             {}
\t                              {}
\r                              {}
\n                              {}
.                               {
                                    writeIndicator(getCurrentColumnNum());
                                    writeMessage("Illegal Character in lex");
                                }

%%

int yywrap() 
{
    return 1;
}