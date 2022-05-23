import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import io.qt.salus 1.0

Page {
    id: root

    property int buttonStandartTextFontSize: 10
    property int standartTextSize: 14

    Label {
        text: "[Заглушка] Окно БД вариантов лечения"

        font.pointSize: standartTextSize
        font.bold: true

        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
