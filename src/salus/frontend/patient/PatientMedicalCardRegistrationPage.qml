import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import io.qt.salus 1.0

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

    width: ScreenInfo.desktopAvailableWidth
    height: ScreenInfo.desktopAvailableHeight

    property int textFieldsWidth: 300
    property int textFieldBorderRadius: 10

    property int buttonStandartTextFontSize: 10
    property int standartTextSize: 14


    background: Rectangle {
        id: backgroundRect

        color: "#FFFFFFFF"
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

        transformOrigin: Item.Center

        anchors.centerIn: parent

        spacing: 30

       TextField {
           id: textEditFullName

           placeholderText: "Введите ФИО"
           text: patientFullName

           font.pointSize: 11

           width: textFieldsWidth
           height: 30

           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter

           background: {
               color: "#0000ffff"
           }

           Rectangle {
               anchors.fill: parent
               border.width: 1
               radius: textFieldBorderRadius
               color: "#0000ffff"

           }
       }

       TextField {
           id: textEditAge

           placeholderText: ("Введите возраст")
           font.pointSize: 11

           width: textFieldsWidth
           height: 30

           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter

           validator: IntValidator {
               bottom: 0
               top: 255
           }

           background: {
               color: "#0000ffff"
           }

           Rectangle {
               anchors.fill: parent
               border.width: 1
               radius: textFieldBorderRadius
               color: "#0000ffff"

           }
       }

       Label {
           id: label_sex

           text: "Пол: "

           font.pointSize: standartTextSize

           ComboBox {
               id: combobox_sex

               font.pointSize: 11

               anchors.top: parent.top
               anchors.bottom: parent.bottom
               anchors.left: parent.right
               anchors.leftMargin: 40

               model: ListModel {
                   id: list_sex

                   ListElement { text: "Мужской" }
                   ListElement { text: "Женский" }
               }

               onActivated: {
                   patientSex = index === 0 ? false : true
               }
           }
       }

       TextField {
           id: textEditBirthDate
           placeholderText: ("Введите дату рождения")
           font.pointSize: 11

           width: textFieldsWidth
           height: 30

           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter

           background: {
               color: "#0000ffff"
           }

           Rectangle {
               anchors.fill: parent
               border.width: 1
               radius: textFieldBorderRadius
               color: "#0000ffff"

           }
       }

       TextField {
           id: textEditAddress
           placeholderText: ("Введите адрес проживания")
           font.pointSize: 11

           width: textFieldsWidth
           height: 30

           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter

           background: {
               color: "#0000ffff"
           }

           Rectangle {
               anchors.fill: parent
               border.width: 1
               radius: textFieldBorderRadius
               color: "#0000ffff"

           }
       }

       TextField {
           id: textEditPhoneNumber
           placeholderText: ("Введите номер телефона")
           font.pointSize: 11

           width: textFieldsWidth
           height: 30

           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter

           background: {
               color: "#0000ffff"
           }

           Rectangle {
               anchors.fill: parent
               border.width: 1
               radius: textFieldBorderRadius
               color: "#0000ffff"

           }
       }

       TextField {
           id: textEditOccupation
           placeholderText: ("Введите профессию")
           font.pointSize: 11

           width: textFieldsWidth
           height: 30

           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter

           background: {
               color: "#0000ffff"
           }

           Rectangle {
               anchors.fill: parent
               border.width: 1
               radius: textFieldBorderRadius
               color: "#0000ffff"

           }
       }

        Button {
            id: buttonRegisterPatient

            text: "Зарегистрировать новую карту"

            font.pointSize: 10

            anchors.left: parent.left
            anchors.right: parent.right

            anchors.leftMargin: 30
            anchors.rightMargin: 30

            width: 200
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
