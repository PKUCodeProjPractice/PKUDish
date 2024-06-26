#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dishfilehandler.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(800, 600);

    browseTab = new BrowseTab();
    ui->tabWidget->addTab(browseTab, "浏览");
    randomTab = new RandomTab();
    ui->tabWidget->addTab(randomTab, "随机");

    // load dishes
    Dishes dishes;
    try
    {
        DishFileHandler::read("://assets/data/dishes-jia2.csv", dishes);
        DishFileHandler::read("://assets/data/dishes-nong2.csv", dishes);
    }
    catch (const DishFileException &e)
    {
        qDebug() << "error reading file:" << e.getMessage();
    }
    browseTab->setDishes(dishes);
    randomTab->setDishes(dishes);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete browseTab;
    delete randomTab;
}
