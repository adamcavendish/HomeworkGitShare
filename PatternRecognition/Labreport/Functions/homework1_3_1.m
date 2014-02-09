m = [0 1]';
S = eye(2);
X1 = [0.2 1.3]';
X2 = [2.2 -1.3]';
pg1 = multi_var_gaussian_probability_density(m, S, X1);
pg2 = multi_var_gaussian_probability_density(m, S, X2);
disp(pg1);
disp(pg2);
