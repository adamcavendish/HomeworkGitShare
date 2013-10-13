% f(x) = x + 2/x
hold on
x_data = linspace(0.5, 2.5);
y_data = x_data + 2 ./ x_data;
plot(x_data, y_data);

X = [1 2 2.5];
Y = X + 2 ./ X;

[C, ~] = newpoly(X, Y);
fprintf('quadratic newton f(1.5) = %.4f\n', polyval(C, 1.5));
fprintf('quadratic newton f(1.2) = %.4f\n', polyval(C, 1.2));
y_data = polyval(C, x_data);
plot(x_data, y_data, 'r');
plot(X, Y, 'r*');

X = [0.5 1 2 2.5];
Y = X + 2 ./ X;
[C, ~] = newpoly(X, Y);
fprintf('cubic newton f(1.5) = %.4f\n', polyval(C, 1.5));
fprintf('cubic newton f(1.2) = %.4f\n', polyval(C, 1.2));
y_data = polyval(C, x_data);
plot(x_data, y_data, 'g');
plot(X, Y, 'g*');

fprintf('actual data f(1.5) = %.4f\n', 1.5 + 2/1.5);
fprintf('actual data f(1.2) = %.4f\n', 1.2 + 2/1.2);