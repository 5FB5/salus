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

    property string currentRecord: ""

    signal returnBack()
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

        recordsListView.currentIndex = 0;

        currentRecord = recordsListView.currentItem == null ? "" : recordsListView.currentItem.text
    }

    Dialog
    {
        id: dialogDeleteRecord

        anchors.centerIn: parent

        width: parent.width / 3.5
        height: parent.height / 3.5
        modal: true
        standardButtons: Dialog.Yes | Dialog.No
        title: "Подтвердите действие"

        Text
        {
            id: dialogboxText

            anchors.fill: parent

            font.pointSize: 14
            wrapMode: Text.WordWrap
            text: qsTr("Удалить запись " + currentRecord + "?")
        }

        onAccepted: function()
        {
            if (currentRecord === "")
                return;

            backend.deleteRecord(currentRecord);
            recordDeleted();
        }
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
        text: "Дневник лечения"
    }

    Label {
        id: labelRecords

        anchors
        {
            top: labelTitle.bottom
            topMargin: 40
            horizontalCenter: parent.horizontalCenter
        }
        font.pointSize: 17
        font.bold: true
        text: "Записи"
    }

    ListView
    {
        id: recordsListView

        Component.onCompleted:
        {
            highlightMoveDuration = 0;
        }

        anchors
        {
            left: parent.left
            right: parent.right
            top: labelRecords.bottom
            bottom: parent.bottom
            topMargin: 10
            bottomMargin: 200
        }
        clip: true
        focus: true
        model: patientRecordsListModel
        spacing: 15

        delegate: Text
        {
            anchors.horizontalCenter: parent.horizontalCenter

            height: 40
            font.pointSize: 15
            text: display

            MouseArea
            {
                anchors.fill: parent

                onClicked: function()
                {
                    recordsListView.currentIndex = index;
                    currentRecord = display;
                }
            }
        }

        highlight: Rectangle
        {
            anchors
            {
                left: parent.left
                right: parent.right
                leftMargin: 300
                rightMargin: 300
            }
            color: "lightsteelblue"
        }
    }

    Row {
        id: buttons_diary

        anchors
        {
            top: recordsListView.bottom
            topMargin: 20
            horizontalCenter: parent.horizontalCenter
        }
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

            onClicked: function()
            {
                openAddRecordPage();
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

            onClicked: function()
            {
                if (currentRecord === "")
                    return;

                openEditPage();
            }
        }

        Button
        {
            id: buttonPrintRecord

            font.pointSize: buttonStandartTextFontSize * 1.1
            font.bold: false

            width: 200
            height: 60

            text: "Печать записи"

            onClicked:
            {
                console.log("TODO: Печать записи")
                backend.printCard();
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

            onClicked: function()
            {
                dialogDeleteRecord.open();
            }
        }
    }
}
