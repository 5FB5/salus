import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import io.qt.salus 1.0

Page {
    id: root

    property int buttonStandartTextFontSize: 10
    property int standartTextSize: 14

    property string patientFullName
    property int patientAge
    property bool patientSex
    property string patientBirthDate
    property string patientAddress
    property int patientPhoneNumber
    property string patientOccupation
    property var patientComplaints: []
    property string patientDiagnosis
    property var patientDiseases: []
    property string patientAnamnesis

    Backend {
        id: backend
    }

    Label {
        id: labelTitle

        text: "Амбулаторная карта"

        font.pointSize: 20
        font.bold: true

        anchors.top: parent.top
        anchors.topMargin: 50
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Label {
        id: labelPatientName

        text: "Пациент: " + patientFullName

        font.pointSize: 20
        font.bold: true

        anchors.top: parent.top
        anchors.topMargin: 100
        anchors.horizontalCenter: parent.horizontalCenter

        Row {
            id: buttons_medical_card

            anchors.fill: parent
            anchors.topMargin: 250
            anchors.leftMargin: 45 // FIXME: позиционирование по середине должно быть динамическим

            spacing: 50

            Button {
                id: buttonDiary

                font.pointSize: buttonStandartTextFontSize * 1.1
                font.bold: false

                width: 200
                height: 60

                text: "Дневник лечения"
            }

            Button {
                id: buttonPrintMedicalCard

                font.pointSize: buttonStandartTextFontSize * 1.1
                font.bold: false

                width: 200
                height: 60

                text: "Печать амбулаторной карты"
            }
        }
    }
}
