import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import io.qt.salus 1.0

Window {
    id: applicationWindow

    width: ScreenInfo.desktopAvailableWidth
    height: ScreenInfo.desktopAvailableHeight

    minimumWidth: 1366
    minimumHeight: 768
    visibility: "Maximized"

    title: qsTr("Салюс")

    property string doctorFullName
    property string doctorSpecialization
    property string doctorInstitutionName
    property string doctorInstitutionCode
    property string doctorInstitutionAddress
    property string doctorInn
    property string doctorLicenseInfo

    Backend {
        id: backend
    }

    //FIXME: don't do that, 'cause it will be call once on start
    //property string doctorProfileName: backend.currentDoctorFullName

    // Отображается только при запуске системы (открывается окно входа)
    StackView {
        id: stackview_startup

        initialItem: backend.isDoctorDbEmpty === true ? page_doctor_registration : page_login

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

        Button {
            id: button_profile

            font.pointSize: 12

            width: parent.width
            height: 60

            text: doctorFullName
        }

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
            doctorFullName = page_login.logInDoctorName.toString()
            doctorSpecialization = page_login.logInDoctorSpecialization.toString()
            doctorInstitutionName = page_login.logInDoctorInstitutionName.toString()
            doctorInstitutionCode = page_login.logInDoctorInstitutionCode.toString()
            doctorInstitutionAddress = page_login.logInDoctorInstitutionAddress.toString()
            doctorInn = page_login.logInDoctorInn.toString()
            doctorLicenseInfo = page_login.logInDoctorLicenseInfo.toString()

            stackview_startup.push(menu_bar)
        }

        visible: false;

    }

    DoctorProfileRegistrationPage {
        id: page_doctor_registration

        visible: false;

        onProfileRegistered: {
            doctorFullName = page_doctor_registration.registeredDoctorFullName.toString()
            doctorSpecialization = page_doctor_registration.registeredDoctorSpecialization.toString()
            doctorInstitutionName = page_doctor_registration.registeredDoctorInstitutionName.toString()
            doctorInstitutionCode = page_doctor_registration.registeredDoctorInstitutionCode.toString()
            doctorInstitutionAddress = page_doctor_registration.registeredDoctorInstitutionAddress.toString()
            doctorInn = page_doctor_registration.registeredDoctorInn.toString()
            doctorLicenseInfo: page_doctor_registration.registeredDoctorLicenseInfo.toString()

            stackview_startup.push(menu_bar)
        }
    }

    /*

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
