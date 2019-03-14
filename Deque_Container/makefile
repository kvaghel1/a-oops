CPPFLAGS= -Wall -Wextra -pedantic

all:
	# Insert command to compile the code and generate executable
	g++ -std=c++11 test.cpp -g -ldl -o test

run:
	# Insert command to run the executable
	./test

checkmem:
	# Insert command to run the executable with valgrind
	valgrind --leak-check=yes -v ./test

clean:
	# Insert command to clean object files, executables
	rm test