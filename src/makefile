# variable
OBJECTS = lex.yy.o y.tab.o errormsg.o util.o absyn.o prabsyn.o symbol.o \
          table.o parse.o

# executable
all: lex parsetest absyntest
.PHONY: all

lex: lex.o $(OBJECTS)
	cc -g -o $@ lex.o $(OBJECTS)

parsetest: parsetest.o $(OBJECTS)
	cc -g -o $@ parsetest.o $(OBJECTS)

absyntest: absyntest.o $(OBJECTS)
	cc -g -o $@ absyntest.o $(OBJECTS)

# objects
errormsg.o: errormsg.c errormsg.h util.h
util.o: util.c util.h
absyn.o: absyn.c absyn.h util.h symbol.h
prabsyn.o: prabsyn.c prabsyn.h util.h absyn.h
symbol.o: symbol.c symbol.h util.h table.h
table.o: table.c table.h util.h
parse.o: parse.c parse.h util.h errormsg.h symbol.h absyn.h

# lex
lex.o: lex.c y.tab.h include/errormsg.h include/utilities.h
lex.yy.o: lex.yy.c y.tab.h include/errormsg.h include/utilities.h
lex.yy.c: tiger.lex
	lex tiger.lex

# parse
parsetest.o: parsetest.c errormsg.h util.h absyn.h symbol.h
y.tab.o: y.tab.c
y.tab.c: tiger.y
	yacc -dv tiger.y
y.tab.h: y.tab.c
	echo "y.tab.h was created at the same time as y.tab.c"

# absyn
absyntest.o: absyntest.c errormsg.h util.h absyn.h symbol.h parse.h prabsyn.h

.PHONY: clean
clean:
	rm -f *.o a.out lex parsetest absyntest lex.yy.c y.output y.tab.c y.tab.h
