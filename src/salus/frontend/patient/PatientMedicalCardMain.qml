import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import salus 1.0

import "components"

Page
{
    id: root

    property int buttonStandartTextFontSize: 10
    property int standartTextSize: 14

    property string buttonDefaultColor: "#E1E1E1"
    property string buttonPressedColor: "#BABABA"
    property string buttonTextColor: "#007AFF"
    property string buttonTextPressedColor: Qt.darker(buttonTextColor, 0.5)

    property Item returnButtonAddress: buttonReturn

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
        patientFullName = backend.currentPatientFullName;
        patientAge = backend.currentPatientAge;
        patientSex = backend.currentPatientSex;
        patientBirthDate = backend.currentPatientBirthDate;
        patientAddress = backend.currentPatientAddress;
        patientPhoneNumber = backend.currentPatientPhoneNumber;
        patientOccupation = backend.currentPatientOccupation;

        backend.sortPatientRecordListModel();
    }

    Rectangle
    {
        id: background

        anchors.fill: parent
        color: mainBackgroundColor
    }

    Menu
    {
        id: menuPrintCard

        MenuItem
        {
            text: "Вся карта"

            onTriggered: function()
            {
                backend.printCard(0);
            }
        }

        MenuItem
        {
            text: "Страница"
        }

        MenuItem
        {
            text: "Дневник"
        }
    }

    ButtonReturn
    {
        id: buttonReturn

        anchors
        {
            top: parent.top
            left: parent.left
            margins: 5
        }
    }

    Label
    {
        id: labelTitle

        anchors
        {
            top: parent.top
            topMargin: 50
            horizontalCenter: parent.horizontalCenter
        }
        font.pointSize: 20
        font.bold: true        
        text: "Амбулаторная карта"
    }

    Label
    {
        id: labelPatientName

        anchors
        {
            top: parent.top
            topMargin: 100
            horizontalCenter: parent.horizontalCenter
        }
        font.pointSize: 20
        font.bold: false        
        text: "<b>Пациент:</b> " + patientFullName
    }

    Row
    {
        id: buttons_medical_card

        anchors.centerIn: parent

        spacing: 50

        Button
        {
            id: buttonDiary

            contentItem: Text
            {
                font.pointSize: 13
                opacity: enabled ? 1.0 : 0.3
                color: buttonDiary.down ? buttonTextPressedColor : buttonTextColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: "Дневник лечения"
            }

            background: Rectangle
            {
                anchors.fill: parent
                radius: 14
                color: buttonDiary.down ? buttonPressedColor : buttonDefaultColor
            }

            width: 200
            height: 70

            onClicked: function()
            {
                openDiary();
            }
        }

        Button
        {
            id: buttonPrintMedicalCard

            contentItem: Text
            {
                font.pointSize: 13
                opacity: enabled ? 1.0 : 0.3
                color: buttonPrintMedicalCard.down ? buttonTextPressedColor : buttonTextColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: "Печать карты"
            }

            background: Rectangle
            {
                anchors.fill: parent
                radius: 14
                color: buttonPrintMedicalCard.down ? buttonPressedColor : buttonDefaultColor
            }

            width: 200
            height: 70

            onClicked: function()
            {
                menuPrintCard.popup();
            }
        }

        Button
        {
            id: buttonDeletePatient

            contentItem: Text
            {
                font.pointSize: 13
                opacity: enabled ? 1.0 : 0.3
                color: buttonDeletePatient.down ? buttonTextPressedColor : buttonTextColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: "Удалить карту"
            }

            background: Rectangle
            {
                anchors.fill: parent
                radius: 14
                color: buttonDeletePatient.down ? buttonPressedColor : buttonDefaultColor
            }

            width: 200
            height: 70

            onClicked: function()
            {
                deletePatient();
            }
        }
    }
}
