import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import salus 1.0

Page {
    id: root

    // Поля для базовой регистрации
    property string patientFullName: ""
    property int patientAge: 0
    property bool patientSex
    property string patientBirthDate: ""
    property string patientAddress: ""
    property string patientPhoneNumber: ""
    property string patientOccupation: ""

    property int fontSize: 11

    signal patientRegistered(string fullname)

    function clearTextFields() {
        if (textEditFullName.text !== "" || textEditAge.text !== "" || textEditBirthDate.text !== "" || textEditAddress ||
                textEditPhoneNumber.text !== "" || textEditOccupation.text !== "")
        {
            textEditFullName.text = ""
            textEditAge.text = ""
            textEditBirthDate.text = ""
            textEditAddress.text = ""
            textEditPhoneNumber.text = ""
            textEditOccupation.text = ""
        }
    }

//    width: ScreenInfo.desktopAvailableWidth
//    height: ScreenInfo.desktopAvailableHeight

    property int textFieldsWidth: 300
    property int textFieldBorderRadius: 10

    property int buttonStandartTextFontSize: 10
    property int standartTextSize: 14

    Rectangle
    {
        id: background

        anchors.fill: parent

        color: "#ffffff"
    }

    Label {
        id: labelTitle

        text: "Регистрация новой амбулаторной карты"

        font.pointSize: 20
        font.bold: true

        anchors.top: parent.top
        anchors.topMargin: 50
        anchors.horizontalCenter: parent.horizontalCenter

    }

    Column {
        id: registrationFields

        anchors
        {
            top: labelTitle.bottom
            topMargin: 30
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }

        spacing: 15

        Text {
            id: labelFullName
            text: "Введите ФИО"
            font.pointSize: fontSize
            anchors.horizontalCenter: parent.horizontalCenter
        }

       TextField {
           id: textEditFullName

           anchors.horizontalCenter: parent.horizontalCenter

           placeholderText: "Введите ФИО"
           text: patientFullName

           font.pointSize: fontSize

           width: textFieldsWidth
           height: 30

           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter

           Rectangle {
               anchors.fill: parent
               border.width: 1
//               radius: textFieldBorderRadius
               color: "#0000ffff"

           }
       }

       Text {
           id: labelAge
           text: "Введите возраст"
           font.pointSize: fontSize
           anchors.horizontalCenter: parent.horizontalCenter
       }

       TextField {
           id: textEditAge

           anchors.horizontalCenter: parent.horizontalCenter

           font.pointSize: fontSize

           width: textFieldsWidth
           height: 30

           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter

           validator: IntValidator {
               bottom: 0
               top: 255
           }

           Rectangle {
               anchors.fill: parent
               border.width: 1
//               radius: textFieldBorderRadius
               color: "#0000ffff"

           }
       }

       Text {
           id: labelSex
           text: "Пол"
           font.pointSize: fontSize
           anchors.horizontalCenter: parent.horizontalCenter
       }

       ComboBox {
           id: combobox_sex

           font.pointSize: fontSize

           anchors.horizontalCenter: parent.horizontalCenter

           model: ListModel {
               id: list_sex

               ListElement { text: "Мужской" }
               ListElement { text: "Женский" }
           }

           onActivated: {
               patientSex = index === 0 ? false : true
           }
       }

       Text {
           id: labelBirthDate
           text: "Введите дату рождения"
           font.pointSize: fontSize
           anchors.horizontalCenter: parent.horizontalCenter
       }

       TextField {
           id: textEditBirthDate

           anchors.horizontalCenter: parent.horizontalCenter

           placeholderText: "12.12.1985"

           font.pointSize: fontSize

           width: textFieldsWidth
           height: 30

           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter

           Rectangle {
               anchors.fill: parent
               border.width: 1
//               radius: textFieldBorderRadius
               color: "#0000ffff"

           }
       }

       Text {
           id: labelAddress
           text: "Введите адрес проживания"
           font.pointSize: fontSize
           anchors.horizontalCenter: parent.horizontalCenter
       }

       TextField {
           id: textEditAddress

           anchors.horizontalCenter: parent.horizontalCenter

           placeholderText: "г. Краснодар, ул. 40 лет Победы"

           font.pointSize: fontSize

           width: textFieldsWidth
           height: 30

           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter

           Rectangle {
               anchors.fill: parent
               border.width: 1
//               radius: textFieldBorderRadius
               color: "#0000ffff"

           }
       }

       Text {
           id: labelPhoneNumber
           text: "Введите номер телефона"
           font.pointSize: fontSize
           anchors.horizontalCenter: parent.horizontalCenter
       }

       TextField {
           id: textEditPhoneNumber

           anchors.horizontalCenter: parent.horizontalCenter

           font.pointSize: fontSize

           width: textFieldsWidth
           height: 30

           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter

           Rectangle {
               anchors.fill: parent
               border.width: 1
//               radius: textFieldBorderRadius
               color: "#0000ffff"

           }
       }

       Text {
           id: labelOccupation
           text: "Введите профессию"
           font.pointSize: fontSize
           anchors.horizontalCenter: parent.horizontalCenter
       }

       TextField {
           id: textEditOccupation

           anchors.horizontalCenter: parent.horizontalCenter

           placeholderText: "Аналитик"
           font.pointSize: 11

           width: textFieldsWidth
           height: 30

           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter

           Rectangle {
               anchors.fill: parent
               border.width: 1
//               radius: textFieldBorderRadius
               color: "#0000ffff"

           }
       }

        Button {
            id: buttonRegisterPatient

            text: "Зарегистрировать новую карту"

            font.pointSize: 10

            anchors.horizontalCenter: parent.horizontalCenter

//            anchors.left: parent.left
//            anchors.right: parent.right

//            anchors.leftMargin: 30
//            anchors.rightMargin: 30

            width: 300
            height: 50

            onClicked: {
                backend.addNewPatient(textEditFullName.text.toString(), textEditAge.text, patientSex, textEditBirthDate.text,
                                      textEditAddress.text.toString(), textEditPhoneNumber.text, textEditOccupation.text.toString())

                patientFullName = textEditFullName.text.toString()
                patientAge = textEditAge.text
                patientBirthDate = textEditBirthDate.text
                patientPhoneNumber = textEditPhoneNumber.text
                patientOccupation = textEditOccupation.text.toString()

                patientRegistered(textEditFullName.text.toString())

            }
        }
    }
}
