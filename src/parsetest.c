#include <stdio.h>
#include <stdlib.h>
#include "./include/util.h"
#include "./include/errormsg.h"

extern int yyparse(void);

static void parse(string fname) {
  EM_start(fname);
  if(yyparse() == 0) 
    fprintf(stderr,"Parse OK!\n");
  else fprintf(stderr,"Parse error\n");
}

int main(int argc, char **argv) {
  if (argc!=2) {fprintf(stderr,"usage: a.out filename\n"); exit(1);}
  parse(argv[1]);
  return 0;
}
