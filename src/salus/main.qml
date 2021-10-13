import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window {
    id: applicationWindow
    width: 1600
    height: 900
    minimumWidth: 800
    minimumHeight: 600
    visible: true
    visibility: "Maximized"
    title: qsTr("Салюс")

    // Отображается только при запуске система (открывается окно входа)
    StackView {
        id: stackview_startup
        initialItem: page_login

        anchors.fill: parent
        anchors.centerIn: parent
    }

    Rectangle {
        id: menu_bar
        visible: false

        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left

        width: 256

        color: "#828282"

        StackView {
            id: stackview_content_main
            x: 0
            y: 0

            width: 1344
            height: 900

            anchors.top: applicationWindow.top
            anchors.bottom: applicationWindow.bottom
            anchors.left: parent.right
            anchors.right: applicationWindow.right
        }
    }

    LoginPage {
        id: page_login
        onLogIn: {
            stackview_startup.push(menu_bar)
        }

    }

    DoctorProfileRegistrationPage {
        id: page_doctor_registration
    }

    /*
    Component {
        id: page_login
    }

    Component {
        id: page_doctor_profile_registration
    }

    Component {
        id: page_doctor_profile
    }

    Component {
        id: page_doctor_diagnoses_list
    }

    Component {
        id: page_patient_medical_card
    }

    Component {
        id: page_patient_registration
    }

    */
}



/*##^##
Designer {
    D{i:0;formeditorZoom:0.66}
}
##^##*/
