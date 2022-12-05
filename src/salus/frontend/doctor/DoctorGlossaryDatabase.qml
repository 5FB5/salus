import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.12
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
    property string currentSymptom: ""
    property string currentUserFormulation: ""

    Component.onCompleted: function()
    {
        editPanelDiagnoses.addRecord.connect(dialogAddDiagnosis.open);
        editPanelDiagnoses.editRecord.connect(dialogEditDiagnosis.open);
        editPanelDiagnoses.removeRecord.connect(dialogDeleteDiagnosis.open);

        editPanelSymptoms.addRecord.connect(dialogAddSymptom.open);
        editPanelSymptoms.editRecord.connect(dialogEditSymptom.open);
        editPanelSymptoms.removeRecord.connect(dialogDeleteSymptom.open);

        editPanelTreatments.addRecord.connect(dialogAddTreatment.open);
        editPanelTreatments.editRecord.connect(dialogEditTreatment.open);
        editPanelTreatments.removeRecord.connect(dialogDeleteTreatment.open);

        editPanelUser.addRecord.connect(dialogAddUser.open);
        editPanelUser.editRecord.connect(dialogEditUser.open);
        editPanelUser.removeRecord.connect(dialogDeleteUser.open);
    }

    // FIXME: Сделать 3 окна на каждое действие, меняя только на требуемые данные
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
        id: dialogDeleteSymptom

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
                id: labelDeleteSymptom

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
                id: labelDeleteSymptomData

                anchors
                {
                    left: parent.left
                    right: parent.right
                    top: labelDeleteSymptom.bottom
                    topMargin: 15
                }
                font.bold: false
                font.pixelSize: 18
                wrapMode: Text.WordWrap
                text: "'" + currentSymptom + "'"
            }
        }

        onAccepted: function()
        {
            backend.deleteGlossarySymptom(currentSymptom);
        }
    }

    Dialog
    {
        id: dialogDeleteUser

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
                id: labelDeleteUser

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
                id: labelDeleteUserData

                anchors
                {
                    left: parent.left
                    right: parent.right
                    top: labelDeleteUser.bottom
                    topMargin: 15
                }
                font.bold: false
                font.pixelSize: 18
                wrapMode: Text.WordWrap
                text: "'" + currentUserFormulation + "'"
            }
        }

        onAccepted: function()
        {
            backend.deleteGlossaryUserFormulation(currentUserFormulation);
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
            currentDiagnosis = inputEditDiagnosis.text;
            inputEditDiagnosis.text = "";
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
            currentTreatment = inputEditTreatment.text;
            inputEditTreatment.text = "";
        }
    }

    Dialog
    {
        id: dialogEditSymptom

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
                id: labelEditSymptomInput

                anchors
                {
                    top: parent.top
                    horizontalCenter: parent.horizontalCenter
                    topMargin: 15
                }
                font.bold: true
                font.pixelSize: 18
                text: "Введите симптом"
            }

            TextField
            {
                id: inputEditSymptom

                anchors
                {
                    top: labelEditSymptomInput.bottom
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
            backend.editGlossarySymptom(currentSymptom.toString(), inputEditSymptom.text);
            currentSymptom = inputEditSymptom.text;
            inputEditSymptom.text = "";
        }
    }

    Dialog
    {
        id: dialogEditUser

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
                id: labelEditUserInput

                anchors
                {
                    top: parent.top
                    horizontalCenter: parent.horizontalCenter
                    topMargin: 15
                }
                font.bold: true
                font.pixelSize: 18
                text: "Введите формулировку"
            }

            TextField
            {
                id: inputEditUser

                anchors
                {
                    top: labelEditUserInput.bottom
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
            backend.editGlossaryUserFormulation(currentUserFormulation.toString(), inputEditUser.text);
            currentUserFormulation = inputEditUser.text;
            inputEditUser.text = "";
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
            inputDiagnosis.text = "";
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
            inputTreatment.text = "";
        }
    }

    Dialog
    {
        id: dialogAddSymptom

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
                id: labelSymptomInput

                anchors
                {
                    top: parent.top
                    horizontalCenter: parent.horizontalCenter
                    topMargin: 15
                }
                font.bold: true
                font.pixelSize: 18
                text: "Введите симптом"
            }

            TextField
            {
                id: inputSymptom

                anchors
                {
                    top: labelSymptomInput.bottom
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
            backend.addGlossarySymptom(inputSymptom.text);
            inputSymptom.text = "";
        }
    }

    Dialog
    {
        id: dialogAddUser

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
                id: labelUserInput

                anchors
                {
                    top: parent.top
                    horizontalCenter: parent.horizontalCenter
                    topMargin: 15
                }
                font.bold: true
                font.pixelSize: 18
                text: "Введите формулировку"
            }

            TextField
            {
                id: inputUser

                anchors
                {
                    top: labelUserInput.bottom
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
            backend.addGlossaryUserFormulation(inputUser.text);
            inputUser.text = "";
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

    SplitView
    {
        id: splitView

        anchors
        {
            top: labelTitle.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            topMargin: 15
        }
        orientation: Qt.Horizontal

        Rectangle
        {
            id: listDiagnoses

            width: 200
            Layout.maximumWidth: 900
            Layout.minimumWidth: 150
            clip: true
            color: listViewBackgroundColor

            Text
            {
                id: labelListViewDiagnoses

                anchors
                {
                    top: parent.top
                    horizontalCenter: parent.horizontalCenter
                    topMargin: 15
                }
                font.bold: true
                font.pixelSize: 25
                text: "Диагноз"
            }

            ListView
            {
                id: listViewDiagnoses

                Component.onCompleted: function()
                {
                    highlightMoveDuration = 0;

                    // Чтобы если мы ещё не выбрали элемент,
                    // то при нажатии на изменение или удаление работали с первым элементом
                    currentDiagnosis = backend.getGlossaryDiagnosisAt(0);
                }

                anchors
                {
                    fill: parent
                    left: parent.left
                    right: parent.right
                    top: labelListViewDiagnoses.bottom
                    topMargin: 55
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
        }

        Rectangle
        {
            id: listTreatments

            width: 200
            Layout.minimumWidth: 50
            clip: true
            color: listViewBackgroundColor

            Text
            {
                id: labelListViewTreatments

                anchors
                {
                    top: parent.top
                    horizontalCenter: parent.horizontalCenter
                    topMargin: 15
                }
                font.bold: true
                font.pixelSize: 25
                text: "Терапия"
            }

            ListView
            {
                id: listViewTreatments

                Component.onCompleted: function()
                {
                    highlightMoveDuration = 0;
                    // Чтобы если мы ещё не выбрали элемент,
                    // то при нажатии на изменение или удаление работали с первым элементом
                    currentTreatment = backend.getGlossaryTreatmentAt(0);
                }

                anchors
                {
                    fill: parent
                    left: parent.left
                    right: parent.right
                    top: labelListViewTreatments.bottom
                    topMargin: 55
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

        Rectangle
        {
            id: listSymptoms

            width: 200
            Layout.maximumWidth: 900
            Layout.minimumWidth: 150
            clip: true
            color: listViewBackgroundColor

            Text
            {
                id: labelListViewSymptoms

                anchors
                {
                    top: parent.top
                    horizontalCenter: parent.horizontalCenter
                    topMargin: 15
                }
                font.bold: true
                font.pixelSize: 25
                text: "Симптомы"
            }

            ListView
            {
                id: listViewSymptoms

                Component.onCompleted: function()
                {
                    highlightMoveDuration = 0;
                    // Чтобы если мы ещё не выбрали элемент,
                    // то при нажатии на изменение или удаление работали с первым элементом
                    currentSymptom = backend.getGlossarySymptomAt(0);
                }

                anchors
                {
                    fill: parent
                    left: parent.left
                    right: parent.right
                    top: labelListViewSymptoms.bottom
                    topMargin: 55
                    bottomMargin: listViewBottomMargin
                }

                clip: true
                model: glossarySymptomsListModel
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
                    color: listViewSymptoms.currentIndex === index ? "#ffffff" : "#000000"
                    text: display

                    MouseArea
                    {
                        anchors.fill: parent

                        onClicked: function()
                        {
                            listViewSymptoms.currentIndex = index;
                            currentSymptom = display.toString();
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
                id: editPanelSymptoms

                anchors
                {
                    top: listViewSymptoms.bottom
                    left: listViewSymptoms.left
                    right: listViewSymptoms .right
                    topMargin: 5
                }
            }
        }

        Rectangle
        {
            id: listUser

            width: 200
            Layout.maximumWidth: root.width
            Layout.minimumWidth: 150
            clip: true
            color: listViewBackgroundColor

            Text
            {
                id: labelListViewUser

                anchors
                {
                    top: parent.top
                    left: parent.left
                    right: parent.right
                    topMargin: 15
                    leftMargin: 15
                    rightMargin: 15
                }
                font.bold: true
                font.pixelSize: 25
                wrapMode: Text.WordWrap
                text: "Пользоват. формулировки"
            }

            ListView
            {
                id: listViewUser

                Component.onCompleted: function()
                {
                    highlightMoveDuration = 0;
                    // Чтобы если мы ещё не выбрали элемент,
                    // то при нажатии на изменение или удаление работали с первым элементом
                    currentUserFormulation = backend.getGlossaryUserFormulationAt(0);
                }

                anchors
                {
                    fill: parent
                    left: parent.left
                    right: parent.right
                    top: labelListViewUser.bottom
                    topMargin: 75
                    bottomMargin: listViewBottomMargin
                }

                clip: true
                model: glossaryUserListModel
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
                    color: listViewUser.currentIndex === index ? "#ffffff" : "#000000"
                    text: display

                    MouseArea
                    {
                        anchors.fill: parent

                        onClicked: function()
                        {
                            listViewUser.currentIndex = index;
                            currentUserFormulation = display.toString();
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
                id: editPanelUser

                anchors
                {
                    top: listViewUser.bottom
                    left: listViewUser.left
                    right: listViewUser.right
                    topMargin: 5
                }
            }
        }
    }
}
