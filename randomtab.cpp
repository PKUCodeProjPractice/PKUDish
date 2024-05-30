#include "randomtab.h"
#include "ui_randomtab.h"

RandomTabCtrl::RandomTabCtrl(const RandomTab* _view):view(_view){}

RandomTab::RandomTab(QWidget *parent)
    : QWidget(parent)
    , controller(this)
    , ui(new Ui::RandomTab)
{
    ui->setupUi(this);
}

RandomTab::~RandomTab()
{
    delete ui;
}

RandConfig RandomTab::dumpConfig(){
    RandConfig config;

}
