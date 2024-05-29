#include "randomtab.h"
#include "ui_randomtab.h"

RandomTab::RandomTab(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RandomTab)
{
    ui->setupUi(this);
}

RandomTab::~RandomTab()
{
    delete ui;
}
