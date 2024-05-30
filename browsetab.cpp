#include "browsetab.h"
#include "ui_browsetab.h"
#include "dishbox.h"

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

void BrowseTab::setDishes(const Dishes &d)
{
    dishes = d;
    updateView();
}

void BrowseTab::updateView()
{
    QLayoutItem *w;
    while ((w = ui->gridLayout_scroll->takeAt(0)) != 0)
    {
        if (w->widget())
            w->widget()->setParent(NULL);
        delete w;
    }

    int cnt = 0;
    foreach (const Dish &dish, dishes.getAllDishes())
    {
        DishBox *db = new DishBox(this);
        db->setDish(dish);
        ui->gridLayout_scroll->addWidget(
            db, cnt / 2, cnt % 2, Qt::AlignCenter
        );
        cnt += 1;
    }
}
