function val = multi_var_gaussian_probability_density(mu, Sigma, x)
% multi_var_gaussian_probability_density
%   Computes multi-variable Gaussian Probability Density Value.
%   Formular:
%       p(x) ~ N(mu, Sigma) where d is dimension
%       p(x) = 1./((2 * pi) ^(d/2) * det(Sigma) ^ (1./2) ...
%           * exp(-1./2 * (x - mu)' * Sigma^(-1) * (x - mu))
% Input:
%   mu - mean vector of the Gauss distribution
%   Sigma - covariance matrix of the Gauss distribution
%   x - the independent variable of p(x), multi-var Gaussian probability density value
[dimension, ~] = size(mu);

%val = (1/((2*pi) ^ (dimension/2) * det(Sigma) ^ 0.5)) * exp(-0.5 * (x-mu)' * inv(Sigma) * (x-mu));
val = (1/((2 * pi) ^ (dimension/2) * det(Sigma) ^ 0.5)) ...
    * exp(-0.5 * (Sigma \ (x - mu))' * (x - mu));

end

