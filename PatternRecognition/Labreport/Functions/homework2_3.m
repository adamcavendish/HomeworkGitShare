a = 3;
c = 4;

m = zeros(c, a);
m(1,:) = [-50 0 0];
m(2,:) = [0 -50 0];
m(3,:) = [0 0 -50];
m(4,:) = [50 50 50];

S = zeros(a,a,c);
S(:,:,1) = [10 0 0; 0 10 0; 0 0 10];
S(:,:,2) = [10 0 0; 0 10 0; 0 0 10];
S(:,:,3) = [10 0 0; 0 10 0; 0 0 10];
S(:,:,4) = [1000 0 0; 0 1000 0; 0 0 1000];

P = zeros(c, 1);
P(1) = 0.1;
P(2) = 0.2;
P(3) = 0.5;
P(4) = 0.2;

[X, y] = generate_gauss_classes(m,S,P,1000);
disp('Base: ');
disp(y);
disp('DataSet: ');
disp(X);

g1index = find(y == 1);
g2index = find(y == 2);
g3index = find(y == 3);
g4index = find(y == 4);

g1 = X(g1index, :);
g2 = X(g2index, :);
g3 = X(g3index, :);
g4 = X(g4index, :);

figure
grid on
hold all
scatter3(g1(:,1), g1(:,2), g1(:,3), 'MarkerFaceColor', [0, 0.75, 0.75]);
scatter3(g2(:,1), g2(:,2), g2(:,3), 'MarkerFaceColor', [0.75, 0, 0.75]);
scatter3(g3(:,1), g3(:,2), g3(:,3), 'MarkerFaceColor', [0.75, 0.75, 0]);
scatter3(g4(:,1), g4(:,2), g4(:,3), 'MarkerFaceColor', [0.75, 0.75, 0.75]);
