import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0

Window {
    id: gradeManageWindow
    title: qsTr("Grade Manager")

    property string cno;
    property variant studentGradeManageModel;
    property variant courseInfoModel;

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
                Label { text: qsTr("Select Course: "); }

                Rectangle {
                    width: 200
                    height: 300
                    Component {
                        id: hlComponent
                        Rectangle {
                            color: "lightsteelblue"
                            radius: 5
                            y: courseList.currentItem.y
                        }//Rectangle
                    }//Component

                    Component {
                        id: dlComponent
                        Text {
                            text: model.modelData.cno + ": " + model.modelData.cname
                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    gradeManageWindow.cno = model.modelData.cno
                                    courseList.currentIndex = index;
                                    studentGradeManageModel =
                                            sqlManager.getCourseStudentsGrade(model.modelData.cno);
                                }//onClicked
                            }//MouseArea
                        }//Text
                    }//Component

                    ListView {
                        id: courseList
                        anchors.fill: parent
                        model: courseInfoModel
                        delegate: dlComponent
                        highlight: hlComponent
                        focus: true
                    }//ListView
                }//Rectangle
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
                            delegate: gradeDlComponent
                            width: 50
                        }//TableViewColumn

                        Component {
                            id: gradeDlComponent
                            TextInput {
                                id: gradeInput
                                text: styleData.value
                                onEditingFinished: {
                                    var sno = gradeManageWindow.studentGradeManageModel[styleData.row].sno;
                                    var grade = parseInt(gradeInput.text);
                                    if(sno !== "" && grade < 100 && grade > 0)
                                        sqlManager.updateGrade(sno, gradeManageWindow.cno, grade);
                                }//onEditingFinished
                            }//TextInput
                        }//Component

                        frameVisible: true
                        headerVisible: true
                        sortIndicatorVisible: false
                        alternatingRowColors: true
                    }//TableView
                }//Rectangle
            }//ColumnLayout
        }//RowLayout

        ColumnLayout {
            id: buttonsCol
        }//ColumnLayout
    }//ColumnLayout
}//Window
