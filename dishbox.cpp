#include "dishbox.h"
#include "ui_dishbox.h"
#include <QTextStream>
#include "tags.h"

DishBox::DishBox(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DishBox)
{
    ui->setupUi(this);
}

DishBox::~DishBox()
{
    delete ui;
}

void DishBox::setDish(const Dish &dish)
{
    ui->name->setText(dish.name);
    ui->canteen->setText(getCanteenName(dish.canteen));
    ui->price->setText(QString::number(dish.price));
    QTextStream tags;
    foreach (const DishTag *tag, dish.tags)
        tags << tag->toString() << " ";
    QString tagsStr;
    tags >> tagsStr;
    ui->tags->setText(tagsStr);
}
