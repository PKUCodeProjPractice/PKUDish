#ifndef RANDOMTAB_H
#define RANDOMTAB_H

#include <QWidget>

namespace Ui {
class RandomTab;
}

class RandomTab : public QWidget
{
    Q_OBJECT

public:
    explicit RandomTab(QWidget *parent = nullptr);
    ~RandomTab();

private:
    Ui::RandomTab *ui;
};

#endif // RANDOMTAB_H
