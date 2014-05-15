var courseSelectionApp = angular.module('courseSelectionApp', ['ui.bootstrap', 'ngGrid', 'customFilter']);

var genderCellTemplate = '<div class="ngCellText" ng-class="col.colIndex()"><span ng-cell-text>{{row.entity.gender | genderFilter}}</span></div>';
var overallScoreCellTemplate = 
    '<div class="ngCellText" ng-class="col.colIndex()"><span ng-cell-text>{{row.entity.overallScore | scoreFilter}}</span></div>';

var selectTheOpenCourseBtnTemplate =
    '<input type="button" class="btn btn-primary btn-sm" value="select" ng-click="selectTheOpenCourseRow()"/>';
var courseSelectionRemoveBtnTemplate =
    '<input type="button" class="btn btn-primary btn-sm" value="remove" ng-class="{disabled: row.entity.overallScore != -1}" ng-click="removeCourseSelectionRow()"/>';

courseSelectionApp.controller('accordionCourseSelectionCtrl', ['$scope', '$http',
    function($scope, $http) {
        
        $scope.getOpenCoursesFunction = function() {
            $http.get('/OpenCourse.json').success(function(data) {
                $scope.openCourses = data;
            });
        };
        
        $scope.getCourseSelectionFunction = function() {
            $http.get('/CourseSelection.json').success(function(data) {
                $scope.courseSelection = data;
            });
        };
        
        $scope.refreshData = function(event) {
            if(event)
                event.preventDefault();

            $scope.getOpenCoursesFunction();
            $scope.getCourseSelectionFunction();
        };
        
        $scope.openCourseGridOptions = {
            data: 'openCourses',
            enableCellSelection: false,
            enableRowSelection: true,
            enableCellEdit: false,
            multiSelect: false,
            sortInfo: {fields: ['semester'], directions: ['desc']},
            columnDefs: [
                {field: 'semester', displayName: 'Semester', enableCellEdit: false},
                {field: 'courseId', displayName: 'CourseID', enableCellEdit: false},
                {field: 'teacherId', displayName: 'teacherID', enableCellEdit: false},
                {field: 'time', displayName:'Time', enableCellEdit: false},
                {field: 'select', displayName: 'Select', cellTemplate: selectTheOpenCourseBtnTemplate}
            ]
        };
        
        $scope.courseSelectionGridOptions = {
            data: 'courseSelection',
            enableCellSelection: false,
            enableRowSelection: true,
            enableCellEdit: false,
            multiSelect: false,
            sortInfo: {fields: ['semester'], directions: ['desc']},
            columnDefs: [
                {field: 'semester', displayName: 'Semester', enableCellEdit: false},
                {field: 'courseId', displayName: 'CourseID', enableCellEdit: false},
                {field: 'teacherId', displayName:'TeacherID', enableCellEdit: false},
                {field: 'overallScore', displayName: 'Overall Score', enableCellEdit: false, cellTemplate: overallScoreCellTemplate},
                {field: 'remove', displayName:'Delete', cellTemplate: courseSelectionRemoveBtnTemplate}
            ]
        };
        
        $scope.selectTheOpenCourseRow = function() {
            var rowData = this.row.entity;
            rowData.overallScore = -1;
            
            $.ajax({
                type: 'POST',
                data: rowData,
                url: '/addCourseSelection_post',
                dataType: 'JSON'
            }).done(function(response) {
                if (response.msg === '') {
                    $scope.getCourseSelectionFunction();
                } else {
                    alert('Error: ' + response.msg);
                }//if-else
            });
        };
        
        $scope.removeCourseSelectionRow = function() {
            var rowData = this.row.entity;

            $.ajax({
                type: 'POST',
                data: rowData,
                url: '/delCourseSelection_post',
                dataType: 'JSON'
            }).done(function(response) {
                if(response.msg === '') {
                    $scope.getCourseSelectionFunction();    
                } else {
                    alert('Error: ' + response.msg);
                }//if-else
            });
        };
    }]);

function AddCourseSelection_btnClick() {
    // Super basic validation - increase errorCount variable if any fields are blank
    var errorCount = 0;
    $('#AddCourseSelection_form input').each(function(index, val) {
        if($(this).val() === '' && $(this).attr('type') !== 'radio')
            errorCount++;
    });

    if(errorCount === 0) {
        var overallScore = $('#inputCourseSelectionOverallScore').val();
        var newCourseSelection = {
            'semester': $('#inputCourseSelectionSemester').val(),
            'courseId': $('#inputCourseSelectionCourseID').val(),
            'teacherId': $('#inputCourseSelectionTeacherID').val(),
            'overallScore': (overallScore >= 0) ? overallScore : -1
        };

        $.ajax({
            type: 'POST',
            data: newCourseSelection,
            url: '/addCourseSelection_post',
            dataType: 'JSON'
        }).done(function(response) {
            if (response.msg === '') {
                $('#AddCourseSelection_form input').val('');
                angular.element('#accordionCourseSelection_Id').scope().getCourseSelectionFunction();
            } else {
                alert('Error: ' + response.msg);
            }//if-else
        });
    } else {
        alert('Please fill in all fields');
        return false;
    }//if-else
    return true;
}