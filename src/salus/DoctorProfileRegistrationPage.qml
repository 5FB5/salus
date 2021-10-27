import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import io.qt.salus 1.0

Page {
    id: root

    Doctor {
        id: doctor
    }

    width: Screen.width
    height: Screen.height

    property int textFieldsWidth: 300
    property int textFieldBorderRadius: 10

    background: Rectangle {
        id: backgroundRect
        color: "white"
    }

    Label {
        text: "Регистрация нового профиля"
        anchors.top: registrationFields.top
        anchors.topMargin: -112
        anchors.horizontalCenter: parent.horizontalCenter
        font.pointSize: 20
    }

    Column {
        id: registrationFields
        transformOrigin: Item.Center
        anchors.centerIn: parent
        spacing: 15

       TextField {
           id: textEditFullName

           placeholderText: "Введите ФИО"
           font.pointSize: 11

           width: textFieldsWidth
           height: 30

           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter

           background: {
               color: "transparent"
           }

           Rectangle {
               anchors.fill: parent
               border.width: 1
               radius: textFieldBorderRadius
               color: "transparent"

           }
       }

       TextField {
           id: textEditInn
           placeholderText: ("Введите ИНН")
           font.pointSize: 11

           width: textFieldsWidth
           height: 30

           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter

           background: {
               color: "transparent"
           }

           Rectangle {
               anchors.fill: parent
               border.width: 1
               radius: textFieldBorderRadius
               color: "transparent"

           }
       }

       TextField {
           id: textEditSpecialization
           placeholderText: ("Введите специализацию")
           font.pointSize: 11

           width: textFieldsWidth
           height: 30

           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter

           background: {
               color: "transparent"
           }

           Rectangle {
               anchors.fill: parent
               border.width: 1
               radius: textFieldBorderRadius
               color: "transparent"

           }
       }

       TextField {
           id: textEditLicense
           placeholderText: ("Введите лицензию")
           font.pointSize: 11

           width: textFieldsWidth
           height: 30

           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter

           background: {
               color: "transparent"
           }

           Rectangle {
               anchors.fill: parent
               border.width: 1
               radius: textFieldBorderRadius
               color: "transparent"

           }
       }

       TextField {
           id: textEditInstitutionName
           placeholderText: ("Введите название организации")
           font.pointSize: 11

           width: textFieldsWidth
           height: 30

           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter

           background: {
               color: "transparent"
           }

           Rectangle {
               anchors.fill: parent
               border.width: 1
               radius: textFieldBorderRadius
               color: "transparent"

           }
       }

       TextField {
           id: textEditInstitutionAddress
           placeholderText: ("Введите адрес организации")
           font.pointSize: 11

           width: textFieldsWidth
           height: 30

           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter

           background: {
               color: "transparent"
           }

           Rectangle {
               anchors.fill: parent
               border.width: 1
               radius: textFieldBorderRadius
               color: "transparent"

           }
       }

       TextField {
           id: textEditInstitutionCode
           placeholderText: ("Введите код организации")
           font.pointSize: 11

           width: textFieldsWidth
           height: 30

           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter

           background: {
               color: "transparent"
           }

           Rectangle {
               anchors.fill: parent
               border.width: 1
               radius: textFieldBorderRadius
               color: "transparent"

           }
       }

        Button {
            id: buttonRegisterProfile

            text: "Зарегистрироваться"

            font.pointSize: 10

            anchors.left: parent.left
            anchors.right: parent.right

            anchors.leftMargin: 30
            anchors.rightMargin: 30

            width: 200
            height: 50

            onClicked: {
                doctor.createNewProfile(
                            textEditFullName.text.toString(), textEditSpecialization.text.toString(),
                            textEditInstitutionName.text.toString(), textEditInstitutionCode.text.toString(),
                            textEditInstitutionAddress.text.toString(), textEditInn.text.toString(),
                            textEditInn.text.toString()
                            )
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}D{i:18}
}
##^##*/
