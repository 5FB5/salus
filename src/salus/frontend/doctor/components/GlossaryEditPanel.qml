import QtQuick 2.0
import QtQuick.Controls 2.12

Item
{
    id: root

    property int buttonWidth: 50
    property int buttonHeight: 50
    property int fontPixelSize: 18

    property string buttonDefaultColor: "#E1E1E1"
    property string buttonPressedColor: "#BABABA"

    property string buttonTextColor: "#007AFF"
    property string buttonTextPressedColor: Qt.darker(buttonTextColor, 0.5)

    signal addRecord()
    signal removeRecord()
    signal editRecord()

    Button
    {
        id: buttonEdit

        anchors
        {
            top: buttonAdd.top
            bottom: buttonAdd.bottom
            horizontalCenter: parent.horizontalCenter
        }

        contentItem: Text
        {
            font.pointSize: 12
            opacity: enabled ? 1.0 : 0.3
            color: buttonEdit.down ? buttonTextPressedColor : buttonTextColor
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
            text: "Изменить"
        }

        background: Rectangle
        {
            anchors.fill: parent
            radius: 14
            color: buttonEdit.down ? buttonPressedColor : buttonDefaultColor
        }

        width: 100
        height: buttonHeight

        onClicked: function()
        {
            editRecord();
        }
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

        contentItem: Text
        {
            font.pointSize: 16
            opacity: enabled ? 1.0 : 0.3
            color: buttonAdd.down ? buttonTextPressedColor : buttonTextColor
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
            text: "+"
        }

        background: Rectangle
        {
            anchors.fill: parent
            radius: 14
            color: buttonAdd.down ? buttonPressedColor: buttonDefaultColor
        }

        width: buttonWidth
        height: buttonHeight

        onClicked: function()
        {
            addRecord();
        }
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

        contentItem: Text
        {
            font.pointSize: 16
            opacity: enabled ? 1.0 : 0.3
            color: buttonRemove.down ? buttonTextPressedColor : buttonTextColor
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
            text: "-"
        }

        background: Rectangle
        {
            anchors.fill: parent
            radius: 14
            color: buttonRemove.down ? buttonPressedColor: buttonDefaultColor
        }
        width: buttonWidth
        height: buttonHeight

        onClicked: function()
        {
            removeRecord();
        }
    }
}
