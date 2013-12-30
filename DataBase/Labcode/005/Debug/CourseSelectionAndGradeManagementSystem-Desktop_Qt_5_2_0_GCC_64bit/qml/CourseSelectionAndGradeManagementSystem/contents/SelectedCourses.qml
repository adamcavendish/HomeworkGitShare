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
            width: 300
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
                    role: "sno"
                    title: qsTr("Course")
                    width: 80
                }//TableViewColumn

                TableViewColumn {
                    role: "grade"
                    title: qsTr("Grade")
                    width: 30
                }//TableViewColumn

                frameVisible: true
                headerVisible: true
                sortIndicatorVisible: true
                alternatingRowColors: true
            }//TabelView
        }//Rectangle
    }//ColumnLayout
}//Item
