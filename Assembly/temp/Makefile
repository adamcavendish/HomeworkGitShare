# files
file1 = test
file2 = test64

# config
FLAG = -g3
SUFFIX = .out
INCLUDE = "/files/Nutstore/000/AssemblyWorkSpace/adamcavendish/"
LIB += "/lib32/ld-linux.so.2"
LIB += "/usr/lib32/libc.so"

all:
	make -C ../../adamcavendish/
	
	as --32 $(FLAG) -I$(INCLUDE) -o $(file1).o $(file1).s
	ld -m elf_i386 -o $(file1)$(SUFFIX) $(file1).o --dynamic-linker $(LIB)
	rm $(file1).o
	
	as $(FLAG) -o $(file2).o $(file2).s
	ld -o $(file2)$(SUFFIX) $(file2).o
	rm $(file2).o
	
