#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "randomtab.h"
#include "tab1.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    BrowseTab *browseTab;
    RandomTab *randomTab;
};
#endif // MAINWINDOW_H
