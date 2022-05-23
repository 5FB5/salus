import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import io.qt.salus 1.0

Page {
    id: root

    signal profileRegistered()

    property string registeredDoctorFullName
    property string registeredDoctorSpecialization
    property string registeredDoctorInstitutionName
    property string registeredDoctorInstitutionCode
    property string registeredDoctorInstitutionAddress
    property string registeredDoctorInn
    property string registeredDoctorLicenseInfo

//    Backend {
//        id: backend
//    }

    width: ScreenInfo.desktopAvailableWidth
    height: ScreenInfo.desktopAvailableHeight

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
           id: textEditInn
           placeholderText: ("Введите ИНН")
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
           id: textEditSpecialization
           placeholderText: ("Введите специализацию")
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
           id: textEditLicenseInfo
           placeholderText: ("Введите лицензию")
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
           id: textEditInstitutionName
           placeholderText: ("Введите название организации")
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
           id: textEditInstitutionAddress
           placeholderText: ("Введите адрес организации")
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
           id: textEditInstitutionCode
           placeholderText: ("Введите код организации")
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
                backend.addNewDoctorProfile(textEditFullName.text.toString(), textEditSpecialization.text.toString(),
                                            textEditInstitutionName.text.toString(), textEditInstitutionCode.text.toString(),
                                            textEditInstitutionAddress.text.toString(), textEditInn.text.toString(),
                                            textEditLicenseInfo.text.toString()
                                            )

                registeredDoctorFullName = textEditFullName.text.toString()
                registeredDoctorSpecialization = textEditSpecialization.text.toString()
                registeredDoctorInstitutionName = textEditInstitutionName.text.toString()
                registeredDoctorInstitutionCode = textEditInstitutionCode.text.toString()
                registeredDoctorInstitutionAddress = textEditInstitutionAddress.text.toString()
                registeredDoctorInn = textEditInn.text.toString()
                registeredDoctorLicenseInfo = textEditLicenseInfo.text.toString()

                profileRegistered()
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
