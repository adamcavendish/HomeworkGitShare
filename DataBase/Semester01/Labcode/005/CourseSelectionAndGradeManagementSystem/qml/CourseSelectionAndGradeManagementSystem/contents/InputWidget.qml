import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1

Item {
    id: inputWidgetItem
    width: courseIDInputCol.width
    height: courseIDInputCol.height
    property string cno;

    ColumnLayout {
        id: courseIDInputCol

        Label {
            id: courseIDInputLabel
            text: qsTr("Course ID:")
        }//Label

        TextField {
            id: courseIDInputText
            focus: true

            text: ""
            placeholderText: "Course ID Here"

            Binding {
                target: inputWidgetItem
                property: "cno"
                value: courseIDInputText.text
            }//Binding
        }//TextField
    }//ColumnLayout
}//Item
