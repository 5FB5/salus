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
        color: "#FFFFFF"
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

            contentItem: Text
            {
                font.pointSize: 12
                opacity: enabled ? 1.0 : 0.3
                color: buttonEnterToProfile.down ? buttonTextPressedColor : buttonTextDefaultColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: "Войти"
            }

            background: Rectangle
            {
                anchors.fill: parent
                radius: 10
                color: buttonEnterToProfile.down ? buttonPressedColor: buttonDefaultColor
            }
            font.pointSize: buttonStandartTextFontSize
            width: 200
            height: 60

            onClicked: function()
            {
                logIn();
            }
        }
    }
}
