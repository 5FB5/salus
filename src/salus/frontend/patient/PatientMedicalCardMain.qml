import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
//import Qt.labs.platform 1.1
import QtQuick.Dialogs 1.3

import salus 1.0

Page {
    id: root

    property int buttonStandartTextFontSize: 10
    property int standartTextSize: 14

    property string patientFullName: ""
    property int patientAge: 0
    property bool patientSex: false
    property string patientBirthDate: ""
    property string patientAddress: ""
    property string patientPhoneNumber: ""
    property string patientOccupation: ""
    property var patientComplaints: []
    property string patientDiagnosis: ""
    property var patientDiseases: []
    property string patientAnamnesis: ""

    signal openDiary()
    signal deletePatient()

    function updatePatientData()
    {
        patientFullName = backend.currentPatientFullName
        patientAge = backend.currentPatientAge
        patientSex = backend.currentPatientSex
        patientBirthDate = backend.currentPatientBirthDate
        patientAddress = backend.currentPatientAddress
        patientPhoneNumber = backend.currentPatientPhoneNumber
        patientOccupation = backend.currentPatientOccupation
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

        text: "<b>Пациент:</b> " + patientFullName

        font.pointSize: 20
        font.bold: false

        anchors.top: parent.top
        anchors.topMargin: 100
        anchors.horizontalCenter: parent.horizontalCenter
    }


    Row {
        id: buttons_medical_card

        anchors.centerIn: parent

        spacing: 50

        Button {
            id: buttonDiary

            font.pointSize: buttonStandartTextFontSize * 1.1
            font.bold: false

            width: 200
            height: 60

            text: "Дневник лечения"

            onClicked: {
                openDiary()
            }
        }

        Button {
            id: buttonPrintMedicalCard

            font.pointSize: buttonStandartTextFontSize * 1.1
            font.bold: false

            width: 200
            height: 60

            text: "Печать карты"

            onClicked:
            {
                console.log("TODO: Печать карты");
                backend.printCard();
            }
        }

        Button {
            id: buttonDeletePatient

            font.pointSize: buttonStandartTextFontSize * 1.1
            font.bold: false

            width: 200
            height: 60

            text: "Удалить пациента из БД"

            onClicked: {
                deletePatient()
            }
        }
    }
}
