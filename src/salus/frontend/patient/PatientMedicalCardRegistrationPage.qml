import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import salus 1.0

Page
{
    id: root

    property string patientFullName: ""
    property int patientAge: 0
    property bool patientSex
    property string patientBirthDate: ""
    property string patientAddress: ""
    property string patientPhoneNumber: ""
    property string patientOccupation: ""

    property int fontSize: 11    
    property int textFieldsWidth: 300
    property int textFieldBorderRadius: 10
    property int buttonStandartTextFontSize: 10
    property int standartTextSize: 14


    signal returnBack()
    signal patientRegistered(string fullname)

    function clearTextFields()
    {
        textEditFullName.clear();
        textEditAge.clear();
        textEditBirthDate.clear();
        textEditAddress.clear();
        textEditPhoneNumber.clear();
        textEditOccupation.clear();
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
        text: "Регистрация новой амбулаторной карты"
    }

    Column
    {
        id: registrationFields

        anchors
        {
            top: labelTitle.bottom
            bottom: parent.bottom
            left: parent.left
            right: parent.right
            topMargin: 30
        }
        spacing: 15

        Text
        {
            id: labelFullName

            anchors.horizontalCenter: parent.horizontalCenter

            text: "Введите ФИО"
            font.pointSize: fontSize
        }

       TextField {
           id: textEditFullName

           anchors.horizontalCenter: parent.horizontalCenter

           font.pointSize: fontSize
           width: textFieldsWidth
           height: 30
           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter

           placeholderText: "Введите ФИО"
           text: patientFullName

           Rectangle
           {
               anchors.fill: parent

               border.width: 1
               color: "#0000ffff"
           }
       }

       Text
       {
           id: labelAge

           anchors.horizontalCenter: parent.horizontalCenter

           font.pointSize: fontSize
           text: "Введите возраст"
       }

       TextField
       {
           id: textEditAge

           anchors.horizontalCenter: parent.horizontalCenter

           font.pointSize: fontSize
           width: textFieldsWidth
           height: 30
           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter

           validator: IntValidator
           {
               bottom: 0
               top: 255
           }

           Rectangle
           {
               anchors.fill: parent
               border.width: 1
               color: "#0000ffff"
           }
       }

       Text
       {
           id: labelSex

           anchors.horizontalCenter: parent.horizontalCenter

           font.pointSize: fontSize
           text: "Пол"
       }

       ComboBox
       {
           id: combobox_sex

           anchors.horizontalCenter: parent.horizontalCenter

           font.pointSize: fontSize

           model: ListModel
           {
               id: list_sex

               ListElement { text: "Мужской" }
               ListElement { text: "Женский" }
           }

           onActivated: function()
           {
               patientSex = index === 0 ? false : true;
           }
       }

       Text
       {
           id: labelBirthDate

           anchors.horizontalCenter: parent.horizontalCenter

           font.pointSize: fontSize
           text: "Введите дату рождения"
       }

       TextField
       {
           id: textEditBirthDate

           anchors.horizontalCenter: parent.horizontalCenter

           font.pointSize: fontSize
           width: textFieldsWidth
           height: 30
           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter

           placeholderText: "12.12.1985"

           Rectangle
           {
               anchors.fill: parent
               border.width: 1
               color: "#0000ffff"
           }
       }

       Text
       {
           id: labelAddress

           anchors.horizontalCenter: parent.horizontalCenter

           font.pointSize: fontSize
           text: "Введите адрес проживания"
       }

       TextField
       {
           id: textEditAddress

           anchors.horizontalCenter: parent.horizontalCenter

           font.pointSize: fontSize
           width: textFieldsWidth
           height: 30
           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter

           placeholderText: "г. Краснодар, ул. 40 лет Победы"

           Rectangle
           {
               anchors.fill: parent
               border.width: 1
               color: "#0000ffff"

           }
       }

       Text
       {
           id: labelPhoneNumber

           anchors.horizontalCenter: parent.horizontalCenter

           font.pointSize: fontSize
           text: "Введите номер телефона"

       }

       TextField
       {
           id: textEditPhoneNumber

           anchors.horizontalCenter: parent.horizontalCenter

           font.pointSize: fontSize
           width: textFieldsWidth
           height: 30
           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter

           Rectangle
           {
               anchors.fill: parent
               border.width: 1
               color: "#0000ffff"
           }
       }

       Text
       {
           id: labelOccupation

           anchors.horizontalCenter: parent.horizontalCenter

           font.pointSize: fontSize
           text: "Введите профессию"
       }

       TextField
       {
           id: textEditOccupation

           anchors.horizontalCenter: parent.horizontalCenter

           font.pointSize: 11
           width: textFieldsWidth
           height: 30
           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter

           placeholderText: "Аналитик"

           Rectangle
           {
               anchors.fill: parent
               border.width: 1
               color: "#0000ffff"
           }
       }

        Button
        {
            id: buttonRegisterPatient

            anchors.horizontalCenter: parent.horizontalCenter

            font.pointSize: 10
            width: 300
            height: 50

            text: "Зарегистрировать новую карту"

            onClicked: function()
            {
                backend.addNewPatient(textEditFullName.text.toString(), textEditAge.text, patientSex, textEditBirthDate.text,
                                      textEditAddress.text.toString(), textEditPhoneNumber.text, textEditOccupation.text.toString());
            }
        }
    }
}
