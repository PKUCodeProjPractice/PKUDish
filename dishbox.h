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

protected:
    bool event(QEvent *event);
    void hoverEnter(QHoverEvent *event);
    void hoverLeave(QHoverEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    Ui::DishBox *ui;
    bool hovered;
};

#endif // DISHBOX_H
