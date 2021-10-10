import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window {
    id: applicationWindow
    width: 1600
    height: 900
    visible: true
    title: qsTr("Салюс")

    StackView {
        id: stackview_startup
        initialItem: page_login

        anchors.fill: parent

        width: parent.width
        height: parent.height
    }

    Item {
        id: mainWindow
        anchors.fill: parent
        visible: false

        Rectangle {
            id: menu_bar
            visible: true
            anchors.left: parent.left
            width: 256
            height: parent.height
            color: "#828282"

            StackView {
                id: stackview_content_main
                initialItem: patient_medical_card
                x: parent.width
                y: 0
                width: window.width - parent.width
                height: parent.height
            }
        }
    }

    LoginPage {
        id: page_login
        onLogIn: {
            stackview_startup.push(mainWindow)
        }

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
    D{i:0;formeditorZoom:0.5}
}
##^##*/
