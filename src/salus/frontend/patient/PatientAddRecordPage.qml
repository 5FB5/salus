import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQml 2.12

import salus 1.0

Page {
    id: root

    property int fontSize: 11

    property int textFieldsWidth: 300
    property int textFieldBorderRadius: 10

    property int buttonStandartTextFontSize: 10
    property int standartTextSize: 14

    signal returnBack()

    function clearTextFields()
    {
        textEditAnamnesis.clear()
        textEditComplaints.clear()
        textEditDiagnosis.clear()
        textEditDiseases.clear()
        textEditTreatment.clear()
    }

    Dialog
    {
        id: dialogRecordExists

        width: parent.width / 4
        height: parent.height / 4

        anchors.centerIn: parent

        modal: true

        title: "Данная запись уже существует"
        standardButtons: Dialog.Ok

        Text {
            id: dialogboxText
            font.pointSize: 14

            anchors.fill: parent

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

    Label {
        id: labelTitle

        text: "Добавление новой записи"

        font.pointSize: 20
        font.bold: true

        anchors.top: parent.top
        anchors.topMargin: 50
        anchors.horizontalCenter: parent.horizontalCenter

    }

    Column {
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

        Text {
            id: labelRecordDate
            text: "Введите дату новой записи"
            font.pointSize: fontSize
            anchors.horizontalCenter: parent.horizontalCenter
        }

       TextField {
           id: textEditRecordDate

           anchors.horizontalCenter: parent.horizontalCenter

           placeholderText: "день.месяц.год"
           text: Qt.formatDateTime(new Date(), "dd.MM.yyyy")

           font.pointSize: fontSize

           width: textFieldsWidth
           height: 30

           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter

           Rectangle {
               anchors.fill: parent
               border.width: 1
               color: "#0000ffff"
           }
       }

       Text {
           id: labelAnamnesis
           text: "Введите анамнез"
           font.pointSize: fontSize
           anchors.horizontalCenter: parent.horizontalCenter
           anchors.bottomMargin: 5
       }

       Rectangle {
           id: anamnesisInput

           width: 500
           height: 80

           anchors.horizontalCenter: parent.horizontalCenter

           border.width: 1
           color: "#0000ffff"

           ScrollView {
               id: scrollViewAnamnesis

               anchors.fill: parent
               anchors.horizontalCenter: parent.horizontalCenter

               clip: true

               TextArea {
                   id: textEditAnamnesis

                   font.pointSize: fontSize

                   placeholderText: "По словам пациента , считает себя больным на протяжении 6 лет..."

                   focus: true
               }
           }
       }

       Text {
           id: labelComplaints
           text: "Введите жалобы"
           font.pointSize: fontSize
           anchors.horizontalCenter: parent.horizontalCenter
       }

       Rectangle {
           id: complaintsInput

           width: 500
           height: 80

           anchors.horizontalCenter: parent.horizontalCenter

           border.width: 1
           color: "#0000ffff"

           ScrollView {
               id: scrollViewComplaints

               anchors.fill: parent
               anchors.horizontalCenter: parent.horizontalCenter

               clip: true

               TextArea {
                   id: textEditComplaints

                   font.pointSize: fontSize

                   placeholderText: "Боль в нижней челюсти, кровоточивость десны, ..."

                   focus: true
               }
           }
       }

       Text {
           id: labelDiseases
           text: "Введите перенесённые заболевания"
           font.pointSize: fontSize
           anchors.horizontalCenter: parent.horizontalCenter
       }

       Rectangle {
           id: diseasesInput

           width: 500
           height: 80

           anchors.horizontalCenter: parent.horizontalCenter

           border.width: 1
           color: "#0000ffff"

           ScrollView {
               id: scrollViewDiseases

               anchors.fill: parent
               anchors.horizontalCenter: parent.horizontalCenter

               clip: true

               TextArea {
                   id: textEditDiseases

                   font.pointSize: fontSize

                   placeholderText: "Пульпит, Гингивит, ..."

                   focus: true
               }
           }
       }

       Text {
           id: labelDiagnosis
           text: "Введите текущий диагноз"
           font.pointSize: fontSize
           anchors.horizontalCenter: parent.horizontalCenter
       }

       Rectangle {
           id: diagnosisInput

           width: 500
           height: 80

           anchors.horizontalCenter: parent.horizontalCenter

           border.width: 1
           color: "#0000ffff"

           ScrollView {
               id: scrollViewDiagnosis

               anchors.fill: parent
               anchors.horizontalCenter: parent.horizontalCenter

               clip: true

               TextArea {
                   id: textEditDiagnosis

                   font.pointSize: fontSize

                   placeholderText: "Пародонтоз"

                   focus: true
               }
           }
       }

       Text {
           id: labelTreatment
           text: "Введите наименование лечения"
           font.pointSize: fontSize
           anchors.horizontalCenter: parent.horizontalCenter
       }

       Rectangle {
           id: treatmentInput

           width: 500
           height: 80

           anchors.horizontalCenter: parent.horizontalCenter

           border.width: 1
           color: "#0000ffff"

           ScrollView {
               id: scrollViewTreatment

               anchors.fill: parent
               anchors.horizontalCenter: parent.horizontalCenter

               clip: true

               TextArea {
                   id: textEditTreatment

                   font.pointSize: fontSize

                   placeholderText: "Реминерализирующая терапия, ..."

                   focus: true
               }
           }
       }

        Button {
            id: buttonAddRecord

            text: "Добавить запись"

            font.pointSize: 10

            anchors.horizontalCenter: parent.horizontalCenter

            width: 300
            height: 50

            onClicked: {
                if (backend.addNewRecord(textEditRecordDate.text.toString(), textEditAnamnesis.text.toString(), textEditComplaints.text.toString(), textEditDiseases.text.toString(),
                                     textEditDiagnosis.text.toString(), textEditTreatment.text.toString()) === false)
                {
                    dialogRecordExists.open();
                }
            }
        }
    }
}
