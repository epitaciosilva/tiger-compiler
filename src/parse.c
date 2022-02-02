#include <stdio.h>
#include <stdlib.h>

#include "include/utilities.h"
#include "include/errormsg.h"

extern int yyparse(void);

void parse(string fname) {
  EM_start(fname);

  if(yyparse() == 0) {
    fprintf(stderr, "Parsing ok!!!\n");
  } else {
    fprintf(stderr, "Parsing failed!!!\n");
  }
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr,"filename is missing. type ./parsetest filename\n"); 
    exit(1);
  }
  parse(argv[1]);
  return 0;
}