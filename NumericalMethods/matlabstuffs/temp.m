x_data = linspace(0, 3);
y_data = cos(x_data);
axis([0 3 -1 1]);
plot(x_data, y_data);

hold on

X = [0 1 2 3];
Y = cos(X);
[C, ~] = newpoly(X, Y);
y_data = polyval(C, x_data);
plot(x_data, y_data);

plot(X, Y, '*');