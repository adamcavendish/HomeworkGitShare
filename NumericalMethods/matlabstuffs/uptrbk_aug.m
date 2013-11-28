function [ Aret, Bret ] = uptrbk_aug( A, B )
%UPTRBK_AUG Return the augmented matrix (Ax=B)'s upper triangle form
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
    
    Aret = A;
    Bret = B;
    
    for i = 1 : N-1
        [~, maxrowid] = max(abs(Aret(i:N, i)));
        
        % swap the row
        row = Aret(i, :); Aret(i, :) = Aret(maxrowid+i-1, :); Aret(maxrowid+i-1, :) = row;
        temp = Bret(i, 1); Bret(i, 1) = Bret(maxrowid+i-1, 1); Bret(maxrowid+i-1, 1) = temp;
        if Aret(i, i) == 0
            error('A is a singular matrix');
        end
        
        % elimination at column p
        for j = i+1 : N
            m = Aret(j, i)/Aret(i, i);
            Aret(j, i : N) = Aret(j, i : N) - m * Aret(i, i : N);
            Bret(j, 1) = Bret(j, 1) - m * Bret(i, 1);
        end
    end
end
