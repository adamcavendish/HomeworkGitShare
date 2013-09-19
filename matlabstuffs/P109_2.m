% How to run:
% first way:
% >> P109_2([])
% second way:
% >> P109_2([0 1; 1 3; 2 2; 4 1; 8 8; 5 2; 6 10])
%
% Second way will let you input any 7*2 matrix representing the corresponding 7 points
% Anyway, just have a try and you will see.
%
% Expected:
% well, the plot ...

function P109_2(data)
    if isempty(data)
        data = [0 1; 1 3; 2 2; 3 1; 4 3; 5 2; 6 1];
    end
    
    if (size(data, 1) ~= 7) || (size(data, 2) ~= 2)
        error('data must be 7*2 matrix');
    end

    fun = @(x) [x.^0, x, x.^2, x.^3, x.^4, x.^5, x.^6];

    point_x = data(:, 1);
    point_y = data(:, 2);
    A = fun(point_x);
    B = point_y;
    X = linear_solve(A, B);

    mky = @(x) fun(x') * X;
    x_space = linspace(-0.5 + min(point_x), max(point_x) + 0.5);
    y_space = mky(x_space);

    plot(x_space, y_space);
    hold on
    plot(point_x, point_y, '*');
    hold off
end

