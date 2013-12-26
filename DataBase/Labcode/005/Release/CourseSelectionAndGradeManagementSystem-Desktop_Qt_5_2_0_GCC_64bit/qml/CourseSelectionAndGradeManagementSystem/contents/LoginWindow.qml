import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Window 2.0
import QtQuick.Layouts 1.1

Window {
    id: loginWindow
    title: qsTr("Login")

    x: Screen.desktopAvailableWidth/2 - loginWindow.width/2
    y: Screen.desktopAvailableHeight/2 - loginWindow.height/2

    width: mainLayout.implicitWidth
    height: mainLayout.implicitHeight
    maximumWidth: mainLayout.implicitWidth
    maximumHeight: mainLayout.implicitHeight

    ColumnLayout {
        id: mainLayout

        RowLayout {
            id: row1
            spacing: 10
            anchors.rightMargin: 10

            Image {
                id: loginImage
                height: sourceSize.height
                width: sourceSize.width
                source: "qrc:///Image/user_login"
            }//Image

            ColumnLayout {
                id: col1

                RowLayout {
                    id: userNameRow

                    Label {
                        id: userNameLabel
                        text: qsTr("User Name: ")
                    }//Label

                    TextField {
                        id: userNameText
                        Layout.fillWidth: true

                        text: ""
                        placeholderText: "User Name Here"
                    }//TextField
                }//RowLayout

                RowLayout {
                    id: passwordRow

                    Label {
                        id: passwordLabel

                        text: qsTr("Password: ")
                    }//Label

                    TextField {
                        id: passwordText
                        Layout.fillWidth: true

                        echoMode: TextInput.Password
                        text: ""
                    }//TextField
                }//RowLayout
            }//ColumnLayout
        }//RowLayout

        RowLayout {
            id: row2
            anchors.horizontalCenter: parent.horizontalCenter

            Button {
                id: loginButton
                text: qsTr("Login")
                onClicked: {
                    console.log("I'm going to login")
                }//onClicked
            }//Button

            Button {
                id: exitButton
                text: qsTr("Quit")
                onClicked: Qt.quit()
            }//Button
        }//RowLayout
    }//ColumnLayout
}//Window
