#ifndef _TAGS_H
#define _TAGS_H

#include<QString>
#include<QMap>

enum class TagKind{
  KIND,
  TASTE,
  WAIT,
  NORMAL
};

struct DishTag{
  TagKind kind;
  protected:
  DishTag(TagKind _kind);
};

struct DishNormalTag:public DishTag{
  QString name;
  DishNormalTag(QString & _name);
};

enum class DishKind{
  TAOCAN,
  ZHUSHI,
  SHAOKAO,
  TIANDIAN,
  ROU,
  CAI
};

QMap<DishKind, QString> DISHKIND_NAME={
    {DishKind::TAOCAN, "套餐"},
    {DishKind::ZHUSHI, "主食"},
    {DishKind::SHAOKAO, "烧烤"},
    {DishKind::TIANDIAN, "甜点"},
    {DishKind::ROU, "荤"},
    {DishKind::CAI, "素"}
};

QMap<QString, DishKind> NAME_DISHKIND={
    {"套餐", DishKind::TAOCAN},
    {"主食", DishKind::ZHUSHI},
    {"烧烤", DishKind::SHAOKAO},
    {"甜点", DishKind::TIANDIAN},
    {"荤", DishKind::ROU},
    {"素", DishKind::CAI}
};

struct DishKindTag:public DishTag{
  DishKind dish_kind;
  DishKindTag(DishKind _kind);
};

enum class DishTaste{
  NOT_SPICY,
  LITTLE_SPICY,
  MIDDLE_SPICY,
  HEAVY_SPICY
};

struct DishTasteTag:public DishTag{
  DishTaste taste;
  DishTasteTag(DishTaste _taste = DishTaste::NOT_SPICY);
};

struct DishWaitTag:public DishTag{
  bool should_wait;
  DishWaitTag(bool _wait = false);
};

extern QMap<QString, DishKindTag*> predefine_tags;

#endif
