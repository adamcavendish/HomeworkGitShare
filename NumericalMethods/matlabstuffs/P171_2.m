time_data = 1:6;
farenheit = [66 66 65 64 63 63];
[coeff, ~] = lagran(time_data, farenheit);
mean_val = (horner_integral(coeff, 0, 6) - horner_integral(coeff, 0, 1))/(6-1);
fprintf('The mean temperature is: %.4f\n', mean_val);
x_data = linspace(1, 6);
y_data = polyval(coeff, x_data);
hold on
plot(x_data, y_data);
plot(time_data, farenheit, '*');
hold off
