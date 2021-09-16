#include "main.h"
#include "launcherwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LauncherWindow launcherWindow;

    if (isDoctorsJsonDbExists() == true) {
        // enter to the system
        launcherWindow.show();
    }
    else {
        // create new profile
        createNewProfileMessageBox();
    }

    return a.exec();
}
