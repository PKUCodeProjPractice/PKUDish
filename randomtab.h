#ifndef RANDOMTAB_H
#define RANDOMTAB_H

#include <QWidget>
#include "randdish.h"

namespace Ui {
class RandomTab;
}

class RandomTab;

class RandomTabCtrl{
    const RandomTab* view;
public:
    RandomTabCtrl(const RandomTab* _view);
};

class RandomTab : public QWidget
{
    Q_OBJECT

public:
    RandomTabCtrl controller;
    explicit RandomTab(QWidget *parent = nullptr);
    ~RandomTab();
    RandConfig dumpConfig();

private:
    Ui::RandomTab *ui;
};

#endif // RANDOMTAB_H
