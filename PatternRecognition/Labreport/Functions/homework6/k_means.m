function [center, label] = k_means(X, center_init)
% FUNCTION
%  [center, label] = k_means(X, center_init)
%  This is k-means clustering algorithm
% INPUT ARGUMENTS:
%  s1 is the number of features in the input data matrix
%  s2 is the number of data in data matrix
%  s3 is the number of categories to be seperated, aka the 'k'
%
%  X: s1*s2 matrix, input data matrix
%  center_init: s1*s3 matrix, initial center guess matrix
% OUTPUT ARGUMENTS:
%  center: s1*s2 matrix, category center of corresponding data in X
%  label: 1*s2 vector, label of corresponding data in X

s1 = size(X, 1);
s2 = size(X, 2);
s3 = size(center_init, 2);

center = zeros(s1, s2);
label = zeros(1, s2);

center_iter = center_init;

% change_flag indicates whether center and label are changed in the loop
change_flag = 1;

while change_flag == 1
    change_flag = 0;

    % for every data
    for i = 1 : s2
        min_dist = inf;
        min_index = 0;

        % for every center
        for j = 1 : s3
            % calculate the distance between every data and every center
            distance = norm(center_iter(:, j) - X(:, i));
            if distance < min_dist
                min_dist = distance;
                min_index = j;
            end
        end
        
        % if it is changed
        if label(1, i) ~= min_index
            change_flag = 1;
            label(1, i) = min_index;
        end
    end

    % for every category, aka every center
    for i = 1 : s3
        points_in_category = find(label == i);
        center_iter(:, i) = mean(X(:, points_in_category)')';
    end
end

for i = 1 : s2
    center(:, i) = center_iter(:, label(1, i));
end

end

