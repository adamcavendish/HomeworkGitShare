function [ Xret ] = backsub( A, B )
%BACKSUB Back substitution
%   A must be a upper triangular square matrix and non-singular
%   B must be a N*1 matrix where N is the size of A
    [nrowb, ncolb] = size(B);
    if 1 ~= ncolb
        error('B must be a n*1 matrix');
    end
    
    [nrowa, ncola] = size(A);
    if nrowa ~= ncola
        error('A must be a square matrix');
    else
        N = nrowa;
    end
    
    if nrowb ~= N
        error('B column size must equal to A column size');
    end
    
    Xret = zeros(N, 1);
    
    Xret(N, 1) = B(N, 1)/A(N, N);
    for i = N-1 : -1 : 1
        Xret(i, 1) = (B(i, 1) - A(i, i+1 : N)*Xret(i + 1:N, 1))/A(i, i);
    end
end
