# Scrabble Bot

Get the highest scoring word at Scrabble! Just provide the moves that have been made, and see the result!

## Getting started

__Note that this repository includes submodules and thus should be cloned recursively (`clone --recursive`) before compiling.__

A C++11-compatible compiler is required to build the program. The Makefile compiles the binary statically such that no shared libraries are required.

A Makefile is included, compile with `make`. Other targets include `build` (no testing) and `test` to run the testsuite (as per CI above).

## User guide

`./ScrabbleBot -b WordsWFriends`

Board presets:

- 'WordsWFriends': aims to replicate the rules played by the popular mobile game
- 'Scrabble': aims to replicate the rules played in traditional Hasbro Scrabble.

Languages:

- `en` / `en_GB` / `English` : Uses wordlist for the English language

Arguments:

- `-b` Sets board configuration file (optional, but requires filepath argument or one of the presets above)
- `-p` Sets the number of players in the game (optional, but requires number argument)
- `-o` Sets the index for the current player, such that if you go first, set 1 (optional, but requires number argument between 1 and argument of `-p`)
- `-l` Sets the language file used. This is a filepath to a file containing a list of words which are valid or an option from the languages section above. 
