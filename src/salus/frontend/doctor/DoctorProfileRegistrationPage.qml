import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import salus 1.0

Page
{
    id: root

    property int fontSize: 11

    property int textFieldsWidth: 300
    property int textFieldBorderRadius: 10

    Rectangle
    {
        id: backgroundRect

        anchors.fill: parent
        color: "#ffffff"
    }

    Text
    {
        anchors
        {
            top: parent.top
            topMargin: 15
            horizontalCenter: parent.horizontalCenter
        }
        font.pointSize: 20
        text: "Регистрация нового профиля"
    }

    Column
    {
        id: registrationFields

        anchors.centerIn: parent

        transformOrigin: Item.Center
        spacing: 15

       Text
       {
           id: labelFullName

           anchors.horizontalCenter: parent.horizontalCenter

           font.pointSize: fontSize
           text: "Введите ФИО"
       }

       TextField
       {
           id: textEditFullName

           font.pointSize: fontSize
           width: textFieldsWidth
           height: 30
           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter

           placeholderText: "Иванов Иван Иванович"

           Rectangle
           {
               anchors.fill: parent

               border.width: 1
               color: "#0000ffff"

           }
       }

       Text
       {
           id: labelInn

           anchors.horizontalCenter: parent.horizontalCenter

           font.pointSize: fontSize
           text: "Введите ИНН"
       }

       TextField
       {
           id: textEditInn

           font.pointSize: fontSize
           width: textFieldsWidth
           height: 30
           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter

           placeholderText: "797057359509"

           Rectangle
           {
               anchors.fill: parent
               border.width: 1
               color: "#0000ffff"
           }
       }

       Text
       {
           id: labelSpecialization

           anchors.horizontalCenter: parent.horizontalCenter

           font.pointSize: fontSize
           text: "Введите специализацию"
       }

       TextField
       {
           id: textEditSpecialization

           font.pointSize: fontSize
           width: textFieldsWidth
           height: 30
           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter

           placeholderText: "Врач-стоматолог"

           Rectangle
           {
               anchors.fill: parent
               border.width: 1
               color: "#0000ffff"
           }
       }

       Text
       {
           id: labelLicense

           anchors.horizontalCenter: parent.horizontalCenter

           font.pointSize: fontSize
           text: "Введите лицензию"
       }

       TextField
       {
           id: textEditLicenseInfo

           font.pointSize: fontSize
           width: textFieldsWidth
           height: 30
           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter

           placeholderText: "1423645678"

           Rectangle
           {
               anchors.fill: parent
               border.width: 1
               color: "#0000ffff"
           }
       }

       Text
       {
           id: labelOrganization

           anchors.horizontalCenter: parent.horizontalCenter

           font.pointSize: fontSize
           text: "Введите название организации"
       }

       TextField
       {
           id: textEditInstitutionName

           font.pointSize: fontSize
           width: textFieldsWidth
           height: 30
           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter

           placeholderText: "ИП Иванов И.И."

           Rectangle
           {
               anchors.fill: parent
               border.width: 1
               color: "#0000ffff"
           }
       }

       Text
       {
           id: labelOrganizationAddress

           anchors.horizontalCenter: parent.horizontalCenter

           font.pointSize: fontSize
           text: "Введите адрес организации"
       }

       TextField
       {
           id: textEditInstitutionAddress

           font.pointSize: fontSize
           width: textFieldsWidth
           height: 30
           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter

           placeholderText: ("г. Краснодар, ул. 40 лет Победы")

           Rectangle
           {
               anchors.fill: parent
               border.width: 1
               color: "#0000ffff"
           }
       }

       Text
       {
           id: labelOrganizationCode

           anchors.horizontalCenter: parent.horizontalCenter

           font.pointSize: fontSize
           text: "Введите код организации"
       }

       TextField
       {
           id: textEditInstitutionCode

           font.pointSize: fontSize
           width: textFieldsWidth
           height: 30
           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter

           placeholderText: ("1111111")

           Rectangle
           {
               anchors.fill: parent
               border.width: 1
               color: "#0000ffff"
           }
       }

        Button
        {
            id: buttonRegisterProfile

            anchors
            {
                left: parent.left
                right: parent.right
                leftMargin: 30
                rightMargin: 30
            }

            font.pointSize: 10
            text: "Зарегистрироваться"

            onClicked: function()
            {
                backend.addNewDoctorProfile(textEditFullName.text.toString(), textEditSpecialization.text.toString(),
                                            textEditInstitutionName.text.toString(), textEditInstitutionCode.text.toString(),
                                            textEditInstitutionAddress.text.toString(), textEditInn.text.toString(),
                                            textEditLicenseInfo.text.toString()
                                            );
            }
        }
    }
}
