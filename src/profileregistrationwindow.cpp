#include <QDebug>

#include "profileregistrationwindow.h"
#include "ui_profileregistrationwindow.h"

ProfileRegistrationWindow::ProfileRegistrationWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProfileRegistrationWindow)
{
    ui->setupUi(this);
}

ProfileRegistrationWindow::~ProfileRegistrationWindow()
{
    delete ui;
}
