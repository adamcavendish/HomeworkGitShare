clear;

m=[1 1 1; 5 3 2; 3 3 4]';
[l,c]=size(m);
S1=[0.8 0.2 0.1; 0.2 0.8 0.2; 0.1 0.2 0.8];
S(:,:,1)=S1;
S(:,:,2)=S1;
S(:,:,3)=S1;
P=[1/3 1/3 1/3];

% 1. Generate X1
N1=120;
randn('seed',0)
[X1,y1]=generate_gauss_classes(m,S,P,N1);
[l,N1]=size(X1);
X1=[X1; ones(1,N1)];

% Generate X2
N2=120;
randn('seed',100)
[X2,y2]=generate_gauss_classes(m,S,P,N2);
[l,N2]=size(X2);
X2=[X2; ones(1,N2)];

% Generate z1
z1=-ones(c,N1);
for i=1:N1
    z1(y1(i),i)=1;
end

% Generate z2
z2=-ones(c,N2);
for i=1:N2
    z2(y2(i),i)=1;
end

dlmwrite('data242/data242.mat', X1);
dlmwrite('data242/data242.mat', z1, '-append');
dlmwrite('data242/data242-test.mat', X2);
dlmwrite('data242/data242-test.mat', z2, '-append');

