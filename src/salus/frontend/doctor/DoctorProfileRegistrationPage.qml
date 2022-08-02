import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import salus 1.0

Page {
    id: root

    //signal profileRegistered()

//    property string registeredDoctorFullName
//    property string registeredDoctorSpecialization
//    property string registeredDoctorInstitutionName
//    property string registeredDoctorInstitutionCode
//    property string registeredDoctorInstitutionAddress
//    property string registeredDoctorInn
//    property string registeredDoctorLicenseInfo

    property int fontSize: 11

    property int textFieldsWidth: 300
    property int textFieldBorderRadius: 10

    Rectangle {
        id: backgroundRect
        anchors.fill: parent
        color: "#ffffff"
    }

    Text {
        text: "Регистрация нового профиля"
        anchors.top: parent.top
        anchors.topMargin: 15
        anchors.horizontalCenter: parent.horizontalCenter
        font.pointSize: 20
    }

    Column {
        id: registrationFields
        transformOrigin: Item.Center
        anchors.centerIn: parent
        spacing: 15

       Text {
           id: labelFullName
           text: "Введите ФИО"
           font.pointSize: fontSize
           anchors.horizontalCenter: parent.horizontalCenter
       }

       TextField {
           id: textEditFullName

           placeholderText: "Иванов Иван Иванович"
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
           id: labelInn
           text: "Введите ИНН"
           font.pointSize: fontSize
           anchors.horizontalCenter: parent.horizontalCenter
       }

       TextField {
           id: textEditInn

           placeholderText: "797057359509"
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
           id: labelSpecialization
           text: "Введите специализацию"
           font.pointSize: fontSize
           anchors.horizontalCenter: parent.horizontalCenter
       }

       TextField {
           id: textEditSpecialization

           placeholderText: "Врач-стоматолог"
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
           id: labelLicense
           text: "Введите лицензию"
           font.pointSize: fontSize
           anchors.horizontalCenter: parent.horizontalCenter
       }

       TextField {
           id: textEditLicenseInfo

           placeholderText: "1423645678"
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
           id: labelOrganization
           text: "Введите название организации"
           font.pointSize: fontSize
           anchors.horizontalCenter: parent.horizontalCenter
       }

       TextField {
           id: textEditInstitutionName

           placeholderText: "ИП Иванов И.И."
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
           id: labelOrganizationAddress
           text: "Введите адрес организации"
           font.pointSize: fontSize
           anchors.horizontalCenter: parent.horizontalCenter
       }

       TextField {
           id: textEditInstitutionAddress
           placeholderText: ("г. Краснодар, ул. 40 лет Победы")
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
           id: labelOrganizationCode
           text: "Введите код организации"
           font.pointSize: fontSize
           anchors.horizontalCenter: parent.horizontalCenter
       }

       TextField {
           id: textEditInstitutionCode

           placeholderText: ("1111111")
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

        Button {
            id: buttonRegisterProfile

            text: "Зарегистрироваться"

            font.pointSize: 10

            anchors.left: parent.left
            anchors.right: parent.right

            anchors.leftMargin: 30
            anchors.rightMargin: 30

            onClicked: {
                backend.addNewDoctorProfile(textEditFullName.text.toString(), textEditSpecialization.text.toString(),
                                            textEditInstitutionName.text.toString(), textEditInstitutionCode.text.toString(),
                                            textEditInstitutionAddress.text.toString(), textEditInn.text.toString(),
                                            textEditLicenseInfo.text.toString()
                                            )

//                registeredDoctorFullName = textEditFullName.text.toString()
//                registeredDoctorSpecialization = textEditSpecialization.text.toString()
//                registeredDoctorInstitutionName = textEditInstitutionName.text.toString()
//                registeredDoctorInstitutionCode = textEditInstitutionCode.text.toString()
//                registeredDoctorInstitutionAddress = textEditInstitutionAddress.text.toString()
//                registeredDoctorInn = textEditInn.text.toString()
//                registeredDoctorLicenseInfo = textEditLicenseInfo.text.toString()

                //profileRegistered()
            }
        }
    }
}
