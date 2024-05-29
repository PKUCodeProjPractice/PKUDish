#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dishfilehandler.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    browseTab = new BrowseTab;
    ui->tabWidget->addTab(browseTab, "浏览");
    randomTab = new RandomTab;
    ui->tabWidget->addTab(randomTab, "随机");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete browseTab;
    delete randomTab;
}
