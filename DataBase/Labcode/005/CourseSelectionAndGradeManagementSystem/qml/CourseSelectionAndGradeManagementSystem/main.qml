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
                id: loginButton
                text: qsTr("Login")
                onClicked: loginWindow.visible = true
            }//Button

            Button {
                id: selectCourseButton
                text: qsTr("Select it!")
                onClicked: console.log("I want nobody, nobody... but you~")
            }//Button

            Button {
                id: dropCourseButton
                text: qsTr("Drop it!")
                onClicked: console.log("I really don't want you!")
            }//Button
        }//ColumnLayout
    }//RowLayout
}//ApplicationWindow
