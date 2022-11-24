import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import salus 1.0

import "../frontend/doctor"
import "../frontend/patient"

ApplicationWindow
{
    id: applicationWindow

    minimumWidth: 1280
    minimumHeight: 720

    visibility: "Windowed"

    title: qsTr("Салюс")

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
        page_doctor_profile.doctorName = backend.currentDoctorFullName;
        page_doctor_profile.doctorSpecialization = backend.currentDoctorSpecialization;
        page_doctor_profile.doctorInstitutionName = backend.currentDoctorInstitutionName;
        page_doctor_profile.doctorInstitutionAddress = backend.currentDoctorInstitutionAddress;
        page_doctor_profile.doctorInstitutionCode = backend.currentDoctorInstitutionCode;
        page_doctor_profile.doctorInn = backend.currentDoctorInn;
        page_doctor_profile.doctorLicenseInfo = backend.currentDoctorLicenseInfo;
    }

    function setDataToMainCard()
    {
        patientListModel.reloadPatientList();
        page_patient_registration.clearTextFields();
        stack_content_main.currentIndex = 5;
    }

    function setDataToDiary()
    {
        stack_content_main.currentIndex = 6;
        page_patient_add_record.clearTextFields();
    }

    function addNewProfile()
    {
        doctorFullName = backend.currentDoctorFullName;

        page_doctor_profile.doctorName = backend.currentDoctorFullName;
        page_doctor_profile.doctorSpecialization = backend.currentDoctorSpecialization;
        page_doctor_profile.doctorInstitutionName = backend.currentDoctorInstitutionName;
        page_doctor_profile.doctorInstitutionAddress = backend.currentDoctorInstitutionAddress;
        page_doctor_profile.doctorInstitutionCode = backend.currentDoctorInstitutionCode;
        page_doctor_profile.doctorInn = backend.currentDoctorInn;
        page_doctor_profile.doctorLicenseInfo = backend.currentDoctorLicenseInfo;

        stackview_startup.push(menu_bar);
    }

    Component.onCompleted: function()
    {
        doctorFullName = backend.currentDoctorFullName;
        updateProfilePage();

        backend.patientDeleted.connect(patientListModel.reloadPatientList);
        backend.patientAdded.connect(setDataToMainCard);
        backend.recordAdded.connect(setDataToDiary);
        backend.profileAdded.connect(addNewProfile);

        patientListModel.modelReloaded.connect(page_patient_medical_card_main.updatePatientData);
    }

    // Окно, отображающее контент на основной странице
    StackLayout
    {
        id: stack_content_main

        anchors
        {
            top: applicationWindow.top
            bottom: applicationWindow.bottom
            left: menu_bar.right
            right: applicationWindow.right
        }

        width: applicationWindow.width - menu_bar.width
        height: applicationWindow.height

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

            onOpenCurrentMedicalCard: function(fullname)
            {
                if (backend.isPatientDbEmpty === true)
                    return;

                console.log("Salus: [QML](openCurrentMedicalCard) - Opening medical card of " + fullname + "...\n");

                backend.setPatient(fullname);
                page_patient_medical_card_main.updatePatientData();
                stack_content_main.currentIndex = 5;

            }

            onRegisterMedicalCard: function(fullname)
            {
                console.log("Salus: [QML](PatientSearchMedicalCardPage -> registerMedicalCard) - Open registration page for " + fullname + "...\n");

                page_patient_registration.patientFullName = fullname;
                stack_content_main.currentIndex = 4;
            }
        }

        PatientMedicalCardRegistrationPage // 4
        {
            id: page_patient_registration

            onReturnBack: function()
            {
                stack_content_main.currentIndex = 3;
            }
       }

        PatientMedicalCardMain // 5
        {
            id: page_patient_medical_card_main

            onReturnBack: function()
            {
                stack_content_main.currentIndex = 3;
            }

            // Диалоговое окно для подтверждения удаления пациента из БД
            Dialog
            {
                id: dialogbox_delete_patient

                anchors.centerIn: parent

                width: parent.width / 4
                height: parent.height / 4
                title: "Удаление карты пациента '" + page_patient_medical_card_main.patientFullName + "'"
                standardButtons: Dialog.Yes | Dialog.No

                Text
                {
                    id: dialogbox_text

                    anchors.fill: parent

                    font.pointSize: 14
                    wrapMode: Text.WordWrap
                    text: qsTr("Удалить карту?")
                }

                onAccepted: function()
                {
                    backend.deletePatient();
                    stack_content_main.currentIndex = 3;
                }
            }

            onOpenDiary: function()
            {
                console.log("Salus: [QML](PatientMedicalCardMain -> openDiary) - Opening diary page...\n");

                page_patient_medical_card_diary.updatePatientData();
                stack_content_main.currentIndex = 6;

                console.log("Salus: [QML](PatientMedicalCardMain -> openDiary) - Diary page opened\n");
            }

            onDeletePatient: function()
            {
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

            onOpenAddRecordPage: function()
            {
                stack_content_main.currentIndex = 7;
            }

            onOpenEditPage: function()
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
        }

        PatientEditRecordPage // 8
        {
            id: page_patient_edit_record

            onReturnBack: function()
            {
                stack_content_main.currentIndex = 6;
            }

            onRecordUpdated: function()
            {
                stack_content_main.currentIndex = 6;
            }
        }
    }

    // Отображается только при запуске системы (открывается окно входа)
    StackView
    {
        id: stackview_startup

        anchors
        {
            fill: parent
            centerIn: parent
        }
        initialItem: backend.isDoctorDbEmpty === true ? page_doctor_registration : page_login
    }

    // Левая панель управления
    Rectangle {
        id: menu_bar

        anchors
        {
            top: parent.top
            bottom: parent.bottom
            left: parent.left
        }
        visible: false
        width: 256
        color: "#828282"

        Button
        {
            id: button_profile

            anchors
            {
                top: parent.top
                topMargin: buttonsTopMargin
            }

            font.pointSize: 12
            font.bold: true
            width: parent.width
            height: 60
            text: doctorFullName

            onClicked: function()
            {
                stack_content_main.currentIndex = 0;
            }
        }

        Button
        {
            id: button_patient_card

            anchors
            {
                top: parent.top
                topMargin: buttonsTopMargin + 100
            }
            font.pointSize: 12
            width: parent.width
            height: 60
            text: "Амбулаторная карта"

            onClicked: function()
            {
                stack_content_main.currentIndex = 3;
            }
        }

        Button
        {
            id: button_diagnoses_database

            anchors
            {
                top: parent.top
                topMargin: buttonsTopMargin + 200
            }
            font.pointSize: 12
            width: parent.width
            height: 60
            text: "База диагнозов"

            onClicked: function()
            {
                stack_content_main.currentIndex = 1;
            }
        }

        Button
        {
            id: button_treatments_database

            anchors
            {
                top: parent.top
                topMargin: buttonsTopMargin + 300
            }

            font.pointSize: 12
            width: parent.width
            height: 60
            text: "База вариантов лечения"

            onClicked: function()
            {
                stack_content_main.currentIndex = 2;
            }
        }
    }

    // Страница логина, передающая данные профиля
    LoginPage
    {
        id: page_login

        visible: false

        onLogIn: function()
        {
            stackview_startup.push(menu_bar)
        }
    }

    // Страница регистрации, передающая данные о только что зарегистрированном пользователе
    DoctorProfileRegistrationPage
    {
        id: page_doctor_registration

        anchors.fill: parent
        visible: false
    }
}
