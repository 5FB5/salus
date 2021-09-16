#include <QtCore>
#include <QMessageBox>
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
}

LauncherWindow::~LauncherWindow()
{
    delete ui;
}
