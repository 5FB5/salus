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

    signal returnBack()
    signal recordUpdated()

    function updateRecordData()
    {
        if (recordDate === "")
            return;

        recordAnamnesis = backend.getRecordAnamnesis(recordDate);
        recordComplaints = backend.getRecordComplaints(recordDate);
        recordDiagnosis = backend.getRecordDiagnosis(recordDate);
        recordDiseases = backend.getRecordDiseases(recordDate);
        recordTreatment = backend.getRecordTreatment(recordDate);

        console.log(recordAnamnesis, recordComplaints, recordDiagnosis, recordDiseases, recordTreatment);
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

    Dialog
    {
        id: dialogConfirm

        anchors.centerIn: parent

        width: parent.width / 4
        height: parent.height / 4
        modal: true
        standardButtons: Dialog.Yes | Dialog.No
        title: "Подтвердите действие"

        Text
        {
            id: dialogboxText

            anchors.fill: parent

            font.pointSize: 14
            wrapMode: Text.WordWrap
            text: qsTr("Сохранить изменения?")
        }

        onAccepted: function()
        {
            backend.updateRecord(recordDate, textEditAnamnesis.text.toString(), textEditComplaints.text.toString(),
                                 textEditDiseases.text.toString(), textEditDiagnosis.text.toString(), textEditTreatment.text.toString());
            recordUpdated();
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
        text: "Редактирование записи"
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
            text: "Дата записи"
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
           text: recordDate//Qt.formatDateTime(new Date(), "dd.MM.yyyy")

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

                   font.pointSize: fontSize
                   focus: true
                   placeholderText: "По словам пациента , считает себя больным на протяжении 6 лет..."
                   text: recordAnamnesis

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
                   text: recordComplaints
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
                   text: recordDiseases
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
                   text: recordDiagnosis
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
                   text: recordTreatment

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
            text: "Сохранить запись"

            onClicked: function()
            {
                dialogConfirm.open();
            }
        }
    }
}
