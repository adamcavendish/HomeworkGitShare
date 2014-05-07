'use strict';

var usersApp = angular.module('usersApp', []);
/*
usersApp.controller('usersCtrl', function($scope) {
        $scope.users = [{ 'name': 'abc' }, {'name': 'def'}];
    });
*/

usersApp.controller('usersCtrl', ['$scope', '$http',
    function($scope, $http) {
        $http.get('student.json').success(function(data) {
            $scope.users = data.splice(0, 5);
        });
    }]);