var gradeManagementApp = angular.module('gradeManagementApp', ['ui.bootstrap', 'ngGrid', 'customFilter']);

var genderCellTemplate = '<div class="ngCellText" ng-class="col.colIndex()"><span ng-cell-text>{{row.entity.gender | genderFilter}}</span></div>';
var overallScoreCellTemplate = 
//    '<div class="ngCellText" ng-class="col.colIndex()"><span ng-cell-text>{{row.entity.overallScore | scoreFilter}}</span></div>';
    '<input class="form-control input-sm" type="text" value="{{row.entity.overallScore | scoreFilter}}"></input>';

gradeManagementApp.controller('accordionGradeManagementCtrl', ['$scope', '$http', 
    function($scope, $http) {
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
            enableCellEdit: false,
            multiSelect: false,
            columnDefs: [
                {field: 'studentId', displayName: 'StudentID', enableCellEdit: false},
                {field: 'semester', displayName: 'Semester', enableCellEdit: false},
                {field: 'courseId', displayName: 'CourseID', enableCellEdit: false},
                {field: 'teacherId', displayName:'TeacherID', enableCellEdit: false},
                {field: 'overallScore', displayName: 'Overall Score', enableCellEdit: false, cellTemplate: overallScoreCellTemplate},
            ]
        };
    }]);