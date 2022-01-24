CFLAGS = -g -Wall -Wextra
OBJECTS = lex.yy.o y.tab.o errormsg.o utilities.o

parsetest: src/parsetest.o $(OBJECTS)
	gcc -g -o $@ src/parsetest.o $(OBJECTS)

# tiger: main.o lex.yy.o errormsg.o utilities.o
# 	gcc $(CFLAGS) -o tiger main.o lex.yy.o errormsg.o utilities.o

main.o: src/main.c include/tokens.h include/errormsg.h include/utilities.h
	gcc $(CFLAGS) -c src/main.c

errormsg.o: src/errormsg.c include/errormsg.h include/utilities.h
	gcc $(CFLAGS) -c src/errormsg.c

lex.yy.o: lex.yy.c include/tokens.h include/errormsg.h include/utilities.h
	gcc $(CFLAGS) -c lex.yy.c

utilities.o: src/utilities.c include/utilities.h
	gcc $(CFLAGS) -c src/utilities.c

lex.yy.c: src/tiger.lex
	flex src/tiger.lex

# parse
parsetest.o: src/parsetest.c include/errormsg.h include/utilities.h
y.tab.o: y.tab.c
y.tab.c: src/tiger.y
	yacc -dv src/tiger.y
y.tab.h: y.tab.c
	echo "y.tab.h was created at the same time as y.tab.c"

clean: 
	rm -f tiger include/utilities.o main.o lex.yy.o lex.yy.c parsetest parsetest.o y.tab.o y.tab.c y.tab.h include/errormsg.o
