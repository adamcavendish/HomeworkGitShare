function [ DataSet, BasedGaussDistIndex ] = generate_gauss_classes(mu, Sigma, Probability, Count)
% BRIEF: generate gauss data set
%
% `a` is the dimension of your data set, and we are going to make `N` of them
% `c` is the number of `gauss distribution`(s) that we should use
%
% INPUTS:
%    `mu` is  a `c*a` matrix, each row is the mean vector of the ith
% distribution.
%    `Sigma` is a `a*a*c` matrix, each S(:,:,i) is the covariance of the ith
% distribution.
%    `Probability` is a `c*1` vector, representing the corresponding probability
% of ith distribution.
%    `count` is the number of data sets that we are going to generate
%
% OUTPUTS:
%    `DataSet` is a `a*N` matrix, the corresponding data set (every row is
% a data set)
%    `BasedGaussDistIndex` is the index matrix, representing the ith data set
% is generated based on the jth gauss distribution.

if sum(Probability) ~= 1
    error(['The `Probability` vector indicating the probability should'...
    'sum up to 1.0']);
end

[row, column] = size(mu);
DataSet = zeros(Count, column);
BasedGaussDistIndex = zeros(Count, 1);

% Generate the Acucumulated Probability Vector
prob_sz = row;
ProbGenVec = zeros(prob_sz, 1);
accumulated_probability = 0;
for i = 1 : prob_sz
    accumulated_probability = accumulated_probability + Probability(i, 1);
    ProbGenVec(i, 1) = accumulated_probability;
end

% `ith` is a variable storing using of ith Gauss Distribution.
% (Bad design though because of matlab)
ith = 0;

for i = 1 : Count
    % rand to use ith Gauss Distribution
    rnd = rand();
    for j = 1 : prob_sz
        if rnd < ProbGenVec(j, 1)
            ith = j;
            break;
        end
    end

    temp = mvnrnd(mu(ith,:), Sigma(:,:,ith), 1);
    DataSet(i,:) = temp;
    BasedGaussDistIndex(i, 1) = ith;
end

end
