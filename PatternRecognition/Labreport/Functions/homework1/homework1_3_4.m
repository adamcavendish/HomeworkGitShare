Prob = [0.5 0.5];
mu = [1 1; 3 3];
Sig = zeros(2,2,2);
Sig(:,:,1) = [1 0; 0 1];
Sig(:,:,2) = [1 0; 0 1];

x = [1.8 1.8];

disp('mu1:'); disp(mu(1,:));
disp('mu2:'); disp(mu(2,:));
disp('Sigma1:'); disp(Sig(:,:,1));
disp('Sigma2:'); disp(Sig(:,:,2));
disp('x: '); disp(x);

fprintf('----------\n');
ret = bayes_classifier(mu, Sig, Prob, x);
disp('Probability: '); disp(Prob);
fprintf('Class: %i\n', ret);
fprintf('----------\n');

Prob = [1/6 5/6];
ret = bayes_classifier(mu, Sig, Prob, x);
disp('Probability: '); disp(Prob);
fprintf('Class: %i\n', ret);
fprintf('----------\n');

Prob = [5/6 1/6];
ret = bayes_classifier(mu, Sig, Prob, x);
disp('Probability: '); disp(Prob);
fprintf('Class: %i\n', ret);
fprintf('----------\n');

