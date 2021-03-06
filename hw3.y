%{

    #include "semantics.h"
    #include "IOMngr.h"
    #include <string.h>

    extern int yylex();
    extern char* yytext;
    extern int yyleng;
    extern int yyerror(char*);

    extern SymTab* table;
    extern SymEntry* entry;

%}

%union 
{
    void* symtab;
    char* string;
}

%type <string> Id
%type <symtab> Expr
%type <symtab> Term
%type <symtab> Factor

%token Ident
%token Set

%%

    Prog        : StmtSeq           {printSymTab();}
    StmtSeq     : Stmt StmtSeq      {};
    StmtSeq     :                   {};
    Stmt        : Id '=' Expr ';'   {storeVar($1,$3);};
    Expr        : Expr '+' Term     {$$ = doUnion($1, $3);};
    Expr        : Term              {$$ = $1;};
    Term        : Term '*' Factor   {$$ = doIntersect($1, $3);};
    Term        : Factor            {$$ = $1;};
    Factor      : '(' Expr ')'      {$$ = $2;};
    Factor      : Id                {$$ = getVal($1);};
    Factor      : Set               {$$ = newSet(strdup(yytext));};
    Id          : Ident             {$$ = strdup(yytext);};

%%

int yyerror(char *s) 
{
    writeIndicator(getCurrentColumnNum());
    writeMessage("Illegal Character in YACC");
    return 1;
}