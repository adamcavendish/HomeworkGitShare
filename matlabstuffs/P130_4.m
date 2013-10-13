A = diag(12*ones(50,1)) + diag(ones(48,1), -2) + diag(-2*ones(49,1),-1)	+ diag(-2*ones(49,1),1) + diag(ones(48,1), 2);
B = 5 * ones(50, 1);
X = gauss_seidel(A, B, B, eps, 10000)
