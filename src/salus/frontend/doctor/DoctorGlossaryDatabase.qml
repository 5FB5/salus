import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.4
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import salus 1.0

import "components"

Page
{
    id: root

    property int buttonStandartTextFontSize: 10
    property int standartTextSize: 14
    property int listViewBottomMargin: 150
    property string listViewBackgroundColor: "#FFFFFF"
    property string listViewDelegateHighlightColor: "#E1E1E1"
    property int dialogBoxHeight: 250

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

        anchors.centerIn: parent

        font.pixelSize: 15
        title: "Удаление записи"
        modal: true
        width: 500
        height: dialogBoxHeight

        Button
        {
            id: dialogDeleteDiagnosisRejectButton

            anchors
            {
                left:  parent.horizontalCenter
                right: parent.right
                top: dialogDeleteDiagnosisAcceptButton.top
                leftMargin: 5
            }

            contentItem: Text
            {
                font.pointSize: 12
                opacity: enabled ? 1.0 : 0.3
                color: dialogDeleteDiagnosisRejectButton.down ? buttonTextPressedColor : buttonTextDefaultColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: "Нет"
            }

            background: Rectangle
            {
                anchors.fill: parent
                radius: 14
                color: dialogDeleteDiagnosisRejectButton.down ? buttonPressedColor : buttonDefaultColor
            }

            height: 40

            onClicked: function()
            {
                dialogDeleteDiagnosis.close();
            }
        }

        Button
        {
            id: dialogDeleteDiagnosisAcceptButton

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
                color: dialogDeleteDiagnosisAcceptButton.down ? buttonTextDefaultColor : buttonTextPressedColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: "Да"
            }

            background: Rectangle
            {
                anchors.fill: parent
                radius: 14
                color: dialogDeleteDiagnosisAcceptButton.down ? buttonDefaultColor : buttonPressedColor
            }

            height: 40

            onClicked: function()
            {
                backend.deleteGlossaryDiagnosis(currentDiagnosis);
                dialogDeleteDiagnosis.close();
            }
        }

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
    }

    Dialog
    {
        id: dialogDeleteTreatment

        anchors.centerIn: parent

        font.pixelSize: 15
        title: "Удаление записи"
        modal: true
        width: 500
        height: dialogBoxHeight

        Button
        {
            id: dialogDeleteTreatmentRejectButton

            anchors
            {
                left:  parent.horizontalCenter
                right: parent.right
                top: dialogDeleteTreatmentAcceptButton.top
                leftMargin: 5
            }

            contentItem: Text
            {
                font.pointSize: 12
                opacity: enabled ? 1.0 : 0.3
                color: dialogDeleteTreatmentRejectButton.down ? buttonTextPressedColor : buttonTextDefaultColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: "Нет"
            }

            background: Rectangle
            {
                anchors.fill: parent
                radius: 14
                color: dialogDeleteTreatmentRejectButton.down ? buttonPressedColor : buttonDefaultColor
            }

            height: 40

            onClicked: function()
            {
                dialogDeleteTreatment.close();
            }
        }

        Button
        {
            id: dialogDeleteTreatmentAcceptButton

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
                color: dialogDeleteTreatmentAcceptButton.down ? buttonTextDefaultColor : buttonTextPressedColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: "Да"
            }

            background: Rectangle
            {
                anchors.fill: parent
                radius: 14
                color: dialogDeleteTreatmentAcceptButton.down ? buttonDefaultColor : buttonPressedColor
            }

            height: 40

            onClicked: function()
            {
                backend.deleteGlossaryTreatment(currentTreatment);
                dialogDeleteTreatment.close();
            }
        }

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
    }

    Dialog
    {
        id: dialogDeleteSymptom

        anchors.centerIn: parent

        font.pixelSize: 15
        title: "Удаление записи"
        modal: true
        width: 500
        height: dialogBoxHeight

        Button
        {
            id: dialogDeleteSymptomRejectButton

            anchors
            {
                left:  parent.horizontalCenter
                right: parent.right
                top: dialogDeleteSymptomAcceptButton.top
                leftMargin: 5
            }

            contentItem: Text
            {
                font.pointSize: 12
                opacity: enabled ? 1.0 : 0.3
                color: dialogDeleteSymptomRejectButton.down ? buttonTextPressedColor : buttonTextDefaultColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: "Нет"
            }

            background: Rectangle
            {
                anchors.fill: parent
                radius: 14
                color: dialogDeleteSymptomRejectButton.down ? buttonPressedColor : buttonDefaultColor
            }

            height: 40

            onClicked: function()
            {
                dialogDeleteSymptom.close();
            }
        }

        Button
        {
            id: dialogDeleteSymptomAcceptButton

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
                color: dialogDeleteSymptomAcceptButton.down ? buttonTextDefaultColor : buttonTextPressedColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: "Да"
            }

            background: Rectangle
            {
                anchors.fill: parent
                radius: 14
                color: dialogDeleteSymptomAcceptButton.down ? buttonDefaultColor : buttonPressedColor
            }

            height: 40

            onClicked: function()
            {
                backend.deleteGlossarySymptom(currentSymptom);
                dialogDeleteSymptom.close();
            }
        }

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
    }

    Dialog
    {
        id: dialogDeleteUser

        anchors.centerIn: parent

        font.pixelSize: 15
        title: "Удаление записи"
        modal: true
        width: 500
        height: dialogBoxHeight

        Button
        {
            id: dialogDeleteUserRejectButton

            anchors
            {
                left:  parent.horizontalCenter
                right: parent.right
                top: dialogDeleteUserAcceptButton.top
                leftMargin: 5
            }

            contentItem: Text
            {
                font.pointSize: 12
                opacity: enabled ? 1.0 : 0.3
                color: dialogDeleteUserRejectButton.down ? buttonTextPressedColor : buttonTextDefaultColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: "Нет"
            }

            background: Rectangle
            {
                anchors.fill: parent
                radius: 14
                color: dialogDeleteUserRejectButton.down ? buttonPressedColor : buttonDefaultColor
            }

            height: 40

            onClicked: function()
            {
                dialogDeleteUser.close();
            }
        }

        Button
        {
            id: dialogDeleteUserAcceptButton

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
                color: dialogDeleteUserAcceptButton.down ? buttonTextDefaultColor : buttonTextPressedColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: "Да"
            }

            background: Rectangle
            {
                anchors.fill: parent
                radius: 14
                color: dialogDeleteUserAcceptButton.down ? buttonDefaultColor : buttonPressedColor
            }

            height: 40

            onClicked: function()
            {
                backend.deleteGlossaryUserFormulation(currentUserFormulation);
                dialogDeleteUser.close();
            }
        }

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
    }

    Dialog
    {
        id: dialogEditDiagnosis

        anchors.centerIn: parent

        font.pixelSize: 15
        title: "Редактирование записи"
        modal: true
        width: 500
        height: dialogBoxHeight

        Button
        {
            id: dialogEditDiagnosisRejectButton

            anchors
            {
                left:  parent.horizontalCenter
                right: parent.right
                top: dialogEditDiagnosisAcceptButton.top
                leftMargin: 5
            }

            contentItem: Text
            {
                font.pointSize: 12
                opacity: enabled ? 1.0 : 0.3
                color: dialogEditDiagnosisRejectButton.down ? buttonTextPressedColor : buttonTextDefaultColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: "Отмена"
            }

            background: Rectangle
            {
                anchors.fill: parent
                radius: 14
                color: dialogEditDiagnosisRejectButton.down ? buttonPressedColor : buttonDefaultColor
            }

            height: 40

            onClicked: function()
            {
                dialogEditDiagnosis.close();
            }
        }

        Button
        {
            id: dialogEditDiagnosisAcceptButton

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
                color: dialogEditDiagnosisAcceptButton.down ? buttonTextDefaultColor : buttonTextPressedColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: "Изменить"
            }

            background: Rectangle
            {
                anchors.fill: parent
                radius: 14
                color: dialogEditDiagnosisAcceptButton.down ? buttonDefaultColor : buttonPressedColor
            }

            height: 40

            onClicked: function()
            {
                backend.editGlossaryDiagnosis(currentDiagnosis.toString(), inputEditDiagnosis.text);
                currentDiagnosis = inputEditDiagnosis.text;
                inputEditDiagnosis.text = "";

                dialogEditDiagnosis.close();
            }
        }

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
    }

    Dialog
    {
        id: dialogEditTreatment

        anchors.centerIn: parent

        font.pixelSize: 15
        title: "Редактирование записи"
        modal: true
        width: 500
        height: dialogBoxHeight

        Button
        {
            id: dialogEditTreatmentRejectButton

            anchors
            {
                left:  parent.horizontalCenter
                right: parent.right
                top: dialogEditTreatmentAcceptButton.top
                leftMargin: 5
            }

            contentItem: Text
            {
                font.pointSize: 12
                opacity: enabled ? 1.0 : 0.3
                color: dialogEditTreatmentRejectButton.down ? buttonTextPressedColor : buttonTextDefaultColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: "Отмена"
            }

            background: Rectangle
            {
                anchors.fill: parent
                radius: 14
                color: dialogEditTreatmentRejectButton.down ? buttonPressedColor : buttonDefaultColor
            }

            height: 40

            onClicked: function()
            {
                dialogEditTreatment.close();
            }
        }

        Button
        {
            id: dialogEditTreatmentAcceptButton

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
                color: dialogEditTreatmentAcceptButton.down ? buttonTextDefaultColor : buttonTextPressedColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: "Изменить"
            }

            background: Rectangle
            {
                anchors.fill: parent
                radius: 14
                color: dialogEditTreatmentAcceptButton.down ? buttonDefaultColor : buttonPressedColor
            }

            height: 40

            onClicked: function()
            {
                backend.editGlossaryTreatment(currentTreatment.toString(), inputEditTreatment.text);
                currentTreatment = inputEditTreatment.text;
                inputEditTreatment.text = "";

                dialogEditTreatment.close();
            }
        }

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
    }

    Dialog
    {
        id: dialogEditSymptom

        anchors.centerIn: parent

        font.pixelSize: 15
        title: "Редактирование записи"
        modal: true
        width: 500
        height: dialogBoxHeight

        Button
        {
            id: dialogEditSymptomRejectButton

            anchors
            {
                left:  parent.horizontalCenter
                right: parent.right
                top: dialogEditSymptomAcceptButton.top
                leftMargin: 5
            }

            contentItem: Text
            {
                font.pointSize: 12
                opacity: enabled ? 1.0 : 0.3
                color: dialogEditSymptomRejectButton.down ? buttonTextPressedColor : buttonTextDefaultColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: "Отмена"
            }

            background: Rectangle
            {
                anchors.fill: parent
                radius: 14
                color: dialogEditSymptomRejectButton.down ? buttonPressedColor : buttonDefaultColor
            }

            height: 40

            onClicked: function()
            {
                dialogEditSymptom.close();
            }
        }

        Button
        {
            id: dialogEditSymptomAcceptButton

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
                color: dialogEditSymptomAcceptButton.down ? buttonTextDefaultColor : buttonTextPressedColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: "Изменить"
            }

            background: Rectangle
            {
                anchors.fill: parent
                radius: 14
                color: dialogEditSymptomAcceptButton.down ? buttonDefaultColor : buttonPressedColor
            }

            height: 40

            onClicked: function()
            {
                backend.editGlossarySymptom(currentSymptom.toString(), inputEditSymptom.text);
                currentSymptom = inputEditSymptom.text;
                inputEditSymptom.text = "";

                dialogEditSymptom.close();
            }
        }

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
    }

    Dialog
    {
        id: dialogEditUser

        anchors.centerIn: parent

        font.pixelSize: 15
        title: "Редактирование записи"
        modal: true
        width: 500
        height: dialogBoxHeight

        Button
        {
            id: dialogEditUserRejectButton

            anchors
            {
                left:  parent.horizontalCenter
                right: parent.right
                top: dialogEditUserAcceptButton.top
                leftMargin: 5
            }

            contentItem: Text
            {
                font.pointSize: 12
                opacity: enabled ? 1.0 : 0.3
                color: dialogEditUserRejectButton.down ? buttonTextPressedColor : buttonTextDefaultColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: "Отмена"
            }

            background: Rectangle
            {
                anchors.fill: parent
                radius: 14
                color: dialogEditUserRejectButton.down ? buttonPressedColor : buttonDefaultColor
            }

            height: 40

            onClicked: function()
            {
                dialogEditUser.close();
            }
        }

        Button
        {
            id: dialogEditUserAcceptButton

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
                color: dialogEditUserAcceptButton.down ? buttonTextDefaultColor : buttonTextPressedColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: "Изменить"
            }

            background: Rectangle
            {
                anchors.fill: parent
                radius: 14
                color: dialogEditSymptomAcceptButton.down ? buttonDefaultColor : buttonPressedColor
            }

            height: 40

            onClicked: function()
            {
                backend.editGlossaryUserFormulation(currentUserFormulation.toString(), inputEditUser.text);
                currentUserFormulation = inputEditUser.text;
                inputEditUser.text = "";

                dialogEditUser.close();
            }
        }

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
    }

    Dialog
    {
        id: dialogAddDiagnosis

        anchors.centerIn: parent

        font.pixelSize: 15
        title: "Новая запись"
        modal: true
        width: 500
        height: dialogBoxHeight

        Button
        {
            id: dialogAddDiagnosisRejectButton

            anchors
            {
                left:  parent.horizontalCenter
                right: parent.right
                top: dialogAddDiagnosisAcceptButton.top
                leftMargin: 5
            }

            contentItem: Text
            {
                font.pointSize: 12
                opacity: enabled ? 1.0 : 0.3
                color: dialogAddDiagnosisRejectButton.down ? buttonTextPressedColor : buttonTextDefaultColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: "Отмена"
            }

            background: Rectangle
            {
                anchors.fill: parent
                radius: 14
                color: dialogAddDiagnosisRejectButton.down ? buttonPressedColor : buttonDefaultColor
            }

            height: 40

            onClicked: function()
            {
                dialogAddDiagnosis.close();
            }
        }

        Button
        {
            id: dialogAddDiagnosisAcceptButton

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
                color: dialogAddDiagnosisAcceptButton.down ? buttonTextDefaultColor : buttonTextPressedColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: "Добавить"
            }

            background: Rectangle
            {
                anchors.fill: parent
                radius: 14
                color: dialogAddDiagnosisAcceptButton.down ? buttonDefaultColor : buttonPressedColor
            }

            height: 40

            onClicked: function()
            {
                backend.addGlossaryDiagnosis(inputDiagnosis.text);
                inputDiagnosis.text = "";

                dialogAddDiagnosis.close();
            }
        }

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
    }

    Dialog
    {
        id: dialogAddTreatment

        anchors.centerIn: parent

        font.pixelSize: 15
        title: "Новая запись"
        modal: true
        width: 500
        height: dialogBoxHeight

        Button
        {
            id: dialogAddTreatmentRejectButton

            anchors
            {
                left:  parent.horizontalCenter
                right: parent.right
                top: dialogAddTreatmentAcceptButton.top
                leftMargin: 5
            }

            contentItem: Text
            {
                font.pointSize: 12
                opacity: enabled ? 1.0 : 0.3
                color: dialogAddTreatmentRejectButton.down ? buttonTextPressedColor : buttonTextDefaultColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: "Отмена"
            }

            background: Rectangle
            {
                anchors.fill: parent
                radius: 14
                color: dialogAddTreatmentRejectButton.down ? buttonPressedColor : buttonDefaultColor
            }

            height: 40

            onClicked: function()
            {
                dialogAddTreatment.close();
            }
        }

        Button
        {
            id: dialogAddTreatmentAcceptButton

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
                color: dialogAddTreatmentAcceptButton.down ? buttonTextDefaultColor : buttonTextPressedColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: "Добавить"
            }

            background: Rectangle
            {
                anchors.fill: parent
                radius: 14
                color: dialogAddTreatmentAcceptButton.down ? buttonDefaultColor : buttonPressedColor
            }

            height: 40

            onClicked: function()
            {
                backend.addGlossaryTreatment(inputTreatment.text);
                inputTreatment.text = "";

                dialogAddTreatment.close();
            }
        }

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
    }

    Dialog
    {
        id: dialogAddSymptom

        anchors.centerIn: parent

        font.pixelSize: 15
        title: "Новая запись"
        modal: true
        width: 500
        height: dialogBoxHeight

        Button
        {
            id: dialogAddSymptomRejectButton

            anchors
            {
                left:  parent.horizontalCenter
                right: parent.right
                top: dialogAddSymptomAcceptButton.top
                leftMargin: 5
            }

            contentItem: Text
            {
                font.pointSize: 12
                opacity: enabled ? 1.0 : 0.3
                color: dialogAddSymptomRejectButton.down ? buttonTextPressedColor : buttonTextDefaultColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: "Отмена"
            }

            background: Rectangle
            {
                anchors.fill: parent
                radius: 14
                color: dialogAddSymptomRejectButton.down ? buttonPressedColor : buttonDefaultColor
            }

            height: 40

            onClicked: function()
            {
                dialogAddSymptom.close();
            }
        }

        Button
        {
            id: dialogAddSymptomAcceptButton

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
                color: dialogAddSymptomAcceptButton.down ? buttonTextDefaultColor : buttonTextPressedColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: "Добавить"
            }

            background: Rectangle
            {
                anchors.fill: parent
                radius: 14
                color: dialogAddSymptomAcceptButton.down ? buttonDefaultColor : buttonPressedColor
            }

            height: 40

            onClicked: function()
            {
                backend.addGlossarySymptom(inputSymptom.text);
                inputSymptom.text = "";

                dialogAddSymptom.close();
            }
        }

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
    }

    Dialog
    {
        id: dialogAddUser

        anchors.centerIn: parent

        font.pixelSize: 15
        title: "Новая запись"
        modal: true
        width: 500
        height: dialogBoxHeight

        Button
        {
            id: dialogAddUserRejectButton

            anchors
            {
                left:  parent.horizontalCenter
                right: parent.right
                top: dialogAddUserAcceptButton.top
                leftMargin: 5
            }

            contentItem: Text
            {
                font.pointSize: 12
                opacity: enabled ? 1.0 : 0.3
                color: dialogAddUserRejectButton.down ? buttonTextPressedColor : buttonTextDefaultColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: "Отмена"
            }

            background: Rectangle
            {
                anchors.fill: parent
                radius: 14
                color: dialogAddUserRejectButton.down ? buttonPressedColor : buttonDefaultColor
            }

            height: 40

            onClicked: function()
            {
                dialogAddUser.close();
            }
        }

        Button
        {
            id: dialogAddUserAcceptButton

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
                color: dialogAddUserAcceptButton.down ? buttonTextDefaultColor : buttonTextPressedColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: "Добавить"
            }

            background: Rectangle
            {
                anchors.fill: parent
                radius: 14
                color: dialogAddUserAcceptButton.down ? buttonDefaultColor : buttonPressedColor
            }

            height: 40

            onClicked: function()
            {
                backend.addGlossaryUserFormulation(inputUser.text);
                inputUser.text = "";

                dialogAddUser.close();
            }
        }

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
    }

    SplitView
    {
        id: splitView

        anchors
        {
            top: parent.top//labelTitle.bottom
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
                    color: "#000000"
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
                        color: listViewDelegateHighlightColor
                    }

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
                    color: listViewDelegateHighlightColor
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
                    color: "#000000"
                    text: display

                    Rectangle
                    {
                        id: separatorTreatments

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
                    color: listViewDelegateHighlightColor
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
                    color: "#000000"
                    text: display

                    Rectangle
                    {
                        id: separatorSymptoms

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
                    color: listViewDelegateHighlightColor
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
                    color: "#000000"
                    text: display

                    Rectangle
                    {
                        id: separatorUser

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
                    color: listViewDelegateHighlightColor
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
