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

    property string diagnosesListColor: "#bbbbbb"
    property string treatmentsListColor: "#bbbbbb"
    property string symptomsListcolor: "#bbbbbb"

    signal returnBack()
    signal openContextMenu();

    function clearTextFields()
    {
        textEditAnamnesis.clear();
        textEditComplaints.clear();
        textEditDiagnosis.clear();
        textEditDiseases.clear();
        textEditTreatment.clear();
    }

    Component.onCompleted: function()
    {
        openContextMenu.connect(glossaryContextMenu.openMenu);
    }

    GlossaryPasteContextMenu
    {
        id: glossaryContextMenu
    }

    Dialog
    {
        id: dialogDiagnosesMenu

        anchors.centerIn: parent

        font.pixelSize: 15
        title: "Выбор записи"
        modal: true
        width: 500
        height: 400

        contentItem: Item
        {
            id: itemDiagnosesList

            anchors.fill: parent

            Rectangle
            {
                id: testBg

                anchors.fill: parent

                color: diagnosesListColor
            }
        }
    }

    Dialog
    {
        id: dialogRecordExists

        anchors.centerIn: parent

        width: parent.width / 4
        height: parent.height / 4
        modal: true
        standardButtons: Dialog.Ok
        title: "Данная запись уже существует"

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

                   focus: true
                   font.pointSize: fontSize
                   placeholderText: "По словам пациента , считает себя больным на протяжении 6 лет..."
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

                   font.pointSize: fontSize
                   focus: true
                   placeholderText: "Боль в нижней челюсти, кровоточивость десны, ..."

                   MouseArea
                   {
                       id: mouseAreaComplaints

                       anchors.fill: parent

                       acceptedButtons: Qt.RightButton
                       onClicked: function()
                       {
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

                   font.pointSize: fontSize
                   focus: true
                   placeholderText: "Пульпит, Гингивит, ..."
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

                   font.pointSize: fontSize
                   focus: true
                   placeholderText: "Пародонтоз"

                   MouseArea
                   {
                       id: mouseAreaDiagnosis

                       anchors.fill: parent

                       acceptedButtons: Qt.RightButton
                       onClicked: function()
                       {
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

                   font.pointSize: fontSize
                   focus: true
                   placeholderText: "Реминерализирующая терапия, ..."

                   MouseArea
                   {
                       id: mouseAreaTreatment

                       anchors.fill: parent

                       acceptedButtons: Qt.RightButton
                       onClicked: function()
                       {
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

            font.pointSize: 10
            width: 300
            height: 50
            text: "Добавить запись"

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
