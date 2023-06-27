connect4: main.o game.o grid.o statetree.o minimax.o
	g++ bin/main.o bin/game.o bin/grid.o bin/statetree.o bin/minimax.o -o bin/connect4 -g

clean: 
	rm -rf bin/

main.o: src/main.cpp
	mkdir -p bin/
	g++ src/main.cpp -c -o bin/main.o -g

game.o: src/game.cpp include/game.hpp
	mkdir -p bin/
	g++ src/game.cpp -c -o bin/game.o -g

grid.o: src/grid.cpp include/grid.hpp
	mkdir -p bin/
	g++ src/grid.cpp -c -o bin/grid.o -g

minimax.o: src/minimax.cpp include/minimax.hpp
	mkdir -p bin/
	g++ src/minimax.cpp -c -o bin/minimax.o -g

statetree.o: src/statetree.cpp include/statetree.hpp
	mkdir -p bin/
	g++ src/statetree.cpp -c -o bin/statetree.o -g