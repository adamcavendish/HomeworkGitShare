clear

format compact

l=2;   % Dimensionality
N=150; % Number of vectors

% Generate the training set X1
rand('seed',0)
X1=10*rand(l,N)-5;
for i=1:N
    t=0.05*(X1(1,i)^3+X1(1,i)^2+X1(1,i)+1);
    if(t>X1(2,i))
        y1(i)=1;
    else
        y1(i)=-1;
    end
end

% Generate the test set X2
rand('seed',100)
X2=10*rand(l,N)-5;
for i=1:N
    t=0.05*(X2(1,i)^3+X2(1,i)^2+X2(1,i)+1);
    if(t>X2(2,i))
        y2(i)=1;
    else
        y2(i)=-1;
    end
end

dlmwrite('data251/data251.mat', X1);
dlmwrite('data251/data251.mat', y1, '-append');
dlmwrite('data251/data251-test.mat', X2);
dlmwrite('data251/data251-test.mat', y2, '-append');

