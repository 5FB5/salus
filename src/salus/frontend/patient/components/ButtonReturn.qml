import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQml 2.12
import salus 1.0

Button
{
    id: root

    property string buttonDefaultColor: "#EBEBEB"
    property string buttonPressedColor: "#EBEBEB"
    property string buttonTextDefaultColor: "#E1E1E1"
    property string buttonTextPressedColor: "#FFFFFF"

    property string buttonTextColor: "#BABABA"

    signal returnBack()

    anchors
    {
        top: parent.top
        left: parent.left
        topMargin: 15
        leftMargin: 15
    }

    contentItem: Text
    {
        anchors
        {
            centerIn: parent
        }

        font.pointSize: 19
        opacity: enabled ? 1.0 : 0.3
        color: root.down ? buttonTextPressedColor : buttonTextColor
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
        text: "❮"
    }

    background: Rectangle
    {
        anchors.fill: parent
        radius: 14
        color: root.down ? buttonPressedColor : "transparent"
    }

    width: 60
    height: 60

    onClicked: function()
    {
        returnBack();
    }
}
