#ifndef DISHBOX_H
#define DISHBOX_H

#include <QWidget>
#include "dish.h"

namespace Ui {
class DishBox;
}

class DishBox : public QWidget
{
    Q_OBJECT

public:
    explicit DishBox(QWidget *parent = nullptr);
    ~DishBox();

    void setDish(const Dish &dish);

private:
    Ui::DishBox *ui;
};

#endif // DISHBOX_H
