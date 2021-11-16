import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

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

    // Окно, отображающее контент на основной странице
    StackLayout {
        id: stack_content_main

        width: applicationWindow.width - menu_bar.width
        height: applicationWindow.height

        anchors.top: applicationWindow.top
        anchors.bottom: applicationWindow.bottom
        anchors.left: menu_bar.right
        anchors.right: applicationWindow.right

        // По умолчанию отображается окно амбулаторной карты
        currentIndex: 3

        DoctorProfilePage { // 0
            id: page_doctor_profile

            width: parent.width
            height: parent.height
        }

        DoctorDiagnosesDataBase { // 1
            id: page_doctor_diagnoses

            width: parent.width
            height: parent.height
        }

        DoctorTreatmentsDatabase { // 2
            id: page_doctor_treatments

            width: parent.width
            height: parent.height
        }

        PatientMedicalCardPage { // 3
            id: page_medical_card

            width: parent.width
            height: parent.height

        }

        PatientMedicalCardRegistrationPage { // 4
            id: page_patient_registration

            width: parent.width
            height: parent.height
        }
    }

    // Отображается только при запуске системы (открывается окно входа)
    StackView {
        id: stackview_startup

        initialItem: backend.isDoctorDbEmpty === true ? page_doctor_registration : page_login

        anchors.fill: parent
        anchors.centerIn: parent
    }

    // Левая панель управления
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
            font.bold: true

            width: parent.width
            height: 60

            anchors.top: parent.top

            text: doctorFullName

            onClicked: {
                stack_content_main.currentIndex = 0
            }
        }

        Button {
            id: button_patient_card

            font.pointSize: 12

            width: parent.width
            height: 60

            anchors.top: parent.top
            anchors.topMargin: 250

            text: "Амбулаторная карта"

            onClicked: {
                stack_content_main.currentIndex = 3
            }
        }

        Button {
            id: button_diagnoses_database

            font.pointSize: 12

            width: parent.width
            height: 60

            anchors.top: parent.top
            anchors.topMargin: 400

            text: "База диагнозов"

            onClicked: {
                stack_content_main.currentIndex = 1
            }
        }

        Button {
            id: button_treatments_database

            font.pointSize: 12

            width: parent.width
            height: 60

            anchors.top: parent.top
            anchors.topMargin: 480

            text: "База вариантов лечения"

            onClicked: {
                stack_content_main.currentIndex = 2
            }
        }
    }

    // Страница логина, передающая данные профиля
    LoginPage {
        id: page_login

        visible: false;

        onLogIn: {
            doctorFullName = page_login.logInDoctorName.toString()
            doctorSpecialization = page_login.logInDoctorSpecialization.toString()
            doctorInstitutionName = page_login.logInDoctorInstitutionName.toString()
            doctorInstitutionCode = page_login.logInDoctorInstitutionCode.toString()
            doctorInstitutionAddress = page_login.logInDoctorInstitutionAddress.toString()
            doctorInn = page_login.logInDoctorInn.toString()
            doctorLicenseInfo = page_login.logInDoctorLicenseInfo.toString()

            // Передаём данные на страницу профиля
            page_doctor_profile.doctorName = doctorFullName
            page_doctor_profile.doctorSpecialization = doctorSpecialization
            page_doctor_profile.doctorInstitutionName = doctorInstitutionName
            page_doctor_profile.doctorInstitutionCode = doctorInstitutionCode
            page_doctor_profile.doctorInstitutionAddress = doctorInstitutionAddress
            page_doctor_profile.doctorInn = doctorInn
            page_doctor_profile.doctorLicenseInfo = doctorLicenseInfo

            stackview_startup.push(menu_bar)
        }
    }

    // Страница регистрации, передающая данные о только что зарегистрированном пользователе
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

            // Передаём данные на страницу профиля
            page_doctor_profile.doctorName = doctorFullName
            page_doctor_profile.doctorSpecialization = doctorSpecialization
            page_doctor_profile.doctorInstitutionName = doctorInstitutionName
            page_doctor_profile.doctorInstitutionCode = doctorInstitutionCode
            page_doctor_profile.doctorInstitutionAddress = doctorInstitutionAddress
            page_doctor_profile.doctorInn = doctorInn
            page_doctor_profile.doctorLicenseInfo = doctorLicenseInfo

            stackview_startup.push(menu_bar)
        }
    }
}


/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
