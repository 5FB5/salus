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

    property string sidePanelColor: "#D8D7DC"
    property string mainBackgroundColor: "#EBEBEB"

    property string buttonDefaultColor: "#EBEBEB"
    property string buttonPressedColor: "#007AFF"
    property string buttonTextDefaultColor: "#000000"
    property string buttonTextPressedColor: "#FFFFFF"

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
        stack_content_main.currentIndex = 5;
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
        currentIndex: 2

        DoctorProfilePage // 0
        {
            id: page_doctor_profile
        }

        DoctorGlossaryDatabase // 1
        {
            id: page_doctor_glossary
        }

        PatientSearchMedicalCardPage // 2
        {
            id: page_medical_card_search

            onOpenCurrentMedicalCard: function(fullname)
            {
                if (backend.isPatientDbEmpty === true)
                    return;

                console.log("Salus: [QML](openCurrentMedicalCard) - Opening medical card of " + fullname + "...\n");

                backend.setPatient(fullname);
                page_patient_medical_card_main.updatePatientData();
                stack_content_main.currentIndex = 4;

            }

            onRegisterMedicalCard: function(fullname)
            {
                console.log("Salus: [QML](PatientSearchMedicalCardPage -> registerMedicalCard) - Open registration page for " + fullname + "...\n");

                page_patient_registration.patientFullName = fullname;
                stack_content_main.currentIndex = 3;
            }
        }

        PatientMedicalCardRegistrationPage // 3
        {
            id: page_patient_registration

            onReturnBack: function()
            {
                stack_content_main.currentIndex = 2;
            }
       }

        PatientMedicalCardMain // 4
        {
            id: page_patient_medical_card_main

            onReturnBack: function()
            {
                stack_content_main.currentIndex = 2;
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
                    stack_content_main.currentIndex = 2;
                }
            }

            onOpenDiary: function()
            {
                page_patient_medical_card_diary.updatePatientData();
                stack_content_main.currentIndex = 5;
            }

            onDeletePatient: function()
            {
                dialogbox_delete_patient.open();
            }
        }

        PatientMedicalCardDiary // 5
        {
            id: page_patient_medical_card_diary

            onReturnBack: function()
            {
                stack_content_main.currentIndex = 4;
            }

            onOpenAddRecordPage: function()
            {
                stack_content_main.currentIndex = 6;
            }

            onOpenEditPage: function()
            {
                console.log(currentRecord);

                page_patient_edit_record.recordDate = currentRecord;
                page_patient_edit_record.updateRecordData();
                stack_content_main.currentIndex = 7;
            }
        }

        PatientAddRecordPage // 6
        {
            id: page_patient_add_record

            onReturnBack: function()
            {
                stack_content_main.currentIndex = 5;
            }
        }

        PatientEditRecordPage // 7
        {
            id: page_patient_edit_record

            onReturnBack: function()
            {
                stack_content_main.currentIndex = 5;
            }

            onRecordUpdated: function()
            {
                stack_content_main.currentIndex = 5;
                page_patient_edit_record.clearTextFields();
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
    Rectangle
    {
        id: menu_bar

        anchors
        {
            top: parent.top
            bottom: parent.bottom
            left: parent.left
        }
        visible: false
        width: 256
        color: sidePanelColor

        Button
        {
            id: button_profile

            anchors
            {
                left: parent.left
                right: parent.right
                bottom: parent.bottom
                bottomMargin: 30
                leftMargin: 10
                rightMargin: 10
            }

            contentItem: Text
            {
                font.pointSize: 12
                opacity: enabled ? 1.0 : 0.3
                color: button_profile.down ? buttonTextPressedColor : buttonTextDefaultColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: doctorFullName
            }

            background: Rectangle
            {
                anchors.fill: parent
                radius: 10
                color: button_profile.down ? buttonPressedColor: buttonDefaultColor
            }
            font.pointSize: 12
            font.bold: true
            height: 60
//            display: AbstractButton.TextBesideIcon

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
                left: parent.left
                right: parent.right
                top: parent.top
                topMargin: buttonsTopMargin + 230
                leftMargin: 10
                rightMargin: 10
            }

            contentItem: Text
            {
                font.pointSize: 13
                opacity: enabled ? 1.0 : 0.3
                color: button_patient_card.down ? buttonTextPressedColor : buttonTextDefaultColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: "Амбулаторная карта"
            }

            background: Rectangle
            {
                anchors.fill: parent
                radius: 10
                color: button_patient_card.down ? buttonPressedColor: buttonDefaultColor
            }
            font.pointSize: 12
            height: 60

            onClicked: function()
            {
                stack_content_main.currentIndex = 2;
            }
        }

        Button
        {
            id: button_glossary

            anchors
            {
                left: parent.left
                right: parent.right
                top: button_patient_card.bottom
                topMargin: buttonsTopMargin
                leftMargin: 10
                rightMargin: 10
            }

            contentItem: Text
            {
                font.pointSize: 13
                opacity: enabled ? 1.0 : 0.3
                color: button_glossary.down ? buttonTextPressedColor : buttonTextDefaultColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: "Глоссарий"
            }

            background: Rectangle
            {
                anchors.fill: parent
                radius: 10
                color: button_glossary.down ? buttonPressedColor: buttonDefaultColor
            }
            font.pointSize: 12
            height: 60

            onClicked: function()
            {
                stack_content_main.currentIndex = 1;
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
