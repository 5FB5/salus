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
        initialItem: login_page

        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            top: parent.top
        }

        width: parent.width
        height: parent.height
    }

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

    Component {
        id: login_page
    }

    Component {
        id: doctor_profile_registration
    }

    Component {
        id: doctor_profile
    }

    Component {
        id: doctor_diagnoses_list
    }

    Component {
        id: patient_medical_card
    }

    Component {
        id: patient_registration
    }
}



/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}
}
##^##*/
