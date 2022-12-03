import QtQuick 2.0
import QtQuick.Controls 2.0
import salus 1.0

Item
{
    id: root

    signal openGlossaryMenu(int type);

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
                openGlossaryMenu(0);
            }
        }

        MenuItem
        {
            text: "Вставить терапию"

            onTriggered: function()
            {
                openGlossaryMenu(1);
            }
        }

        MenuItem
        {
            text: "Вставить симптом"

            onTriggered: function()
            {
                openGlossaryMenu(2);
            }
        }

        MenuItem
        {
            text: "Вставить свою формулировку"

            onTriggered: function()
            {
                openGlossaryMenu(3);
            }
        }
    }
}
