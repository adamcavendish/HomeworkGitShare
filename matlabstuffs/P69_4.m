% How to run:
% >> P69_4
% Expected:
% 7^(1/3) = 1.912931182772389e+00
% 200^(1/3) = 5.848035476425732e+00
% -7^(1/3) = -1.912931182772389e+00

r1 = cube_root(7, 2, eps);
fprintf('7^(1/3) = %.15e\n', r1);

r2 = cube_root(200, 6, eps);
fprintf('200^(1/3) = %.15e\n', r2);

r3 = cube_root(-7, -2, eps);
fprintf('-7^(1/3) = %.15e\n', r3);
