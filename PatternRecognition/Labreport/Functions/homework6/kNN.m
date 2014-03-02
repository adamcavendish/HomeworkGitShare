function dataTag = kNN(train, trainTag, k, data)

% FUNCTION
%  dataTag = kNN(train, trainTag, k, data)
% Use k-Nearest-Neighbor classifying algorithm to classify data
%
% INPUT ARGUMENTS:
%  s1 is the number of features in the matrix
%  s2 is the number of Training Data provided
%  s3 is the number of Classifiying Data provided
%
%  train: s1*s2 matrix, the training data
%  trainTag: 1*s2 matrix, the training data tag naming the categories
%  k: the results should be splited into k categories
%  data: s1*s3 matrix, the data to be classified
% OUTPUT ARGUMENTS:
%  dataTag: 1*s3 matrix, the corresponding categories of data

s2 = size(train, 2);
s3 = size(data, 2);

% the returning dataTag
dataTag = zeros(1, s3);

% distanceList is the temporary saving for Euclidean Distance List
% between data(:, i) and every training data
distanceList = zeros(1, s2);

% realk is the real k, aka number of categories, used in the program
realk = min([k s2]);

for i = 1 : s3
    % compute distance between data(:, i) and every training data
    vdata = data(:, i)';
    for j = 1 : s2
        % compute Euclidean Distance
        %distanceList(1, j) = norm(train(:, j)' - data(:, i)');
        vsub = train(:, j)' - vdata;
        distanceList(1, j) = (vsub * vsub');
    end
    % sort the distance, and get the indexes
    [~, index] = sort(distanceList, 'descend');

    tagMap = containers.Map('KeyType', 'int64', 'ValueType', 'int64');
    for kk = 1 : realk
        tag = trainTag(1, index(1, kk));
        if tagMap.isKey(tag) == 0
            tagMap(tag) = 0;
        end

        tagMap(tag) = tagMap(tag) + 1;
    end

    % terrible matlab
    values = tagMap.values;
    values = [values{:}];
    [~, max_value_index] = max(values);
    keys = tagMap.keys;
    dataTag(1, i) = keys{max_value_index};
end

end
