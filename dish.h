#ifndef DISH_H
#define DISH_H

#include<QSet>
#include<QMap>
#include<QVector>
#include<QString>

/* 食堂定义
 * 如需修改请修改如下关联内容
 * enum Canteen
 * const QString CANTEEN_NAME
 * QMap<QString, Canteen> NAME_CANTEEN
 *
 * TODO: 添加食堂的不同层，例如家园一二三层
 */
enum Canteen{
    CANTEEN_XUE_YI = 0,
    CANTEEN_XUE_WU,
    CANTEEN_NONG_YUAN_YI_CENG,
    CANTEEN_NONG_YUAN_ER_CENG,
    CANTEEN_NONG_YUAN_SAN_CENG,
    CANTEEN_JIA_YUAN_YI_CENG,
    CANTEEN_JIA_YUAN_ER_CENG,
    CANTEEN_JIA_YUAN_SAN_CENG,
    CANTEEN_JIA_YUAN_SI_CENG,
    CANTEEN_YAN_NAN,
    CANTEEN_SONG_LIN,
    CANTEEN_UNDEF
};
const QString CANTEEN_NAME[CANTEEN_UNDEF] = {
    [CANTEEN_XUE_YI]             = "学一",
    [CANTEEN_XUE_WU]             = "学五",
    [CANTEEN_NONG_YUAN_YI_CENG]  = "农园一层",
    [CANTEEN_NONG_YUAN_ER_CENG]  = "农园二层",
    [CANTEEN_NONG_YUAN_SAN_CENG] = "农园三层",
    [CANTEEN_JIA_YUAN_YI_CENG]   = "家园一层",
    [CANTEEN_JIA_YUAN_ER_CENG]   = "家园二层",
    [CANTEEN_JIA_YUAN_SAN_CENG]  = "家园三层",
    [CANTEEN_JIA_YUAN_SI_CENG]   = "家园四层",
    [CANTEEN_YAN_NAN]            = "燕南",
    [CANTEEN_SONG_LIN]           = "松林"
};

// 不知道为什么, 要加个 const 才能编译过
const QMap<QString, Canteen> NAME_CANTEEN = {
    {"学一", CANTEEN_XUE_YI},
    {"学五", CANTEEN_XUE_WU},
    {"农园一层", CANTEEN_NONG_YUAN_YI_CENG},
    {"农园二层", CANTEEN_NONG_YUAN_ER_CENG},
    {"农园三层", CANTEEN_NONG_YUAN_SAN_CENG},
    {"家园一层", CANTEEN_JIA_YUAN_YI_CENG},
    {"家园二层", CANTEEN_JIA_YUAN_ER_CENG},
    {"家园三层", CANTEEN_JIA_YUAN_SAN_CENG},
    {"家园四层", CANTEEN_JIA_YUAN_SI_CENG},
    {"燕南", CANTEEN_YAN_NAN},
    {"松林", CANTEEN_SONG_LIN},
};
Canteen getCanteenFromName(const QString &name);
QString getCanteenName(const Canteen);

struct Dish
{
    int id;
    QString name;
    float price; // 感觉就两位小数不需要double
    Canteen canteen;
    QSet<QString> tags;
};

#endif // DISH_H
