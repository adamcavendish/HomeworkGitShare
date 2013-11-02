function [ A, df ] = diff_poly_new( X, Y, t )
% Input
%   - X is the 1xn abscissa vector
%   - Y is the 1xn ordinate vector
%   - t is the value x in the `P'(x)`
% Output
%   - A is the 1xn vector containing the coefficients of the Nth-degree
%       Newton polynomial
%   - df is the approximate derivative

A = Y;
N = length(X);
for j = 2:N
    for k = N: -1: j
        A(k) = (A(k) - A(k-1))/(X(k)-X(k-j+1));
    end
end

df = A(2);
n1 = length(A) - 1;
for i = 2 : n1
    sum = 0;
    for k = 1 : i
        product = 1;
        for j = 1 : i
            if j == k
                continue;
            end
            product = product * (t - X(j));
        end
        sum = sum + product;
    end
    df = df + sum * A(i+1);
end

end
