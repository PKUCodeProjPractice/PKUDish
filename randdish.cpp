#include<optional>
#include<random>
#include"randdish.h"
#include<iostream>
using namespace std;

// 不在头文件中
optional<Dish> randChoiceOneFromTag(Dishes & dishes, const QString & tag, Canteen & canteen){
    // 初始化随机数
    default_random_engine gen;
    Dishes filt;
    if(canteen != CANTEEN_UNDEF){
        filt = dishes.filterCanteen(canteen); // 这个if或许可以通过修改过滤的实现方式合并
    }else{
        filt = dishes;
    }
    if(filt.size() <= 0) return nullopt;
    filt = filt.searchInTags(tag);
    cout << filt.size() << endl;
    if(filt.size() <= 0) return nullopt;
    uniform_int_distribution distrib(0, filt.size());
    gen.seed(time(0));
    distrib(gen); // 我也不知道为啥一定得先吐出来一个数才能做到随机
    Dish choice = filt.getAllDishes()[distrib(gen)];
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
        cout << "没有符合要求的菜" << endl;
        // TODO:这里可能得加个报错，用来在前端显示
    }
}

Dishes randChoice(Dishes & dishes, const RandConfig & config){
    // 首先先进行针对单菜品的筛选
    Dishes filt = dishes;
    // 等待时间
    if(config.no_wait){
        Dishes rev = dishes.searchInTags("需要等待");
        for(const Dish & d:rev.getAllDishes()){
            dishes.remove(d.id);
        }
    }
    // 接着根据辣度筛选
    filt = filt.filterGeneral([&](const Dish & d) -> bool {return d.getTaste() < config.upper_spicy or d.getTaste() == config.upper_spicy;});
    // 还有菜品价格
    // TODO: 这个菜品价格有点问题，它筛的是单品
    filt = filt.filterGeneral([&](const Dish & d) -> bool {return d.price >= config.total_price_lower and d.price <= config.total_price_upper;});
    // 选择一个菜品，查看它的食堂; 用第一个菜确定食堂
    cout << filt.size() << endl;
    Dishes res;
    Canteen canteen = config.canteen;
    if(config.has_pack){
        Dishes filt2 = filt.filterGeneral([&](const Dish & d) -> bool {return d.price >= config.total_price_lower and d.price <= config.total_price_upper;});
        appendDishChoice(res, filt2, "套餐", canteen);
    }
    if(config.has_main){
        uniform_real_distribution distrib;
        default_random_engine gen;
        Dishes maindishes = filt.searchInTags("主食");
        cout << maindishes.size() << endl;
        Dishes meatdishes = filt.searchInTags("荤");
        cout << meatdishes.size() << endl;
        Dishes vegedishes = filt.searchInTags("素");
        cout << vegedishes.size() << endl;
        optional<Dish> final_maindish = nullopt;
        optional<Dish> final_meatdish = nullopt;
        optional<Dish> final_vegedish = nullopt;
        int count = 0;
        gen.seed(time(0));
        distrib(gen);
        for(const Dish & maindish : maindishes.getAllDishes()){
            for(const Dish & meatdish : meatdishes.getAllDishes()){
                for(const Dish & vegedish : vegedishes.getAllDishes()){
                    float total_price = maindish.price + meatdish.price + vegedish.price;
                    if(total_price >= config.total_price_lower and total_price <= config.total_price_upper
                        and maindish.canteen == meatdish.canteen and vegedish.canteen == meatdish.canteen
                        and (canteen == CANTEEN_UNDEF or canteen == maindish.canteen)){
                        if(distrib(gen) < 1.0 / ((count++) + 1)){ // 抽签随机，因为不知道有多少个
                            final_maindish = maindish;
                            final_meatdish = meatdish;
                            final_vegedish = vegedish;
                        }
                    }
                }
            }
        }
        if(final_maindish.has_value()){
            res.append(final_maindish.value());
            res.append(final_meatdish.value());
            res.append(final_vegedish.value());
        }
    }
    return res;
}
