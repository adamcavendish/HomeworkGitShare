function hw24_plot_data(DataSet, BasedGaussDistIndex, mu)
    [c, ~] = size(mu);

    if c > 6
        disp(['Warning: This function supports only a maximum'...
        'of 6 gauss dist classes']);
        disp('We will draw the first 6 classes');
    end

    g1index = (BasedGaussDistIndex == 1);
    g2index = (BasedGaussDistIndex == 2);
    g3index = (BasedGaussDistIndex == 3);
    g4index = (BasedGaussDistIndex == 4);
    g5index = (BasedGaussDistIndex == 5);
    g6index = (BasedGaussDistIndex == 6);

    g1 = DataSet(g1index, :);
    g2 = DataSet(g2index, :);
    g3 = DataSet(g3index, :);
    g4 = DataSet(g4index, :);
    g5 = DataSet(g5index, :);
    g6 = DataSet(g6index, :);

    figure(1);
    % plot the DataSet
    hold on;
    plot(g1(:, 1), g1(:, 2), 'r.');
    plot(g2(:, 1), g2(:, 2), 'g.');
    plot(g3(:, 1), g3(:, 2), 'b.');
    plot(g4(:, 1), g4(:, 2), 'y.');
    plot(g5(:, 1), g5(:, 2), 'm.');
    plot(g6(:, 1), g6(:, 2), 'c.');

    % plot the `mu`
    plot(mu(:, 1), mu(:, 2), 'k + ');
end

