CC=g++
CFLAGS=-std=c++11 -Wall

.PHONY: all clean debug

all: CFLAGS+=-D NDEBUG -O3
all: vmtranslator	

vmtranslator: VMTranslator.o
	$(CC) $(CFLAGS) Parser.o Codewriter.o VMTranslator.o -o VMTranslator
	rm -rf *.o

parser.o: Parser.cpp
	$(CC) $(CFLAGS) -c Parser.cpp

codewriter.o: Codewriter.cpp
	$(CC) $(CFLAGS) -c Codewriter.cpp

VMTranslator.o: VMTranslator.cpp Parser.o Codewriter.o	
	$(CC) $(CFLAGS) -c VMTranslator.cpp


clean:
	rm -rf *.o VMTranslator

debug: CFLAGS+=-g
debug: VMTranslator