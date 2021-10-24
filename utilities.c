#include "utilities.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void *check_malloc(int length){
    void *p = malloc(length);
    if(!p){
        fprintf(stderr, "\nProgram ran out of memory!\n");
        exit(1);
    }
    return p;
}

string String(char *s){
    string p = check_malloc(strlen(s)+1);
    strcpy(p,s);
    return p;
}

U_boolList U_BoolList(bool head, U_boolList tail)
{ 
    U_boolList list = check_malloc(sizeof(*list));
    list->head = head;
    list->tail = tail;
    return list;
}