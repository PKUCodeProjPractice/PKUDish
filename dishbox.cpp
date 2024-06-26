﻿#include "dishbox.h"
#include "ui_dishbox.h"
#include <QTextStream>
#include <QGraphicsScene>
#include <QDebug>
#include "tags.h"

QString tasteToColor(const DishTasteTag *tag)
{
    switch (tag->taste) {
    case DishTaste::HEAVY_SPICY:
        return "\"color:rgba(225, 0, 0, 1);\"";
    case DishTaste::MIDDLE_SPICY:
        return "\"color:rgba(190, 0, 0, 1);\"";
    case DishTaste::LITTLE_SPICY:
        return "\"color:rgba(100, 0, 0, 1);\"";
    default:
    case DishTaste::NOT_SPICY:
        return "\"color:rgba(0, 0, 0, 1);\"";
    }
}

DishBox::DishBox(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DishBox)
    , hovered(false)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_Hover, true);
    this->installEventFilter(this);
}

DishBox::~DishBox()
{
    delete ui;
}

void DishBox::setDish(const Dish &dish)
{
    // picture
    QString filepath;
    QTextStream(&filepath)<<"://assets/imgs/"<<dish.id<<".png";
    QPixmap pixmp = QPixmap(filepath);
    if (pixmp.isNull())
        pixmp.load("://assets/icons/dish.png");

    QGraphicsScene *scene = new QGraphicsScene;
    scene->addPixmap(pixmp);
    ui->picture->setScene(scene);

    // background
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, QColor(255, 255, 255));
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    // text
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
        if (tag->kind == TagKind::TASTE)
            stream << "<span style=" << tasteToColor(static_cast<const DishTasteTag *>(tag)) << ">"
                   << tag->toString() << "</span>";
        else
            stream << tag->toString();
        sep = true;
    }

    ui->tags->setText(tags);
    ui->tags->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
}
