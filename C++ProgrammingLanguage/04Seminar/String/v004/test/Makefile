SRC=test.cpp
DST=a.out
CPP=g++ -std=c++0x -Wall
LOG=log.log

release: $(SRC)
	$(CPP) $(SRC) -o $(DST) > $(LOG) 2>&1

debug: $(SRC)
	$(CPP) $(SRC) -DDEBUG -o $(DST) > $(LOG) 2>&1

