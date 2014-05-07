'use strict';

var rootManagementApp = angular.module('rootManagementApp', ['ui.bootstrap', 'ngGrid', 'customFilter']);

var genderCellTemplate = '<div class="ngCellText" ng-class="col.colIndex()"><span ng-cell-text>{{row.entity.gender | genderFilter}}</span></div>';
var overallScoreCellTemplate = 
    '<div class="ngCellText" ng-class="col.colIndex()"><span ng-cell-text>{{row.entity.overallScore | scoreFilter}}</span></div>';

var studentRemoveBtnTemplate = '<input type="button" class="btn btn-primary btn-sm" value="remove" ng-click="removeStudentRow()"/>';
var teacherRemoveBtnTemplate = '<input type="button" class="btn btn-primary btn-sm" value="remove" ng-click="removeTeacherRow()"/>';
var courseRemoveBtnTemplate = '<input type="button" class="btn btn-primary btn-sm" value="remove" ng-click="removeCourseRow()"/>';
var collegeRemoveBtnTemplate = '<input type="button" class="btn btn-primary btn-sm" value="remove" ng-click="removeCollegeRow()"/>';
var openCourseRemoveBtnTemplate = '<input type="button" class="btn btn-primary btn-sm" value="remove" ng-click="removeOpenCourseRow()"/>';
var courseSelectionRemoveBtnTemplate =
    '<input type="button" class="btn btn-primary btn-sm" value="remove" ng-click="removeCourseSelectionRow()"/>';

