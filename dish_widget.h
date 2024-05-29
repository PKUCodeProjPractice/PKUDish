#ifndef DISH_WIDGET_H
#define DISH_WIDGET_H

#include <QWidget>

namespace Ui {
class dish_widget;
}

class dish_widget : public QWidget
{
    Q_OBJECT

public:
    explicit dish_widget(QWidget *parent = nullptr);
    ~dish_widget();

private:
    Ui::dish_widget *ui;
};

#endif // DISH_WIDGET_H
