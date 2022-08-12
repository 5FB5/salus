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

    property string recordDate: ""
    property string recordComplaints: ""
    property string recordAnamnesis: ""
    property string recordDiagnosis: ""
    property string recordDiseases: ""
    property string recordTreatment: ""

    function updateRecordData()
    {
        if (recordDate !== "")
        {
            recordAnamnesis = backend.getRecordAnamnesis(recordDate);
            recordComplaints = backend.getRecordComplaints(recordDate);
            recordDiagnosis = backend.getRecordDiagnosis(recordDate);
            recordDiseases = backend.getRecordDiseases(recordDate);
            recordTreatment = backend.getRecordTreatment(recordDate);

            console.log(recordAnamnesis, recordComplaints, recordDiagnosis, recordDiseases, recordTreatment);
        }
    }

    Rectangle
    {
        id: background

        anchors.fill: parent

        color: "#ffffff"
    }

    Label {
        id: labelTitle

        text: "Редактирование записи"

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
            text: "Дата записи"
            font.pointSize: fontSize
            anchors.horizontalCenter: parent.horizontalCenter
        }

       TextField {
           id: textEditRecordDate

           anchors.horizontalCenter: parent.horizontalCenter

           placeholderText: "день.месяц.год"
           text: recordDate//Qt.formatDateTime(new Date(), "dd.MM.yyyy")

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
                   text: recordAnamnesis

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
                   text: recordComplaints

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
                   text: recordDiseases

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
                   text: recordDiagnosis

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
                   text: recordTreatment

                   focus: true
               }
           }
       }

        Button {
            id: buttonAddRecord

            text: "Сохранить запись"

            font.pointSize: 10

            anchors.horizontalCenter: parent.horizontalCenter

            width: 300
            height: 50

            onClicked: {
//                backend.updateRecord(recordDate, textEditRecordDate.text.toString(), textEditAnamnesis.text.toString(), textEditComplaints.text.toString(),
//                                     textEditDiseases.text.toString(), textEditDiagnosis.text.toString(), textEditTreatment.text.toString())
            }
        }
    }
}
