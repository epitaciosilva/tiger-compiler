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
    "AND", "OR", "ASSIGN"};

string tokname(tok)
{
    return tok < 257 || tok > 299 ? "BAD_TOKEN" : toknames[tok - 257];
}

void eat(int token);

void error()
{
    switch (tok)
    {
    case ID:
    case STRING:
        printf("%10s %4d %s\n", tokname(tok), EM_tokPos, yylval.sval);
        break;
    case INT:
        printf("%10s %4d %d\n", tokname(tok), EM_tokPos, yylval.ival);
        break;
    default:
        //printf("%s", "Erro no programa 0");
        printf("%10s %4d\n", tokname(tok), EM_tokPos);
    }
    printf("%d", tok);
    fprintf(stderr, "Error (%d %d)\n", yylineno, offSet);
    exit(1);
}

void advance()
{
    tok = yylex();
    if (tok == 0)
        exit(1);
    switch (tok)
    {
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

void eat(int t)
{
    if (tok == t)
    {
        advance();
    }
    else
    {
        printf("Chamou aqui");
        printf("%10s %4d\n", tokname(tok), EM_tokPos);
        printf("%10s %4d\n", tokname(t), EM_tokPos);
        error();
    }
}

void LValuePrime()
{
    switch (tok)
    {
    case DOT:
        /* code */
        eat(DOT);
        eat(ID);
        break;
    case LPARENTHESIS:
        eat(LPARENTHESIS);
        Exp();
        eat(RPARENTHESIS);
        break;
    default:
        break;
    }
}

void RecordList()
{
    switch (tok)
    {
    case COMMA:
        eat(COMMA);
        Record();
        break;

    default:
        break;
    }
}

void Record()
{
    switch (tok)
    {
    case ID:
        eat(ID);
        eat(EQ);
        Exp();
        RecordList();
        break;

    default:
        break;
    }
}

void ArrayRecordFactor()
{
    switch (tok)
    {
    case LBRACE:
        eat(LBRACE);
        Record();
        eat(RBRACE);
        break;
    case LBRACKET:
        eat(LBRACKET);
        Exp();
        eat(RBRACKET);
        eat(OF);
        Exp();
        break;
    default:
        error();
    }
}

void FactorFact1()
{
    switch (tok)
    {
    case ASSIGN:
        eat(ID);
        Exp();
        break;
    default:
        break;
    }
}

void FactotFact()
{
    switch (tok)
    {
    case DOT:
        LValuePrime();
        FactorFact1();
        break;
    case LPARENTHESIS:
        LValuePrime();
        FactorFact1();
        break;
    case LBRACE:
        ArrayRecordFactor();
        break;
    case LBRACKET:
        ArrayRecordFactor();
        break;
    case ASSIGN:
        ArrayRecordFactor();
        break;
    default:
        error();
    }
}

void Factor()
{
    switch (tok)
    {
    case LPARENTHESIS:
        eat(LPARENTHESIS);
        Exps();
        eat(RPARENTHESIS);
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
        FactotFact();
        break;
    default:
        //printf("%s", "Erro no programa 2");
        error();
    }
}

void Term()
{
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
        //printf("%s", "Erro no programa 3");
        error();
    }
}

void AExpFactor()
{
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

void AExpPrime()
{
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

void AExp()
{
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
        //printf("%s", "Erro no programa 4");
        error();
    }
}

void FlFactor()
{
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

void Fl()
{
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
        //printf("%s", "Erro no programa 6");
        error();
    }
}

void TlPrime()
{
    switch (tok)
    {
    case AND:
        eat(AND);
        Fl();
        TlPrime();
        break;
    default:
        //printf("%s", "Erro no programa 7");
        break;
    }
}

void Tl()
{
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
        //printf("%s", "Erro no programa 8");
        error();
    }
}

void TyFieldsList(){
    switch (tok)
    {
    case COMMA:
        TyFields();
        break;
    default:
        break;
    }
}

void TyFields()
{
    switch (tok)
    {
    case ID:
        eat(ID);
        eat(COLON);
        eat(ID);
        TyFieldsList();
        break;
    default:
        break;
    }
}

void Ty(){
    switch (tok)
    {
    case ID:
        eat(ID);
        break;
    case LBRACE:
        eat(LBRACE);
        TyFields();
        eat(RBRACE);
        break;
    case ARRAY:
        eat(ARRAY);
        eat(OF);
        eat(ID);
        break;
    default:
        error();
    }
}

void ResultType(){
    switch (tok)
    {
    case COLON:
        eat(COLON);
        eat(ID);
        break;
    default:
        break;
    }
}

void Vardec(){
    switch (tok)
    {
    case VAR:
        eat(VAR);
        eat(ID);
        ResultType();
        eat(ASSIGN);
        Exp();
        break;
    
    default:
        break;
    }
}

void Dec(){
    switch (tok)
    {
    case TYPE:
        eat(TYPE);
        eat(ID);
        eat(EQ);
        Ty();
        break;
    case FUNCTION:
        eat(FUNCTION);
        eat(ID);
        eat(LPARENTHESIS);
        TyFields();
        eat(RPARENTHESIS);
        ResultType();
        eat(EQ);
        Exp();
        break;
    case VAR:
        Vardec();
        break;
    default:
        error();
    }
}

void Decs()
{
    switch (tok)
    {
    case TYPE:
        Dec();
        Decs();
        Program();
        break;
    case FUNCTION:
        Dec();
        Decs();
        Program();
        break;
    case VAR:
        Dec();
        Decs();
        Program();
        break;
    default:
        //printf("%s", "Erro no programa 9");
        error();
    }
}

void ExpPrime()
{
    switch (tok)
    {
    case OR:
        Tl();
        ExpPrime();
        break;
    default:
        //printf("%s", "Erro no programa 10");
        break;
    }
}

void IfFactor()
{
    switch (tok)
    {
    case ELSE:
        eat(ELSE);
        Exp();
        break;
    default:
        break;
    }
}

void Exp()
{
    switch (tok)
    {
    case LET:
        eat(LET);
        Decs();
        eat(IN);
        Exps();
        eat(END);
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
        eat(THEN);
        Exp();
        IfFactor();
        Program();
        break;
    case WHILE:
        eat(WHILE);
        Exp();
        eat(DO);
        Exp();
        Program();
        break;
    case FOR:
        eat(FOR);
        eat(ID);
        eat(ASSIGN);
        Exp();
        eat(TO);
        Exp();
        eat(DO);
        Exp();
        Program();
        break;
    case BREAK:
        eat(BREAK);
        Program();
        break;
    default:
        //printf("%s", "Erro no programa 11");
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
        //printf("%s", "Erro no programa 12");
        error();
    }
}

void ExpList()
{
    switch (tok)
    {
    case SEMICOLON:
        eat(SEMICOLON);
        Exps();
        break;
    default:
        break;
    }
}

void Exps()
{
    switch (tok)
    {
    case LET:
        Exp();
        ExpList();
        break;
    case LPARENTHESIS:
        Exp();
        ExpList();
        break;
    case NIL:
        Exp();
        ExpList();
        break;
    case INT:
        Exp();
        ExpList();
        break;
    case STRING:
        Exp();
        ExpList();
        break;
    case ID:
        Exp();
        ExpList();
        break;
    case IF:
        Exp();
        ExpList();
        break;
    case WHILE:
        Exp();
        ExpList();
        break;
    case FOR:
        Exp();
        ExpList();
        break;
    case BREAK:
        Exp();
        ExpList();
        break;
    case SEMICOLON:
        Exp();
        ExpList();
        break;
    default:
        break;
    }
}

int main(int argc, char **argv)
{
    string filename;

    if (argc != 2)
    {
        fprintf(stderr, "usage: ./lex filename\n");
        exit(1);
    }

    filename = argv[1];

    EM_start(filename);

    advance();

    Program();
}
