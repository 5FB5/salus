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
    StackLayout
    {
        id: stack_content_main

        width: applicationWindow.width - menu_bar.width
        height: applicationWindow.height

        anchors.top: applicationWindow.top
        anchors.bottom: applicationWindow.bottom
        anchors.left: menu_bar.right
        anchors.right: applicationWindow.right

        // По умолчанию отображается окно амбулаторной карты
        currentIndex: 3

        DoctorProfilePage // 0
        {
            id: page_doctor_profile
        }

        DoctorDiagnosesDataBase // 3
        {
            id: page_doctor_diagnoses
        }

        DoctorTreatmentsDatabase { // 2
            id: page_doctor_treatments
        }

        PatientSearchMedicalCardPage // 3
        {
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
                if (!backend.isPatientDbEmpty)
                {
                    console.log("Salus: [QML](openCurrentMedicalCard) - Opening medical card of " + fullname + "...\n")

                    backend.setPatient(fullname)

                    page_patient_medical_card_main.updatePatientData()

                    stack_content_main.currentIndex = 5
                }
            }

            onRegisterMedicalCard: {
                console.log("Salus: [QML](PatientSearchMedicalCardPage -> registerMedicalCard) - Open registration page for " + fullname + "...\n")
                page_patient_registration.patientFullName = fullname
                stack_content_main.currentIndex = 4
            }
        }

        PatientMedicalCardRegistrationPage // 4
        {
            id: page_patient_registration

            onReturnBack: function()
            {
                stack_content_main.currentIndex = 3;
            }

            Connections
            {
                target: backend

                onPatientAdded:
                {
                    patientListModel.reloadPatientList()

                    page_patient_registration.clearTextFields()

                    stack_content_main.currentIndex = 5
                }
            }
       }

        PatientMedicalCardMain // 5
        {
            id: page_patient_medical_card_main

            onReturnBack: function()
            {
                stack_content_main.currentIndex = 3;
            }

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

                    anchors.fill: parent

                    wrapMode: Text.WordWrap

                    text: qsTr("Удалить карту?")
                }

                onAccepted: {
                    backend.deletePatient()
                    stack_content_main.currentIndex = 3
                }
            }

            onOpenDiary: {
                console.log("Salus: [QML](PatientMedicalCardMain -> openDiary) - Opening diary page...\n")
                page_patient_medical_card_diary.updatePatientData()

                stack_content_main.currentIndex = 6
                console.log("Salus: [QML](PatientMedicalCardMain -> openDiary) - Diary page opened\n")
            }

            onDeletePatient: {
                dialogbox_delete_patient.open();
            }
        }

        PatientMedicalCardDiary // 6
        {
            id: page_patient_medical_card_diary

            onReturnBack: function()
            {
                stack_content_main.currentIndex = 5;
            }

            onOpenAddRecordPage:
            {
                stack_content_main.currentIndex = 7;
            }

            onOpenEditPage:
            {
                console.log(currentRecord);
                page_patient_edit_record.recordDate = currentRecord;
                page_patient_edit_record.updateRecordData();
                stack_content_main.currentIndex = 8;
            }
        }

        PatientAddRecordPage // 7
        {
            id: page_patient_add_record

            onReturnBack: function()
            {
                stack_content_main.currentIndex = 6;
            }

            Connections
            {
                target: backend

                onRecordAdded:
                {
                    stack_content_main.currentIndex = 6
                    page_patient_add_record.clearTextFields()
                }
            }
        }

        PatientEditRecordPage // 8
        {
            id: page_patient_edit_record

            onReturnBack: function()
            {
                stack_content_main.currentIndex = 6;
            }

            onRecordUpdated:
            {
                stack_content_main.currentIndex = 6;
            }
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

        onLogIn:
        {
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
    }
}
