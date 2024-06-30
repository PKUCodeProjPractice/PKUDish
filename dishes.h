#ifndef DISHES_H
#define DISHES_H
#include "dish.h"
#include <QMap>
#include <QVector>

/**
 * 搜索(字符串)的匹配模式
 *
 *   搜索词 query 为 空格 连接的若干关键词
 *   待匹配项 target 为字符串或字符串组
 *
 * PRECISE: query 的 所有关键字 能在 某一个 target 中找到
 * CONTAINS_ALL: query 的 所有关键字 都能在 target 中找到
 * CONTAINS_ANY: query 的 某个关键词 能在 target 中找到
 */
enum class MatchMode
{
    PRECISE,
    CONTAINS_ALL,
    CONTAINS_ANY,
};
bool matches(const QString &query, const QString &target, MatchMode mode);
bool matches(const QString &query, const DishTag* const &target, MatchMode mode);
bool matches(const QString &query, const QSet<DishTag*> &target, MatchMode mode);

class Dishes
{
public:

    Dishes();
    ~Dishes();

    int size() const;
    bool empty() const;
    void clear();

    /**
     * 移除一个 Dish, 并返回.
     * 如果 id 的 Dish 不存在, 则返回 std::nullopt.
     * 注意检查返回值是否为空.
     */
    std::optional<Dish> remove(int id);
    /**
     * 添加一个 Dish, 不检查 id 唯一性.
     */
    void append(const Dish &d);
    /**
     * 用 Dish 替换列表中 id 相同的 Dish.
     * 如果没有 id 相同的 Dish, 则和 append 相同.
     */
    void replace(const Dish &d);

    /**
     * 注意检查返回值是否为空.
     */
    std::optional<Dish> get(int id) const;
    const QVector<Dish> &getAllDishes() const;

    /**
     * 返回满足相应条件的所有 Dish.
     */
    Dishes filterPrice(float lwr, float upr) const;
    Dishes filterCanteen(Canteen c) const;
    Dishes searchInName(const QString &query, MatchMode mode = MatchMode::CONTAINS_ANY) const;
    Dishes searchInTags(const QString &query, MatchMode mode = MatchMode::CONTAINS_ANY) const;
    Dishes searchInNameOrTags(const QString &query, MatchMode mode = MatchMode::CONTAINS_ANY) const;

    template<typename Predicate>
    Dishes filterGeneral(Predicate f){
        Dishes ret;
        foreach (const Dish &d, dishes)
        {
            if (f(d))
            {
                ret.append(d);
            }
        }
        return ret;
    }

    /**
     * 对自身排序.
     * 默认为升序.
     */
    void sortByName(bool reverse = false);
    void sortByPrice(bool reverse = false);

private:
    QVector<Dish> dishes;
};


#endif // DISHES_H
