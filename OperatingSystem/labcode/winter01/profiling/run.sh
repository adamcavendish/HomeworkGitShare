#!/bin/bash
curdir=($PWD)
cd ../build
make && valgrind --tool=callgrind --dump-instr=yes --simulate-cache=yes --collect-jumps=yes --callgrind-out-file=callgrind.out ./main && kcachegrind ./callgrind.out
cd "$curdir"

