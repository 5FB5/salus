import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

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
    property int patientPhoneNumber: 0
    property string patientOccupation: ""
    property var patientComplaints: []
    property string patientDiagnosis: ""
    property var patientDiseases: []
    property string patientAnamnesis: ""

    Label {
        id: labelTitle

        text: "Дневник лечения"

        font.pointSize: 20
        font.bold: true

        anchors.top: parent.top
        anchors.topMargin: 50
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Row {
        id: buttons_diary

        anchors.centerIn: parent

        spacing: 50

        Button {
            id: buttonSaveData

            font.pointSize: buttonStandartTextFontSize * 1.1
            font.bold: false

            width: 200
            height: 60

            text: "Сохранить данные"

            onClicked: {
            }
        }
    }
}
