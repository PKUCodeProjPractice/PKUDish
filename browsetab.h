#ifndef TAB1_H
#define TAB1_H

#include <QWidget>

namespace Ui {
class BrowseTab;
}

class BrowseTab : public QWidget
{
    Q_OBJECT

public:
    explicit BrowseTab(QWidget *parent = nullptr);
    ~BrowseTab();

private:
    Ui::BrowseTab *ui;
};

#endif // TAB1_H
