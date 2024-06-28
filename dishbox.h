#ifndef DISHBOX_H
#define DISHBOX_H

#include <QWidget>
#include <QEvent>
#include <QHoverEvent>
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
    const Dish& getDish() const;
    bool hasPicture() const;

protected:

private:
    Ui::DishBox *ui;
    Dish dish;
    bool hovered;
    bool picture;
};

#endif // DISHBOX_H
