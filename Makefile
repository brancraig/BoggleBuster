# Make file for the Bogglebuster



CC= g++
CFLAGS= -c -Wall
DEBUGFLAGS = -g -Wall
TESTOUTPUT = boggletest.out
RUNGDB= gdb $(TESTOUPUT)
OUTPUTFILE = bogglebuster.out
MEMTEST = valgrind --leak-check=full

MAKE_DIR = $(PWD)
GRIDGRAPH_DIR = $(MAKE_DIR)/2D-Square-Graph-w-Diagonals
DICTIONARY_DIR = $(MAKE_DIR)/Substringary
MAKE = make

all: bogglebuster

debug: 

memtest:

bogglebuster: bogglebuster.o bogglemain.o 
	cd $(DICTIONARY_DIR) && $(MAKE) substringary 
	cd $(GRIDGRAPH_DIR) && $(MAKE) gridgraph  
	$(CC) bogglebuster.o bogglemain.o $(DICTIONARY_DIR)/substringary.o $(GRIDGRAPH_DIR)/gridgraph.o -o $(OUTPUTFILE)


bogglebuster.o:
	$(CC) $(CFLAGS) bogglebuster.cpp

bogglemain.o:
	$(CC) $(CFLAGS) bogglemain.cpp

clean:
	rm -rf *.out *.o
	cd $(DICTIONARY_DIR) && $(MAKE) clean 
	cd $(GRIDGRAPH_DIR) && $(MAKE) clean  
	



