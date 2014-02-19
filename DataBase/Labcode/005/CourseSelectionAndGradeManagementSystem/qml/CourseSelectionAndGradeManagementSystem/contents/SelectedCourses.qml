import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1

Item {
    height: selectedCoursesLayout.implicitHeight
    width: selectedCoursesLayout.implicitWidth

    property variant selectedCoursesModel

    ColumnLayout {
        id: selectedCoursesLayout

        Label {
            text: "Selected Courses"
            font.bold: true
        }//Label

        Rectangle {
            width: 450
            height: 200

            TableView {
                id: selectedCoursesView
                model: selectedCoursesModel

                anchors.fill: parent

                TableViewColumn {
                    role: "cno"
                    title: qsTr("CNO")
                    width: 30
                }//TableViewColumn

                TableViewColumn {
                    role: "cname"
                    title: qsTr("Course Name")
                    width: 150
                }//TableViewColumn

                TableViewColumn {
                    role: "credit"
                    title: qsTr("Credit")
                    width: 50
                }//TableViewColumn

                TableViewColumn {
                    role: "cdept"
                    title: qsTr("Department")
                    width: 100
                }//TableViewColumn

                TableViewColumn {
                    role: "tname"
                    title: qsTr("Teacher Name")
                    width: 100
                }//TableViewColumn

                frameVisible: true
                headerVisible: true
                sortIndicatorVisible: true
                alternatingRowColors: true
            }//TabelView
        }//Rectangle
    }//ColumnLayout
}//Item
