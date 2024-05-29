#include "tab1.h"
#include "ui_tab1.h"

roll::roll(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::roll)
{
    ui->setupUi(this);
}

roll::~roll()
{
    delete ui;
}
