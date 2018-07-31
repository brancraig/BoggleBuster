# Make file for the Substringary

CC=g++
CFLAGS=-c -Wall
DEBUGFLAGS=-g -Wall
TESTOUTPUT=substringarytest.out
RUNGDB=gdb $(TESTOUPUT)
OUTPUTFILE=substringary.out
MEMTEST=valgrind --leak-check=full


all: substringary

substringary: substringary.o
	$(CC) substringary.cpp substringarymain.cpp -o $(OUTPUTFILE)

substringary.o:
	$(CC) $(CFLAGS) substringary.cpp

substringarymain.o:
	$(CC) $(CFLAGS) substringarymain.cpp

clean:
	rm -rf *.o *.out


