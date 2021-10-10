import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Page {
    id: root

    property alias labelDoctorName: doctorName.text
   // property alias backgroundColor: backgroundRect.color

   // property alias buttonLoginText: buttonEnterToProfile.text
   // property alias buttonSignUpText: buttonSignUp.text

    signal logIn();
    signal signUp();

    // Табличка, на которой будет отображаться имя врача из профиля
    Label {
        id: doctorName
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
    }

    background: Rectangle {
        id: backgroundRect
        color: "white"
    }

    Row {
        spacing: 15

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        Button {
            id: buttonEnterToProfile
            text: "Войти"

            width: 200
            height: 60

            onClicked: {
                root.logIn();
            }
        }

        Button {
            id: buttonSignUp
            text: "Зарегистрироваться"

            width: 200
            height: 60

            onClicked: {
                root.signUp();
            }
        }
    }

}
