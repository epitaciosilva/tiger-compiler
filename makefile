CFLAGS = -g -Wall -Wextra

tiger: main.o lex.yy.o errormsg.o utilities.o
	gcc $(CFLAGS) -o tiger main.o lex.yy.o errormsg.o utilities.o

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

clean: 
	rm -f tiger utilities.o main.o lex.yy.o lex.yy.c errormsg.o
