#include <stdio.h>
#include "lex.yy.c"

#define PROGRAM 1
#define EXP 2
#define EXP1 3
#define TL 4
#define TL1 5
#define FL 6
#define FL_FACT 7
#define A_EXP 8
#define A_EXP1 9
#define A_EXP_FACT 10
#define TERM 11
#define TERM1 12
#define TERM_FACT 13
#define FACTOR 14
#define FACTOR_FACT 15
#define ARRAY_RECORD_FACT 16
#define RECORD 17
#define RECORD_LIST 18
#define LVALUE1 19
#define IF_FACTOR 20
#define EXPS 21
#define EXPS_LIST 22
#define DECS 23
#define DEC 24
#define VARDEC 25
#define RESULT_TYPE 26
#define TY 27
#define TYFIELDS 28
#define TYFIELDS_LIST 29
#define CIFRAO 30

int tok, seq_queue = 0;
YYSTYPE yylval;


int yylex(void);
int table[30][300][8] = {0};
int queue[100] = {0};

void insert_queue(int val) {
    queue[seq_queue++] = val;
}

int get_top_queue() {
    return queue[seq_queue-1];
}

void remove_queue() {
    queue[seq_queue--] = 0;
}

void create_table() {
    // PROGRAM
    table[PROGRAM][CIFRAO][0] = -1;
    table[PROGRAM][ID][0] = EXP;
    table[PROGRAM][VAR][0] = DECS;
    table[PROGRAM][LPARENTHESIS][0] = EXP;
    table[PROGRAM][FUNCTION][0] = DECS;
    table[PROGRAM][TYPE][0] = DECS;
    table[PROGRAM][STRING][0] = EXP;
    table[PROGRAM][INT][0] = EXP;
    table[PROGRAM][NIL][0] = EXP;
    table[PROGRAM][LET][0] = EXP;
    table[PROGRAM][FOR][0] = EXP;
    table[PROGRAM][WHILE][0] = EXP;
    table[PROGRAM][IF][0] = EXP;

    // EXP
    table[EXP][CIFRAO][0] = -1;
    table[EXP][COMMA][0] = -1;
    table[EXP][ID][0] = TL;
    table[EXP][ID][1] = EXP1;
    table[EXP][RBRACE][0] = -1;
    table[EXP][VAR][0] = -1;
    table[EXP][EQ][0] = -1;
    table[EXP][RPARENTHESIS][0] = -1;
    table[EXP][LPARENTHESIS][0] = TL;
    table[EXP][LPARENTHESIS][1] = EXP1;
    table[EXP][FUNCTION][0] = -1;
    table[EXP][TYPE][0] = -1;
    table[EXP][SEMICOLON][0] = -1;
    table[EXP][ELSE][0] = -1;
    table[EXP][RBRACKET][0] = -1;
    table[EXP][STRING][0] = TL;
    table[EXP][STRING][1] = EXP1;
    table[EXP][INT][0] = TL;
    table[EXP][INT][1] = EXP1;
    table[EXP][NIL][0] = TL;
    table[EXP][NIL][1] = EXP1;
    table[EXP][DIVIDE][0] = -1;
    table[EXP][TIMES][0] = -1;
    table[EXP][MINUS][0] = -1;
    table[EXP][PLUS][0] = -1;
    table[EXP][LT][0] = -1;
    table[EXP][GT][0] = -1;
    table[EXP][NEQ][0] = -1;
    table[EXP][GE][0] = -1;
    table[EXP][LE][0] = -1;
    table[EXP][AND][0] = -1;
    table[EXP][OR][0] = -1;
    table[EXP][END][0] = -1;
    table[EXP][IN][0] = -1;
    table[EXP][LET][0] = LET;
    table[EXP][LET][1] = DECS;
    table[EXP][LET][2] = IN;
    table[EXP][LET][3] = EXPS;
    table[EXP][LET][4] = END;
    table[EXP][BREAK][0] = BREAK;
    table[EXP][DO][0] = -1;
    table[EXP][TO][0] = -1;
    table[EXP][FOR][0] = FOR;
    table[EXP][FOR][1] = ID;
    table[EXP][FOR][2] = ASSIGN;
    table[EXP][FOR][3] = EXP;
    table[EXP][FOR][4] = TO;
    table[EXP][FOR][5] = EXP;
    table[EXP][FOR][6] = DO;
    table[EXP][FOR][7] = EXP;
    table[EXP][WHILE][0] = WHILE;
    table[EXP][WHILE][1] = EXP;
    table[EXP][WHILE][2] = DO;
    table[EXP][WHILE][3] = EXP;
    table[EXP][THEN][0] = -1;
    table[EXP][IF][0] = IF;
    table[EXP][IF][1] = EXP;
    table[EXP][IF][2] = THEN;
    table[EXP][IF][3] = EXP;
    table[EXP][IF][4] = IF_FACTOR;

    // EXP1
    table[EXP1][CIFRAO][0] = -1;
    table[EXP1][COMMA][0] = -1;
    table[EXP1][RBRACE][0] = -1;
    table[EXP1][VAR][0] = -1;
    table[EXP1][EQ][0] = -1;
    table[EXP1][RPARENTHESIS][0] = -1;
    table[EXP1][FUNCTION][0] = -1;
    table[EXP1][TYPE][0] = -1;
    table[EXP1][SEMICOLON][0] = -1;
    table[EXP1][ELSE][0] = -1;
    table[EXP1][RBRACKET][0] = -1;
    table[EXP1][DIVIDE][0] = -1;
    table[EXP1][TIMES][0] = -1;
    table[EXP1][MINUS][0] = -1;
    table[EXP1][PLUS][0] = -1;
    table[EXP1][LT][0] = -1;
    table[EXP1][GT][0] = -1;
    table[EXP1][NEQ][0] = -1;
    table[EXP1][GE][0] = -1;
    table[EXP1][LE][0] = -1;
    table[EXP1][AND][0] = -1;
    table[EXP1][OR][0] = OR;
    table[EXP1][OR][0] = TL;
    table[EXP1][OR][0] = EXP1;
    table[EXP1][END][0] = -1;
    table[EXP1][IN][0] = -1;
    table[EXP1][DO][0] = -1;
    table[EXP1][TO][0] = -1;
    table[EXP1][THEN][0] = -1;

    //TL
    table[TL][ID][0] = FL;
    table[TL][ID][1] = TL1;
    table[TL][RPARENTHESIS][0] = -1;
    table[TL][LPARENTHESIS][0] = FL;
    table[TL][LPARENTHESIS][1] = TL1;
    table[TL][STRING][0] = FL;
    table[TL][STRING][1] = TL1;
    table[TL][INT][0] = FL;
    table[TL][INT][1] = TL1;
    table[TL][NIL][0] = FL;
    table[TL][NIL][1] = TL1;

    // TL1
    table[TL1][CIFRAO][0] = -1;
    table[TL1][COMMA][0] = -1;
    table[TL1][RBRACE][0] = -1;
    table[TL1][VAR][0] = -1;
    table[TL1][EQ][0] = -1;
    table[TL1][RPARENTHESIS][0] = -1;
    table[TL1][FUNCTION][0] = -1;
    table[TL1][TYPE][0] = -1;
    table[TL1][SEMICOLON][0] = -1;
    table[TL1][ELSE][0] = -1;
    table[TL1][RBRACKET][0] = -1;
    table[TL1][DIVIDE][0] = -1;
    table[TL1][TIMES][0] = -1;
    table[TL1][MINUS][0] = -1;
    table[TL1][PLUS][0] = -1;
    table[TL1][LT][0] = -1;
    table[TL1][GT][0] = -1;
    table[TL1][NEQ][0] = -1;
    table[TL1][GE][0] = -1;
    table[TL1][LE][0] = -1;
    table[TL1][AND][0] = AND;
    table[TL1][AND][0] = FL;
    table[TL1][AND][0] = TL1;
    table[TL1][OR][0] = -1;
    table[TL1][END][0] = -1;
    table[TL1][IN][0] = -1;
    table[TL1][DO][0] = -1;
    table[TL1][TO][0] = -1;
    table[TL1][THEN][0] = -1;

    // FL
    table[FL][ID][0] = A_EXP;
    table[FL][ID][1] = FL_FACT;
    table[FL][LPARENTHESIS][0] = A_EXP;
    table[FL][LPARENTHESIS][1] = FL_FACT;
    table[FL][STRING][0] = A_EXP;
    table[FL][STRING][1] = FL_FACT;
    table[FL][INT][0] = A_EXP;
    table[FL][INT][1] = FL_FACT;
    table[FL][NIL][0] = A_EXP;
    table[FL][NIL][1] = FL_FACT;

    // FL_FACT
    table[FL_FACT][CIFRAO][0] = -1;
    table[FL_FACT][COMMA][0] = -1;
    table[FL_FACT][RBRACE][0] = -1;
    table[FL_FACT][VAR][0] = -1;
    table[FL_FACT][EQ][0] = EQ;
    table[FL_FACT][EQ][1] = A_EXP;
    table[FL_FACT][RPARENTHESIS][0] = -1;
    table[FL_FACT][FUNCTION][0] = -1;
    table[FL_FACT][TYPE][0] = -1;
    table[FL_FACT][SEMICOLON][0] = -1;
    table[FL_FACT][ELSE][0] = -1;
    table[FL_FACT][RBRACKET][0] = -1;
    table[FL_FACT][DIVIDE][0] = -1;
    table[FL_FACT][TIMES][0] = -1;
    table[FL_FACT][MINUS][0] = -1;
    table[FL_FACT][PLUS][0] = -1;
    table[FL_FACT][LT][0] = LT;
    table[FL_FACT][LT][1] = A_EXP;
    table[FL_FACT][GT][0] = GT;
    table[FL_FACT][GT][1] = A_EXP;
    table[FL_FACT][NEQ][0] = NEQ;
    table[FL_FACT][NEQ][1] = A_EXP;
    table[FL_FACT][GE][0] = GE;
    table[FL_FACT][GE][1] = A_EXP;
    table[FL_FACT][LE][0] = LE;
    table[FL_FACT][LE][1] = A_EXP;
    table[FL_FACT][AND][0] = -1;
    table[FL_FACT][OR][0] = -1;
    table[FL_FACT][END][0] = -1;
    table[FL_FACT][IN][0] = -1;
    table[FL_FACT][DO][0] = -1;
    table[FL_FACT][TO][0] = -1;
    table[FL_FACT][THEN][0] = -1;

    // A_EXP
    table[A_EXP][ID][0] = TERM;
    table[A_EXP][ID][1] = A_EXP1;
    table[A_EXP][LPARENTHESIS][0] = TERM;
    table[A_EXP][LPARENTHESIS][1] = A_EXP1;
    table[A_EXP][STRING][0] = TERM;
    table[A_EXP][STRING][1] = A_EXP1;
    table[A_EXP][INT][0] = TERM;
    table[A_EXP][INT][1] = A_EXP1;
    table[A_EXP][NIL][0] = TERM;
    table[A_EXP][NIL][1] = A_EXP1;

    // A_EXP1
    table[A_EXP1][CIFRAO][0] = -1;
    table[A_EXP1][COMMA][0] = -1;
    table[A_EXP1][RBRACE][0] = -1;
    table[A_EXP1][VAR][0] = -1;
    table[A_EXP1][EQ][0] = -1;
    table[A_EXP1][RPARENTHESIS][0] = -1;
    table[A_EXP1][FUNCTION][0] = -1;
    table[A_EXP1][TYPE][0] = -1;
    table[A_EXP1][SEMICOLON][0] = -1;
    table[A_EXP1][ELSE][0] = -1;
    table[A_EXP1][RBRACKET][0] = -1;
    table[A_EXP1][DIVIDE][0] = -1;
    table[A_EXP1][TIMES][0] = -1;
    table[A_EXP1][MINUS][0] = A_EXP_FACT;
    table[A_EXP1][MINUS][0] = A_EXP1;
    table[A_EXP1][PLUS][0] = A_EXP_FACT;
    table[A_EXP1][PLUS][0] = A_EXP1;
    table[A_EXP1][LT][0] = -1;
    table[A_EXP1][GT][0] = -1;
    table[A_EXP1][NEQ][0] = -1;
    table[A_EXP1][GE][0] = -1;
    table[A_EXP1][LE][0] = -1;
    table[A_EXP1][AND][0] = -1;
    table[A_EXP1][OR][0] = -1;
    table[A_EXP1][END][0] = -1;
    table[A_EXP1][IN][0] = -1;
    table[A_EXP1][DO][0] = -1;
    table[A_EXP1][TO][0] = -1;
    table[A_EXP1][THEN][0] = -1;

    // A_EXP_FACT
    table[A_EXP_FACT][MINUS][0] = MINUS;
    table[A_EXP_FACT][MINUS][0] = TERM;
    table[A_EXP_FACT][PLUS][0] = PLUS;
    table[A_EXP_FACT][PLUS][0] = TERM;

    // TERM
    table[TERM][ID][0] = FACTOR;
    table[TERM][ID][1] = TERM1;
    table[TERM][LPARENTHESIS][0] = FACTOR;
    table[TERM][LPARENTHESIS][1] = TERM1;
    table[TERM][STRING][0] = FACTOR;
    table[TERM][STRING][1] = TERM1;
    table[TERM][INT][0] = FACTOR;
    table[TERM][INT][1] = TERM1;
    table[TERM][NIL][0] = FACTOR;
    table[TERM][NIL][1] = TERM1;

     // TERM1
     table[TERM1][CIFRAO][0] = -1;
    table[TERM1][COMMA][0] = -1;
    table[TERM1][RBRACE][0] = -1;
    table[TERM1][VAR][0] = -1;
    table[TERM1][EQ][0] = -1;
    table[TERM1][RPARENTHESIS][0] = -1;
    table[TERM1][FUNCTION][0] = -1;
    table[TERM1][TYPE][0] = -1;
    table[TERM1][SEMICOLON][0] = -1;
    table[TERM1][ELSE][0] = -1;
    table[TERM1][DIVIDE][0] = TERM_FACT;
    table[TERM1][DIVIDE][1] = TERM1;
    table[TERM1][TIMES][0] = TERM_FACT;
    table[TERM1][TIMES][1] = TERM1;
    table[TERM1][MINUS][0] = -1;
    table[TERM1][PLUS][0] = -1;
    table[TERM1][LT][0] = -1;
    table[TERM1][GT][0] = -1;
    table[TERM1][NEQ][0] = -1;
    table[TERM1][GE][0] = -1;
    table[TERM1][LE][0] = -1;
    table[TERM1][AND][0] = -1;
    table[TERM1][OR][0] = -1;
    table[TERM1][END][0] = -1;
    table[TERM1][IN][0] = -1;
    table[TERM1][DO][0] = -1;
    table[TERM1][TO][0] = -1;
    table[TERM1][THEN][0] = -1;

    // TERM_FACT
    table[TERM_FACT][DIVIDE][0] = DIVIDE;
    table[TERM_FACT][DIVIDE][1] = FACTOR;
    table[TERM_FACT][TIMES][0] = DIVIDE;
    table[TERM_FACT][TIMES][1] = FACTOR;

    // FACTOR
    table[FACTOR][ID][0] = ID;
    table[FACTOR][ID][1] = FACTOR_FACT;
    table[FACTOR][LPARENTHESIS][0] = LPARENTHESIS;
    table[FACTOR][LPARENTHESIS][1] = EXPS;
    table[FACTOR][LPARENTHESIS][2] = RPARENTHESIS;
    table[FACTOR][STRING][0] = STRING;
    table[FACTOR][INT][0] = INT;
    table[FACTOR][NIL][0] = NIL;

    // FACTOR_FACT
    table[FACTOR_FACT][LBRACE][0] = ARRAY_RECORD_FACT;
    table[FACTOR_FACT][LBRACKET][0] = ARRAY_RECORD_FACT;
    table[FACTOR_FACT][STRING][0] = STRING;
    table[FACTOR_FACT][INT][0] = INT;
    table[FACTOR_FACT][NIL][0] = NIL;

    // ARRAY_RECORD_FACT
    table[ARRAY_RECORD_FACT][LBRACE][0] = LBRACE;
    table[ARRAY_RECORD_FACT][LBRACE][1] = RECORD;
    table[ARRAY_RECORD_FACT][LBRACE][2] = RBRACE;
    table[ARRAY_RECORD_FACT][LBRACKET][0] = LBRACKET;
    table[ARRAY_RECORD_FACT][LBRACKET][1] = EXP;
    table[ARRAY_RECORD_FACT][LBRACKET][2] = RBRACKET;
    table[ARRAY_RECORD_FACT][LBRACKET][3] = OF;
    table[ARRAY_RECORD_FACT][LBRACKET][4] = EXP;

    // RECORD
    table[RECORD][ID][0] = ID;
    table[RECORD][ID][1] = EQ;
    table[RECORD][ID][2] = EXP;
    table[RECORD][ID][3] = RECORD_LIST;
    table[RECORD][RBRACE][0] = -1;

    // RECORD_LIST
    table[RECORD_LIST][COMMA][0] = COMMA;
    table[RECORD_LIST][COMMA][1] = RECORD;
    table[RECORD_LIST][RBRACE][0] = -1;

    // LVALUE1
    table[LVALUE1][LPARENTHESIS][0] = LPARENTHESIS;
    table[LVALUE1][LPARENTHESIS][1] = EXP;
    table[LVALUE1][LPARENTHESIS][2] = RPARENTHESIS;
    table[LVALUE1][DOT][0] = DOT;
    table[LVALUE1][DOT][1] = ID;
}

void Program() {
    insert_queue(PROGRAM);
    int temp;

    while(1 == 1) {
        tok = yylex();
        temp = get_top_queue();
        printf("%d  %d\n", tok, temp);

        if(temp == -1) {
            remove_queue();
        }
        if(temp == tok) {
            remove_queue();
            continue;
        } else if(tok == 0) {
            remove_queue();
            if (seq_queue == 0) {
                printf("Success!!!");
            } else {
                printf("Error!\n");
            }
            break;
        }
        if(table[temp][tok][0] != 0) {
            for(int i = 0; i < 8; i++) {
                if(table[temp][tok][i] != 0) {
                    printf("\n%d\n\n", table[temp][tok][i]);
                    insert_queue(table[temp][tok][i]);
                } else {
                    break;
                }
            }
        }
    }
}

int main (int argc, char **argv)
{
    create_table();
    string filename;
    
    if (argc!=2) {
        fprintf(stderr,"usage: ./lex filename\n");
        exit(1);
    }

    filename=argv[1];
    
    EM_start(filename);

    Program();

    for(int i = 0; i < seq_queue; i++) {
        printf("%d\n", queue[i]);
    }
}


