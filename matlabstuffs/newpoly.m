function [ C, D ] = newpoly( X, Y )
%Input - X is a vector that contains a list of abscissas
%         - Y is a vector that contains a list of ordinates
%Output - C is a vector that contains the coefficients of the Newton
%intepolatory polynomial
%           - D is the divided-difference table
n = length(X);
D = zeros(n, n);
D(:, 1) = Y';

% Use formula (20) to form the divided-difference table
for j = 2 : n
    for k = j : n
        D(k, j) = (D(k, j-1) - D(k-1, j-1))/(X(k) - X(k-j+1));
    end
end

% Determine the coefficients of the Newton interpolating polynomial
C = D(n, n);
for k = (n-1) : -1 : 1
    C = conv(C, poly(X(k)));
    m = length(C);
    C(m) = C(m) + D(k, k);
end

end

