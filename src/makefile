# variable
OBJECTS = lex.yy.o y.tab.o errormsg.o utilities.o util.o absyn.o prabsyn.o symbol.o \
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
errormsg.o: errormsg.c ./include/errormsg.h ./include/util.h
utilities.o: utilities.c ./include/utilities.h
util.o: util.c ./include/util.h
absyn.o: absyn.c ./include/absyn.h ./include/util.h ./include/symbol.h
prabsyn.o: prabsyn.c ./include/prabsyn.h ./include/util.h ./include/absyn.h
symbol.o: symbol.c ./include/symbol.h ./include/util.h ./include/table.h
table.o: table.c ./include/table.h ./include/util.h
parse.o: parse.c ./include/parse.h ./include/util.h ./include/errormsg.h ./include/symbol.h ./include/absyn.h

# lex
lex.o: lex.c y.tab.h ./include/errormsg.h ./include/utilities.h
lex.yy.o: lex.yy.c y.tab.h ./include/errormsg.h include/utilities.h
lex.yy.c: tiger.lex
	lex tiger.lex

# parse
parsetest.o: parsetest.c ./include/errormsg.h ./include/util.h ./include/absyn.h ./include/symbol.h
y.tab.o: y.tab.c
y.tab.c: tiger.y
	yacc -dv tiger.y
y.tab.h: y.tab.c
	echo "y.tab.h was created at the same time as y.tab.c"

# absyn
absyntest.o: absyntest.c ./include/errormsg.h ./include/utilities.h ./include/util.h ./include/absyn.h ./include/symbol.h ./include/parse.h ./include/prabsyn.h

.PHONY: clean
clean:
	rm -f *.o a.out lex parsetest absyntest lex.yy.c y.output y.tab.c y.tab.h
