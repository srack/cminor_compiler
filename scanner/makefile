all: cminor 

cminor: main.o token.o lex.yy.o
	gcc main.o token.o lex.yy.o -g -o cminor

main.o: main.c lex.yy.c lex.yy.h token.h
	gcc -c main.c

token.o: token.c token.h
	gcc -c token.c

lex.yy.o: lex.yy.c lex.yy.h
	gcc -c lex.yy.c

lex.yy.c: scanner.l
	flex --header-file=lex.yy.h scanner.l

clean:
	rm -f *.o lex.yy.* cminor 
