#include "dishfilehandler.h"
#include<QFile>
#include<QFileInfo>
#include<QTextStream>

const QMap<QString, QVector<Dish> (*)(const QString &)> DishFileHandler::READ_MAP =
{
    {"txt", &DishFileHandler::readTXT}
};

const QMap<QString, void (*)(const QString &, const QVector<Dish> &)> DishFileHandler::WRITE_MAP =
{
    {"txt", &DishFileHandler::writeTXT}
};

DishFileHandler::DishFileHandler() { }

QVector<Dish> DishFileHandler::read(const QString &path)
{
    QFileInfo fileInfo(path);
    auto it = READ_MAP.find(fileInfo.suffix());
    if (it == READ_MAP.end())
    {
        DishFileException("不支持文件类型: " + fileInfo.suffix()).raise();
    }

    return (*it)(path);
}

void DishFileHandler::write(const QString &path, const QVector<Dish> &dishes)
{
    QFileInfo fileInfo(path);
    auto it = WRITE_MAP.find(fileInfo.suffix());
    if (it == WRITE_MAP.end())
    {
        DishFileException("不支持文件类型: " + fileInfo.suffix()).raise();
    }

    return (*it)(path, dishes);
}

QVector<Dish> DishFileHandler::readTXT(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        DishFileException("无法打开文件: " + file.errorString()).raise();
    }

    QVector<Dish> dishes;
    QTextStream in(&file);
    while (!in.atEnd())
    {
        Dish d;
        QString line = in.readLine();
        QStringList strs = line.split("\t", Qt::SkipEmptyParts);
        bool ok;

        if (strs.empty()) continue;
        d.name = strs.takeFirst();

        if (strs.empty()) DishFileException("文件内容格式错误").raise();
        d.price = strs.takeFirst().toFloat(&ok);

        if (strs.empty() || !ok) DishFileException("文件内容格式错误").raise();
        d.canteen = getCanteenFromName(strs.takeFirst());

        if (!strs.empty())
        {
            foreach (const QString &s, strs.first().split(" ", Qt::SkipEmptyParts))
                d.tags.insert(s);
        }
        dishes.push_back(d);
    }

    return dishes;
}

void DishFileHandler::writeTXT(const QString &path, const QVector<Dish> &dishes)
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        DishFileException("无法打开文件: " + file.errorString()).raise();
    }

    QTextStream out(&file);
    out.setRealNumberPrecision(2);
    foreach (const Dish &d, dishes)
    {
        out << d.name << "\t" << d.price << "\t" << getCanteenName(d.canteen) << "\t";
        foreach (const QString &t, d.tags)
        {
            out << t << " ";
        }
        out << "\n";
    }
}
