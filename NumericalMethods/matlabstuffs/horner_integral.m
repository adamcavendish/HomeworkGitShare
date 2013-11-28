function [ Val ] = horner_integral( Poly, C, X )
%horder_integral: calculate integral of P(x)dx via horner method
%   Poly --- the polynomial vector
%   C --- the constant vector
%   X --- the variant vector

n = length(Poly);
Val = Poly(1)/n * X;
for i = 2 : n
    Val = (Poly(i)/(n - i + 1) + Val)' * X;
end
Val = Val + C;

end

