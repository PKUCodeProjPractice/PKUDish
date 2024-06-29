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

    //
    QSizePolicy sp_retain = ui->scrollArea->sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);
    ui->scrollArea->setSizePolicy(sp_retain);

    // init filters
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

    // loading label
    loadingLabel = new QLabel(this);
    loadingLabel->setText(tr("加载菜品..."));
    loadingLabel->setStyleSheet("QLabel { color: #780000; font-size: 28px; }");
    loadingLabel->adjustSize();
    loadingLabel->hide();
}

BrowseTab::~BrowseTab()
{
    delete loadingLabel;
    delete ui;
    foreach (DishBox *db, boxes)
    {
        delete db;
    }
}

void BrowseTab::setDishes(const Dishes &d)
{
    setLoading(true);
    dishes = d;
    initBoxes();
    clearView();
    updateView(boxes);
    setLoading(false);
}

void BrowseTab::updateView(QVector<DishBox *> &bxs)
{
    int cnt = 0;
    foreach (DishBox *db, bxs)
    {
        db->show();
        ui->gridLayout_scroll->addWidget(
            db, cnt / 2, cnt % 2, Qt::AlignCenter
        );
        cnt += 1;
        QCoreApplication::processEvents();
    }
}

void BrowseTab::setLoading(bool loading)
{
    if (loading)
        loadingLabel->move(ui->scrollArea->mapToParent(ui->scrollArea->rect().center())
                           - loadingLabel->rect().center());
    loadingLabel->setVisible(loading);
    ui->scrollArea->setHidden(loading);
    ui->lineEdit_search->setDisabled(loading);
    ui->pushButton_search->setDisabled(loading);
    ui->groupBox_canteen->setDisabled(loading);
    ui->groupBox_kind->setDisabled(loading);
    ui->groupBox_price->setDisabled(loading);
    ui->groupBox_taste->setDisabled(loading);
}

void BrowseTab::initBoxes()
{
    boxes.clear();
    foreach (const Dish &dish, dishes.getAllDishes())
    {
        DishBox *db = new DishBox(this);
        db->hide();
        db->setDish(dish);
        if (db->hasPicture())
            boxes.prepend(db);
        else
            boxes.append(db);
        QCoreApplication::processEvents();
    }
}

void BrowseTab::clearView()
{
    QLayoutItem *w;
    while ((w = ui->gridLayout_scroll->takeAt(0)) != 0)
    {
        if (w->widget())
        {
            w->widget()->setParent(NULL);
            w->widget()->hide();
        }
        delete w;
        QCoreApplication::processEvents();
    }
}

void BrowseTab::on_pushButton_search_clicked()
{
    setLoading(true);

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
        if ((query.size() && !matches(query, d.name, MatchMode::CONTAINS_ANY)) ||
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
    QVector<DishBox *> result;
    foreach (DishBox *db, boxes)
    {
        if (pred(db->getDish()))
            result.append(db);
    }

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

    clearView();
    updateView(result);
    setLoading(false);
}

void BrowseTab::on_comboBox_order_currentIndexChanged(int)
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

void BrowseTab::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
    case Qt::Key_Enter:
    case Qt::Key_Return:{
        on_pushButton_search_clicked();
    }break;
    }
}
