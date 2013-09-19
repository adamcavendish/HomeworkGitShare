function [ X, Aupper, Bupper ] = linear_solve( A, B )
%LINEAR_SOLVE Solves linear equations
    [Aupper, Bupper] = uptrbk_aug(A, B);
    X = backsub(Aupper, Bupper);
end
