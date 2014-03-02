a = 2;
c = 6; % maximum is 6 because of colors

m = zeros(c, a);
m(1,:) = [-50 0];
m(2,:) = [0 -50];
m(3,:) = [0 0];
m(4,:) = [50 0];
m(5,:) = [0 50];
m(6,:) = [50 50];

S = zeros(a,a,c);
S(:,:,1) = [10 0; 0 10];
S(:,:,2) = [10 0; 0 10];
S(:,:,3) = [100 0; 0 100];
S(:,:,4) = [10 0; 0 10];
S(:,:,5) = [10 0; 0 10];
S(:,:,6) = [10 0; 0 10];

P = zeros(c, 1);
P(1) = 0.1;
P(2) = 0.4;
P(3) = 0.1;
P(4) = 0.2;
P(5) = 0.1;
P(6) = 0.1;

[X, y] = generate_gauss_classes(m,S,P,5000);
disp('Base: ');
disp(y);
disp('DataSet: ');
disp(X);

hw24_plot_data(X, y, m);

