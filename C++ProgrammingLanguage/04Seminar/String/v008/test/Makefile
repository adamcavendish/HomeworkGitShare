SRC1=test.cpp
SRC2=test_ICS.cpp
DST1=String.out
DST2=ICSString.out

CPP=g++ -std=c++0x -Wall
LOG=log.log

release: $(SRC1) $(SRC2)
	$(CPP) $(SRC1) -o $(DST1) > $(LOG) 2>&1
	$(CPP) $(SRC2) -o $(DST2) >> $(LOG) 2>&1

debug: $(SRC1) $(SRC2)
	$(CPP) -g $(SRC1) -o $(DST1) > $(LOG) 2>&1
	$(CPP) -g $(SRC2) -o $(DST2) >> $(LOG) 2>&1

