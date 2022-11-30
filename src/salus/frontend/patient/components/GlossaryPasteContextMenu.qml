import QtQuick 2.0
import QtQuick.Controls 2.0
import salus 1.0

Item
{
    id: root

    signal openDiagnosesMenu()
    signal openTreatmentsMenu()
    signal openSymptomsMenu()

    function openMenu()
    {
        contextMenu.popup();
    }

    Menu
    {
        id: contextMenu

        MenuItem
        {
            text: "Вставить диагноз"

            onTriggered: function()
            {
                openDiagnosesMenu();
            }
        }

        MenuItem
        {
            text: "Вставить терапию"

            onTriggered: function()
            {
                openTreatmentsMenu();
            }
        }

        MenuItem
        {
            text: "Вставить симптом"

            onTriggered: function()
            {
                openSymptomsMenu();
            }
        }
    }
}
