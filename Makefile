connect4: main.o game.o grid.o
	g++ bin/main.o bin/game.o bin/grid.o -o bin/connect4 -g

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