rootManagementApp.controller('accordionRootManageCtrl', ['$scope', '$http',
      function($scope, $http) {
          var getStudentsFunction = function() {
              $http.get('/Student.json').success(function(data) {
                  $scope.students = data;
              });
          };
          
          var getTeachersFunction = function() {
              $http.get('/Teacher.json').success(function(data) {
                  $scope.teachers = data;
              });
          };
          
          var getCoursesFunction = function() {
              $http.get('/Course.json').success(function(data) {
                  $scope.courses = data;
              });
          };
          
          var getCollegesFunction = function() {
              $http.get('/College.json').success(function(data) {
                  $scope.colleges = data;
              });
          };
          
          var getOpenCoursesFunction = function() {
              $http.get('/OpenCourse.json').success(function(data) {
                  $scope.openCourses = data;
              });
          };
          
          var getCourseSelectionFunction = function() {
              $http.get('/CourseSelection.json').success(function(data) {
                  $scope.courseSelection = data;
              });
          };
          
          getStudentsFunction();
          getTeachersFunction();
          getCoursesFunction();
          getCollegesFunction();
          getOpenCoursesFunction();
          getCourseSelectionFunction();
          
          $scope.studentsGridOptions = {
              data: 'students',
              enableCellSelection: false,
              enableRowSelection: true,
              enableCellEdit: false,
              columnDefs: [
                  {field: 'id', displayName: 'ID', enableCellEdit: false},
                  {field: 'name', displayName: 'Name', enableCellEdit: false},
                  {field: 'gender', displayName: 'Gender', enableCellEdit: false, cellTemplate: genderCellTemplate},
                  {field: 'age', displayName:'Age', enableCellEdit: false},
                  {field: 'collegeId', displayName: 'CollegeID', enableCellEdit: false},
                  {field: 'logn', displayName: 'Logn', enableCellEdit: false},
                  {field: 'pswd', displayName: 'pswd', enableCellEdit: false},
                  {field: 'remove', displayName:'Delete', cellTemplate: studentRemoveBtnTemplate}
              ]
          };
          
          $scope.teachersGridOptions = {
              data: 'teachers',
              enableCellSelection: false,
              enableRowSelection: true,
              enableCellEdit: false,
              columnDefs: [
                  {field: 'id', displayName: 'ID', enableCellEdit: false},
                  {field: 'name', displayName: 'Name', enableCellEdit: false},
                  {field: 'gender', displayName: 'Gender', enableCellEdit: false, cellTemplate: genderCellTemplate},
                  {field: 'age', displayName:'Age', enableCellEdit: false},
                  {field: 'collegeId', displayName: 'CollegeID', enableCellEdit: false},
                  {field: 'logn', displayName: 'Logn', enableCellEdit: false},
                  {field: 'pswd', displayName: 'pswd', enableCellEdit: false},
                  {field: 'remove', displayName:'Delete', cellTemplate: teacherRemoveBtnTemplate}
              ]
          };
          
          $scope.coursesGridOptions = {
              data: 'courses',
              enableCellSelection: false,
              enableRowSelection: true,
              enableCellEdit: false,
              columnDefs: [
                  {field: 'id', displayName: 'ID', enableCellEdit: false},
                  {field: 'name', displayName: 'Name', enableCellEdit: false},
                  {field: 'credit', displayName: 'Credit', enableCellEdit: false},
                  {field: 'classHours', displayName:'ClassHours', enableCellEdit: false},
                  {field: 'collegeId', displayName: 'CollegeID', enableCellEdit: false},
                  {field: 'remove', displayName:'Delete', cellTemplate: courseRemoveBtnTemplate}
              ]
          };
          
          $scope.collegeGridOptions = {
              data: 'colleges',
              enableCellSelection: false,
              enableRowSelection: true,
              enableCellEdit: false,
              columnDefs: [
                  {field: 'id', displayName: 'ID', enableCellEdit: false},
                  {field: 'name', displayName: 'Name', enableCellEdit: false},
                  {field: 'addr', displayName: 'Addr', enableCellEdit: false},
                  {field: 'telephone', displayName:'Telephone', enableCellEdit: false},
                  {field: 'remove', displayName:'Delete', cellTemplate: collegeRemoveBtnTemplate}
              ]
          };
          
          $scope.openCourseGridOptions = {
              data: 'openCourses',
              enableCellSelection: false,
              enableRowSelection: true,
              enableCellEdit: false,
              columnDefs: [
                  {field: 'semester', displayName: 'Semester', enableCellEdit: false},
                  {field: 'courseId', displayName: 'CourseID', enableCellEdit: false},
                  {field: 'teacherId', displayName: 'teacherID', enableCellEdit: false},
                  {field: 'time', displayName:'Time', enableCellEdit: false},
                  {field: 'remove', displayName:'Delete', cellTemplate: openCourseRemoveBtnTemplate}
              ]
          };
          
          $scope.courseSelectionGridOptions = {
              data: 'courseSelection',
              enableCellSelection: false,
              enableRowSelection: true,
              enableCellEdit: false,
              columnDefs: [
                  {field: 'studentId', displayName: 'StudentID', enableCellEdit: false},
                  {field: 'semester', displayName: 'Semester', enableCellEdit: false},
                  {field: 'courseId', displayName: 'CourseID', enableCellEdit: false},
                  {field: 'teacherId', displayName:'TeacherID', enableCellEdit: false},
                  {field: 'overallScore', displayName: 'Overall Score', enableCellEdit: false, cellTemplate: overallScoreCellTemplate},
                  {field: 'remove', displayName:'Delete', cellTemplate: courseSelectionRemoveBtnTemplate}
              ]
          };
          
          $scope.removeStudentRow = function() {
              var index = this.row.rowIndex;
              
              $.ajax({
                  type: 'POST',
                  data: $scope.students[index],
                  url: '/delStudent_post',
                  dataType: 'JSON'
              }).done(function(response) {
                  if(response.msg === '') {
                      getStudentsFunction();
                  } else {
                      alert('Error: ' + response.msg);
                  }//if-else
              });
          };
          
          $scope.removeTeacherRow = function() {
              var index = this.row.rowIndex;

              $.ajax({
                  type: 'POST',
                  data: $scope.teachers[index],
                  url: '/delTeacher_post',
                  dataType: 'JSON'
              }).done(function(response) {
                  if(response.msg === '') {
                      getTeachersFunction();
                  } else {
                      alert('Error: ' + response.msg);
                  }//if-else
              });
          };
          
          $scope.removeCourseRow = function() {
              var index = this.row.rowIndex;

              $.ajax({
                  type: 'POST',
                  data: $scope.courses[index],
                  url: '/delCourse_post',
                  dataType: 'JSON'
              }).done(function(response) {
                  if(response.msg === '') {
                      getCoursesFunction();
                  } else {
                      alert('Error: ' + response.msg);
                  }//if-else
              });
          };
          
          $scope.removeCollegeRow = function() {
              var index = this.row.rowIndex;

              $.ajax({
                  type: 'POST',
                  data: $scope.colleges[index],
                  url: '/delCollege_post',
                  dataType: 'JSON'
              }).done(function(response) {
                  if(response.msg === '') {
                      getCollegesFunction();
                  } else {
                      alert('Error: ' + response.msg);
                  }//if-else
              });
          };
          
          $scope.removeOpenCourseRow = function() {
              var index = this.row.rowIndex;

              $.ajax({
                  type: 'POST',
                  data: $scope.openCourses[index],
                  url: '/delOpenCourse_post',
                  dataType: 'JSON'
              }).done(function(response) {
                  if(response.msg === '') {
                      getOpenCoursesFunction();
                  } else {
                      alert('Error: ' + response.msg);
                  }//if-else
              });
          };
          
          $scope.removeCourseSelectionRow = function() {
              var index = this.row.rowIndex;

              $.ajax({
                  type: 'POST',
                  data: $scope.courseSelection[index],
                  url: '/delCourseSelection_post',
                  dataType: 'JSON'
              }).done(function(response) {
                  if(response.msg === '') {
                      getCourseSelectionFunction();
                  } else {
                      alert('Error: ' + response.msg);
                  }//if-else
              });
          };
      }]);


