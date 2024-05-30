#include "randomtab.h"
#include "ui_randomtab.h"

RandomTabCtrl::RandomTabCtrl(RandomTab* _view):view(_view){}
void RandomTabCtrl::view_reset(){view->reset();}

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

    controller.view_reset();
}

void RandomTab::reset(){
    // 初始化食堂列表
    ui->comboBox_canteen->setCurrentIndex(0);
    // 初始化价格
    ui->doubleSpinBox_priceLwr->setValue(0);
    ui->doubleSpinBox_priceUpr->setValue(0);
    // 初始化菜品类型
    ui->radioButton_single->setChecked(true);
    ui->radioButton_set->setChecked(false);
    // TODO: 清空之前的菜品
}

RandomTab::~RandomTab()
{
    delete ui;
}

RandConfig RandomTab::dumpConfig(){
    RandConfig config;

}
