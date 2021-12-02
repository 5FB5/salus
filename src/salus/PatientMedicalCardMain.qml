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
    property string patientBirthData
    property string patientAddress
    property string patientInsuranceCompany
    property int patientInsuranceNumber
    property int patientPhoneNumber
    property string patientOccupation
    property string patientDiagnosis
    property string patientDiseases
    property string anamnesis

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
}
