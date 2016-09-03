# Scrabble Bot

Get the highest scoring word at Scrabble! Just provide the moves that have been made, and see the result!

## Installation / Compilation

_Note that this repository includes submodules and thus should be cloned recursively (`clone --recursive`) before compiling._

A C++11-compatible compiler is required to build the program. The Makefile compiles the binary statically such that no shared libraries are required.

A Makefile is included, compile with `make`. Other targets include `build` (no testing) and `test` to run the testsuite (as per CI above).