// ---------------------------------------------

function AddStudent_btnClick() {
    // Super basic validation - increase errorCount variable if any fields are blank
    var errorCount = 0;
    $('#AddStudent_form input').each(function(index, val) {
        if($(this).val() === '')
            errorCount++;
    });
    
    if(errorCount === 0) {
        var newStudent = {
            'id': $('#inputID').val(),
            'name': $('#inputName').val(),
            'gender': $('#inputGenderMale').is(":checked"),
            'age': parseInt($('#inputAge').val()),
            'collegeId': $('#inputCollege').val(),
            'logn': $('#inputLogn').val(),
            'pswd': $('#inputPswd').val()
        };

        $.ajax({
            type: 'POST',
            data: newStudent,
            url: '/addStudent_post',
            dataType: 'JSON'
        }).done(function(response) {
            if (response.msg === '') {
                $('#AddStudent_form input').val('');
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

function AddTeacher_btnClick() {
    // Super basic validation - increase errorCount variable if any fields are blank
    var errorCount = 0;
    $('#AddTeacher_form input').each(function(index, val) {
        if($(this).val() === '')
            errorCount++;
    });

    if(errorCount === 0) {
        var newTeacher = {
            'id': $('#inputTeacherID').val(),
            'name': $('#inputTeacherName').val(),
            'gender': $('#inputTeacherGenderMale').is(":checked"),
            'age': parseInt($('#inputTeacherAge').val()),
            'collegeId': $('#inputTeacherCollege').val(),
            'logn': $('#inputTeacherLogn').val(),
            'pswd': $('#inputTeacherPswd').val()
        };

        $.ajax({
            type: 'POST',
            data: newTeacher,
            url: '/addTeacher_post',
            dataType: 'JSON'
        }).done(function(response) {
            if (response.msg === '') {
                $('#AddTeacher_form input').val('');
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

function AddCourse_btnClick() {
    // Super basic validation - increase errorCount variable if any fields are blank
    var errorCount = 0;
    $('#AddCourse_form input').each(function(index, val) {
        if($(this).val() === '')
            errorCount++;
    });

    if(errorCount === 0) {
        var newCourse = {
            'id': $('#inputCourseID').val(),
            'name': $('#inputCourseName').val(),
            'credit': parseInt($('#inputCourseCredit').val()),
            'classHours': parseInt($('#inputCourseClassHours').val()),
            'collegeId': $('#inputCourseCollege').val()
        };

        $.ajax({
            type: 'POST',
            data: newCourse,
            url: '/addCourse_post',
            dataType: 'JSON'
        }).done(function(response) {
            if (response.msg === '') {
                $('#AddCourse_form input').val('');
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

function AddCollege_btnClick() {
    // Super basic validation - increase errorCount variable if any fields are blank
    var errorCount = 0;
    $('#AddCollege_form input').each(function(index, val) {
        if($(this).val() === '')
            errorCount++;
    });

    if(errorCount === 0) {
        var newCollege = {
            'id': $('#inputCollegeID').val(),
            'name': $('#inputCollegeName').val(),
            'addr': $('#inputCollegeAddr').val(),
            'telephone': $('#inputCollegeTelephone').val()
        };

        $.ajax({
            type: 'POST',
            data: newCollege,
            url: '/addCollege_post',
            dataType: 'JSON'
        }).done(function(response) {
            if (response.msg === '') {
                $('#AddCollege_form input').val('');
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

function AddOpenCourse_btnClick() {
    // Super basic validation - increase errorCount variable if any fields are blank
    var errorCount = 0;
    $('#AddOpenCourse_form input').each(function(index, val) {
        if($(this).val() === '')
            errorCount++;
    });

    if(errorCount === 0) {
        var newOpenCourse = {
            'semester': $('#inputOpenCourseSemester').val(),
            'courseId': $('#inputOpenCourseCourseID').val(),
            'teacherId': $('#inputOpenCourseTeacherID').val(),
            'time': $('#inputOpenCourseTime').val()
        };

        $.ajax({
            type: 'POST',
            data: newOpenCourse,
            url: '/addOpenCourse_post',
            dataType: 'JSON'
        }).done(function(response) {
            if (response.msg === '') {
                $('#AddOpenCourse_form input').val('');
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

function AddCourseSelection_btnClick() {
    // Super basic validation - increase errorCount variable if any fields are blank
    var errorCount = 0;
    $('#AddCourseSelection_form input').each(function(index, val) {
        if($(this).val() === '')
            errorCount++;
    });

    if(errorCount === 0) {
        var overallScore = $('#inputCourseSelectionOverallScore').val();
        var newCourseSelection = {
            'studentId': $('#inputCourseSelectionStudentId').val(),
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
