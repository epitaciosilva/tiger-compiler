CFLAGS = -g -Wall -Wextra

lextest: main.o lex.yy.o errormsg.o utilities.o
	gcc $(CFLAGS) -o lextest main.o lex.yy.o errormsg.o utilities.o

main.o: main.c tokens.h errormsg.h utilities.h
	gcc $(CFLAGS) -c main.c

errormsg.o: errormsg.c errormsg.h utilities.h
	gcc $(CFLAGS) -c errormsg.c

lex.yy.o: lex.yy.c tokens.h errormsg.h utilities.h
	gcc $(CFLAGS) -c lex.yy.c

lex.yy.c: tiger.lex
	flex tiger.lex

utilities.o: utilities.c utilities.h
	gcc $(CFLAGS) -c utilities.c

clean: 
	rm -f a.out utilities.o driver.o lex.yy.o lex.yy.c errormsg.o
