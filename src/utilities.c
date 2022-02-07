/*
 * utilities.c - commonly used utilitiesity functions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./include/utilities.h"

void *check_malloc(int len) {
  void *p = malloc(len);
  if (!p) {
    fprintf(stderr,"\nRan out of memory!\n");
    exit(1);
  }
  return p;
}
