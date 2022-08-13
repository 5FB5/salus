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

    property string currentRecord: ""

    signal openAddRecordPage()
    signal openEditPage()
    signal recordDeleted()

    function updatePatientData()
    {
        patientFullName = backend.currentPatientFullName;
        patientAge = backend.currentPatientAge;
        patientSex = backend.currentPatientSex;
        patientBirthDate = backend.currentPatientBirthDate;
        patientAddress = backend.currentPatientAddress;
        patientPhoneNumber = backend.currentPatientPhoneNumber;
        patientOccupation = backend.currentPatientOccupation;
    }

    Dialog
    {
        id: dialogDeleteRecord

        width: parent.width / 3.5
        height: parent.height / 3.5

        anchors.centerIn: parent

        modal: true

        title: "Подтвердите действие"
        standardButtons: Dialog.Yes | Dialog.No

        Text {
            id: dialogboxText
            font.pointSize: 14

            anchors.fill: parent

            wrapMode: Text.WordWrap

            text: qsTr("Удалить запись " + currentRecord + "?")
        }

        onAccepted: {
            if (currentRecord !== "")
            {
                backend.deleteRecord(currentRecord);
                recordDeleted();
            }
        }
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

    ListView
    {
        id: recordsListView

        model: patientRecordsListModel

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
                        text: display
                    }
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked:
                    {
                        recordsListView.currentIndex = index;
                        currentRecord = display;
                    }
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

        Component.onCompleted:
        {
//            highlightMoveVelocity = 0
            highlightMoveDuration = 0
        }
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
                openAddRecordPage()
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
                if (currentRecord !== "") {
                    openEditPage();
                }
                else {
                    console.log("Запись не выбрана");
                }
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
                dialogDeleteRecord.open();
            }
        }
    }
}
