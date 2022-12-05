import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import salus 1.0

Page
{
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

    signal returnBack()
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

    Button
    {
        id: buttonReturn

        anchors
        {
            top: parent.top
            left: parent.left
            topMargin: 15
            leftMargin: 15
        }
        text: "Назад"

        onClicked: function()
        {
            returnBack();
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

            font.pointSize: buttonStandartTextFontSize * 1.1
            font.bold: false
            width: 200
            height: 60

            text: "Дневник лечения"

            onClicked: function()
            {
                openDiary();
            }
        }

        Button
        {
            id: buttonPrintMedicalCard

            font.pointSize: buttonStandartTextFontSize * 1.1
            font.bold: false
            width: 200
            height: 60
            enabled: false

            text: "Печать карты"
        }

        Button
        {
            id: buttonDeletePatient

            font.pointSize: buttonStandartTextFontSize * 1.1
            font.bold: false
            width: 200
            height: 60

            text: "Удалить пациента"

            onClicked: function()
            {
                deletePatient();
            }
        }
    }
}
