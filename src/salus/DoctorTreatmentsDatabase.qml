import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import io.qt.salus 1.0

Page {
    id: root

    Backend {
        id: backend
    }

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
