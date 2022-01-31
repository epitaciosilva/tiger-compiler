%{
#include <stdio.h>
#include <ctype.h>

int yylex(void);

void yyerror(char *c);


%}

%nonassoc LOW
%nonassoc TYPE FUNCTION
%nonassoc ID
%nonassoc LBRACKET
%nonassoc DO OF
%nonassoc THEN
%nonassoc ELSE
%left SEMICOLON
%nonassoc ASSIGN
%left OR
%left AND
%nonassoc EQ NEQ LT LE GT GE
%left PLUS MINUS
%left TIMES DIVIDE
%left UMINUS

%token COMMA SEMICOLON LPARENTHESIS RPARENTHESIS LBRACKET RBRACKET 
  LBRACE RBRACE DOT 
  PLUS MINUS TIMES DIVIDE LTE GTE EQ NEQ GT LT
  AND OR ASSIGN
  ARRAY IF THEN ELSE WHILE FOR TO DO LET IN END OF 
  BREAK NIL 
  FUNCTION VAR TYPE NEW ID INTEGER COLON STRING

%%

program: exp

exp: NIL
    | INTEGER
    | STRING

    | lvalue

    | array_create
    | record_create

    | NEW ID

    | lvalue LPARENTHESIS call_fac

    | arith_exp
    | cmp_exp
    | bool_exp

    | LPARENTHESIS exp RPARENTHESIS

    | lvalue ASSIGN exp

    | IF exp THEN exp if_opc
    | WHILE exp DO exp
    | FOR ID ASSIGN exp TO exp DO exp
    | BREAK
    | LET decs IN exps END

    arith_exp: exp PLUS exp
            | exp MINUS exp
            | exp TIMES exp
            | exp DIVIDE exp

    cmp_exp: exp EQ exp
        | exp NEQ exp
        | exp LT exp
        | exp LE exp
        | exp GT exp
        | exp GE exp

    bool_exp: exp AND exp
            | exp OR exp
            
    record_create: ID LBRACE record_create_list RBRACE

    record_create_list: 
                  | record_create_list_nonempty

    record_create_list_nonempty: record_create_field
                           | record_create_list_nonempty COMMA record_create_field

    record_create_field: ID EQ exp

    ID_fac: RBRACE | ID EQ exp ID_aux RBRACE
    ID_aux: | COMMA ID EQ exp ID_aux

    call_fac: RPARENTHESIS | exp call_aux
    call_aux: | COMMA exp call_aux

    if_opc: | ELSE exp


    lvalue: ID
      | ID LBRACKET exp RBRACKET
      | lvalue LBRACKET exp RBRACKET
      | lvalue DOT ID

    array_create: ID LBRACKET exp RBRACKET OF exp

    exps: | exp exps_list
    exps_list: | SEMICOLON exp

    decs: | decs dec

    dec: tydec
    | vardec
    | fundec

    fundec: FUNCTION ID LPARENTHESIS tyfields RPARENTHESIS COLON ID EQ exp
    | FUNCTION ID LPARENTHESIS tyfields RPARENTHESIS EQ exp

    tydeclist: tydec %prec LOW | tydeclist tydec 

    tydec: TYPE ID EQ ty

    vardec: VAR ID COLON ID ASSIGN exp
    | VAR ID ASSIGN exp

    ty: ID
        | LBRACKET tyfields RBRACKET
        | ARRAY OF ID

    tyfields: | ID COLON ID tyfields_factor
    tyfields_factor: | tyfields_aux
    tyfields_aux: COMMA ID COLON ID tyfields_aux_factor
    tyfields_aux_factor: | tyfields_aux
%%

void yyerror(char *c){
    printf("Erro: %s\n", c);
}

int main(){
    yyparse();
    return 0;
}