#include"dish.h"
#include<algorithm>

Canteen getCanteenFromName(const QString & name)
{
    auto iter = NAME_CANTEEN.find(name);
    if(iter != NAME_CANTEEN.end())return iter.value();
    return CANTEEN_UNDEF;
}

QString getCanteenName(const Canteen canteen)
{
    if(canteen == CANTEEN_UNDEF)return "未知";
    return CANTEEN_NAME[canteen];
}

DishTaste Dish::getTaste() const {
    auto iter = tags.begin();
    for(; iter != tags.end(); ++iter){
        if((*iter)->kind == TagKind::TASTE) break;
    }
    if(iter != tags.end()){
        return NAME_DISHTASTE[(*iter)->toString()];
    }
    return DishTaste::NOT_SPICY;
}
