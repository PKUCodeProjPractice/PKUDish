#include<random>
#include"randdish.h"
using namespace std;

Dishes randChoice(Dishes & dishes, const RandConfig & config){
    // 初始化随机数
    default_random_engine gen;
    gen.seed(time(0));
    // 首先先进行针对单菜品的筛选
    Dishes filt;
    // 等待时间
    if(config.no_wait){
        filt = dishes.searchInTags("等待制作");
    }
    // TODO：辣度
    // 需要定义辣度上的序关系
    // 选择一个菜品，查看它的食堂; 用第一个菜确定食堂
    // TODO：用更好的方式进行遍历，而不是现在这样来一个条件判断一次
    Dishes res;
    Canteen canteen = CANTEEN_UNDEF;
    if(config.has_pack){
        Dishes filt2;
        if(canteen != CANTEEN_UNDEF){
            filt2 = filt.filterCanteen(canteen); // 这个if或许可以通过修改过滤的实现方式合并
        }else{
            filt2 = filt;
        }
        uniform_int_distribution distrib(0, filt2.size());
        Dish choice = filt.getAllDishes()[distrib(gen)];
        if(canteen == CANTEEN_UNDEF){
            canteen = choice.canteen;
        }
        res.append(choice);
    }
    return res;
}
