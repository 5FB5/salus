#ifndef MAIN_H
#define MAIN_H

#include <QtCore>
#include <QWidget>
#include <QMessageBox>
#include <QString>
#include <QFileInfo>
#include <QDebug>

#include "profileregistrationwindow.h"

QString getPathToApp() {
    return QCoreApplication::applicationDirPath();
}

bool isDoctorsJsonExists() {
    QFileInfo doctorsDataBaseFile(getPathToApp(), "doctors.json");

    if (doctorsDataBaseFile.exists() == false) {
        qDebug() << "File: 'doctors.json' database doesn't exists!\n";
        return false;
    }
    else {
        qDebug() << "File: 'doctors.json' database exists!\n";
        return true;
    }

}

QMessageBox* initializeMessageBox() {
    QMessageBox* m_mb = new QMessageBox;

    m_mb->setWindowTitle("Салюс");
    m_mb->setText("Профиль отсутствует");
    m_mb->setInformativeText("В системе не обнаружено сохранённого профиля. Хотите создать новый?");

    m_mb->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    m_mb->setButtonText(QMessageBox::Ok, "Создать");
    m_mb->setButtonText(QMessageBox::Cancel, "Отмена");
    m_mb->setDefaultButton(QMessageBox::Ok);

    return m_mb;
}

void createNewProfileMessageBox() {
    QMessageBox* mb = initializeMessageBox();

    int pressed = mb->exec();

    switch(pressed) {
        case QMessageBox::Ok : {

            mb->close();
            delete mb;
            qDebug() << "Salus: MessageBox closed and deleted!\n";

            qDebug() << "Salus: Opening registration window...\n";

            ProfileRegistrationWindow* rw = new ProfileRegistrationWindow;
            rw->show();
            qDebug() << "Salus: Registration window opened successfully!\n";

            // TODO: clear rw from memory

            break;
        }

        case QMessageBox::Cancel :
            qDebug() << "Salus: Closing the window...\n";

            QCoreApplication::quit();
            qDebug() << "Salus: Application is closed!\n";

            break;

        default :
            break;
        }

    }


#endif // MAIN_H
