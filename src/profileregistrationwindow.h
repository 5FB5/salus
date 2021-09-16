#ifndef PROFILEREGISTRATIONWINDOW_H
#define PROFILEREGISTRATIONWINDOW_H

#include <QWidget>

namespace Ui {
class ProfileRegistrationWindow;
}

class ProfileRegistrationWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ProfileRegistrationWindow(QWidget *parent = nullptr);
    ~ProfileRegistrationWindow();

private:
    Ui::ProfileRegistrationWindow *ui;
};

#endif // PROFILEREGISTRATIONWINDOW_H
