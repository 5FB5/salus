import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Page {
    id: root

    width: Screen.width
    height: Screen.height

    property alias labelDoctorName: doctorName.text
    property int buttonStandartTextFontSize: 10
    property int standartTextSize: 14

    signal logIn();

    // Табличка, на которой будет отображаться имя врача из профиля
    Label {
        id: doctorName
        text: "[Заглушка] Фамилия Имя Отчество"

        font.pointSize: standartTextSize

        anchors.top: rowButtons.top
        anchors.topMargin: -112
        anchors.horizontalCenter: parent.horizontalCenter
    }

    background: Rectangle {
        id: backgroundRect
        color: "white"
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
                root.logIn();
            }
        }

//        Button {
//            id: buttonSignUp
//            text: "Зарегистрироваться"

//            font.pointSize: buttonStandartTextFontSize

//            width: 200
//            height: 60

//            onClicked: {
//                root.signUp();
//            }
//        }
    }

}
