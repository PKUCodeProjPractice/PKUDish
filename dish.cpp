#include"dish.h"
using namespace std;

Canteen getCanteenFromName(const string & name){
    auto iter = NAME_CANTEEN.find(name);
    if(iter != NAME_CANTEEN.end())return iter->second;
    return CANTEEN_UNDEF;
}

string getCanteenName(const Canteen canteen){
    if(canteen == CANTEEN_UNDEF)return "未知";
    return CANTEEN_NAME[canteen];
}
