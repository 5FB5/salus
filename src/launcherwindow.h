#ifndef LAUNCHERWINDOW_H
#define LAUNCHERWINDOW_H

#include <QWidget>

namespace Ui {
class LauncherWindow;
}

class LauncherWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LauncherWindow(QWidget *parent = nullptr);
    ~LauncherWindow();

private:
    Ui::LauncherWindow *ui;
};

#endif // LAUNCHERWINDOW_H
