# files
file1=No_14
file2=No_15
file3=No_19

srcfile=$(file1).cpp $(file2).cpp $(file3).cpp
tgtfile=$(srcfile:.cpp=.out)

# compile
FLAG += 
g11  = g++-4.8 -std=c++11 -Wall -m64 -msse -msse2

$(tgtfile) : $(srcfile)
	$(g11) $(FLAG) -o $(file1).out $(file1).cpp
	$(g11) $(FLAG) -o $(file2).out $(file2).cpp
	$(g11) $(FLAG) -o $(file3).out $(file3).cpp

clean:
	rm *.out

