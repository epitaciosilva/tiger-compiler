#include <stdio.h>
#include <stdlib.h>

#include "include/utilities.h"
#include "include/errormsg.h"
#include "include/tokens.h"

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
  return tok<258 || tok>300 ? "BAD_TOKEN" : toknames[tok-258];
}

int main(int argc, char **argv) {
  string filename; 
  int tok;
  if (argc!=2) {
    fprintf(stderr,"usage: ./lex filename\n");
    exit(1);
  }

  filename=argv[1];
  
  EM_start(filename);
  
  for(;;) {
    tok = yylex();
    if (tok == 0) break;
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
  return 0;
}
