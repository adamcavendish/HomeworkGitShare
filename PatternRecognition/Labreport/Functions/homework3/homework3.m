features_mat = dlmread('spam_features.txt');
labels_mat = dlmread('spam_labels.txt');

[row, ~] = size(labels_mat);
trainamount = floor(row/2);

traindata = features_mat(1:trainamount, :);
trainlabels = labels_mat(1:trainamount, :);
testdata = features_mat(trainamount+1:row, :);
testlabels = labels_mat(trainamount+1:row, :);

params = nbayes_learn(traindata, trainlabels);
predictions = nbayes_predict(params, testdata);

temp = abs(predictions - testlabels);
rate = sum(temp)/size(temp, 1);

fprintf('Training Data size = %d\n', trainamount);
fprintf('Accuracy = %f\n', 1-rate);

