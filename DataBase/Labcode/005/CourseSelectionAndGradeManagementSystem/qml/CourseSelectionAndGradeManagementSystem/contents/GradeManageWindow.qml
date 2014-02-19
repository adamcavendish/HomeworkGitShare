import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0

Window {
    id: gradeManageWindow
    title: qsTr("Grade Manager")

    property string cno;
    property variant studentGradeManageModel;

    x: Screen.desktopAvailableWidth/2 - gradeManageWindow.width/2
    y: Screen.desktopAvailableHeight/2 - gradeManageWindow.height/2

    width: mainLayout.implicitWidth
    height: mainLayout.implicitHeight
    maximumWidth: mainLayout.implicitWidth
    maximumHeight: mainLayout.implicitHeight

    ColumnLayout {
        id: mainLayout

        RowLayout {
            id: courseInfoRow
            Label {
                id: courseNameLabel
                text: {
                    if(cno == "")
                        return "";
                    var cname = sqlManager.getCourseName(cno);
                    if(cname !== "") {
                        return qsTr("Course: ") + cname;
                    }//if
                    return qsTr("Course: Invalid CourseID");
                }//text
            }//Label

            Label {
                id: teacherNameLabel
                text: {
                    if(cno == "")
                        return "";
                    var tname = sqlManager.getTeacherName(cno);
                    if(tname !== "") {
                        return qsTr("Teacher: ") + tname;
                    }//if
                    return qsTr("Course: Invalid CourseID");
                }//text
            }//Label
        }//RowLayout

        RowLayout {
            ColumnLayout {
                Label { text: qsTr("Course Selection: "); }

                ComboBox {
                    // @TODO
                }//ComboBox
            }//ColumnLayout

            ColumnLayout {
                Label { text: qsTr("Students and Grades: "); }

                Rectangle {
                    width: 200
                    height: 300

                    TableView {
                        id: studentGradeManageView
                        model: studentGradeManageModel

                        anchors.fill: parent

                        TableViewColumn {
                            role: "sno"
                            title: qsTr("SNO")
                            width: 30
                        }//TableViewColumn

                        TableViewColumn {
                            role: "grade"
                            title: qsTr("Grade")
                            width: 50
                        }//TableViewColumn

                        frameVisible: true
                        headerVisible: true
                        sortIndicatorVisible: true
                        alternatingRowColors: true
                    }//TableView
                }//Rectangle
            }//ColumnLayout
        }//RowLayout
    }//ColumnLayout
}//Window
