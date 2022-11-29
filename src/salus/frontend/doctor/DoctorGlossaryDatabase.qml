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
    property int listViewBottomMargin: 150
    property string listViewBackgroundColor: "#bbbbbb"
    property string currentDiagnosis: ""
    property string currentTreatment: ""

    Component.onCompleted: function()
    {
        editPanelDiagnoses.addRecord.connect(dialogAddDiagnosis.open);
        editPanelDiagnoses.editRecord.connect(dialogEditDiagnosis.open);
        editPanelDiagnoses.removeRecord.connect(dialogDeleteDiagnosis.open);

        editPanelTreatments.addRecord.connect(dialogAddTreatment.open);
        editPanelTreatments.editRecord.connect(dialogEditTreatment.open);
        editPanelTreatments.removeRecord.connect(dialogDeleteTreatment.open);
    }

    Dialog
    {
        id: dialogDeleteDiagnosis

        Component.onCompleted: function()
        {
            standardButton(Dialog.Ok).text = "Да";
            standardButton(Dialog.Cancel).text = "Нет";
        }

        anchors.centerIn: parent

        font.pixelSize: 15
        title: "Удаление записи"
        modal: true
        standardButtons: Dialog.Ok | Dialog.Cancel
        width: 500
        height: 400

        contentItem: Item
        {
            Text
            {
                id: labelDeleteDiagnosis

                anchors
                {
                    top: parent.top
                    horizontalCenter: parent.horizontalCenter
                    topMargin: 15
                }
                font.bold: true
                font.pixelSize: 18
                text: "Вы точно хотите удалить запись?"
            }

            Text
            {
                id: labelDeleteDiagnosisData

                anchors
                {
                    left: parent.left
                    right: parent.right
                    top: labelDeleteDiagnosis.bottom
                    topMargin: 15
                }
                font.bold: false
                font.pixelSize: 18
                wrapMode: Text.WordWrap
                text: "'" + currentDiagnosis + "'"
            }
        }

        onAccepted: function()
        {
            backend.deleteGlossaryDiagnosis(currentDiagnosis);
        }
    }

    Dialog
    {
        id: dialogDeleteTreatment

        Component.onCompleted: function()
        {
            standardButton(Dialog.Ok).text = "Да";
            standardButton(Dialog.Cancel).text = "Нет";
        }

        anchors.centerIn: parent

        font.pixelSize: 15
        title: "Удаление записи"
        modal: true
        standardButtons: Dialog.Ok | Dialog.Cancel
        width: 500
        height: 400

        contentItem: Item
        {
            Text
            {
                id: labelDeleteTreatment

                anchors
                {
                    top: parent.top
                    horizontalCenter: parent.horizontalCenter
                    topMargin: 15
                }
                font.bold: true
                font.pixelSize: 18
                text: "Вы точно хотите удалить запись?"
            }

            Text
            {
                id: labelDeleteTreatmentData

                anchors
                {
                    left: parent.left
                    right: parent.right
                    top: labelDeleteTreatment.bottom
                    topMargin: 15
                }
                font.bold: false
                font.pixelSize: 18
                wrapMode: Text.WordWrap
                text: "'" + currentTreatment + "'"
            }
        }

        onAccepted: function()
        {
            backend.deleteGlossaryTreatment(currentTreatment);
        }
    }

    Dialog
    {
        id: dialogEditDiagnosis

        Component.onCompleted: function()
        {
            standardButton(Dialog.Ok).text = "Изменить";
            standardButton(Dialog.Cancel).text = "Отмена";
        }

        anchors.centerIn: parent

        font.pixelSize: 15
        title: "Редактирование записи"
        modal: true
        standardButtons: Dialog.Ok | Dialog.Cancel
        width: 500
        height: 400

        contentItem: Item
        {
            Text
            {
                id: labelEditDiagnosisInput

                anchors
                {
                    top: parent.top
                    horizontalCenter: parent.horizontalCenter
                    topMargin: 15
                }
                font.bold: true
                font.pixelSize: 18
                text: "Введите диагноз"
            }

            TextField
            {
                id: inputEditDiagnosis

                anchors
                {
                    top: labelEditDiagnosisInput.bottom
                    horizontalCenter: parent.horizontalCenter
                    topMargin: 15
                }
                width: 450
                height: 40
                font.pixelSize: 15
            }
        }

        onAccepted: function()
        {
            backend.editGlossaryDiagnosis(currentDiagnosis.toString(), inputEditDiagnosis.text);
        }
    }

    Dialog
    {
        id: dialogEditTreatment

        Component.onCompleted: function()
        {
            standardButton(Dialog.Ok).text = "Изменить";
            standardButton(Dialog.Cancel).text = "Отмена";
        }

        anchors.centerIn: parent

        font.pixelSize: 15
        title: "Редактирование записи"
        modal: true
        standardButtons: Dialog.Ok | Dialog.Cancel
        width: 500
        height: 400

        contentItem: Item
        {
            Text
            {
                id: labelEditTreatmentInput

                anchors
                {
                    top: parent.top
                    horizontalCenter: parent.horizontalCenter
                    topMargin: 15
                }
                font.bold: true
                font.pixelSize: 18
                text: "Введите название терапии"
            }

            TextField
            {
                id: inputEditTreatment

                anchors
                {
                    top: labelEditTreatmentInput.bottom
                    horizontalCenter: parent.horizontalCenter
                    topMargin: 15
                }
                width: 450
                height: 40
                font.pixelSize: 15
            }
        }

        onAccepted: function()
        {
            backend.editGlossaryTreatment(currentTreatment.toString(), inputEditTreatment.text);
        }
    }

    Dialog
    {
        id: dialogAddDiagnosis

        Component.onCompleted: function()
        {
            standardButton(Dialog.Ok).text = "Добавить";
            standardButton(Dialog.Cancel).text = "Отмена";
        }

        anchors.centerIn: parent

        font.pixelSize: 15
        title: "Новая запись"
        modal: true
        standardButtons: Dialog.Ok | Dialog.Cancel
        width: 500
        height: 400

        contentItem: Item
        {
            Text
            {
                id: labelDiagnosisInput

                anchors
                {
                    top: parent.top
                    horizontalCenter: parent.horizontalCenter
                    topMargin: 15
                }
                font.bold: true
                font.pixelSize: 18
                text: "Введите диагноз"
            }

            TextField
            {
                id: inputDiagnosis

                anchors
                {
                    top: labelDiagnosisInput.bottom
                    horizontalCenter: parent.horizontalCenter
                    topMargin: 15
                }
                width: 450
                height: 40
                font.pixelSize: 15
            }
        }

        onAccepted: function()
        {
            backend.addGlossaryDiagnosis(inputDiagnosis.text);
        }
    }

    Dialog
    {
        id: dialogAddTreatment

        Component.onCompleted: function()
        {
            standardButton(Dialog.Ok).text = "Добавить";
            standardButton(Dialog.Cancel).text = "Отмена";
        }

        anchors.centerIn: parent

        font.pixelSize: 15
        title: "Новая запись"
        modal: true
        standardButtons: Dialog.Ok | Dialog.Cancel
        width: 500
        height: 400

        contentItem: Item
        {
            Text
            {
                id: labelTreatmentInput

                anchors
                {
                    top: parent.top
                    horizontalCenter: parent.horizontalCenter
                    topMargin: 15
                }
                font.bold: true
                font.pixelSize: 18
                text: "Введите название терапии"
            }

            TextField
            {
                id: inputTreatment

                anchors
                {
                    top: labelTreatmentInput.bottom
                    horizontalCenter: parent.horizontalCenter
                    topMargin: 15
                }
                width: 450
                height: 40
                font.pixelSize: 15
            }
        }

        onAccepted: function()
        {
            backend.addGlossaryTreatment(inputTreatment.text);
        }
    }

    Text
    {
        id: labelTitle

        anchors
        {
            top: parent.top
            topMargin: 20
            horizontalCenter: parent.horizontalCenter
        }
        font.pointSize: 20
        font.bold: true
        text: "Глоссарий"
    }

    Text
    {
        id: labelListViewDiagnoses

        anchors
        {
            top: labelListViewTreatments.top
            bottom: listViewDiagnoses.top
            bottomMargin: 20
            horizontalCenter: listViewDiagnoses.horizontalCenter
        }
        font.bold: true
        font.pixelSize: 25
        text: "Диагноз"
    }

    Rectangle
    {
        id: backgroundDiagnoses

        anchors
        {
            left: listViewDiagnoses.left
            right: listViewDiagnoses.right
            top: labelListViewDiagnoses.bottom
            bottom: listViewDiagnoses.bottom
            topMargin: 5
        }
        color: listViewBackgroundColor
    }

    ListView
    {
        id: listViewDiagnoses

        Component.onCompleted: function()
        {
            highlightMoveDuration = 0;
            currentDiagnosis = backend.getGlossaryDiagnosisAt(0);
        }

        anchors
        {
            left: parent.left
            right: labelTitle.horizontalCenter
            top: listViewTreatments.top
            bottom: parent.bottom
            leftMargin: 5
            rightMargin: 5
            bottomMargin: listViewBottomMargin
        }
        clip: true
        model: glossaryDiagnosesListModel
        spacing: 15

        delegate: Text
        {
            anchors
            {
                left: parent.left
                right: parent.right
                leftMargin: 10
                rightMargin: 10
            }
            width: parent.width
            wrapMode: Text.WordWrap
            font.pixelSize: 17
            color: listViewDiagnoses.currentIndex === index ? "#ffffff" : "#000000"
            text: display

            MouseArea
            {
                anchors.fill: parent

                onClicked: function()
                {
                    listViewDiagnoses.currentIndex = index;
                    currentDiagnosis = display.toString();
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
            color: "lightsteelblue"
        }
    }

    GlossaryEditPanel
    {
        id: editPanelDiagnoses

        anchors
        {
            top: listViewDiagnoses.bottom
            left: listViewDiagnoses.left
            right: listViewDiagnoses.right
            topMargin: 5
        }
    }

    Text
    {
        id: labelListViewTreatments

        anchors
        {
           bottom: listViewTreatments.top
           bottomMargin: 20
           horizontalCenter: listViewTreatments.horizontalCenter
        }
        font.bold: true
        font.pixelSize: 25
        text: "Терапия"
    }

    Rectangle
    {
        id: backgroundTreatments

        anchors
        {
            left: listViewTreatments.left
            right: listViewTreatments.right
            top: labelListViewTreatments.bottom
            bottom: listViewTreatments.bottom
            topMargin: 5
        }
        color: listViewBackgroundColor
    }

    ListView
    {
        id: listViewTreatments

        Component.onCompleted: function()
        {
            highlightMoveDuration = 0;
            currentTreatment = backend.getGlossaryTreatmentAt(0);
        }

        anchors
        {
            left: labelTitle.horizontalCenter
            right: parent.right
            top: labelTitle.bottom
            bottom: parent.bottom
            rightMargin: 5
            topMargin: 50
            bottomMargin: listViewBottomMargin
        }
        clip: true
        model: glossaryTreatmentsListModel
        spacing: 15

        delegate: Text
        {
            anchors
            {
                left: parent.left
                right: parent.right
                leftMargin: 10
                rightMargin: 10
            }
            width: parent.width
            wrapMode: Text.WordWrap
            font.pixelSize: 17
            color: listViewTreatments.currentIndex === index ? "#ffffff" : "#000000"
            text: display

            MouseArea
            {
                anchors.fill: parent

                onClicked: function()
                {
                    listViewTreatments.currentIndex = index;
                    currentTreatment = display.toString();
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
            color: "lightsteelblue"
        }
    }

    GlossaryEditPanel
    {
        id: editPanelTreatments

        anchors
        {
            top: listViewTreatments.bottom
            left: listViewTreatments.left
            right: listViewTreatments.right
            topMargin: 5
        }
    }
}
