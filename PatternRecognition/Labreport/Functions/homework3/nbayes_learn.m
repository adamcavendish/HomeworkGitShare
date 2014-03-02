function [params] = nbayes_learn(traindata, trainlabels)
% function [params] = nbayeslearn(traindata,trainlabels)
%
%  function to learn from data the probabilities for a naive Bayes model 
%
%                                             CS 177 template, Homework 3
%                                                             Winter 2007
%
%  Inputs
%     traindata: a n x d data matrix, d features/variables and n observations
%     trainlabels: a n x 1 vector of classlabels for traindata  
%     [Note to 177 students: you can if you wish assume that all variables
%      are binary, taking values = 1 or 2]
% 
%  Output
%     params: a stucture for the parameters for a Naive Bayes classifier
%     params(j).mprobs(k): probability that variable j takes value k
%     params(j).cprobs(k,i): conditional probability
%                          of prob(variable j = value k | class = value i) 
%     params(1).classprobs(i): probability that class variable = i 

% NOTE TO 177 STUDENTS: YOU ARE FREE TO WRITE THIS CODE IN ANY
% WAY YOU LIKE AS LONG AS IT TAKES AND RETURNS THE ARGUMENTS ABOVE.
% THE OUTLINE BELOW IS JUST ONE EXAMPLE OF HOW YOU COULD WRITE THIS CODE. 
 
% ... define global parameters, etc............ 
nclasses = 2;
[n, d] = size(traindata);

% Estimate class probabilities and conditional probabilities  
for i=1:nclasses
    index = find(trainlabels==i);

    data_ci = traindata(index,:);
    ni = size(index, 1);

    params(1).classprobs(i) = ni/n;  % estimate the probability of class i 

    for j = 1:d 
        data_jcol = data_ci(:,j);
        for k=1:2
            data_k = find(data_jcol == k);
            % estimate prob(variable j = k | class i)
            params(j).cprobs(k,i) = (size(data_k, 1) + 0.5)/(ni + 1);
        end
    end
end
 
% Estimate the probabilities p(x_j = value_k)
for j = 1:d 
    for k=1:2; 
        index = find(traindata(:,j)==k);
        % estimate  prob(variable x_j = k)
        params(j).mprobs(k) = size(index, 1)/n;
    end
end
 
end

