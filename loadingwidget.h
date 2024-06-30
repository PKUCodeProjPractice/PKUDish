#ifndef LOADINGWIDGET_H
#define LOADINGWIDGET_H

#include <QWidget>

namespace Ui {
class LoadingWidget;
}

class LoadingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoadingWidget(QWidget *parent = nullptr);
    ~LoadingWidget();

    void setRange(int, int);
    void setValue(int);

private:
    Ui::LoadingWidget *ui;
};

#endif // LOADINGWIDGET_H
