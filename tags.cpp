#include"tags.h"

/*bool operator<(const DishTaste & a, const DishTaste & b){
    switch(a){
    case DishTaste::NOT_SPICY:switch(b) {
        case DishTaste::NOT_SPICY:return false;
        case DishTaste::LITTLE_SPICY:
        case DishTaste::MIDDLE_SPICY:
        case DishTaste::HEAVY_SPICY:return true;
    }
    case DishTaste::LITTLE_SPICY:switch(b) {
        case DishTaste::NOT_SPICY:
        case DishTaste::LITTLE_SPICY:return false;
        case DishTaste::MIDDLE_SPICY:
        case DishTaste::HEAVY_SPICY:return true;
        }
    case DishTaste::MIDDLE_SPICY:switch(b) {
        case DishTaste::NOT_SPICY:
        case DishTaste::LITTLE_SPICY:
        case DishTaste::MIDDLE_SPICY:return false;
        case DishTaste::HEAVY_SPICY:return true;
    }
    case DishTaste::HEAVY_SPICY:switch(b) {
        case DishTaste::NOT_SPICY:
        case DishTaste::LITTLE_SPICY:
        case DishTaste::MIDDLE_SPICY:
        case DishTaste::HEAVY_SPICY:return false;
    }
    }
}*/

DishTag::DishTag(TagKind _kind):kind(_kind){}
DishNormalTag::DishNormalTag(const QString & _name):DishTag(TagKind::NORMAL), name(_name){}
DishKindTag::DishKindTag(DishKind _kind):DishTag(TagKind::KIND), dish_kind(_kind){}
DishTasteTag::DishTasteTag(DishTaste _taste):DishTag(TagKind::TASTE), taste(_taste){}
DishWaitTag::DishWaitTag(bool _wait):DishTag(TagKind::WAIT), should_wait(_wait){}

QString DishNormalTag::toString() const {return name;}
QString DishKindTag::toString() const {return DISHKIND_NAME[dish_kind];}
QString DishTasteTag::toString() const {return DISHTASTE_NAME[taste];}
QString DishWaitTag::toString() const {return should_wait ? "需要等待" : "无需等待";}

DishKindTag DISHKINDTAG_TAOCAN = DishKindTag(DishKind::TAOCAN);
DishKindTag DISHKINDTAG_ZHUSHI = DishKindTag(DishKind::ZHUSHI);
DishKindTag DISHKINDTAG_SHAOKAO = DishKindTag(DishKind::SHAOKAO);
DishKindTag DISHKINDTAG_TIANDIAN = DishKindTag(DishKind::TIANDIAN);
DishKindTag DISHKINDTAG_ROU = DishKindTag(DishKind::ROU);
DishKindTag DISHKINDTAG_CAI = DishKindTag(DishKind::CAI);

DishTasteTag DISHTASTETAG_NOSPICY = DishTasteTag(DishTaste::NOT_SPICY);
DishTasteTag DISHTASTETAG_LISPICY = DishTasteTag(DishTaste::LITTLE_SPICY);
DishTasteTag DISHTASTETAG_MISPICY = DishTasteTag(DishTaste::MIDDLE_SPICY);
DishTasteTag DISHTASTETAG_HESPICY = DishTasteTag(DishTaste::HEAVY_SPICY);

DishWaitTag DISHWAITTAG_TRUE = DishWaitTag(true);
DishWaitTag DISHWAITTAG_FALSE = DishWaitTag(false);

QMap<QString, DishTag*> predefine_tags = {
    {"套餐", &DISHKINDTAG_TAOCAN},
    {"主食", &DISHKINDTAG_ZHUSHI},
    {"烧烤", &DISHKINDTAG_SHAOKAO},
    {"甜点", &DISHKINDTAG_TIANDIAN},
    {"肉", &DISHKINDTAG_ROU},
    {"素", &DISHKINDTAG_CAI},

    {"辣", &DISHTASTETAG_MISPICY},
    {"不辣", &DISHTASTETAG_NOSPICY},
    {"微辣", &DISHTASTETAG_LISPICY},
    {"中辣", &DISHTASTETAG_MISPICY},
    {"重辣", &DISHTASTETAG_HESPICY},

    {"无需等待", &DISHWAITTAG_FALSE},
    {"需要等待", &DISHWAITTAG_TRUE}
};
