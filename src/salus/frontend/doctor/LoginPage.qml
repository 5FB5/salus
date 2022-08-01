import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import salus 1.0

Page {
    id: root

    property int buttonStandartTextFontSize: 10
    property int standartTextSize: 14

    signal logIn();

//    property string logInDoctorName: backend.currentDoctorFullName
//    property string logInDoctorSpecialization: backend.currentDoctorSpecialization
//    property string logInDoctorInstitutionName: backend.currentDoctorInstitutionName
//    property string logInDoctorInstitutionCode: backend.currentDoctorInstitutionCode
//    property string logInDoctorInstitutionAddress: backend.currentDoctorInstitutionAddress
//    property string logInDoctorInn: backend.currentDoctorInn
//    property string logInDoctorLicenseInfo: backend.currentDoctorLicenseInfo

    Rectangle
    {
        id: background
        anchors.fill: parent

        color: "#ffffff"
    }

    Label {
        text: "Войти как..."

        font.pointSize: standartTextSize
        font.bold: true

        anchors.top: rowButtons.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: -180
    }

    // Табличка, на которой будет отображаться имя врача из профиля
    Label {
        id: doctorName

        text: backend.currentDoctorFullName

        font.pointSize: standartTextSize

        anchors.top: rowButtons.top
        anchors.topMargin: -112
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Row {
        id: rowButtons

        spacing: 15

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: (parent.height / 2) - 50

        Button {
            id: buttonEnterToProfile
            text: "Войти"

            font.pointSize: buttonStandartTextFontSize

            width: 200
            height: 60

            onClicked: {
                logIn();

            }
        }

        // TODO: add multiple doctor profiles registration
        //        Button {
        //            id: buttonSignUp
        //            text: "Добавить профиль"
        //            enabled: false

        //            font.pointSize: buttonStandartTextFontSize

        //            width: 200
        //            height: 60

        //            onClicked: {
        //                root.signUp();
        //            }
        //        }
    }

}
