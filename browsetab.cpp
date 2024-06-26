#include "browsetab.h"
#include "ui_browsetab.h"
#include "dishbox.h"
#include "dish.h"
#include "tags.h"
#include <algorithm>
#include <QCheckBox>

BrowseTab::BrowseTab(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BrowseTab)
{
    ui->setupUi(this);

    int cnt = 0;
    foreach (const auto &value, NAME_CANTEEN.keys())
    {
        QCheckBox *check = new QCheckBox(value);
        check->setChecked(true);
        ui->layout_canteen->addWidget(check, cnt / 6, cnt % 6);
        this->canteenCheck.insert(NAME_CANTEEN.value(value), check);
        cnt += 1;
    }

    cnt = 0;
    foreach (const auto &key, DISHKIND_NAME.keys())
    {
        QCheckBox *check = new QCheckBox(DISHKIND_NAME.value(key));
        check->setChecked(true);
        ui->layout_kind->addWidget(check, cnt / 5, cnt % 5);
        this->dishKindCheck.insert(key, check);
        cnt += 1;
    }

    cnt = 0;
    foreach (const auto &key, DISHTASTE_NAME.keys())
    {
        QCheckBox *check = new QCheckBox(DISHTASTE_NAME.value(key));
        check->setChecked(true);
        ui->layout_taste->addWidget(check, cnt / 5, cnt % 5);
        this->dishTasteCheck.insert(key, check);
        cnt += 1;
    }
}

BrowseTab::~BrowseTab()
{
    delete ui;
    foreach (DishBox *db, boxes)
    {
        delete db;
    }
}

void BrowseTab::setDishes(const Dishes &d)
{
    dishes = d;
    initBoxes();
    updateView(boxes);
}

void BrowseTab::updateView(QVector<DishBox *> &bxs)
{
    qDebug() << "remove widgets start, size =" << ui->gridLayout_scroll->count();
    QLayoutItem *w;
    while ((w = ui->gridLayout_scroll->takeAt(0)) != 0)
    {
        if (w->widget())
            w->widget()->setParent(NULL);
        delete w;
    }
    qDebug() << "remove widgets end";

    qDebug() << "add widgets start";
    int cnt = 0;
    foreach (DishBox *db, bxs)
    {
        ui->gridLayout_scroll->addWidget(
            db, cnt / 2, cnt % 2, Qt::AlignCenter
        );
        cnt += 1;
    }
    qDebug() << "add widgets end, size =" << cnt;
}

void BrowseTab::initBoxes()
{
    boxes.clear();
    foreach (const Dish &dish, dishes.getAllDishes())
    {
        DishBox *db = new DishBox(this);
        db->setDish(dish);
        if (db->hasPicture())
            boxes.prepend(db);
        else
            boxes.append(db);
    }
}

void BrowseTab::on_pushButton_search_clicked()
{
    QString query = ui->lineEdit_search->text().trimmed();
    double lwr = ui->doubleSpinBox_lwr->value();
    double upr = ui->doubleSpinBox_upr->value();

    QSet<Canteen> canteens;
    foreach (const auto &key, canteenCheck.keys())
    {
        if (canteenCheck.value(key)->isChecked())
            canteens.insert(key);
    }
    QSet<DishKind> kinds;
    foreach (const auto &key, dishKindCheck.keys())
    {
        if (dishKindCheck.value(key)->isChecked())
            kinds.insert(key);
    }
    QSet<DishTaste> tastes;
    foreach (const auto &key, dishTasteCheck.keys())
    {
        if (dishTasteCheck.value(key)->isChecked())
            tastes.insert(key);
    }

    auto pred = [&](const Dish &d) -> bool
    {
        if (query.size() && !matches(query, d.name, MatchMode::CONTAINS_ANY) ||
            d.price > upr || d.price < lwr ||
            !canteens.contains(d.canteen) ||
            !tastes.contains(d.getTaste()))
            return false;
        foreach (const DishTag *tag, d.tags)
        {
            if (tag->kind == TagKind::KIND &&
                kinds.contains(NAME_DISHKIND.value(tag->toString())))
                return true;
        }
        return false;
    };

    // Dishes result = dishes.filterGeneral(pred);
    qDebug() << "filter begin";
    QVector<DishBox *> result;
    foreach (DishBox *db, boxes)
    {
        if (pred(db->getDish()))
            result.append(db);
    }
    qDebug() << "filter end, size =" << result.size();

    qDebug() << "sort begin";
    bool ascending = ui->comboBox_order->currentIndex() == 1;
    // result.sortByPrice(ascending);
    if (ascending)
        std::sort(
            result.begin(), result.end(),
            [](const DishBox *db1, const DishBox *db2) {
                return (db1->getDish().price < db2->getDish().price);
            }
        );
    else
        std::sort(
            result.begin(), result.end(),
            [](const DishBox *db1, const DishBox *db2) {
                return (db1->getDish().price > db2->getDish().price);
            }
        );
    qDebug() << "sort end";

    // update
    updateView(result);
}

void BrowseTab::on_comboBox_order_currentIndexChanged(int index)
{
}

void BrowseTab::on_doubleSpinBox_lwr_valueChanged(double lwr)
{
    ui->doubleSpinBox_upr->setMinimum(lwr);
}

void BrowseTab::on_doubleSpinBox_upr_valueChanged(double upr)
{
    ui->doubleSpinBox_lwr->setMaximum(upr);
}

