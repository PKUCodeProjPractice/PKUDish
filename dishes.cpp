#include "dishes.h"
#include "optional"
#include "algorithm"
#include <QDebug>

Dishes::Dishes()
{

}

Dishes::~Dishes()
{

}

int Dishes::size() const
{
    return dishes.size();
}

bool Dishes::empty() const
{
    return dishes.size() == 0;
}

void Dishes::clear()
{
    dishes.clear();
}

std::optional<Dish> Dishes::remove(int id)
{
    for (auto it = dishes.begin(); it != dishes.end(); ++it)
    {
        if (it->id != id) continue;
        dishes.erase(it);
        return *it;
    }
    return std::nullopt;
}

void Dishes::append(const Dish &d)
{
    dishes.append(d);
}

std::optional<Dish> Dishes::get(int id) const
{
    for (auto it = dishes.constBegin(); it != dishes.constEnd(); ++it)
    {
        if (it->id != id) continue;
        return *it;
    }
    return std::nullopt;
}

const QVector<Dish> &Dishes::getAllDishes() const
{
    return dishes;
}

Dishes Dishes::searchInName(const QString &query, MatchMode mode) const
{
    Dishes ret;
    foreach (const Dish &d, dishes)
    {
        if (matches(query, d.name, mode))
        {
            ret.append(d);
        }
    }
    return ret;
}

Dishes Dishes::filterPrice(float lwr, float upr) const
{
    Dishes ret;
    foreach (const Dish &d, dishes)
    {
        if (d.price <= upr && d.price >= lwr)
            ret.append(d);
    }
    return ret;
}

Dishes Dishes::filterCanteen(Canteen c) const
{
    Dishes ret;
    foreach (const Dish &d, dishes)
    {
        if (d.canteen == c)
            ret.append(d);
    }
    return ret;
}

Dishes Dishes::searchInTags(const QString &query, MatchMode mode) const
{
    Dishes ret;
    foreach (const Dish &d, dishes)
    {
        if (matches(query, d.tags, mode))
        {
            ret.append(d);
        }
    }
    return ret;
}

Dishes Dishes::searchInNameOrTags(const QString &query, MatchMode mode) const
{
    Dishes ret;
    foreach (const Dish &d, dishes)
    {
        if (matches(query, d.name, mode) || matches(query, d.tags, mode))
        {
            ret.append(d);
        }
    }
    return ret;
}

void Dishes::sortByName(bool reverse)
{
    if (!reverse)
        std::sort(dishes.begin(), dishes.end(), [](const Dish &d1, const Dish &d2) {
            return d1.name < d2.name;
        });
    else
        std::sort(dishes.begin(), dishes.end(), [](const Dish &d1, const Dish &d2) {
            return d1.name > d2.name;
        });
}

void Dishes::sortByPrice(bool reverse)
{
    if (!reverse)
        std::sort(dishes.begin(), dishes.end(), [](const Dish &d1, const Dish &d2) {
            return d1.price < d2.price;
        });
    else
        std::sort(dishes.begin(), dishes.end(), [](const Dish &d1, const Dish &d2) {
            return d1.price > d2.price;
        });
}

bool matches(const QString &query, const QString &target, MatchMode mode)
{
    switch (mode)
    {
    case MatchMode::PRECISE:
    case MatchMode::CONTAINS_ALL:
        foreach (const QString &q, query.split(" ", Qt::SkipEmptyParts))
        {
            if (!target.contains(q))
                return false;
        }
        return true;

    case MatchMode::CONTAINS_ANY:
        foreach (const QString &q, query.split(" ", Qt::SkipEmptyParts))
        {
            if (target.contains(q))
                return true;
        }
        return false;

    default:
        return false;
    }
}

bool matches(const QString &query, const QSet<QString> &target, MatchMode mode)
{
    switch (mode)
    {
    case MatchMode::PRECISE:
        foreach (const QString &t, target)
        {
            if (matches(query, t, MatchMode::PRECISE))
                return true;
        }
        return false;

    case MatchMode::CONTAINS_ALL:
        foreach (const QString &q, query.split(" ", Qt::SkipEmptyParts))
        {
            bool found = false;
            foreach (const QString &t, target)
            {
                if (!t.contains(q)) continue;
                found = true;
                break;
            }
            if (!found)
                return false;
        }
        return true;

    case MatchMode::CONTAINS_ANY:
        foreach (const QString &q, query.split(" ", Qt::SkipEmptyParts))
        {
            foreach (const QString &t, target)
            {
                if (t.contains(q))
                    return true;
            }
        }
        return false;

    default:
        return false;
    }
}
