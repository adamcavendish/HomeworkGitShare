function perceptronDemo
%PERCEPTRONDEMO
%
%   A simple demonstration of the perceptron algorithm for training
%   a linear classifier, made as readable as possible for tutorial
%   purposes. It is derived from the treatment of linear learning
%   machines presented in Chapter 2 of "An Introduction to Support
%   Vector Machines" by Nello Cristianini and John Shawe-Taylor.
%
%

    Data  = createTrainingData;
    Model = trainPerceptron( Data );

end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function Model = trainPerceptron( Data )
%TRAINPERCEPTRON

    DOWN   = 1;
    ACROSS = 2;

    assert( isequal( unique( Data.labels ), [-1; +1] ), ...
        'Labels must be -1 or +1' );

    % ---------------------------------------------------------------------
    % Normalise the data by calculating z-scores
    %
    %   This makes plotting easier, but is not needed by the algorithm.
    %

    sampleMean   = mean( Data.samples );
    sampleStdDev = std(  Data.samples );
    Data.samples = bsxfun( @minus,   Data.samples, sampleMean   );
    Data.samples = bsxfun( @rdivide, Data.samples, sampleStdDev );

    % ---------------------------------------------------------------------
    % Calculate the squared radius of the smallest ball that encloses the
    % data and is centred on the origin. This is used to provide an
    % appropriate range and step size when updating the threshold (bias)
    % parameter.
    %

    sampleSize = size( Data.samples, DOWN );
    maxNorm    = realmin;
    for iObservation = 1:sampleSize
        observationNorm = norm( Data.samples(iObservation,:) );
        if observationNorm > maxNorm
            maxNorm = observationNorm;
        end
    end
    enclosingBallRadius        = maxNorm;
    enclosingBallRadiusSquared = enclosingBallRadius .^ 2;

    % ---------------------------------------------------------------------
    % Define the starting weight vector and bias. These should be zeros,
    % as the algorithm omits a learning rate, and it is suggested in
    % Cristianini & Shawe-Taylor that learning rate may only be omitted
    % safely when the starting weight vector and bias are zero.
    %

    Model.weights = [0.0 0.0];
    Model.bias    = 0.0;

    % ---------------------------------------------------------------------
    % Run the perceptron training algorithm
    %
    %   To prevent program running forever when nonseparable data are
    %   provided, limit the number of steps in the outer loop.
    %

    maxNumSteps = 1000;

    for iStep = 1:maxNumSteps

        isAnyObsMisclassified = false;

        for iObservation = 1:sampleSize;

            inputObservation = Data.samples( iObservation, : );
            desiredLabel     = Data.labels(  iObservation    ); % +1 or -1

            perceptronOutput = sum( Model.weights .* inputObservation, ACROSS ) + Model.bias;
            margin           = desiredLabel * perceptronOutput;

            isCorrectLabel   = margin > 0;

            % -------------------------------------------------------------
            % If the model misclassifies the observation, update the
            % weights and the bias.
            %

            if ~isCorrectLabel

                isAnyObsMisclassified = true;

                weightCorrection = desiredLabel  * inputObservation;
                Model.weights    = Model.weights + weightCorrection;

                biasCorrection   = desiredLabel .* enclosingBallRadiusSquared;
                Model.bias       = Model.bias   + biasCorrection;

                displayPerceptronState( Data, Model );

            end % if this observation misclassified.

        end % loop over observations

        if ~isAnyObsMisclassified
            disp( 'Done!' );
            break;
        end

    end % outer loop

end % TRAINPERCEPTRON
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function Data = createTrainingData
%CREATETRAININGDATA
%
%   Return a structure containing training data suitable for linear
%   classification.
%

    sampleAsize   = 1024;
    sampleBsize   = 1024;

    sampleAmean   = [ 5.5 5.0 ];
    sampleAstdDev = [ 0.5 1.0 ];

    sampleBmean   = [ 2.5 3.0 ];
    sampleBstdDev = [ 0.3 0.7 ];

    Data.samples  = [ normallyDistributedSample( sampleAsize, sampleAmean, sampleAstdDev ); ...
                      normallyDistributedSample( sampleBsize, sampleBmean, sampleBstdDev ) ];

    Data.labels   = [  ones(sampleAsize,1); ...
                      -ones(sampleBsize,1) ];

    % ---------------------------------------------------------------------
    % Randomly permute samples & class labels.
    %
    %   This is not really necessary, but done to illustrate that the order
    %   in which observations are evaluated does not matter.
    %

    randomOrder   = randperm( sampleAsize + sampleBsize );
    Data.samples  = Data.samples( randomOrder, : );
    Data.labels   = Data.labels(  randomOrder, : );

end % CREATETRAININGDATA
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function samples = normallyDistributedSample( sampleSize, sampleMean, sampleStdDev )
%NORMALDISTRIBUTIONSAMPLE
%
%   Draw a sample from a normal distribution with specified mean and
%   standard deviation.
%

    assert(    isequal( size( sampleMean ), size( sampleStdDev ) ) ...
            && 1 == size( sampleMean, 1 ),                         ...
        'Sample mean and standard deviation must be row vectors of equal length.' );

    numFeatures = numel( sampleMean );
    samples     = randn( sampleSize, numFeatures );
    samples     = bsxfun( @times, samples, sampleStdDev );
    samples     = bsxfun( @plus,  samples, sampleMean   );

end % NORMALDISTRIBUTIONSAMPLE
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function displayPerceptronState( Data, Model )
%DISPLAYPERCEPTRONSTATE

    hFig = figure( 1 );
    clf;
    set( hFig,                        ...
        'NumberTitle', 'off',         ...
        'Name',         mfilename,    ...
        'MenuBar',      'none',       ...
        'Color',        [1.0 1.0 1.0] );

    displayXmin = -4;
    displayXmax =  4;
    displayYmin = -4;
    displayYmax =  4;

    hAx = subplot( 1, 1, 1 );
    axis('equal');
    set( hAx,                                  ...
        'Box',      'on',                      ...
        'NextPlot', 'add',                     ...
        'xgrid',    'on',                      ...
        'ygrid',    'on',                      ...
        'xlim',     [displayXmin displayXmax], ... % Bounds suitable for Z-scored data
        'ylim',     [displayYmin displayYmax]  );
    xlabel( 'x_1' );
    ylabel( 'x_2' );

    % ---------------------------------------------------------------------
    % Plot data points from the two classes
    %

    isPositiveClass = Data.labels >  0;
    isNegativeClass = Data.labels <= 0;

    plot( hAx, Data.samples(isPositiveClass,1), Data.samples(isPositiveClass,2), 'b+' );
    plot( hAx, Data.samples(isNegativeClass,1), Data.samples(isNegativeClass,2), 'rx' );

    % ---------------------------------------------------------------------
    % Display parameters for separating hyperplane in title
    %

    xWeight   = Model.weights(1);
    yWeight   = Model.weights(2);
    bias      = Model.bias;

    szTitle   = sprintf( 'Linear classifier parameters: %0.2f x_1 + %0.2f x_2 + %0.2f = 0', xWeight, yWeight, bias );
    title( szTitle );

    % ---------------------------------------------------------------------
    % Plot separating hyperplane
    %

    y1 = ( (xWeight*displayXmin) + bias ) ./ -yWeight;
    y2 = ( (xWeight*displayXmax) + bias ) ./ -yWeight;

    plot( hAx, [displayXmin; displayXmax], [y1, y2], 'k-', 'linewidth', 2 );

    pause(0.1);

end % DISPLAYPERCEPTRONSTATE 



 