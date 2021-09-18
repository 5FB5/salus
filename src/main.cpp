#include <QApplication>

#include "main.h"
#include "launcherwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LauncherWindow lw;

    if (isDoctorsJsonExists() == false) {
        createNewProfileMessageBox();
    }
    else {
        lw.show();
    }

    return a.exec();
}
