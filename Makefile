CC = g++
CCOPT = -Wall -Werror -pedantic -std=c++11
RM = rm -rf

all: main

main: main.cpp main.hpp
	$(CC) $(CCOPT) -c $< -o $@

%.o: %.cpp %.hpp
	$(CC) $(CCOPT) -c $< -o $@

clean:
	$(RM) main *.o *.hpp.gch

.PHONY: all clean
