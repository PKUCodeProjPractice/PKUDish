#include "dishfilehandler.h"
#include<QFile>
#include<QFileInfo>
#include<QTextStream>

const QMap<QString, void (*)(const QString &, Dishes &)> DishFileHandler::READ_MAP =
{
    {"txt", &DishFileHandler::readTXT},
    {"csv", &DishFileHandler::readCSV}
};

const QMap<QString, void (*)(const QString &, const Dishes &)> DishFileHandler::WRITE_MAP =
{
    {"txt", &DishFileHandler::writeTXT},
    {"csv", &DishFileHandler::writeCSV}
};

DishFileHandler::DishFileHandler() { }

void DishFileHandler::read(const QString &path, Dishes &dishes)
{
    QFileInfo fileInfo(path);
    auto it = READ_MAP.find(fileInfo.suffix().toLower());
    if (it == READ_MAP.end())
    {
        DishFileException("不支持文件类型: " + fileInfo.suffix()).raise();
    }

    (*it)(path, dishes);
}

void DishFileHandler::write(const QString &path, const Dishes &dishes)
{
    QFileInfo fileInfo(path);
    auto it = WRITE_MAP.find(fileInfo.suffix());
    if (it == WRITE_MAP.end())
    {
        DishFileException("不支持文件类型: " + fileInfo.suffix()).raise();
    }

    (*it)(path, dishes);
}

void DishFileHandler::readTXT(const QString &path, Dishes &dishes)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        DishFileException("无法打开文件: " + file.errorString()).raise();
    }

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
        dishes.append(d);
    }
}

void DishFileHandler::writeTXT(const QString &path, const Dishes &dishes)
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        DishFileException("无法打开文件: " + file.errorString()).raise();
    }

    QTextStream out(&file);
    out.setRealNumberPrecision(2);
    foreach (const Dish &d, dishes.getAllDishes())
    {
        out << d.name << "\t" << d.price << "\t" << getCanteenName(d.canteen) << "\t";
        foreach (const QString &t, d.tags)
        {
            out << t << " ";
        }
        out << "\n";
    }
}

void DishFileHandler::readCSV(const QString &path, Dishes & dishes)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        DishFileException("无法打开文件: " + file.errorString()).raise();
    }

    QTextStream in(&file);
    while (!in.atEnd())
    {
        Dish d;
        QString line = in.readLine();
        QStringList strs = line.split(",", Qt::SkipEmptyParts);
        bool ok;

        if (strs.empty()) continue;
        d.id = strs.takeFirst().toInt(&ok);

        if (strs.empty() || !ok) DishFileException("文件内容格式错误").raise();
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
        dishes.append(d);
    }
}

void DishFileHandler::writeCSV(const QString &path, const Dishes &dishes)
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        DishFileException("无法打开文件: " + file.errorString()).raise();
    }

    QTextStream out(&file);
    out.setRealNumberPrecision(2);
    foreach (const Dish &d, dishes.getAllDishes())
    {
        out << d.id << "," << d.name << "," << d.price << "," << getCanteenName(d.canteen) << ",";
        foreach (const QString &t, d.tags)
        {
            out << t << " ";
        }
        out << "\n";
    }
}
