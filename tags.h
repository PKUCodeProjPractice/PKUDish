#ifndef _TAGS_H
#define _TAGS_H

enum class TagKind{
  KIND,
  TASTE,
  WAIT
};

struct DishTag{
  TagKind kind;
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
};

enum class DishTaste{
  NOT_SPICY,
  LITTLE_SPICY,
  MIDDLE_SPICY,
  HEAVY_SPICY
};

struct DishTasteTag:public DishTag{
  DishTaste taste;
  public:
};

struct DishWaitTag:public DishTag{
  bool should_wait;
};

#endif