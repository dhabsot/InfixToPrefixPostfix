InfixToPrefixPostfix.o: InfixToPrefixPostfix.o Makefile
	gcc -ansi -Wall -O InfixToPrefixPostfix.c -o InfixToPrefixPostfix

clean:
	-rm -f InfixToPrefixPostfix.o

clean_everything:
	rm -f InfixToPrefixPostfix InfixToPrefixPostfix.o
