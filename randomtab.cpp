#include "randomtab.h"
#include "ui_randomtab.h"
#include "dishbox.h"

RandomTabCtrl::RandomTabCtrl(RandomTab* _view):view(_view){}
void RandomTabCtrl::view_reset(){view->reset();}
void RandomTabCtrl::view_dish_reset(){view->dish_reset();}
void RandomTabCtrl::setDishes(Dishes & _dishes){dishes = _dishes;}
void RandomTabCtrl::random_choice(){
    view_dish_reset();
    RandConfig config = view->dumpConfig();
    Dishes _dishes = randChoice(dishes, config);
    view->show_dishes(_dishes);
}

RandomTab::RandomTab(QWidget *parent)
    : QWidget(parent)
    , controller(this)
    , ui(new Ui::RandomTab)
{
    ui->setupUi(this);

    // 初始化食堂列表
    ui->comboBox_canteen->addItem(getCanteenName(CANTEEN_UNDEF));
    for(auto iter = NAME_CANTEEN.begin(); iter != NAME_CANTEEN.end(); ++iter){
        ui->comboBox_canteen->addItem(iter.key());
    }

    connect(ui->reset, &QPushButton::clicked, [&](){controller.view_reset();});
    connect(ui->confirm, &QPushButton::clicked, [&](){controller.random_choice();});

    controller.view_reset();
}

void RandomTab::setDishes(Dishes & _dishes){
    controller.setDishes(_dishes);
}

void RandomTab::reset(){
    // 初始化食堂列表
    ui->comboBox_canteen->setCurrentIndex(0);
    // 初始化价格
    ui->doubleSpinBox_priceLwr->setValue(0);
    ui->doubleSpinBox_priceUpr->setValue(100);
    // 初始化菜品类型
    ui->radioButton_single->setChecked(true);
    ui->radioButton_set->setChecked(false);
    // 清空之前的菜品
    dish_reset();
}

void RandomTab::dish_reset(){
    QLayoutItem *w;
    while ((w = ui->gridLayout->takeAt(0)) != 0)
    {
        if (w->widget())
            w->widget()->setParent(NULL);
        delete w;
    }
}

RandomTab::~RandomTab()
{
    delete ui;
}

RandConfig RandomTab::dumpConfig(){
    RandConfig config;
    config.canteen = getCanteenFromName(ui->comboBox_canteen->currentText());
    config.total_price_lower = ui->doubleSpinBox_priceLwr->value();
    config.total_price_upper = ui->doubleSpinBox_priceUpr->value();
    config.has_pack = ui->radioButton_set->isChecked();
    config.has_main = config.has_meat = config.has_vege = ui->radioButton_single->isChecked();
    return config;
}

void RandomTab::show_dishes(const Dishes & dishes){
    dish_reset();
    int cnt = 0;
    foreach (const Dish &dish, dishes.getAllDishes())
    {
        DishBox *db = new DishBox(this);
        db->setDish(dish);
        ui->gridLayout->addWidget(
            db, cnt / 2, cnt % 2, Qt::AlignCenter
            );
        cnt += 1;
    }
}
