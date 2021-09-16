#ifndef MAIN_H
#define MAIN_H

#include <QtCore>
#include <QMessageBox>
#include <QString>
#include <QFileInfo>
#include <QDebug>

#include "profileregistrationwindow.h"

bool isDoctorsJsonDbExists() {
    QString appDir(QCoreApplication::applicationDirPath());

    QFileInfo doctorsDataBaseFile(appDir, "doctors.json");

    if (doctorsDataBaseFile.exists() == false) {
        qDebug() << "File: 'doctors.json' database doesn't exists!\n";
        return false;
    }
    else {
        qDebug() << "File: 'doctors.json' database exists!\n";
        return true;
    }

}

void createNewProfileMessageBox() {
    QMessageBox mb;

    mb.setText("Профиль отсутствует");
    mb.setInformativeText("В системе не обнаружено сохранённого профиля. Хотите создать новый?");

    mb.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    mb.setButtonText(QMessageBox::Ok, "Создать");
    mb.setButtonText(QMessageBox::Cancel, "Отмена");
    mb.setDefaultButton(QMessageBox::Ok);

    int pressed = mb.exec();

    switch(pressed) {
    case QMessageBox::Ok : {
        // enter to registration form
        qDebug() << "Salus: Open registration window...\n";
        ProfileRegistrationWindow* registrationWindow = new ProfileRegistrationWindow;
        registrationWindow->show();
        qDebug() << "Salus: Registration window opened successfully!\n";
        break;
    }

    case QMessageBox::Cancel :
        qDebug() << "Salus: Closing the window...\n";
        break;

    default :
        break;
    }

}


#endif // MAIN_H
