#include<optional>
#include<random>
#include"randdish.h"
using namespace std;

// 不在头文件中
optional<Dish> randChoiceOneFromTag(Dishes & dishes, const QString & tag, Canteen & canteen){
    // 初始化随机数
    default_random_engine gen;
    gen.seed(time(0));
    Dishes filt;
    if(canteen != CANTEEN_UNDEF){
        filt = dishes.filterCanteen(canteen); // 这个if或许可以通过修改过滤的实现方式合并
    }else{
        filt = dishes;
    }
    if(filt.size() <= 0) return nullopt;
    filt = filt.searchInTags(tag);
    if(filt.size() <= 0) return nullopt;
    uniform_int_distribution distrib(0, filt.size());
    Dish choice = dishes.getAllDishes()[distrib(gen)];
    if(canteen == CANTEEN_UNDEF){
        canteen = choice.canteen;
    }
    return choice;
}

// 不在头文件中
void appendDishChoice(Dishes & res, Dishes & dishes, const QString & tag, Canteen & canteen){
    auto dish = randChoiceOneFromTag(dishes, tag, canteen);
    if(dish.has_value()){
        res.append(dish.value());
    }else{
        // TODO:这里可能得加个报错，用来在前端显示
    }
}

Dishes randChoice(Dishes & dishes, const RandConfig & config){
    // 首先先进行针对单菜品的筛选
    Dishes filt;
    // 等待时间
    if(config.no_wait){
        Dishes rev = dishes.searchInTags("需要等待");
        filt = dishes;
        for(const Dish & d:rev.getAllDishes()){
            dishes.remove(d.id);
        }
    }
    // 接着根据辣度筛选
    filt = filt.filterGeneral([&](const Dish & d) -> bool {return d.getTaste() < config.upper_spicy or d.getTaste() == config.upper_spicy;});
    // 选择一个菜品，查看它的食堂; 用第一个菜确定食堂
    Dishes res;
    Canteen canteen = CANTEEN_UNDEF;
    if(config.has_pack)appendDishChoice(res, filt, "套餐", canteen);
    if(config.has_main)appendDishChoice(res, filt, "主食", canteen);
    if(config.has_meat)appendDishChoice(res, filt, "荤", canteen);
    if(config.has_vege)appendDishChoice(res, filt, "素", canteen);
    return res;
}
