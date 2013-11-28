h = 0.1;
x_init_val = 20;
x_num = 10;

X = zeros(x_num);
fprintf('X: ');
for i = 1 : x_num
    X(i) = x_init_val + h * i;
    fprintf('%f ', X(i));
end
fprintf('\n');

Y = X.^2;
fprintf('Y: ');
for i = 1 : x_num
    fprintf('%f ', Y(i));
end
fprintf('\n');

vals_num = 9;
vals = zeros(vals_num);
for i = 1 : vals_num
    t = 1/vals_num * i + x_init_val;
    [~, val] = diff_poly_new(X, Y, t);
    vals(i) = val;
end

x_val = linspace(x_init_val, x_init_val + 1);
y_val = 2.*x_val;
plot(x_val, y_val);

hold on
for i = 1 : vals_num
    x_val = 1/vals_num * i + x_init_val;
    plot(x_val, vals(i), '*');
end
hold off
