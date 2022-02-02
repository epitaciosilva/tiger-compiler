OBJECTS = lex.yy.o y.tab.o errormsg.o utilities.o

all: lex parse
.PHONY: all

lex: lex.o $(OBJECTS)
	gcc -g -o $@ lex.o $(OBJECTS)

parse: parse.o $(OBJECTS)
	gcc -g -o $@ parse.o $(OBJECTS)

errormsg.o: errormsg.c include/errormsg.h include/utilities.h
utilities.o: utilities.c include/utilities.h

# lex
lex.o: lex.c y.tab.h include/errormsg.h include/utilities.h
lex.yy.o: lex.yy.c y.tab.h include/errormsg.h include/utilities.h
lex.yy.c: tiger.lex
	lex tiger.lex

# parse
parse.o: parse.c include/errormsg.h include/utilities.h
y.tab.o: y.tab.c
y.tab.c: tiger.y
	yacc -dv tiger.y
y.tab.h: y.tab.c

.PHONY: clean
clean:
	rm -f *.o a.out lex parse lex.yy.c y.output y.tab.c y.tab.h
