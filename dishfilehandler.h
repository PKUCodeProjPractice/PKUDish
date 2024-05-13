#ifndef DISHFILEH_H
#define DISHFILEH_H

#include<QMap>
#include<QString>
#include<QVector>
#include<QException>
#include"dish.h"

class DishFileException : public QException
{
public:
    explicit DishFileException(const QString &msg = "") : message(msg) {}
    void raise() const override { throw *this; }
    const QString &getMessage() const { return message; }
    DishFileException *clone() const override { return new DishFileException(message); }
private:
    QString message;
};

class DishFileHandler
{
public:
    DishFileHandler();

    static QVector<Dish> read(const QString &path);
    static void write(const QString &path, const QVector<Dish> &dishes);

    static const QMap<QString, QVector<Dish> (*)(const QString &)> READ_MAP;
    static const QMap<QString, void (*)(const QString &, const QVector<Dish> &)> WRITE_MAP;

private:

    /****
     * TXT 格式
     * 每行一个菜品, 格式为
     *
     *   [name] TAB [price] TAB [canteen] TAB [tag1] WHITESPACE ... WHITESPACE [tagn]
     *
     * 主要标签之间用 TAB 分隔, 其他标签之间用 WHITESPACE 分隔.
     */
    static QVector<Dish> readTXT(const QString &path);
    static void writeTXT(const QString &path, const QVector<Dish> &dishes);
};

#endif // DISHFILEH_H
