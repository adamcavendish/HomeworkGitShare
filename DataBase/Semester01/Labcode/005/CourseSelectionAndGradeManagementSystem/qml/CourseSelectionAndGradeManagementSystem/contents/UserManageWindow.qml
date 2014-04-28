import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0

Window {
    id: gradeManageWindow
    title: qsTr("User Manager")

    property variant userModel;

    x: Screen.desktopAvailableWidth/2 - gradeManageWindow.width/2
    y: Screen.desktopAvailableHeight/2 - gradeManageWindow.height/2

    width: mainLayout.implicitWidth
    height: mainLayout.implicitHeight
    maximumWidth: mainLayout.implicitWidth
    maximumHeight: mainLayout.implicitHeight

    RowLayout {
        id: mainLayout

        ColumnLayout {
            id: col1

            Rectangle {
                width: 450
                height: 300

                TableView {
                    id: studentInfoView
                    model: userModel

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

                    TableViewColumn {
                        role: "sno"
                        title: "User"
                        width: 50
                    }//TableViewColumn

                    TableViewColumn {
                        role: "sno"
                        title: "PSWD"
                        width: 50
                    }//TableViewColumn

                    frameVisible: true
                    headerVisible: true
                    sortIndicatorVisible: true
                    alternatingRowColors: true
                }//TableView
            }//Rectangle
        }//ColumnLayout

        ColumnLayout {
            TextField {
                id: sno
                placeholderText: qsTr("ID")
            }//TextField

            TextField {
                id: sname
                placeholderText: qsTr("Name")
            }//TextField

            TextField {
                id: gender
                placeholderText: qsTr("Gender")
            }//TextField

            TextField {
                id: age
                placeholderText: qsTr("Age")
            }//TextField

            TextField {
                id: dept
                placeholderText: qsTr("Department")
            }//TextField
        }//ColumnLayout

        ColumnLayout {
            id: btnCol

            Button {
                id: addUserBtn
                text: qsTr("Add User")
                onClicked: {
                    sqlManager.addUser(sno.text, sname.text, gender.text, parseInt(age.text), dept.text)
                    userModel = sqlManager.getAllUsers();
                }//onClicked
            }//Button

            Button {
                id: delUserBtn
                text: qsTr("Delete User")
                onClicked: {
                    sqlManager.dropUser(studentInfoView.model[studentInfoView.currentRow].sno);
                    userModel = sqlManager.getAllUsers();
                }
            }//Button
        }//ColumnLayout
    }//ColumnLayout
}//Window
