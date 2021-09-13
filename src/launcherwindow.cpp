#include <QString>
#include <QFileInfo>
#include <QDebug>

#include "launcherwindow.h"
#include "ui_launcherwindow.h"

LauncherWindow::LauncherWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LauncherWindow)
{
    ui->setupUi(this);

    QFileInfo checkDoctorDb("./doctors.csv");

    if (checkDoctorDb.exists() == false) {
        qDebug() << "\nFile: 'doctor.csv' database doesn't exists!";
    }

}

LauncherWindow::~LauncherWindow()
{
    delete ui;
}
