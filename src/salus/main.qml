import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    TextEdit {
        id: textEdit
        text: qsTr("Enter some text...")
        verticalAlignment: Text.AlignVCenter
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20

        Rectangle {
            id: rectangle
            anchors.fill: parent
            anchors.margins: -10
            color: "transparent"
            radius: 15
            border.width: 1
        }
    }
}



/*##^##
Designer {
    D{i:0;formeditorZoom:1.1}
}
##^##*/
