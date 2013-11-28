function [ Aret ] = uptrbk( A )
%UPTRBK returns A's upper triangle form
    [nrow, ncol] = size(A);
    if nrow ~= ncol
        error('A must be a square matrix');
    else
        N = nrow;
    end
    
    Aret = A;
    for i = 1 : N-1
        [~, maxrowid] = max(abs(Aret(i:N, i)));
        
        % swap the row
        row = Aret(i, :); Aret(i, :) = Aret(maxrowid+i-1, :); Aret(maxrowid+i-1, :) = row;
        if Aret(i, i) == 0
            error('A is a singular matrix');
        end
        
        % elimination at column p
        for j = i+1 : N
            m = Aret(j, i)/Aret(i, i);
            Aret(j, i : N) = Aret(j, i : N) - m * Aret(i, i : N);           
        end
    end


end

