#include "tab1.h"
#include "ui_tab1.h"

BrowseTab::BrowseTab(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BrowseTab)
{
    ui->setupUi(this);
}

BrowseTab::~BrowseTab()
{
    delete ui;
}
