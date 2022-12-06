import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import salus 1.0

Page
{
    id: root

    property int buttonStandartTextFontSize: 10
    property int standartTextSize: 14

    property string buttonDefaultColor: "#E1E1E1"
    property string buttonPressedColor: "#BABABA"
    property string buttonTextColor: "#007AFF"
    property string buttonTextPressedColor: Qt.darker(buttonTextColor, 0.5)

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

        width: 500
        height: 250
        modal: true
        title: "Подтвердите действие"

        Text
        {
            id: dialogboxText

            anchors.fill: parent

            font.pointSize: 14
            wrapMode: Text.WordWrap
            text: "Удалить запись " + currentRecord + "?"
        }

        Button
        {
            id: dialogDeleteRecordRejectButton

            anchors
            {
                left:  parent.horizontalCenter
                right: parent.right
                top: dialogDeleteRecordAcceptButton.top
                leftMargin: 5
            }

            contentItem: Text
            {
                font.pointSize: 12
                opacity: enabled ? 1.0 : 0.3
                color: dialogDeleteRecordRejectButton.down ? "#FFFFFF" : "#000000"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: "Нет"
            }

            background: Rectangle
            {
                anchors.fill: parent
                radius: 14
                color: dialogDeleteRecordRejectButton.down ? "#007AFF" : buttonDefaultColor
            }

            height: 40

            onClicked: function()
            {
                dialogDeleteRecord.close();
            }
        }

        Button
        {
            id: dialogDeleteRecordAcceptButton

            anchors
            {
                left: parent.left
                right: parent.horizontalCenter
                bottom: parent.bottom
                rightMargin: 5
            }

            contentItem: Text
            {
                font.pointSize: 12
                opacity: enabled ? 1.0 : 0.3
                color: dialogDeleteRecordAcceptButton.down ? buttonTextDefaultColor : buttonTextPressedColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: "Да"
            }

            background: Rectangle
            {
                anchors.fill: parent
                radius: 14
                color: dialogDeleteRecordAcceptButton.down ? buttonDefaultColor : "#007AFF"
            }

            height: 40

            onClicked: function()
            {
                if (currentRecord === "")
                    return;

                backend.deleteRecord(currentRecord);
                recordDeleted();

                dialogDeleteRecord.close();
            }
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

        contentItem: Text
        {
            anchors
            {
                fill: parent
                verticalCenter: parent.verticalCenter
                horizontalCenter: parent.horizontalCenter
            }

            font.pointSize: 13
            opacity: enabled ? 1.0 : 0.3
            color: buttonReturn.down ? buttonTextPressedColor : buttonTextColor
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
            text: "❮"
        }

        background: Rectangle
        {
            anchors.fill: parent
            radius: 14
            color: buttonReturn.down ? buttonPressedColor : buttonDefaultColor
        }

        width: 50
        height: 50

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

            font.pointSize: 15
            height: 40
            text: display

            Rectangle
            {
                id: separator

                anchors
                {
                    left: parent.left
                    right: parent.right
                    bottom: parent.bottom
                }
                height: 1
                color: "#E1E1E1"
            }

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
            }
            color: "#E1E1E1"
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

            contentItem: Text
            {
                font.pointSize: 13
                opacity: enabled ? 1.0 : 0.3
                color: buttonAddMedicalData.down ? buttonTextPressedColor : buttonTextColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: "Добавить запись"
            }

            background: Rectangle
            {
                anchors.fill: parent
                radius: 14
                color: buttonAddMedicalData.down ? buttonPressedColor : buttonDefaultColor
            }

            width: 200
            height: 70

            onClicked: function()
            {
                openAddRecordPage();
            }
        }

        Button
        {
            id: buttonEditMedicalData

            contentItem: Text
            {
                font.pointSize: 13
                opacity: enabled ? 1.0 : 0.3
                color: buttonEditMedicalData.down ? buttonTextPressedColor : buttonTextColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: "Изменить запись"
            }

            background: Rectangle
            {
                anchors.fill: parent
                radius: 14
                color: buttonEditMedicalData.down ? buttonPressedColor : buttonDefaultColor
            }

            width: 200
            height: 70

            onClicked: function()
            {
                if (currentRecord === "")
                    return;

                openEditPage();
            }
        }

        Button
        {
            id: buttonDeleteMedicalData

            contentItem: Text
            {
                font.pointSize: 13
                opacity: enabled ? 1.0 : 0.3
                color: buttonDeleteMedicalData.down ? buttonTextPressedColor : buttonTextColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: "Удалить запись"
            }

            background: Rectangle
            {
                anchors.fill: parent
                radius: 14
                color: buttonDeleteMedicalData.down ? buttonPressedColor : buttonDefaultColor
            }

            width: 200
            height: 70

            text: "Удалить запись"

            onClicked: function()
            {
                dialogDeleteRecord.open();
            }
        }
    }
}
