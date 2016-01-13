CC = g++
CCOPT = -Wall -Werror -pedantic -std=c++11
RM = rm -rf

all: main

main: main.o \
	Game.o Board.o BoardMarker.o Direction.o \
	CharacterInput.o Modifier.o WordGenerator.o \
	WordPlay.o
	$(CC) $(CCOPT) $^ -o $@

%.o: %.cpp %.hpp
	$(CC) $(CCOPT) -c $< -o $@

clean:
	$(RM) main *.o *.hpp.gch

.PHONY: all clean
