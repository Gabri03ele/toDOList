OPTIONS=-O3 -DNDEBUG -Wall -Wextra

all: build/finalTest

debug: OPTIONS=-O0 -g -DDEBUG -Wall -Wextra
debug: build/finalTest

build/finalTest: build/finalTest.o tools/main.cpp
	gcc ${OPTIONS} tools/main.cpp -o build/finalTest -I include/ build/finalTest.o

build/finalTest.o: src/toDo.cpp include/toDo.hpp
	gcc ${OPTIONS} -c src/toDo.cpp -o build/finalTest.o -I include/

clean:
	rm -rf build/*.o build/finalTest
