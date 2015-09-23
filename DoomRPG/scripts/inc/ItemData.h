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
typedef struct
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
} ItemInfo;

typedef ItemInfo ItemSpace *ItemInfoPtr;

extern bool ItemSpace ItemsInitialized;
extern int ItemSpace ItemCategories;
extern str ItemSpace ItemCategoryNames[ITEM_CATEGORIES];
extern int ItemSpace ItemCategoryFlags[ITEM_CATEGORIES];
extern int ItemSpace ItemMax[ITEM_CATEGORIES];
extern ItemInfo ItemSpace ItemData[ITEM_CATEGORIES][ITEM_MAX];
extern bool ItemSpace ItemRanksRemoved;
extern ItemInfoPtr ItemSpace RewardList[ITEM_CATEGORIES * ITEM_MAX];
extern int ItemSpace MaxRewards;
extern bool ItemSpace RewardsInit;

NamedScript void BuildItemData();

void RemoveItemRanks();
int ShieldInversePriceSort(void const *, void const *);
ItemInfoPtr GetRewardItem(int);
ItemInfoPtr FindItem(str);
ItemInfoPtr FindItemInCategory(str, int);
ItemInfoPtr GetBlankItem();

#endif
