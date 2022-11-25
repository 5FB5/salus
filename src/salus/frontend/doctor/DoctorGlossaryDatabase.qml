import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import salus 1.0

Page
{
    id: root

    property int buttonStandartTextFontSize: 10
    property int standartTextSize: 14

    Label
    {
        anchors
        {
            top: parent.top
            horizontalCenter: parent.horizontalCenter
        }
        font.pointSize: standartTextSize
        font.bold: true
        text: "[Заглушка] Окно БД глоссария"
    }
}
