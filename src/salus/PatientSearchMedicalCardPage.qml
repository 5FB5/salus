import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import io.qt.salus 1.0

Page {
    id: root

    property int buttonStandartTextFontSize: 10
    property int standartTextSize: 14


    signal openCurrentMedicalCard(string fullname)
    signal registerMedicalCard(string fullname)

    property var namesArray: []

    function getPatientNames() {
        var array = backend.patientListNames
        var names = []

        for (var i in array) {
            namesArray[i] = array[i]
            console.log("Salus: [QML](PatientSearchMedicalCardPage) - Patient ", i, " is ", namesArray[i])
        }
        return namesArray
    }

    Backend {
        id: backend
    }

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

        model: PatientListModel {} //getPatientNames()

        // Чтобы по умолчанию не выводилось ФИО из списка
        currentIndex: -1

        onAccepted: {
            console.log("Salus: [QML](ComboBox 'combobox_patients') - Patiend accepted\n")
            find(editText) !== -1 ? openCurrentMedicalCard(editText) : registerMedicalCard(editText)
        }
    }
}
