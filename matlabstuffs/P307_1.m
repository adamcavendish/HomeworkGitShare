% Set the tolerance
tol = 1e-6;

f = @(x)  sin(2 .* x) ./ (1 + x .^ 5);
[~, value, ~] = integrate_simpson_adapt(f, 0, 3, tol);
rvalue = integral(f, 0, 3);
fprintf('function is:');
disp(f);
fprintf('\bvalue = %f, realvalue = %f\n\n', value, rvalue);

f = @(x) sin(4 .* x) .* exp(-2 .* x);
[~, value, ~] = integrate_simpson_adapt(f, 0, 3, tol);
rvalue = integral(f, 0, 3);
fprintf('function is:');
disp(f);
fprintf('\bvalue = %f, realvalue = %f\n\n', value, rvalue);


f = @(x) 1 ./ sqrt(x);
[~, value, ~] = integrate_simpson_adapt(f, 0.04, 1, tol);
rvalue = integral(f, 0.04, 1);
fprintf('function is:');
disp(f);
fprintf('\bvalue = %f, realvalue = %f\n\n', value, rvalue);

f = @(x) 1 ./ (x .^ 2 + 1/10);
[~, value, ~] = integrate_simpson_adapt(f, 0, 2, tol);
rvalue = integral(f, 0, 2);
fprintf('function is:');
disp(f);
fprintf('\bvalue = %f, realvalue = %f\n\n', value, rvalue);

f = @(x) sin(1 ./ x);
[~, value, ~] = integrate_simpson_adapt(f, 1/(2*pi), 2, tol);
rvalue = integral(f, 1/(2*pi), 2);
fprintf('function is:');
disp(f);
fprintf('\bvalue = %f, realvalue = %f\n\n', value, rvalue);

f = @(x) sqrt(4 .* x) - x .^ 2;
[~, value, ~] = integrate_simpson_adapt(f, 0, 2, tol);
rvalue = integral(f, 0, 2);
fprintf('function is:');
disp(f);
fprintf('\bvalue = %f, realvalue = %f\n\n', value, rvalue);
