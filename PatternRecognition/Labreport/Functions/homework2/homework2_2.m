maxn = 5;
minn = -5;
step = 0.5;

x1 = minn:step:maxn;
x2 = minn:step:maxn;
[~, sz] = size(x1);
z = zeros(sz, sz);

icnt = 1;
jcnt = 1;
for i = minn:step:maxn
    jcnt = 1;
    for j = minn:step:maxn
        z(icnt, jcnt) = multi_var_gaussian_probability_density([1;-1], [3 0; 0 3], [i; j]);
        %z(icnt, jcnt) = mvnpdf([i j], [1 -1], [3 0; 0 3]);
        
        jcnt = jcnt + 1;
    end
    icnt = icnt + 1;
end

surf(x1, x2, z)