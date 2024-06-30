#ifndef RANDOMTAB_H
#define RANDOMTAB_H

#include <QWidget>
#include "randdish.h"

namespace Ui {
class RandomTab;
}

class RandomTab;

class RandomTabCtrl{
    RandomTab* view;
    Dishes dishes;
public:
    RandomTabCtrl(RandomTab* _view);
    void view_reset();
    void random_choice();
    void view_dish_reset();
    void setDishes(Dishes & _dishes);
};

class RandomTab : public QWidget
{
    Q_OBJECT

public:
    RandomTabCtrl controller;
    explicit RandomTab(QWidget *parent = nullptr);
    ~RandomTab();
    RandConfig dumpConfig();
    void reset();
    void dish_reset();
    void show_dishes(const Dishes & dishes);
    void setDishes(Dishes & _dishes);

private:
    Ui::RandomTab *ui;

private slots:
    void keyPressEvent(QKeyEvent *) override;
};

#endif // RANDOMTAB_H
