#include"tags.h"

DishTag::DishTag(TagKind _kind):kind(_kind){}
DishKindTag::DishKindTag(DishKind _kind):DishTag(TagKind::KIND), dish_kind(_kind){}
DishTasteTag::DishTasteTag(DishTaste _taste):DishTag(TagKind::TASTE), taste(_taste){}
DishWaitTag::DishWaitTag(bool _wait):DishTag(TagKind::WAIT), should_wait(_wait){}
