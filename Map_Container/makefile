CPPFLAGS= -Wall -Wextra -pedantic

all:
	# Insert command to compile the code and generate executable
	g++ -std=c++11 -Wall -Wextra -pedantic minimal.cpp -o minimal 

run:
	# Insert command to run the executable
	./minimal

checkmem:
	# Insert command to run the executable with valgrind
	valgrind --leak-check=yes -v ./minimal

clean:
	# Insert command to clean object files, executables
	rm minimal
