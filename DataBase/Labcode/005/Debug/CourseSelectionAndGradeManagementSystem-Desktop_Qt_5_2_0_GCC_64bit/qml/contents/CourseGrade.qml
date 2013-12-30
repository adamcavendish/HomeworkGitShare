import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1

Item {
    width: courseGradeLayout.implicitWidth
    height: courseGradeLayout.implicitHeight

    property variant courseGradeModel;

    ColumnLayout {
        id: courseGradeLayout

        Label {
            text: qsTr("Grade of Selected Courses")
            font.bold: true
        }//Label

        Rectangle {
            width: 200
            height: 200

            TableView {
                id: courseGradeView
                model: courseGradeModel

                anchors.fill: parent

                TableViewColumn {
                    role: "cno"
                    title: qsTr("CNO")
                    width: 30
                }//TableViewColumn

                TableViewColumn {
                    role: "course_name"
                    title: qsTr("Course Name")
                    width: 100
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
            }//TabelView
        }//Rectangle
    }//ColumnLayout
}//Item
