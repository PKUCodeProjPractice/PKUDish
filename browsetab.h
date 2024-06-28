#ifndef BROWSETAB_H
#define BROWSETAB_H

#include <QMap>
#include <QLabel>
#include <QWidget>
#include <QVector>
#include <QCheckBox>
#include "dish.h"
#include "dishes.h"
#include "dishbox.h"
#include "tags.h"

namespace Ui {
class BrowseTab;
}

class BrowseTab : public QWidget
{
    Q_OBJECT

public:
    explicit BrowseTab(QWidget *parent = nullptr);
    ~BrowseTab();

    void setDishes(const Dishes &d);

private slots:

    void on_pushButton_search_clicked();

    void on_comboBox_order_currentIndexChanged(int index);

    void on_doubleSpinBox_lwr_valueChanged(double arg1);

    void on_doubleSpinBox_upr_valueChanged(double arg1);

private:
    Ui::BrowseTab *ui;
    QLabel *loadingLabel;

    Dishes dishes;
    QVector<DishBox *> boxes;

    QMap<Canteen, QCheckBox *> canteenCheck;
    QMap<DishKind, QCheckBox *> dishKindCheck;
    QMap<DishTaste, QCheckBox *> dishTasteCheck;

    void initBoxes();
    void clearView();
    void updateView(QVector<DishBox *> &bxs);
    void setLoading(bool loading);
};

#endif // BROWSETAB_H
