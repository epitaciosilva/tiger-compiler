#include "utilities.h"
#include "errormsg.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

bool anyError = 0;

static string filename = "";

static int lineNum = 1;

int EM_tokPos = 0;

extern FILE *yyin;

typedef struct intList {
    int i;
    struct intList *rest;
} *IntList;

static IntList intList(int i, IntList rest){
    IntList list = check_malloc(sizeof *list);
    list->i = i;
    list->rest = rest;
    return list;
}

static IntList linePos = NULL;

void EM_newline(void){
    lineNum++;
    linePos = intList(EM_tokPos, linePos);
}

void EM_error(int pos, char *message,...){
    va_list ap;
    IntList lines = linePos;
    int num=lineNum;

    anyError = 1;
    
    while(lines && lines->i >= pos){
        lines=lines->rest;
        num--;
    }

    if (filename) 
        fprintf(stderr,"%s:",filename);

    if (lines) 
        fprintf(stderr,"%d.%d: ", num, pos-lines->i);

    va_start(ap,message);
    
    vfprintf(stderr, message, ap);
    
    va_end(ap);
    
    fprintf(stderr,"\n");
}

void EM_start(string file_name){
    anyError = 0;
    filename = file_name;
    lineNum = 1;

    linePos = intList(0, NULL);
    yyin = fopen(filename, "r");
    
    if(!yyin) {
        EM_error(0, "Cannot open file");
        exit(1);
    }
}
