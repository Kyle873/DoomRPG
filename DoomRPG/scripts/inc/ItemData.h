#ifndef _ITEMDATA_DH_
#define _ITEMDATA_DH_

#include "Defs.h"

AddressSpace extern GlobalArraySpace ItemSpace;

#define ITEMDATA_LIST \
    int ItemCategory; \
    int ItemIndex

#define ITEMDATA_CATEGORY(index, name, flags) \
    ItemCategoryNames[(index)] = (name); \
    ItemCategoryFlags[(index)] = (flags); \
    ItemCategory = (index); \
    ItemIndex = 0

#define ITEMDATA_DEF(actor, name, price, rank, sprite, xofs, yofs) \
    ItemData[ItemCategory][ItemIndex].Actor = (actor); \
    ItemData[ItemCategory][ItemIndex].Name = (name); \
    ItemData[ItemCategory][ItemIndex].Price = (price); \
    ItemData[ItemCategory][ItemIndex].Rank = (rank); \
    ItemData[ItemCategory][ItemIndex].Sprite.Name = (sprite); \
    ItemData[ItemCategory][ItemIndex].Sprite.XOff = (xofs); \
    ItemData[ItemCategory][ItemIndex].Sprite.YOff = (yofs); \
    ItemData[ItemCategory][ItemIndex].Category = ItemCategory; \
    ItemData[ItemCategory][ItemIndex].Index = ItemIndex; \
    ItemIndex++;

#define ITEMDATA_CATEGORY_END \
    ItemMax[ItemCategory] = ItemIndex

// Item Definition
struct ItemInfo
{
    str Actor;
    str Name;
    
    int Price;
    int Rank;
    
    // Sprite information
    struct
    {
        str Name;
        int XOff;
        int YOff;
    } Sprite;
    
    // Only used for the Shop Special and specific DRLA checks
    int Category;
    int Index;
};

typedef struct ItemInfo ItemSpace *ItemInfoPtr;

extern ItemSpace bool ItemsInitialized;
extern ItemSpace int ItemCategories;
extern ItemSpace str ItemCategoryNames[ITEM_CATEGORIES];
extern ItemSpace int ItemCategoryFlags[ITEM_CATEGORIES];
extern ItemSpace int ItemMax[ITEM_CATEGORIES];
extern ItemSpace struct ItemInfo ItemData[ITEM_CATEGORIES][ITEM_MAX];
extern ItemSpace bool ItemRanksRemoved;
extern ItemSpace struct ItemInfo RewardList[ITEM_CATEGORIES * ITEM_MAX];
extern ItemSpace int MaxRewards;
extern ItemSpace bool RewardsInit;

NamedScript void BuildItemData();

void RemoveItemRanks();
int ShieldInversePriceSort(void const *, void const *);
ItemInfoPtr GetRewardItem(int);
ItemInfoPtr FindItem(str);
ItemInfoPtr FindItemInCategory(str, int);
ItemInfoPtr GetBlankItem();

#endif
