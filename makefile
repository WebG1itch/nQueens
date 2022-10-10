run: nQueens
	./nQueens

nQueens.o: nQueens.cpp
	g++ -c nQueens.cpp

nQueens: nQueens.o
	g++ nQueens.o -o nQueens

clean:
	rm -f *.o
	rm nQueens
