CC = g++
CCOPT = -Wall -pedantic -std=c++11
RM = rm -rf

all: ScrabbleBot

ScrabbleBot: main.o \
	Game.o Board.o BoardMarker.o Direction.o \
	CharacterInput.o Modifier.o WordGenerator.o \
	WordPlay.o
	$(CC) $(CCOPT) $^ -o $@

%.o: %.cpp %.hpp
	$(CC) $(CCOPT) -c $< -o $@

clean:
	$(RM) ScrabbleBot *.o *.hpp.gch

.PHONY: all clean
