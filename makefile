OPTIONS=-O3 -DNDEBUG -Wall -Wextra

all: build/todo_list

debug: OPTIONS=-O0 -g -DDEBUG -Wall -Wextra
debug: build/todo_list

build/toDo.o: src/toDo.cpp include/toDo.hpp
	g++ ${OPTIONS} -c src/toDo.cpp -o build/toDo.o -Iinclude/
	
build/main.o: src/toDo.cpp include/toDo.hpp
	g++ ${OPTIONS} -c tools/main.cpp -o build/main.o -Iinclude/
	
build/todo_list: build/main.o build/toDo.o tools/main.cpp
	g++ ${OPTIONS} build/toDo.o build/main.o -o build/todo_list -Iinclude

clean:
	rm -rf build/*.o build/todo_list
