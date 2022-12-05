import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import salus 1.0

Page
{
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

    Label
    {
        anchors
        {
            top: rowButtons.top
            horizontalCenter: parent.horizontalCenter
            topMargin: -180
        }
        font.pointSize: standartTextSize
        font.bold: true
        text: "Войти как..."
    }

    Label {
        id: doctorName

        anchors
        {
            top: rowButtons.top
            topMargin: -112
            horizontalCenter: parent.horizontalCenter
        }
        font.pointSize: standartTextSize
        text: backend.currentDoctorFullName
    }

    Row
    {
        id: rowButtons

        anchors
        {
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
            bottomMargin: (parent.height / 2) - 50
        }
        spacing: 15

        Button
        {
            id: buttonEnterToProfile

            font.pointSize: buttonStandartTextFontSize
            width: 200
            height: 60

            text: "Войти"

            onClicked: function()
            {
                logIn();
            }
        }
    }
}
