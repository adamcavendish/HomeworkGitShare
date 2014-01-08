SRC=test.cpp ../Core/ratio.cc
DST=ratio.out
CC=g++ -std=c++0x -Wall
LOG=log.log

release: $(SRC)
	$(CC) $(SRC) -o $(DST) > $(LOG) 2>&1

debug: $(SRC)
	$(CC) -DDEBUG -g $(SRC) -o $(DST) > $(LOG) 2>&1


