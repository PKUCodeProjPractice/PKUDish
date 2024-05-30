﻿#include "dishbox.h"
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
    ui->textBrowser->setText(dish.name);
    ui->textBrowser->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    ui->canteen->setText(getCanteenName(dish.canteen));
    ui->canteen->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    ui->price->setText(QString::number(dish.price) + tr("元"));
    ui->price->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    bool sep = false;
    QString tags;
    QTextStream stream(&tags);
    foreach (const DishTag *tag, dish.tags)
    {
        if (sep) stream << " ";
        stream << tag->toString();
        sep = true;
    }

    ui->tags->setText(tags);
    ui->tags->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
}
