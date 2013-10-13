function [ X ] = gauss_seidel(A, B, X_init, tolerance, max_iter)
% Input
%    - A is an N * N nonsigular matrix
%    - B is an N * 1 matrix
%    - X_init is the initial guesses of X
%    - tolerance is the tolerance for X
%    - max_iter is the maximum number of iterations
% Output
%    - X is an N * 1 matrix: the gauss-seidel approximation
%       to the solution of A*X = B

N = length(B);

for k = 1 : max_iter
    for j = 1:N
        if j == 1
            X(1) = (B(1) - A(1, 2:N) * X_init(2 : N))/A(1, 1);
        elseif j == N
            X(N) = (B(N) - A(N, 1:N-1)*(X(1:N-1))')/A(N, N);
        else
            X(j) = (B(j) - A(j, 1:j-1)*X(1:j-1)' - A(j,j+1:N)*X_init(j+1:N))/A(j, j);
        end
    end
    
    err = abs(norm(X'-X_init));
    relerr = err/(norm(X) + eps);
    X_init = X';
    
    if (err < tolerance) || (relerr < tolerance)
        break;
    end
end

X = X';

end

