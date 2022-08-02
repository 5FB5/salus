import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "../frontend/doctor"
import "../frontend/patient"

import salus 1.0

ApplicationWindow {
    id: applicationWindow

    minimumWidth: 1280
    minimumHeight: 720

    visibility: "Windowed"

    title: qsTr("Салюс")

    // Здесь хранятся все данные по профилю врача, передающиеся из C++, либо напрямую при регистрации
    property string doctorFullName
    property string doctorSpecialization
    property string doctorInstitutionName
    property string doctorInstitutionCode
    property string doctorInstitutionAddress
    property string doctorInn
    property string doctorLicenseInfo

    property int buttonsTopMargin: 5 // позиционирование кнопок левой панели

    function updateProfilePage()
    {
        page_doctor_profile.doctorName = backend.currentDoctorFullName
        page_doctor_profile.doctorSpecialization = backend.currentDoctorSpecialization
        page_doctor_profile.doctorInstitutionName = backend.currentDoctorInstitutionName
        page_doctor_profile.doctorInstitutionAddress = backend.currentDoctorInstitutionAddress
        page_doctor_profile.doctorInstitutionCode = backend.currentDoctorInstitutionCode
        page_doctor_profile.doctorInn = backend.currentDoctorInn
        page_doctor_profile.doctorLicenseInfo = backend.currentDoctorLicenseInfo
    }

    Component.onCompleted:
    {
        doctorFullName = backend.currentDoctorFullName

        updateProfilePage()
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
        }

        DoctorDiagnosesDataBase { // 1
            id: page_doctor_diagnoses
        }

        DoctorTreatmentsDatabase { // 2
            id: page_doctor_treatments
        }

        PatientSearchMedicalCardPage { // 3
            id: page_medical_card_search

            Connections
            {
                target: backend

                onPatientDeleted:
                {
                    patientListModel.reloadPatientList()
                }
            }

            onOpenCurrentMedicalCard: {
                console.log("Salus: [QML](openCurrentMedicalCard) - Opening medical card of " + fullname + "...\n")

                backend.setPatient(fullname)

                page_patient_medical_card_main.patientFullName = backend.currentPatientFullName
                page_patient_medical_card_main.patientAge = backend.currentPatientAge
                page_patient_medical_card_main.patientSex = backend.currentPatientSex
                page_patient_medical_card_main.patientBirthDate = backend.currentPatientBirthDate
                page_patient_medical_card_main.patientAddress = backend.currentPatientAddress
                page_patient_medical_card_main.patientOccupation = backend.currentPatientOccupation
                page_patient_medical_card_main.patientDiagnosis = backend.currentPatientDiagnosis
                page_patient_medical_card_main.patientComplaints = backend.currentPatientComplaints
                page_patient_medical_card_main.patientDiseases = backend.currentPatientDiseases
                page_patient_medical_card_main.patientAnamnesis = backend.currentPatientAnamnesis

                stack_content_main.currentIndex = 5
            }

            onRegisterMedicalCard: {
                console.log("Salus: [QML](PatientSearchMedicalCardPage -> registerMedicalCard) - Open registration page for " + fullname + "...\n")
                page_patient_registration.patientFullName = fullname
                stack_content_main.currentIndex = 4
            }
        }

        PatientMedicalCardRegistrationPage { // 4
            id: page_patient_registration

            Connections
            {
                target: backend

                onPatientAdded:
                {
                    patientListModel.reloadPatientList()

                    stack_content_main.currentIndex = 5
                }
            }

//            onPatientRegistered: {
////                page_patient_medical_card_main.patientFullName = patientFullName
////                page_patient_medical_card_main.patientAge = patientAge
////                page_patient_medical_card_main.patientBirthDate = patientBirthDate
////                page_patient_medical_card_main.patientPhoneNumber = patientPhoneNumber
////                page_patient_medical_card_main.patientOccupation = patientOccupation

//                var copyList = model // FIXME: пахнет костылём, так делать не стоит, но иначе оно просто не работает
//                copyList.reloadPatientList()
//                page_medical_card_search.patientList = copyList

//                stack_content_main.currentIndex = 5
//            }
        }

        PatientMedicalCardMain { // 5
            id: page_patient_medical_card_main

            Connections
            {
                target: patientListModel

                onModelReloaded:
                {
                    page_patient_medical_card_main.updatePatientData()
                }
            }

            // Диалоговое окно для подтверждения удаления пациента из БД
            Dialog {
                id: dialogbox_delete_patient

                width: parent.width / 4
                height: parent.height / 4

                anchors.centerIn: parent

                title: "Удаление карты пациента '" + page_patient_medical_card_main.patientFullName + "'"
                standardButtons: Dialog.Yes | Dialog.No

                Text {
                    id: dialogbox_text
                    font.pointSize: 14
                    text: qsTr("Удалить карту?")
                }

                onAccepted: {
                    backend.deletePatient()

//                    var copyList = model // FIXME: пахнет костылём, так делать не стоит, но иначе оно просто не работает
//                    copyList.reloadPatientList()

//                    model.reloadPatientList()
//                    var copyList = model

//                    page_medical_card_search.patientList = copyList

//                    patientListModel.reloadPatientList()

                    stack_content_main.currentIndex = 3
                }
            }

            onOpenDiary: {
                console.log("Salus: [QML](PatientMedicalCardMain -> openDiary) - Opening diary page...\n")
                page_patient_medical_card_diary.patientFullName = patientFullName
                page_patient_medical_card_diary.patientAge = patientAge
                page_patient_medical_card_diary.patientBirthDate = patientBirthDate
                page_patient_medical_card_diary.patientPhoneNumber = patientPhoneNumber
                page_patient_medical_card_diary.patientOccupation = patientOccupation

                stack_content_main.currentIndex = 6
                console.log("Salus: [QML](PatientMedicalCardMain -> openDiary) - Diary page opened\n")
            }

            onDeletePatient: {
                dialogbox_delete_patient.open()
            }
        }

        PatientMedicalCardDiary { // 6
            id: page_patient_medical_card_diary
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
            anchors.topMargin: buttonsTopMargin

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
            anchors.topMargin: buttonsTopMargin + 100

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
            anchors.topMargin: buttonsTopMargin + 200

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
            anchors.topMargin: buttonsTopMargin + 300

            text: "База вариантов лечения"

            onClicked: {
                stack_content_main.currentIndex = 2
            }
        }
    }

    // Страница логина, передающая данные профиля
    LoginPage {
        id: page_login

        visible: false

        onLogIn: {
//            doctorFullName = backend.currentDoctorFullName
//            doctorSpecialization = page_login.logInDoctorSpecialization.toString()
//            doctorInstitutionName = page_login.logInDoctorInstitutionName.toString()
//            doctorInstitutionCode = page_login.logInDoctorInstitutionCode.toString()
//            doctorInstitutionAddress = page_login.logInDoctorInstitutionAddress.toString()
//            doctorInn = page_login.logInDoctorInn.toString()
//            doctorLicenseInfo = page_login.logInDoctorLicenseInfo.toString()

            stackview_startup.push(menu_bar)
        }
    }

    // Страница регистрации, передающая данные о только что зарегистрированном пользователе
    DoctorProfileRegistrationPage {
        id: page_doctor_registration

        anchors.fill: parent

        visible: false;

        Connections
        {
            target: backend

            onProfileAdded:
            {
                doctorFullName = backend.currentDoctorFullName

                page_doctor_profile.doctorName = backend.currentDoctorFullName
                page_doctor_profile.doctorSpecialization = backend.currentDoctorSpecialization
                page_doctor_profile.doctorInstitutionName = backend.currentDoctorInstitutionName
                page_doctor_profile.doctorInstitutionAddress = backend.currentDoctorInstitutionAddress
                page_doctor_profile.doctorInstitutionCode = backend.currentDoctorInstitutionCode
                page_doctor_profile.doctorInn = backend.currentDoctorInn
                page_doctor_profile.doctorLicenseInfo = backend.currentDoctorLicenseInfo

                stackview_startup.push(menu_bar)
            }
        }

//        onProfileRegistered: {
//            doctorFullName = page_doctor_registration.registeredDoctorFullName.toString()
//            doctorSpecialization = page_doctor_registration.registeredDoctorSpecialization.toString()
//            doctorInstitutionName = page_doctor_registration.registeredDoctorInstitutionName.toString()
//            doctorInstitutionCode = page_doctor_registration.registeredDoctorInstitutionCode.toString()
//            doctorInstitutionAddress = page_doctor_registration.registeredDoctorInstitutionAddress.toString()
//            doctorInn = page_doctor_registration.registeredDoctorInn.toString()
//            doctorLicenseInfo = page_doctor_registration.registeredDoctorLicenseInfo.toString()

//            // Передаём данные на страницу профиля
//            page_doctor_profile.doctorName = doctorFullName
//            page_doctor_profile.doctorSpecialization = doctorSpecialization
//            page_doctor_profile.doctorInstitutionName = doctorInstitutionName
//            page_doctor_profile.doctorInstitutionCode = doctorInstitutionCode
//            page_doctor_profile.doctorInstitutionAddress = doctorInstitutionAddress
//            page_doctor_profile.doctorInn = doctorInn
//            page_doctor_profile.doctorLicenseInfo = doctorLicenseInfo

//            stackview_startup.push(menu_bar)
//        }
    }
}
