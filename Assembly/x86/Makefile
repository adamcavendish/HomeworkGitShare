# files
file1 = 001HelloWorld
file2 = 002mov
file3 = 003split
file4 = 004find-v2
file5 = 005testInsertionSort

# config
FLAG =
SUFFIX = .out
INCLUDE = "/files/Nutstore/000/AssemblyWorkSpace/adamcavendish/"
LIB += "/lib32/ld-linux.so.2"
LIB += "/usr/lib32/libc.so"

all:
	make -C ../../adamcavendish/
	
	as --32 $(FLAG) -I$(INCLUDE) -o $(file1).o $(file1).s
	ld -o $(file1)$(SUFFIX) $(file1).o --dynamic-linker $(LIB)
	rm $(file1).o
	
	as --32 $(FLAG) -I$(INCLUDE) -o $(file2).o $(file2).s
	ld -o $(file2)$(SUFFIX) $(file2).o
	rm $(file2).o
	
	as --32 $(FLAG) -I$(INCLUDE) -o $(file3).o $(file3).s
	ld -o $(file3)$(SUFFIX) $(file3).o
	rm $(file3).o
	
	as --32 $(FLAG) -I$(INCLUDE) -o $(file4).o $(file4).s
	ld -o $(file4)$(SUFFIX) $(file4).o $(INCLUDE)/insertion_sort32.o $(INCLUDE)/bsearch32.o $(INCLUDE)/utility32.o
	rm $(file4).o
	
	g++-4.8 -c -m32 $(FLAG) -I$(INCLUDE) -o $(file5).o $(file5).cpp
	g++-4.8 -m32 -o $(file5)$(SUFFIX) $(file5).o $(INCLUDE)/insertion_sort32.o $(INCLUDE)/utility32.o
	rm $(file5).o
	
