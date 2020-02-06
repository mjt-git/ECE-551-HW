CPPFLAG=-std=gnu++98 -Wall -Werror -ggdb3 -pedantic
code: code.o
	g++ -o code code.o
code.o: code.cpp code.h
	g++ $(CPPFLAG) -c code.cpp
