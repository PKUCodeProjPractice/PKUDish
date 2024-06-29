#include "loadingwidget.h"
#include "ui_loadingwidget.h"

LoadingWidget::LoadingWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoadingWidget)
{
    ui->setupUi(this);
}

LoadingWidget::~LoadingWidget()
{
    delete ui;
}

void LoadingWidget::setRange(int m, int M){
    ui->progressBar->setRange(m, M);
}

void LoadingWidget::setValue(int v){
    ui->progressBar->setValue(v);
    //QCoreApplication::processEvents();
}
