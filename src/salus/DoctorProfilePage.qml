import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import io.qt.salus 1.0

Page {
    id: root

    Backend {
        id: backend
    }

    property string doctorName
    property string doctorSpecialization
    property string doctorInstitutionName
    property string doctorInstitutionCode
    property string doctorInstitutionAddress
    property string doctorInn
    property string doctorLicenseInfo

    property int buttonStandartTextFontSize: 10
    property int standartTextSize: 14

    // Область с данными текущего профиля
    Label {
        id: labelName

        font.pointSize: standartTextSize
        font.bold: true

        anchors.top: parent.top
        anchors.topMargin: 50

        anchors.left: parent.left
        anchors.leftMargin: 120

        anchors.horizontalCenter: parent.horizontalCenter

        text: "ФИО: "

        Label {
            text: doctorName

            font.bold: false

            anchors.fill: parent
            anchors.leftMargin: parent.anchors.leftMargin - 50
        }
    }

        Label {
            id: labelSpecialization

            font.pointSize: standartTextSize
            font.bold: true

            anchors.top: parent.top
            anchors.topMargin: 100

            anchors.left: parent.left
            anchors.leftMargin: 120

            anchors.horizontalCenter: parent.horizontalCenter

            text: "Специализация: "

            Label {
                text: doctorSpecialization

                font.bold: false

                anchors.fill: parent
                anchors.leftMargin: parent.anchors.leftMargin + 50
            }
        }

        Label {
            id: labelInstitutionName

            font.pointSize: standartTextSize
            font.bold: true

            anchors.top: parent.top
            anchors.topMargin: 150

            anchors.left: parent.left
            anchors.leftMargin: 120

            anchors.horizontalCenter: parent.horizontalCenter

            text: "Наименование учреждения: "

            Label {
                text: doctorInstitutionName

                font.bold: false

                anchors.fill: parent
                anchors.leftMargin: parent.anchors.leftMargin + 170
            }
        }

        Label {
            id: labelInstitutionCode

            font.pointSize: standartTextSize
            font.bold: true

            anchors.top: parent.top
            anchors.topMargin: 200

            anchors.left: parent.left
            anchors.leftMargin: 120

            anchors.horizontalCenter: parent.horizontalCenter

            text: "Код учреждения: "

            Label {
                text: doctorInstitutionCode

                font.bold: false

                anchors.fill: parent
                anchors.leftMargin: parent.anchors.leftMargin + 60
            }
        }

        Label {
            id: labelInstitutionAddress

            font.pointSize: standartTextSize
            font.bold: true

            anchors.top: parent.top
            anchors.topMargin: 250

            anchors.left: parent.left
            anchors.leftMargin: 120

            anchors.horizontalCenter: parent.horizontalCenter

            text: "Адрес учреждения: "

            Label {
                text: doctorInstitutionAddress

                font.bold: false

                anchors.fill: parent
                anchors.leftMargin: parent.anchors.leftMargin + 80
            }
        }

        Label {
            id: labelInn

            font.pointSize: standartTextSize
            font.bold: true

            anchors.top: parent.top
            anchors.topMargin: 300

            anchors.left: parent.left
            anchors.leftMargin: 120

            anchors.horizontalCenter: parent.horizontalCenter

            text: "ИНН: "

            Label {
                text: doctorInn

                font.bold: false

                anchors.fill: parent
                anchors.leftMargin: parent.anchors.leftMargin - 50
            }
        }


        Label {
            id: labelLicenseInfo

            font.pointSize: standartTextSize
            font.bold: true

            anchors.top: parent.top
            anchors.topMargin: 350

            anchors.left: parent.left
            anchors.leftMargin: 120

            anchors.horizontalCenter: parent.horizontalCenter

            text: "Лицензия: "

            Label {
                text: doctorInn

                font.bold: false

                anchors.fill: parent
                anchors.leftMargin: parent.anchors.leftMargin - 10
            }

            Button {
                id: button_change_info
                text: "Изменить профиль"

                font.pointSize: buttonStandartTextFontSize

                anchors.top: parent.top
                anchors.topMargin: 120

                width: 200
                height: 60

            }
        }
    }
