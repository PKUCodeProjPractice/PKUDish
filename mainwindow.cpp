#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dishfilehandler.h"
#include <QDebug>
#include <QString>
#include <QVector>

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
}

MainWindow::~MainWindow()
{
    delete ui;
    delete browseTab;
    delete randomTab;
}

void MainWindow::loadDishes()
{
    Dishes dishes;
    QVector<QString> files = {
        "dishes-jia1.csv",
        "dishes-jia2.csv",
        "dishes-jia3.csv",
        "dishes-nong1.csv",
        "dishes-nong2.csv",
        "dishes-yannan.csv"
    };
    foreach (const QString &f, files)
    {
        try
        {
            DishFileHandler::read("://assets/data/" + f, dishes);
        }
        catch (const DishFileException &e)
        {
            qDebug() << "error reading file:" << e.getMessage();
        }
    }

    randomTab->setDishes(dishes);
    browseTab->setDishes(dishes);
}
