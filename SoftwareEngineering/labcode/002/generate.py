import sh
import os
import glob

files=glob.glob("./*");

for i in files:
	if(i.count(".dot") > 0):
		sh.dot("-Tpng", i, _out=i.replace(".dot", ".png"));

sh.kde_open(files[0].replace(".dot", ".png"));
