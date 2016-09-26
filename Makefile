InfixToPrefixPostfix.o: InfixToPrefixPostfix.o Makefile
	gcc -ansi -Wall -O InfixToPrefixPostfix.c -o InfixToPrefixPostfix

pulisci:
	-rm -f InfixToPrefixPostfix.o

pulisci_tutto:
	rm -f InfixToPrefixPostfix InfixToPrefixPostfix.o