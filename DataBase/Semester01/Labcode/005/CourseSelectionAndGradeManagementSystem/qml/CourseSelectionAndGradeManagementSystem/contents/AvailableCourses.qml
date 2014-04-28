import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1

Item {
    width: availCoursesLayout.implicitWidth
    height: availCoursesLayout.implicitHeight
    property variant availCoursesModel

    ColumnLayout {
       id: availCoursesLayout

       Label {
           text: qsTr("Available Courses")
           font.bold: true
       }//Label

       Rectangle {
           width: 450
           height: 150

            TableView {
                id: availCoursesView
                model: availCoursesModel

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
                sortIndicatorVisible: false
                alternatingRowColors: true
            }//TablView
       }//Rectangle
    }//ColumnLayout
}//Item
