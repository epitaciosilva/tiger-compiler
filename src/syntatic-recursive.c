#include <stdio.h>
#include "lex.yy.c"

int tok;

YYSTYPE yylval;

int yylex(void);

string toknames[] = {
"ID", "STRING", "INT", "ARRAY", "IF", "THEN", "ELSE", "WHILE", "FOR",
"TO", "DO", "LET", "IN", "END", "OF", "BREAK", "NIL", "FUNCTION",
"VAR", "TYPE", "COMMA", "COLON", "SEMICOLON", "LPAREN",
"RPAREN", "LBRACK", "RBRACK", "LBRACE", "RBRACE", "DOT", "PLUS",
"MINUS", "TIMES", "DIVIDE", "EQ", "NEQ", "LT", "LE", "GT", "GE",
"AND", "OR", "ASSIGN"
};


string tokname(tok) {
  return tok<257 || tok>299 ? "BAD_TOKEN" : toknames[tok-257];
}

void eat(int token);

void error(){
    switch(tok) {
        case ID: 
        case STRING:
            printf("%10s %4d %s\n", tokname(tok), EM_tokPos, yylval.sval);
            break;
        case INT:
            printf("%10s %4d %d\n", tokname(tok), EM_tokPos, yylval.ival);
            break;
        default:
            printf("%s", "Erro no programa 0");
            printf("%10s %4d\n", tokname(tok), EM_tokPos);
    }
    fprintf(stderr, "Error (%d %d)\n", yylineno, offSet);
    exit(1);
}

void advance(){
    tok = yylex();
    switch(tok) {
        case ID: 
        case STRING:
            printf("%10s %4d %s\n", tokname(tok), EM_tokPos, yylval.sval);
            break;
        case INT:
            printf("%10s %4d %d\n", tokname(tok), EM_tokPos, yylval.ival);
            break;
        default:
            printf("%10s %4d\n", tokname(tok), EM_tokPos);
    }
}

void eat(int t){
    if(tok==t) {
        advance(); 
    } else {
        printf("Chamou aqui");
         printf("%10s %4d\n", tokname(tok), EM_tokPos);
          printf("%10s %4d\n", tokname(t), EM_tokPos);
        error();
    }
}

void Exps(){

}

void Factor(){
    switch (tok)
    {
    case LPARENTHESIS:
        eat(LPARENTHESIS);
        break;
    case NIL:
        eat(NIL);
        break;
    case INT:
        eat(INT);
        break;
    case STRING:
        eat(STRING);
        break;
    case ID:
        eat(ID);
        break;
    default:
        printf("%s", "Erro no programa 2");
        error();
    }
}

void Term(){
    switch (tok)
    {
    case LPARENTHESIS:
        Factor();
        break;
    case NIL:
        Factor();
        break;
    case INT:
        Factor();
        break;
    case STRING:
        Factor();
        break;
    case ID:
        Factor();
        break;
    default:
        printf("%s", "Erro no programa 3");
        error();
    }
}

void AExpFactor(){
    switch (tok)
    {
    case PLUS:
        eat(PLUS);
        Term();
        break;
    case MINUS:
        eat(PLUS);
        Term();
        break;
    default:
        break;
    }
}

void AExpPrime(){
    switch (tok)
    {
    case PLUS:
        AExpFactor();
        AExpPrime();
        break;  
    case MINUS:
        AExpFactor();
        AExpPrime();
        break;
    default:
        break;
    }
}

void AExp(){
    switch (tok)
    {
    case LPARENTHESIS:
        Term();
        AExpPrime();
        break;
    case NIL:
        Term();
        AExpPrime();
        break;
    case INT:
        Term();
        AExpPrime();
        break;
    case STRING:
        Term();
        AExpPrime();
        break;
    case ID:
        Term();
        AExpPrime();
        break;
    default:
        printf("%s", "Erro no programa 4");
        error();
    }
}

void FlFactor(){
    switch (tok)
    {
    case LT:
        eat(LT);
        AExp();
        break;
    case GT:
        eat(GT);
        AExp();
        break;
    case EQ:
        eat(EQ);
        AExp();
        break;
    case NEQ:
        eat(NEQ);
        AExp();
        break;
    case GE:
        eat(GE);
        AExp();
        break;
    case LE:
        eat(LE);
        AExp();
        break;
    default:
        break;
    }
}

void Fl(){
    switch (tok)
    {
    case LPARENTHESIS:
        AExp();
        FlFactor();
        break;
    case NIL:
        AExp();
        FlFactor();
        break;
    case INT:
        AExp();
        FlFactor();
        break;
    case STRING:
        AExp();
        FlFactor();
        break;
    case ID:
        AExp();
        FlFactor();
        break;
    default:
        printf("%s", "Erro no programa 6");
        error();
    }
}

void TlPrime(){
    switch (tok)
    {
    case AND:
        eat(AND);
        Fl();
        TlPrime();
        break;
    default:
        printf("%s", "Erro no programa 7");
        break;
    }
}

void Tl(){
    switch (tok)
    {
    case LPARENTHESIS:
        Fl();
        TlPrime();
        break;
    case NIL:
        Fl();
        TlPrime();
        break;
    case INT:
        Fl();
        TlPrime();
        break;
    case STRING:
        Fl();
        TlPrime();
        break;
    case ID:
        Fl();
        TlPrime();
        break;
    default:
        printf("%s", "Erro no programa 8");
        error();
    }
}

void Decs(){
    switch (tok)
    {
    case TYPE:
        break;
    case FUNCTION:
        break;
    case VAR:
        break;
    default:
        printf("%s", "Erro no programa 9");
        error();
    }
}

void ExpPrime(){
    switch (tok)
    {
    case OR:
        Tl();
        ExpPrime();
        break;
    default:
        printf("%s", "Erro no programa 10");
        break;
    }
}

void Exp(){
    switch (tok)
    {
    case LET:
        eat(LET);
        Decs();
        break;
    case LPARENTHESIS:
        Tl();
        ExpPrime();
        break;
    case NIL:
        Tl();
        ExpPrime();
        break;
    case INT:
        Tl();
        ExpPrime();
        break;
    case STRING:
        Tl();
        ExpPrime();
        break;
    case ID:
        Tl();
        ExpPrime();
        break;
    case IF:
        eat(IF);
        Exp();
        break;
    case WHILE:
        eat(WHILE);       
        Exp();
        eat(DO);
        Exp();
        break;
    default:
        printf("%s", "Erro no programa 11");
        error();
    }
}   

void Program()
{
    switch (tok)
    {
    case IF:
        Exp();
        break;
    case WHILE:
        Exp();
        break;
    case FOR:
        Exp();
        break;
    case BREAK:
        Exp();
        break;
    case LET:
        Exp();
        break;
    case LPARENTHESIS:
        Exp();
        break;
    case NIL:
        Exp();
        break;
    case INT:
        Exp();
        break;
    case STRING:
        Exp();
        break;
    case ID:
        Exp();
        break;
    case TYPE:
        Decs();
        break;
    case VAR:
        Decs();
        break;
    case FUNCTION:
        Decs();
        break;
    default:
        printf("%s", "Erro no programa 12");
        error();
    }
}

int main (int argc, char **argv)
{
    string filename;
    
    if (argc!=2) {
        fprintf(stderr,"usage: ./lex filename\n");
        exit(1);
    }

    filename=argv[1];
    
    EM_start(filename);

    advance();

    Program();
}


