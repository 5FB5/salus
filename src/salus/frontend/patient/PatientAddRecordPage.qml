import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQml 2.12
import salus 1.0

import "components"

Page
{
    id: root

    property int fontSize: 11

    property int textFieldsWidth: 300
    property int textFieldBorderRadius: 10

    property int buttonStandartTextFontSize: 10
    property int standartTextSize: 14

    property string buttonDefaultColor: "#E1E1E1"
    property string buttonPressedColor: "#BABABA"
    property string buttonTextColor: "#007AFF"
    property string buttonTextPressedColor: Qt.darker(buttonTextColor, 0.5)

    property string diagnosesListColor: "#bbbbbb"
    property string treatmentsListColor: "#bbbbbb"
    property string symptomsListcolor: "#bbbbbb"

    property Item currentTextEditItem
    property Item returnButtonAddress: buttonReturn

    property int currentGlossaryMode: 0
    property string currentGlossaryItem: ""
    property string currentSelectedText: ""

    signal openContextMenu();

    function clearTextFields()
    {
        textEditAnamnesis.clear();
        textEditComplaints.clear();
        textEditDiagnosis.clear();
        textEditDiseases.clear();
        textEditTreatment.clear();
    }

    function initGlossaryMenu(type)
    {
        currentGlossaryMode = type;

        switch (currentGlossaryMode)
        {
        case 0:
            listViewGlossary.model = glossaryDiagnosesListModel;
            break;
        case 1:
            listViewGlossary.model = glossaryTreatmentsListModel;
            break;
        case 2:
            listViewGlossary.model = glossarySymptomsListModel;
            break;
        case 3:
            listViewGlossary.model = glossaryUserListModel;
            break;
        }

        listViewGlossary.currentIndex = 0;
        currentGlossaryItem = listViewGlossary.currentItem.text;

        dialogGlossaryMenu.open();
    }

    function openAddTextToGlossaryMenu()
    {
        if (currentSelectedText === "")
            return;

        dialogAddTextToGlossary.open();
    }

    Component.onCompleted: function()
    {
        openContextMenu.connect(glossaryContextMenu.openMenu);

        glossaryContextMenu.openGlossaryMenu.connect(initGlossaryMenu);
        glossaryContextMenu.openAddTextToGlossaryMenu.connect(openAddTextToGlossaryMenu);
    }

    GlossaryPasteContextMenu
    {
        id: glossaryContextMenu
    }

    Dialog
    {
        id: dialogAddTextToGlossary

        Component.onCompleted: function()
        {
            standardButton(Dialog.Ok).text = "Добавить";
            standardButton(Dialog.Cancel).text = "Отмена";
        }

        anchors.centerIn: parent

        font.pixelSize: 15
        title: "Выберите словарь"
        standardButtons: Dialog.Ok | Dialog.Cancel
        modal: true
        width: 500
        height: 400

        onAccepted: function()
        {
            var comboboxText = comboBoxChooseGlossary.currentText;

            switch (comboboxText)
            {
            case "Диагноз":
                backend.addGlossaryDiagnosis(currentSelectedText);
                break;

            case "Терапия":
                backend.addGlossaryTreatment(currentSelectedText);
                break;

            case "Симптомы":
                backend.addGlossarySymptom(currentSelectedText);
                break;

            case "Пользоват. формулировки":
                backend.addGlossaryUserFormulation(currentSelectedText);
                break;
            }
        }

        contentItem: Item
        {
            Text
            {
                id: labelChooseGlossary

                anchors
                {
                    left: parent.left
                    right: parent.right
                    top: parent.top
                    topMargin: 5
                }
                font.pixelSize: 17
                wrapMode: Text.WordWrap
                text: "В какой словарь добавить текст?"
            }

            Text
            {
                id: labelChooseGlossaryText

                anchors
                {
                    top: labelChooseGlossary.bottom
                    topMargin: 5
                }
                width: parent.width
                height: 50
                font.pixelSize: 17
                wrapMode: Text.WordWrap
                elide: Text.ElideRight
                text: currentSelectedText
            }

            ComboBox
            {
                id: comboBoxChooseGlossary

                anchors
                {
                    left: parent.left
                    right: parent.right
                    top: labelChooseGlossaryText.bottom
                    topMargin: 15
                    leftMargin: 5
                    rightMargin: 5
                }
                model: ["Диагноз", "Терапия", "Симптомы", "Пользоват. формулировки"]
            }
        }
    }

    Dialog
    {
        id: dialogGlossaryMenu

        Component.onCompleted: function()
        {
            standardButton(Dialog.Ok).text = "Вставить";
            standardButton(Dialog.Cancel).text = "Отмена";
        }

        anchors.centerIn: parent

        font.pixelSize: 15
        title: "Выбор записи"
        standardButtons: Dialog.Ok | Dialog.Cancel
        modal: true
        width: 500
        height: 400

        contentItem: Item
        {
            id: itemGlossaryList

            anchors.fill: parent

            ListView
            {
                id: listViewGlossary

                Component.onCompleted:
                {
                    highlightMoveDuration = 0;
                }

                anchors
                {
                    fill: parent
                    topMargin: 50
                    bottomMargin: 80
                }
                clip: true
                spacing: 15

                delegate: Text
                {
                    id: delegateListView

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
                    color: listViewGlossary.currentIndex === index ? "#ffffff" : "#000000"
                    text: display

                    MouseArea
                    {
                        anchors.fill: parent

                        onClicked: function()
                        {
                            listViewGlossary.currentIndex = index;
                            currentGlossaryItem = display.toString();
                        }
                    }
                }

                highlight: Rectangle
                {
                    anchors
                    {
                        left: parent.left
                        right: parent.right
                        margins: 5
                    }
                    color: "lightsteelblue"
                }
            }
        }

        onAccepted: function()
        {
            if (!currentTextEditItem)
                return;

            currentTextEditItem.text += " " + currentGlossaryItem;
        }
    }

    Dialog
    {
        id: dialogRecordExists

        anchors.centerIn: parent

        width: parent.width / 4
        height: parent.height / 4
        modal: true
        title: "Данная запись уже существует"

        Button
        {
            id: dialogConfirmAcceptButton

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
                color: dialogConfirmAcceptButton.down ? buttonTextDefaultColor : "#FFFFFF"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: "Закрыть"
            }

            background: Rectangle
            {
                anchors.fill: parent
                radius: 14
                color: dialogConfirmAcceptButton.down ? "#EBEBEB" : "#007AFF"
            }

            height: 40

            onClicked: function()
            {
                dialogRecordExists.close();
            }
        }

        Text
        {
            id: dialogboxText

            anchors.fill: parent

            font.pointSize: 14
            wrapMode: Text.WordWrap
            text: qsTr("Измените существующую запись, либо укажите иную дату.")
        }
    }

    Rectangle
    {
        id: background

        anchors.fill: parent
        color: "#ffffff"
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
        text: "Добавление новой записи"
    }

    Column
    {
        id: recordsDataFields

        anchors
        {
            top: labelTitle.bottom
            topMargin: 30
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }
        spacing: 10

        Text
        {
            id: labelRecordDate

            anchors.horizontalCenter: parent.horizontalCenter

            font.pointSize: fontSize
            text: "Введите дату новой записи"
        }

       TextField
       {
           id: textEditRecordDate

           anchors.horizontalCenter: parent.horizontalCenter

           font.pointSize: fontSize
           width: textFieldsWidth
           height: 30
           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter

           placeholderText: "день.месяц.год"
           text: Qt.formatDateTime(new Date(), "dd.MM.yyyy")

           Rectangle
           {
               anchors.fill: parent

               border.width: 1
               color: "#0000ffff"
           }
       }

       Text
       {
           id: labelAnamnesis

           anchors
           {
               horizontalCenter: parent.horizontalCenter
               bottomMargin: 5
           }
           font.pointSize: fontSize
           text: "Введите анамнез"
       }

       Rectangle
       {
           id: anamnesisInput

           anchors.horizontalCenter: parent.horizontalCenter

           width: 500
           height: 80
           border.width: 1
           color: "#0000ffff"

           ScrollView
           {
               id: scrollViewAnamnesis

               anchors
               {
                   fill: parent
                   horizontalCenter: parent.horizontalCenter
               }
               clip: true

               TextArea
               {
                   id: textEditAnamnesis

                   selectByMouse: true
                   font.pointSize: fontSize
                   placeholderText: "По словам пациента , считает себя больным на протяжении 6 лет..."

                   MouseArea
                   {
                       id: mouseAreaAnamnesis

                       anchors.fill: parent

                       acceptedButtons: Qt.RightButton
                       onClicked: function()
                       {
                           currentSelectedText = textEditAnamnesis.selectedText;
                           currentTextEditItem = textEditAnamnesis;
                           openContextMenu();
                       }
                   }
               }
           }
       }

       Text
       {
           id: labelComplaints

           anchors.horizontalCenter: parent.horizontalCenter

           font.pointSize: fontSize
           text: "Введите жалобы"
       }

       Rectangle
       {
           id: complaintsInput

           anchors.horizontalCenter: parent.horizontalCenter

           width: 500
           height: 80
           border.width: 1
           color: "#0000ffff"

           ScrollView
           {
               id: scrollViewComplaints

               anchors
               {
                   fill: parent
                   horizontalCenter: parent.horizontalCenter
               }
               clip: true

               TextArea
               {
                   id: textEditComplaints

                   selectByMouse: true
                   font.pointSize: fontSize
                   placeholderText: "Боль в нижней челюсти, кровоточивость десны, ..."

                   MouseArea
                   {
                       id: mouseAreaComplaints

                       anchors.fill: parent

                       acceptedButtons: Qt.RightButton
                       onClicked: function()
                       {
                           currentSelectedText = textEditComplaints.selectedText;
                           currentTextEditItem = textEditComplaints;
                           openContextMenu();
                       }
                   }
               }
           }
       }

       Text
       {
           id: labelDiseases

           anchors.horizontalCenter: parent.horizontalCenter

           font.pointSize: fontSize
           text: "Введите перенесённые заболевания"
       }

       Rectangle
       {
           id: diseasesInput

           anchors.horizontalCenter: parent.horizontalCenter

           width: 500
           height: 80
           border.width: 1
           color: "#0000ffff"

           ScrollView
           {
               id: scrollViewDiseases

               anchors
               {
                   fill: parent
                   horizontalCenter: parent.horizontalCenter
               }
               clip: true

               TextArea
               {
                   id: textEditDiseases

                   selectByMouse: true
                   font.pointSize: fontSize
                   placeholderText: "Пульпит, Гингивит, ..."

                   MouseArea
                   {
                       id: mouseAreaDiseases

                       anchors.fill: parent

                       acceptedButtons: Qt.RightButton
                       onClicked: function()
                       {
                           currentSelectedText = textEditDiseases.selectedText;
                           currentTextEditItem = textEditDiseases;
                           openContextMenu();
                       }
                   }
               }
           }
       }

       Text
       {
           id: labelDiagnosis

           anchors.horizontalCenter: parent.horizontalCenter

           font.pointSize: fontSize
           text: "Введите текущий диагноз"
       }

       Rectangle
       {
           id: diagnosisInput

           anchors.horizontalCenter: parent.horizontalCenter

           width: 500
           height: 80
           border.width: 1
           color: "#0000ffff"

           ScrollView
           {
               id: scrollViewDiagnosis

               anchors
               {
                   fill: parent
                   horizontalCenter: parent.horizontalCenter
               }
               clip: true

               TextArea
               {
                   id: textEditDiagnosis

                   selectByMouse: true
                   font.pointSize: fontSize
                   placeholderText: "Пародонтоз"

                   MouseArea
                   {
                       id: mouseAreaDiagnosis

                       anchors.fill: parent

                       acceptedButtons: Qt.RightButton
                       onClicked: function()
                       {
                           currentSelectedText = textEditDiagnosis.selectedText;
                           currentTextEditItem = textEditDiagnosis;
                           openContextMenu();
                       }
                   }
               }
           }
       }

       Text
       {
           id: labelTreatment

           anchors.horizontalCenter: parent.horizontalCenter

           font.pointSize: fontSize
           text: "Введите наименование лечения"
       }

       Rectangle
       {
           id: treatmentInput

           anchors.horizontalCenter: parent.horizontalCenter

           width: 500
           height: 80
           border.width: 1
           color: "#0000ffff"

           ScrollView
           {
               id: scrollViewTreatment

               anchors
               {
                   fill: parent
                   horizontalCenter: parent.horizontalCenter
               }
               clip: true

               TextArea
               {
                   id: textEditTreatment

                   selectByMouse: true
                   font.pointSize: fontSize
                   placeholderText: "Реминерализирующая терапия, ..."

                   MouseArea
                   {
                       id: mouseAreaTreatment

                       anchors.fill: parent

                       acceptedButtons: Qt.RightButton
                       onClicked: function()
                       {
                           currentSelectedText = textEditTreatment.selectedText;
                           currentTextEditItem = textEditTreatment;
                           openContextMenu();
                       }
                   }
               }
           }
       }

        Button
        {
            id: buttonAddRecord

            anchors.horizontalCenter: parent.horizontalCenter

            contentItem: Text
            {
                font.pointSize: 12
                opacity: enabled ? 1.0 : 0.3
                color: buttonAddRecord.down ? "#FFFFFF" : buttonTextDefaultColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: "Добавить запись"
            }

            background: Rectangle
            {
                anchors.fill: parent
                radius: 10
                color: buttonAddRecord.down ? "#007AFF": "#EBEBEB"
            }

            width: 300
            height: 50

            onClicked: function()
            {
                if (backend.addNewRecord(textEditRecordDate.text.toString(), textEditAnamnesis.text.toString(), textEditComplaints.text.toString(), textEditDiseases.text.toString(),
                                     textEditDiagnosis.text.toString(), textEditTreatment.text.toString()) === false)
                {
                    dialogRecordExists.open();
                }
            }
        }
    }
}
