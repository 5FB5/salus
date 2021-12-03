import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import io.qt.salus 1.0

Page {
    id: root

    property int buttonStandartTextFontSize: 10
    property int standartTextSize: 14

    property int patientInsuranceNumber: 0

    signal openCurrentMedicalCard
    signal registerMedicalCard(string fullname)

    function getPatientNames() {
        var array = backend.patientListNames
        var names = []

        for (var i in array) {
            names[i] = array[i]
            console.log("Salus: [QML](PatientSearchMedicalCardPage) - Patient ", i, " is ", names[i])
        }
        return names
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

        model: getPatientNames()

        // Чтобы по умолчанию не выводилось ФИО из списка
        currentIndex: -1

        onAccepted: {
            console.log("Patiend accepted!")
            // передавать значение индекса в backend
            // если возвращается NULL - открыть окно регистрации, после чего поставить номер страховки как текущий
            // иначе, выставить номер страховки по выбранному пациенту, открыть окно карты и подставить поля из значения страховки
            patientInsuranceNumber = find(editText) !== -1 ? console.log("Yes") : registerMedicalCard(editText) //openCurrentMedicalCard() : registerMedicalCard(editText)

        }
    }
}
