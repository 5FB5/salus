import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import salus 1.0

import "components"

Page
{
    id: root

    property int buttonStandartTextFontSize: 10
    property int standartTextSize: 14
    property int listViewBottomMargin: 150

    Label
    {
        id: labelTitle

        anchors
        {
            top: parent.top
            topMargin: 20
            horizontalCenter: parent.horizontalCenter
        }
        font.pointSize: 20
        font.bold: true
        text: "Глоссарий"
    }

    Text
    {
        id: labelListViewDiagnoses

        anchors
        {
            top: labelListViewTreatments.top
            bottom: listViewDiagnoses.top
            bottomMargin: 20
            horizontalCenter: listViewDiagnoses.horizontalCenter
        }
        font.bold: true
        font.pixelSize: 25
        text: "Диагноз"
    }

    ListView
    {
        id: listViewDiagnoses

        anchors
        {
            left: parent.left
            right: labelTitle.horizontalCenter
            top: listViewTreatments.top
            bottom: parent.bottom
            bottomMargin: listViewBottomMargin
        }
        clip: true
        model: glossaryDiagnosesListModel
        spacing: 15

        delegate: Text
        {
            anchors
            {
                left: parent.left
                right: parent.right
                leftMargin: 10
                rightMargin: 10
            }
            width: parent.width
            wrapMode: Text.WrapAnywhere
            font.pixelSize: 17
            text: display
        }
    }

    GlossaryEditPanel
    {
        id: editPanelDiagnoses

        anchors
        {
            top: listViewDiagnoses.bottom
            left: listViewDiagnoses.left
            right: listViewDiagnoses.right
            topMargin: 5
        }
    }

    Text
    {
        id: labelListViewTreatments

        anchors
        {
           bottom: listViewTreatments.top
           bottomMargin: 20
           horizontalCenter: listViewTreatments.horizontalCenter
        }
        font.bold: true
        font.pixelSize: 25
        text: "Терапия"
    }

    ListView
    {
        id: listViewTreatments

        anchors
        {
            left: labelTitle.horizontalCenter
            right: parent.right
            top: labelTitle.bottom
            bottom: parent.bottom
            topMargin: 50
            bottomMargin: listViewBottomMargin
        }
        clip: true
        model: glossaryTreatmentsListModel
        spacing: 15

        delegate: Text
        {
            anchors
            {
                left: parent.left
                right: parent.right
                leftMargin: 10
                rightMargin: 10
            }
            width: parent.width
            wrapMode: Text.WrapAnywhere
            font.pixelSize: 17
            text: display
        }
    }

    GlossaryEditPanel
    {
        id: editPanelTreatments

        anchors
        {
            top: listViewTreatments.bottom
            left: listViewTreatments.left
            right: listViewTreatments.right
            topMargin: 5
        }
    }
}
