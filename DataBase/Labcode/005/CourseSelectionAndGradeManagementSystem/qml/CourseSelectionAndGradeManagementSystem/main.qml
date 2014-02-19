import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Window 2.0
import QtQuick.Layouts 1.1

// CourseSelectionAndGradeManagementSystem
import "contents/"
import Logics 1.0

ApplicationWindow {
    title: qsTr("Course Selection")
    width: mainLayout.implicitWidth + 50
    height: mainLayout.implicitHeight + 50

    statusBar: StatusBar {
        Label { id: appStatusLabel; text: qsTr("You're not logged in!"); }
    }//StatusBar

    SqlManager { id: sqlManager }

    LoginWindow { id: loginWindow; visible: false }
    GradeManageWindow { id: gradeManageWindow; visible: false }

    RowLayout {
        id: mainLayout
        spacing: 50

        ColumnLayout {
            RowLayout {
                id: row1
                spacing: 30

                StudentInfo { id: studentInfo }

                AvailableCourses { id: availCourses }

                InputWidget { id: inputWidget }
            }//RowLayout

            RowLayout {
                id: row2
                spacing: 30

                CourseGrade { id: courseGrade }

                SelectedCourses { id: selectedCourses }
            }//RowLayout
        }//ColumnLayout

        ColumnLayout {
            id: buttonsLayout

            Button {
                id: gradeManageButton
                text: qsTr("Grade Manager")
                onClicked: {
                    if(inputWidget.cno != "") {
                        gradeManageWindow.cno = inputWidget.cno;
                        gradeManageWindow.visible = true;
                    } else {
                        appStatusLabel.text = qsTr("Please Input A Course ID!");
                    }//if-else
                }//onClicked
            }//Button

            Button {
                id: loginButton
                text: qsTr("Login")
                onClicked: loginWindow.visible = true
            }//Button

            Button {
                id: selectCourseButton
                text: qsTr("Select it!")
                onClicked: {
                    if(!sqlManager.selectCourse(inputWidget.cno)) {
                        appStatusLabel.text =
                                qsTr("Select Course Failed. You've already selected it!");
                    }//if
                    var availCoursesModel = sqlManager.getAvailCourses();
                    availCourses.availCoursesModel = availCoursesModel;
                    var selectedCoursesModel = sqlManager.getSelectedCourses();
                    selectedCourses.selectedCoursesModel = selectedCoursesModel;
                }//onClicked
            }//Button

            Button {
                id: dropCourseButton
                text: qsTr("Drop it!")
                onClicked: {
                    if(!sqlManager.dropCourse(inputWidget.cno)) {
                        appStatusLabel.text =
                                qsTr("Drop Course Failed. You haven't selected the course!");
                    }//if
                    var availCoursesModel = sqlManager.getAvailCourses();
                    availCourses.availCoursesModel = availCoursesModel;
                    var selectedCoursesModel = sqlManager.getSelectedCourses();
                    selectedCourses.selectedCoursesModel = selectedCoursesModel;
                }//onClicked
            }//Button

            Button {
                id: quitButton
                text: qsTr("Quit!")
                onClicked: Qt.quit()
            }//Button
        }//ColumnLayout
    }//RowLayout
}//ApplicationWindow
