#ifndef _TAGS_H
#define _TAGS_H

#include<Qt>

enum class TagKind{
  KIND,
  TASTE,
  WAIT
};

struct DishTag{
  TagKind kind;
  protected:
  DishTag(TagKind _kind);
};

enum class DishKind{
  TAOCAN,
  ZHUSHI,
  SHAOKAO,
  TIANDIAN,
  ROU,
  CAI
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

#endif
