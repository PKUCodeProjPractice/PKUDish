#ifndef RANDDISH_H
#define RANDDISH_H

#include"dish.h"
#include"dishes.h"

struct RandConfig{
    bool no_wait = false;
    bool has_pack = false;
    bool has_main = false;
    bool has_meat = false;
    bool has_vege = false;
    DishTaste upper_spicy = DishTaste::HEAVY_SPICY;
};

Dishes randChoice(Dishes & dishes, const RandConfig & config);

#endif // RANDDISH_H
