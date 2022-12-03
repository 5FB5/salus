import QtQuick 2.0
import QtQuick.Controls 2.0
import salus 1.0

Item
{
    id: root

    signal openGlossaryMenu(int type);
    signal openAddTextToGlossaryMenu();

    function openMenu()
    {
        contextMenu.popup();
    }

    Menu
    {
        id: contextMenu

        MenuItem
        {
            id: menuAddTextToGlossary

            text: "Добавить текст в глоссарий"

            onTriggered: function()
            {
                openAddTextToGlossaryMenu();
            }
        }

        Menu
        {
            id: menuInsert

            title: "Вставить"

            MenuItem
            {
                text: "Диагноз"

                onTriggered: function()
                {
                    openGlossaryMenu(0);
                }
            }

            MenuItem
            {
                text: "Терапию"

                onTriggered: function()
                {
                    openGlossaryMenu(1);
                }
            }

            MenuItem
            {
                text: "Симптом"

                onTriggered: function()
                {
                    openGlossaryMenu(2);
                }
            }

            MenuItem
            {
                text: "Свою формулировку"

                onTriggered: function()
                {
                    openGlossaryMenu(3);
                }
            }
        }
    }
}
