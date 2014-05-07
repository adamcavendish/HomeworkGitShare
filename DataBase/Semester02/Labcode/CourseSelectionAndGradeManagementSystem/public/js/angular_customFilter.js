angular.module('customFilter', [])
    .filter('genderFilter', function() {
        return function(gender) {
            return (gender === true) ? 'Male' : 'Female';
        };
    })
    .filter('scoreFilter', function() {
        return function(score) {
            return (score >= 0) ? score : 'Unavailable';
        };
    });