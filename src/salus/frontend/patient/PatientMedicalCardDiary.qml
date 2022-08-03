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
    property string patientPhoneNumber: ""
    property string patientOccupation: ""
    property var patientComplaints: []
    property string patientDiagnosis: ""
    property var patientDiseases: []
    property string patientAnamnesis: ""

    function updatePatientData()
    {
        patientFullName = backend.currentPatientFullName
        patientAge = backend.currentPatientAge
        patientSex = backend.currentPatientSex
        patientBirthDate = backend.currentPatientBirthDate
        patientAddress = backend.currentPatientAddress
        patientPhoneNumber = backend.currentPatientPhoneNumber
        patientOccupation = backend.currentPatientOccupation
        patientComplaints = backend.currentPatientComplaints
        patientDiagnosis = backend.currentPatientDiagnosis
        patientDiseases = backend.currentPatientDiseases
        patientAnamnesis = backend.currentPatientAnamnesis
    }

    Label {
        id: labelTitle

        text: "Дневник лечения"

        font.pointSize: 20
        font.bold: true

        anchors.top: parent.top
        anchors.topMargin: 50
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Label {
        id: labelRecords

        text: "Записи"

        font.pointSize: 17
        font.bold: true

        anchors.top: labelTitle.bottom
        anchors.topMargin: 40

        anchors.horizontalCenter: parent.horizontalCenter
    }

    ListModel
    {
        id: testModel

        ListElement
        {
            test: "Record1"
        }

        ListElement
        {
            test: "Record2"
        }

        ListElement
        {
            test: "Record3"
        }
    }

    ListView
    {
        id: recordsListView

        model: testModel

        spacing: 15

        anchors
        {
            top: labelRecords.bottom
            topMargin: 10

            bottom: parent.bottom
            bottomMargin: 200

            left: parent.left

            right: parent.right
        }

        delegate: Component {
            Item {
                width: parent.width
                height: 40

                Column {
                    anchors.centerIn: parent

                    Text
                    {
                        font.pointSize: 15
                        text: test // TODO: поставить модель из БД
                    }
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: recordsListView.currentIndex = index
                }
            }
        }
        highlight: Rectangle {

            anchors
            {
                left: parent.left
                leftMargin: 300

                right: parent.right
                rightMargin: 300
            }

            color: "lightsteelblue";
        }

        clip: true
        focus: true
    }

    Row {
        id: buttons_diary

        anchors.top: recordsListView.bottom
        anchors.topMargin: 20

        anchors.horizontalCenter: parent.horizontalCenter

        transformOrigin: Item.Center

        spacing: 50

        Button
        {
            id: buttonAddMedicalData

            font.pointSize: buttonStandartTextFontSize * 1.1
            font.bold: false

            width: 200
            height: 60

            text: "Добавить запись"

            onClicked:
            {
            }
        }

        Button
        {
            id: buttonEditMedicalData

            font.pointSize: buttonStandartTextFontSize * 1.1
            font.bold: false

            width: 200
            height: 60

            text: "Изменить запись"

            onClicked:
            {
            }
        }

        Button
        {
            id: buttonDeleteMedicalData

            font.pointSize: buttonStandartTextFontSize * 1.1
            font.bold: false

            width: 200
            height: 60

            text: "Удалить запись"

            onClicked:
            {
            }
        }
    }
}
