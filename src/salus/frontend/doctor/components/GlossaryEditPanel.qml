import QtQuick 2.0
import QtQuick.Controls 2.12

Item
{
    id: root

    property int buttonWidth: 50
    property int fontPixelSize: 18

    Button
    {
        id: buttonEdit

        anchors
        {
            top: buttonAdd.top
            horizontalCenter: parent.horizontalCenter
        }
        font.pixelSize: 15
        font.bold: true
        text: "Изменить"
    }

    Button
    {
        id: buttonAdd

        anchors
        {
            top: parent.top
            right: buttonEdit.left
            rightMargin: 5
        }
        width: buttonWidth
        font.pixelSize: fontPixelSize
        font.bold: true
        text: "+"
    }

    Button
    {
        id: buttonRemove

        anchors
        {
            top: buttonEdit.top
            left: buttonEdit.right
            leftMargin: 5
        }
        width: buttonWidth
        font.pixelSize: fontPixelSize
        font.bold: true
        text: "-"
    }
}
