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

    | typeid LBRACKET exp RBRACKET OF exp
    | typeid LBRACE typeid_fac
    
    | NEW typeid

    | lvalue

    | ID LPARENTHESIS funcall_fac

    | lvalue DOT ID LPARENTHESIS methodcall_fac

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

    typeid_fac: RBRACE | ID EQ exp typeid_aux RBRACE
    typeid_aux: | COMMA ID EQ exp typeid_aux

    methodcall_fac: RPARENTHESIS | exp methodcall_aux
    methodcall_aux: | COMMA exp methodcall_aux

    funcall_fac: RPARENTHESIS | exp funcall_aux
    funcall_aux: | COMMA exp funcall_aux

    if_opc: | ELSE exp

    lvalue: ID
    | lvalue DOT ID
    | lvalue LBRACKET exp RBRACKET


    exps: | exp exps_list
    exps_list: | SEMICOLON exp

    decs: | decs dec

    dec: tydeclist
    | vardec
    | FUNCTION ID LPARENTHESIS tyfields RPARENTHESIS dec_factor

    dec_factor: COLON typeid EQ exp
    | EQ exp

    tydeclist: tydec | tydec tydeclist

    tydec: TYPE ID EQ ty

    vardec: VAR ID vardec_opc

    vardec_opc: COLON typeid ASSIGN exp
    | ASSIGN exp

    ty: typeid
        | LBRACKET tyfields RBRACKET
        | ARRAY OF typeid

    tyfields: ID COLON typeid tyfields_factor | 
    tyfields_factor: tyfields_aux |
    tyfields_aux: COMMA ID COLON typeid tyfields_aux_factor
    tyfields_aux_factor: tyfields_aux | 

    typeid: ID
%%

void yyerror(char *c){
    printf("Erro: %s\n", c);
}

int main(){
    yyparse();
    return 0;
}