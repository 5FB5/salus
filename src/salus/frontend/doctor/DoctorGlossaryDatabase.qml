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

    ListView
    {
        id: listViewDiagnoses

        anchors
        {
            left: parent.left
            right: labelTitle.horizontalCenter
            top: labelTitle.bottom
            bottom: parent.bottom
            topMargin: 30
            bottomMargin: listViewBottomMargin
        }

        Rectangle
        {
            id: bg1

            anchors.fill: parent
            color: "#ff0000"
        }

        GlossaryEditPanel
        {
            id: editPanelDiagnoses

            anchors
            {
                top: parent.bottom
                left: parent.left
                right: parent.right
            }
        }
    }

    ListView
    {
        id: listViewTreatments

        anchors
        {
            left: labelTitle.horizontalCenter
            top: labelTitle.bottom
            bottom: parent.bottom
            topMargin: 30
            bottomMargin: listViewBottomMargin
        }
        width: parent.width / 2

        Rectangle
        {
            id: bg2

            anchors.fill: parent
            color: "#00ff00"
        }

        GlossaryEditPanel
        {
            id: editPanelTreatments

            anchors
            {
                top: parent.bottom
                left: parent.left
                right: parent.right
            }
        }
    }
}
