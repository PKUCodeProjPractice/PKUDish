#ifndef DISHFILEH_H
#define DISHFILEH_H

#include <QMap>
#include <QString>
#include <QVector>
#include <QException>
#include "dish.h"
#include "dishes.h"

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

    static void read(const QString &path, Dishes &dishes);
    static void write(const QString &path, const Dishes &dishes);

    static const QMap<QString, void (*)(const QString &, Dishes &)> READ_MAP;
    static const QMap<QString, void (*)(const QString &, const Dishes &)> WRITE_MAP;

private:

    /****
     * TODO: Deprecated
     * TXT 格式
     * 每行一个菜品, 格式为
     *
     *   [name] TAB [price] TAB [canteen] TAB [tag1] WHITESPACE ... WHITESPACE [tagn]
     *
     * 主要标签之间用 TAB 分隔, 其他标签之间用 WHITESPACE 分隔.
     */
    static void readTXT(const QString &path, Dishes &dishes);
    static void writeTXT(const QString &path, const Dishes &dishes);

    /****
     * CSV 格式
     * 每行一个菜品, 格式为
     *
     *   [id], [name], [price], [canteen], [tag1] WHITESPACE ... WHITESPACE [tagn]
     *
     * 标签之间用 WHITESPACE 分隔.
     */
    static void readCSV(const QString &path, Dishes &dishes);
    static void writeCSV(const QString &path, const Dishes &dishes);
};

#endif // DISHFILEH_H
