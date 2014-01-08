#pragma once

namespace adamcavendish {
namespace algorithm {

kmp(T, p)
{
	n = length(T);
	m = length(p);
	f = next(p);
	q = 0;
	for(i = 1:n) {
		while(q > 0 && p[q+1] != T[i])
			q = f[q];
		if(p[q+1] = T[i])
			q = q+1;
		if(q == m) {
			print "Pattern occurs with shift" i - m;
			q = f[q];
		}
	}
}
	

next(p)
{
	m = length(p);
	// f start with 1
	f[1] = 0;
	k = 0;
	for(q= 2 : m) {
		while(k > 0 && p[k+1] != p[q])
			k = f[k];
		if(p[k+1] == p[q])
			k = k+1;
		f[q] = k;
	}
	return f;
}//next

}

}//namespace algorithm
}//namespace adamcavendish

