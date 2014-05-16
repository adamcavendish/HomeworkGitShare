var gradeManagementApp = angular.module('gradeManagementApp', ['ui.bootstrap', 'ngGrid', 'customFilter'])
.directive('cusFocus', ['$parse', function($parse) {
    return {
        restrict: 'A',
        link: function(scope, element, attr) {
            element.bind('focus', function () {
                scope.$eval(attr.cusFocus);
            });
        }
    };
}])
.directive('cusBlur', ['$parse', function($parse) {
    return {
        restrict: 'A',
        link: function(scope, element, attr) {
            element.bind('blur', function () {
                scope.$eval(attr.cusBlur);
            });
        }
    };
}])
.directive('scoreDirective', function() {
    return {
        require: 'ngModel',
        link: function(scope, element, attrs, ngModelController) {
            ngModelController.$parsers.push(function(data) {
                //convert data from view format to model format
                console.log(data);
                if(data <= 0 || isNaN(parseInt(data))) {
                    data = -1;
                }//if
                return data; //converted
            });

            ngModelController.$formatters.push(function(data) {
                //convert data from model format to view format
                if(data <= 0 || isNaN(parseInt(data))) {
                    data = 'Unavailable';
                }//if
                return data; //converted
            });
        }
    }
});

var genderCellTemplate = '<div class="ngCellText" ng-class="col.colIndex()"><span ng-cell-text>{{row.entity.gender | genderFilter}}</span></div>';
var overallScoreCellTemplate = 
    '<div class="ngCellText" ng-class="col.colIndex()"><span ng-cell-text>{{row.entity.overallScore | scoreFilter}}</span></div>';
var cellEditableTemplate = '<input score-directive ng-class="\'colt\' + col.index" ng-input="COL_FIELD" ng-model="COL_FIELD" cus-blur="onOverallScoreBlur(row, col)"/>';

gradeManagementApp.controller('accordionGradeManagementCtrl', ['$scope', '$http',
    function ($scope, $http) {
        $scope.getCourseSelectionFunction = function() {
            $http.get('/CourseSelection.json').success(function(data) {
                $scope.courseSelection = data;
            });
        };

        $scope.refreshData = function(event) {
            if(event)
                event.preventDefault();

            $scope.getCourseSelectionFunction();
        };
        
        $scope.courseSelectionGridOptions = {
            data: 'courseSelection',
            enableCellSelection: false,
            enableRowSelection: true,
            enableCellEditOnFocus: true,
            multiSelect: false,
            columnDefs: [
                {field: 'studentId', displayName: 'StudentID'},
                {field: 'semester', displayName: 'Semester'},
                {field: 'courseId', displayName: 'CourseID'},
                {field: 'teacherId', displayName: 'TeacherID'},
                {field: 'overallScore', displayName: 'Overall Score', editableCellTemplate: cellEditableTemplate, cellTemplate: overallScoreCellTemplate}
            ]
        };
        
        $scope.onOverallScoreBlur = function(row, col) {
            var rowData = row.entity;
            
            $.ajax({
                type: 'POST',
                data: rowData,
                url: '/updateCourseSelection_post',
                dataType: 'JSON'
            }).done(function(response) {
                if (response.msg === '') {
                    $scope.getCourseSelectionFunction();
                } else {
                    alert('Error: ' + JSON.stringify(response.msg));
                }//if-else
            });
        }
    }]);

