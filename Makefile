clean:
	rm -rf *.out


testgrid:
	g++ gridgraph.cpp gridtest.cpp bogglebuster.cpp ./Substringary/substringary.cpp -g -Wall -o gridtest.out
	time ./gridtest.out

testbust:
	g++ gridgraph.cpp bogglebuster.cpp boggletest.cpp -g -Wall -o testbust.out
	./testbust.out 4 4 abcdefghijklmnop

testdict:
	g++ ./Substringary/*.cpp -g -Wall -o ./Substringary/dictionary.out
	./Substringary/dictionary.out

testall:
	g++ ./2D-Square-Graph-w-Diagonals/gridgraph.cpp bogglebuster.cpp boggletest.cpp ./Substringary/substringary.cpp -g -Wall -o testbust.out
	./testbust.out 4 4 rsebgaptsntivipm

final:
	g++ gridgraph.cpp bogglebuster.cpp boggletest.cpp ./Substringary/substringary.cpp -g -Wall -o bogglebuster.out


