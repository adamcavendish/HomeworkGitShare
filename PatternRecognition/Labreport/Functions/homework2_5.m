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

ret = bayes_classifier(m, S, P, X);

disp('sum(abs(bayes_classifer_result - answer)): ');
disp(sum(abs(ret' - y)));

