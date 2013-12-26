import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Window 2.0
import QtQuick.Controls.Styles 1.1
import QtQuick.Layouts 1.1
import QtQuick.XmlListModel 2.0
import QtQuick.Particles 2.0

import "contents/"

ApplicationWindow {
    title: qsTr("Course Selection")
    width: 640
    height: 480

    LoginWindow {
        id: loginWindow
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Login");
                onTriggered: {
                    loginWindow.visible = true;
                }//onTriggered
            }//MenuItem
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }//MenuItem
        }//Menu
    }//MenuBar

    Button {
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }
}
