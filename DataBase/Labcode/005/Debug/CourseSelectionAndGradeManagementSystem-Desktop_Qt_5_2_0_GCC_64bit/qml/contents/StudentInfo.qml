import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1

Item {
    width: studentInfo.implicitWidth
    height: studentInfo.implicitHeight

    property variant studentModel;

    ColumnLayout {
        id: studentInfo

        Label {
            id: studentInfoLabel

            font.bold: true
            text: qsTr("Student Information")
        }//Label

        Rectangle {
            width: 200
            height: 60

            TableView {
                id: studentInfoView
                model: studentModel

                anchors.fill: parent

                TableViewColumn {
                    role: "sno"
                    title: qsTr("SNO")
                    width: 30
                }//TableViewColumn

                TableViewColumn {
                    role: "name"
                    title: qsTr("Name")
                    width: 50
                }//TableViewColumn

                TableViewColumn {
                    role: "gender"
                    title: qsTr("Gender")
                    width: 50
                }//TableViewColumn

                TableViewColumn {
                   role: "age"
                   title: qsTr("Age")
                   width: 30
                }//TableViewColumn

                TableViewColumn {
                   role: "department"
                   title: "Depart"
                   width: 80
                }//TableViewColumn

                frameVisible: true
                headerVisible: true
                sortIndicatorVisible: true
                alternatingRowColors: true
            }//TableView
        }//Rectangle
    }//ColumnLayout
}//Item
