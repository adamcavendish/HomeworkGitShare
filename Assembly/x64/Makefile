# files
file1 = 001HelloWorld

# config
FLAG = -g
SUFFIX = .out
INCLUDE = "/files/Nutstore/000/AssemblyWorkSpace/adamcavendish"
LIB += "/lib32/ld-linux.so.2"
LIB += "/usr/lib32/libc.so"

all:
	as --32 $(FLAG) -I$(INCLUDE) -o $(file1).o $(file1).s
	ld -o $(file1)$(SUFFIX) $(file1).o --dynamic-linker $(LIB)
	rm $(file1).o
	
	as --32 $(FLAG) -I$(INCLUDE) -o $(file2).o $(file2).s
	ld -o $(file2)$(SUFFIX) $(file2).o --dynamic-linker $(LIB)
	rm $(file2).o

