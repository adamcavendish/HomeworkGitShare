function [ result, err ] = cube_root( x, estimation, epsilon )
%CUBE_ROOT x^(1/3)
%   x is the x in x^(1/3)
%   estimation is the initial value of iteration
%   epsilon is the err tolerance
    p0 = estimation;
    err = epsilon + 1;
    while(err > epsilon)
        p1 = (2*p0 + x/p0^2)/3;
        err = abs(p1 - p0);
        p0 = p1;
    end
    
    result = p0;
end

