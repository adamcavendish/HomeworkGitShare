import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1

Item {
    width: availCoursesLayout.implicitWidth
    height: availCoursesLayout.implicitHeight

    ColumnLayout {
       id: availCoursesLayout

       Label {
           text: qsTr("Available Courses")
           font.bold: true
       }//Label

       Rectangle {
           width: 300
           height: 60

           /*
            TableView {
                id: availCoursesView

                anchors.fill: parent

                TableViewColumn {
                   role: "cno"
                   title: "CNO"
                   width: 30
                }//TableViewColumn

            }//TablView
            */
       }//Rectangle
    }//ColumnLayout
}//Item
