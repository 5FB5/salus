import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import salus 1.0

Page
{
    id: root

    property int buttonStandartTextFontSize: 10
    property int standartTextSize: 14

    signal openCurrentMedicalCard(string fullname)
    signal registerMedicalCard(string fullname)

    Label
    {
        id: labelTitle

        anchors
        {
            top: parent.top
            topMargin: 50
            horizontalCenter: parent.horizontalCenter
        }
        font.pointSize: 20
        font.bold: true
        text: "Поиск амбулаторной карты"
    }

    ComboBox
    {
        id: combobox_patients

        // Чтобы по умолчанию не выводилось ФИО из списка
        Component.onCompleted: function()
        {
            currentIndex = -1;
        }

        anchors
        {
            top: parent.top
            left: parent.left
            right: parent.right

            topMargin: 256
            leftMargin: 300
            rightMargin: 300
        }

        height: 50
        font.pointSize: standartTextSize
        editable: true
        model: patientListModel

        onAccepted: function()
        {
            console.log("Salus: [QML](ComboBox 'combobox_patients') - Patient accepted " + editText + "\n");
            find(editText) !== -1 ? openCurrentMedicalCard(editText) : registerMedicalCard(editText);
        }
    }
}
