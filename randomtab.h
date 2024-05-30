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
public:
    RandomTabCtrl(RandomTab* _view);
    void view_reset();
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

private:
    Ui::RandomTab *ui;
};

#endif // RANDOMTAB_H
