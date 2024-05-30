#ifndef BROWSETAB_H
#define BROWSETAB_H

#include <QWidget>
#include <QVector>
#include "dishes.h"
#include "dishbox.h"

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
    void updateView();

private:
    Ui::BrowseTab *ui;
    Dishes dishes;
    QVector<DishBox *> boxes;
};

#endif // BROWSETAB_H
