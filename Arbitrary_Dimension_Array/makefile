CPPFLAGS= -Wall -Wextra -pedantic -g

all:
	# Insert command to compile the code and generate executable
	g++ -std=c++11  Test_Array.cpp -o Test_Array 
run:
	# Insert command to run the executable
	./Test_Array

checkmem:
	# Insert command to run the executable with valgrind
	valgrind --leak-check=yes -v ./Test_Array

clean:
	# Insert command to clean object files, executables
	rm Test_Array
