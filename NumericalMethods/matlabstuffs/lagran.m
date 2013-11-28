function [C, L]=lagran(X, Y)
% INPUT - X is a vector that contains a list of abscissas
%           - Y is a vector that contains a list of ordinates
% Output - C is a matrix that contains the coefficients of the Lagrange
% interpolatory polynomial
%            - L is a matrix that contains the Lagrange coefficient
%            polynomials

w = length(X);
n = w-1;
L = zeros(w, w);

% Form the Lagrange coefficient polynomials
for k = 1:n+1
    V = 1;
    for j = 1: n+1
        if k~= j
            V = conv(V, poly(X(j)))/(X(k)-X(j));
        end
    end
    L(k, :) = V;
end

%Determine the coefficients of the Lagrange interpolating polynomial
C = Y*L;
end
