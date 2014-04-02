# files
file1 = insertion_sort32
file2 = utility32
file3 = bsearch32

# config
FLAG =
SUFFIX = .out
INCLUDE = "/files/Nutstore/000/AssemblyWorkSpace/adamcavendish"
LIB += "/lib32/ld-linux.so.2"
LIB += "/usr/lib32/libc.so"

all:
	as --32 $(FLAG) -I$(INCLUDE) -o $(file1).o $(file1).S
	as --32 $(FLAG) -I$(INCLUDE) -o $(file2).o $(file2).S
	as --32 $(FLAG) -I$(INCLUDE) -o $(file3).o $(file3).S

