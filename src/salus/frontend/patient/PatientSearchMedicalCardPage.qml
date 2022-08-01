import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import salus 1.0

Page {
    id: root

    property int buttonStandartTextFontSize: 10
    property int standartTextSize: 14

    property var patientList: PatientListModel {}

    signal openCurrentMedicalCard(string fullname)
    signal registerMedicalCard(string fullname)

    Label {
        id: labelTitle

        text: "Поиск амбулаторной карты"

        font.pointSize: 20
        font.bold: true

        anchors.top: parent.top
        anchors.topMargin: 50
        anchors.horizontalCenter: parent.horizontalCenter

    }

    ComboBox {
        id: combobox_patients

        height: 50

        anchors.top: parent.top
        anchors.topMargin: 256

        anchors.left: parent.left
        anchors.leftMargin: 300

        anchors.right: parent.right
        anchors.rightMargin: 300

        font.pointSize: standartTextSize

        editable: true

        model: patientList

        // Чтобы по умолчанию не выводилось ФИО из списка
        currentIndex: -1

        onAccepted: {
            console.log("Salus: [QML](ComboBox 'combobox_patients') - Patient accepted " + editText + "\n")
            find(editText) !== -1 ? openCurrentMedicalCard(editText) : registerMedicalCard(editText)
        }
    }
}
