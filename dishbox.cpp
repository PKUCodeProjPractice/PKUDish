#include "dishbox.h"
#include "ui_dishbox.h"
#include <QTextStream>

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
    ui->price->setText(dish.price);
    QTextStream tags;
    foreach (const QString &tag, dish.tags)
        tags << tag << " ";
    ui->tags->setText(tags.string());
}
