function result = bayes_classifier(mu, Sigma, Probability, DataSet)
% BRIEF: Use Bayes Classifier to classify DataSet
%
% `a` is the dimension of your data set
% `c` is the number of `gauss distribution`(s) that we should use
% 
% INPUTS:
%    `mu` is  a `c*a` matrix, each row is the mean vector of the ith
% distribution.
%    `Sigma` is a `a*a*c` matrix, each S(:,:,i) is the covariance of the ith
% distribution.
%    `Probability` is a `c*1` vector, representing the corresponding probability
% of ith distribution.
%    `DataSet` is a `a*N` matrix, the input DataSet,
% each row contains one sample data

    [N, ~] = size(DataSet);
    [c, ~] = size(mu);

    t = zeros(1, c);
    result = zeros(1, N);
    
    for i = 1 : N
        for j = 1 : c
            t(j) = Probability(j) * mvnpdf(DataSet(i, :), mu(j, :), Sigma(:,:,j));
        end
        [~, result(i)] = max(t);
    end
end

