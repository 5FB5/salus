import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import io.qt.salus 1.0

Page {
    id: root

    property string doctorName
    property string doctorSpecialization
    property string doctorInstitutionName
    property string doctorInstitutionCode
    property string doctorInstitutionAddress
    property string doctorInn
    property string doctorLicenseInfo

    property int buttonStandartTextFontSize: 11
    property int standartTextSize: 14


    Label {
        id: pageTitle

        font.pointSize: 20
        font.bold: true

        anchors.top: parent.top
        anchors.topMargin: 50

        anchors.horizontalCenter: parent.horizontalCenter

        text: "Личный кабинет"

    }

    // Область с данными текущего профиля
    Column {
        id: column_profile_data

        anchors.top: parent.top
        anchors.topMargin: 150

        anchors.left: parent.left
        anchors.leftMargin: 120

        spacing: 30

        Label {
            id: labelName

            font.pointSize: standartTextSize

            text: "<b>ФИО:</b> " + doctorName
        }

        Label {
            id: labelSpecialization

            font.pointSize: standartTextSize

            text: "<b>Специализация:</b> " + doctorSpecialization
        }

        Label {
            id: labelInstitutionName

            font.pointSize: standartTextSize

            text: "<b>Наименование учреждения:</b> " + doctorInstitutionName
        }

        Label {
            id: labelInstitutionCode

            font.pointSize: standartTextSize

            text: "<b>Код учреждения:</b> " + doctorInstitutionCode

        }

        Label {
            id: labelInstitutionAddress

            font.pointSize: standartTextSize

            text: "<b>Адрес учреждения:</b> " + doctorInstitutionAddress

        }

        Label {
            id: labelInn

            font.pointSize: standartTextSize

            text: "<b>ИНН:</b> " + doctorInn

        }

        Label {
            id: labelLicenseInfo

            font.pointSize: standartTextSize

            text: "<b>Лицензия:</b> " + doctorLicenseInfo
        }

        Button {
            id: button_change_info

            font.pointSize: buttonStandartTextFontSize

            width: 200
            height: 60

            enabled: false

            text: "Изменить профиль"
        }
    }
}

