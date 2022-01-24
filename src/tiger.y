%{
#include <stdio.h>
#include <ctype.h>

int yylex(void);

void yyerror(char *c);


%}

%token COMMA SEMICOLON LPARENTHESIS RPARENTHESIS LBRACKET RBRACKET 
  LBRACE RBRACE DOT 
  PLUS MINUS TIMES DIVIDE LTE GTE EQ NEQ GT LT
  AND OR ASSIGN
  ARRAY IF THEN ELSE WHILE FOR TO DO LET IN END OF 
  BREAK NIL 
  FUNCTION VAR TYPE NEW ID INTEGER COLON STRING

%%

program: exp
    | decs

exp: NIL
    | INTEGER
    | STRING

    | ID lvalue_exp OF exp
    | ID LBRACE ID_fac
    
    | NEW ID

    | lvalue

    | lvalue LPARENTHESIS call_fac

    | MINUS exp
    | exp AND exp
    | exp LTE exp
    | exp GTE exp
    | exp EQ exp
    | exp NEQ exp
    | exp GT exp
    | exp LT exp
    | exp PLUS exp
    | exp MINUS exp
    | exp TIMES exp
    | exp DIVIDE exp
    | LPARENTHESIS exp RPARENTHESIS

    | lvalue ASSIGN exp

    | IF exp THEN exp if_opc
    | WHILE exp DO exp
    | FOR ID ASSIGN exp TO exp DO exp
    | BREAK
    | LET decs IN exps END

    ID_fac: RBRACE | ID EQ exp ID_aux RBRACE
    ID_aux: | COMMA ID EQ exp ID_aux

    call_fac: RPARENTHESIS | exp call_aux
    call_aux: | COMMA exp call_aux

    if_opc: | ELSE exp

    lvalue: ID
    | lvalue DOT ID
    | lvalue lvalue_exp

    lvalue_exp: LBRACKET exp RBRACKET

    exps: | exp exps_list
    exps_list: | SEMICOLON exp

    decs: | decs dec

    dec: tydeclist
    | vardec
    | FUNCTION ID LPARENTHESIS tyfields RPARENTHESIS dec_factor

    dec_factor: COLON ID EQ exp
    | EQ exp

    tydeclist: tydec | tydec tydeclist

    tydec: TYPE ID EQ ty

    vardec: VAR ID vardec_opc

    vardec_opc: COLON ID ASSIGN exp
    | ASSIGN exp

    ty: ID
        | LBRACKET tyfields RBRACKET
        | ARRAY OF ID

    tyfields: ID COLON ID tyfields_factor | 
    tyfields_factor: tyfields_aux |
    tyfields_aux: COMMA ID COLON ID tyfields_aux_factor
    tyfields_aux_factor: tyfields_aux | 
%%

void yyerror(char *c){
    printf("Erro: %s\n", c);
}

int main(){
    yyparse();
    return 0;
}