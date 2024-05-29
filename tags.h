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
  virtual QString toString() const = 0;
  protected:
  DishTag(TagKind _kind);
};

struct DishNormalTag:public DishTag{
  QString name;
  DishNormalTag(const QString & _name);
  QString toString() const;
};

enum class DishKind{
  TAOCAN,
  ZHUSHI,
  SHAOKAO,
  TIANDIAN,
  ROU,
  CAI
};

const QMap<DishKind, QString> DISHKIND_NAME={
  {DishKind::TAOCAN, "套餐"},
  {DishKind::ZHUSHI, "主食"},
  {DishKind::SHAOKAO, "烧烤"},
  {DishKind::TIANDIAN, "甜点"},
  {DishKind::ROU, "荤"},
  {DishKind::CAI, "素"}
};

const QMap<QString, DishKind> NAME_DISHKIND={
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
  QString toString() const;
};

enum class DishTaste{
  NOT_SPICY,
  LITTLE_SPICY,
  MIDDLE_SPICY,
  HEAVY_SPICY
};

bool operator<(const DishTaste & a, const DishTaste & b);

const QMap<DishTaste, QString> DISHTASTE_NAME={
  {DishTaste::NOT_SPICY, "不辣"},
  {DishTaste::LITTLE_SPICY, "微辣"},
  {DishTaste::MIDDLE_SPICY, "中辣"},
  {DishTaste::HEAVY_SPICY, "重辣"}
};

const QMap<QString, DishTaste> NAME_DISHTASTE={
  {"不辣", DishTaste::NOT_SPICY},
  {"微辣", DishTaste::LITTLE_SPICY},
  {"中辣", DishTaste::MIDDLE_SPICY},
  {"重辣", DishTaste::HEAVY_SPICY}
};

struct DishTasteTag:public DishTag{
  DishTaste taste;
  DishTasteTag(DishTaste _taste = DishTaste::NOT_SPICY);
  QString toString() const;
};

struct DishWaitTag:public DishTag{
  bool should_wait;
  DishWaitTag(bool _wait = false);
  QString toString() const;
};

extern QMap<QString, DishTag*> predefine_tags;

#endif
