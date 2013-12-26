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
                        focus: true

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

                        //onEditingFinished: loginButton.clicked()
                    }//TextField
                }//RowLayout
            }//ColumnLayout
        }//RowLayout

        RowLayout {
            id: row2
            anchors.horizontalCenter: parent.horizontalCenter

            Rectangle {
                id: stat
                width: 400
                height: statusLabel.height * 2

                Text {
                    id: statusLabel
                    width: 400
                    horizontalAlignment: Text.AlignHCenter

                    wrapMode: Text.Wrap
                    text: qsTr("Please Login Here ...")
                }//Text
            }//Rectangle
        }//RowLayout

        RowLayout {
            id: row3
            anchors.horizontalCenter: parent.horizontalCenter

            Button {
                id: loginButton
                text: qsTr("Login")
                isDefault: true

                onClicked: {
                    if(sqlManager.login(userNameText.text, passwordText.text)) {
                        statusLabel.text = qsTr("Login Success!");
                        appStatusLabel.text = qsTr("Login Success! Welcome ") + userNameText.text;
                        console.log(userNameText.text, " Login Success!");
                        loginWindow.visible = false;

                        userNameText.text = 'S1';
                        passwordText.text = 'S1';
                        var studentModel = sqlManager.getStudentInfo(
                                    userNameText.text, passwordText.text);
                        studentInfo.studentModel = studentModel;

                        var courseGradeModel = sqlManager.getCourseGrade(
                                    userNameText.text, passwordText.text);
                        courseGrade.courseGradeModel = courseGradeModel;
                    } else {
                        var errStr = qsTr("Login Failed: ") +
                                sqlManager.lastErrorString();
                        statusLabel.text = errStr;

                        console.log("Login Failed!");
                        console.log("Error: ", sqlManager.lastErrorString());
                    }//if-else
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
