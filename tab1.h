#ifndef TAB1_H
#define TAB1_H

#include <QWidget>

namespace Ui {
class roll;
}

class roll : public QWidget
{
    Q_OBJECT

public:
    explicit roll(QWidget *parent = nullptr);
    ~roll();

private:
    Ui::roll *ui;
};

#endif // TAB1_H
