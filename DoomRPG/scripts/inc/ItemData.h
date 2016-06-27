#ifndef _ITEMDATA_DH_
#define _ITEMDATA_DH_

#include "Defs.h"

#define ITEMDATA_LIST \
    int ItemCategory; \
    int ItemIndex

#define ITEMDATA_CATEGORY(index, name, flags) \
    ItemCategoryNames[(index)] = (name); \
    ItemCategoryFlags[(index)] = (flags); \
    ItemCategory = (index); \
    ItemIndex = 0

#define ITEMDATA_DEF(actor, name, price, rank, rarity, sprite, xofs, yofs) \
    ItemData[ItemCategory][ItemIndex].Actor = (actor); \
    ItemData[ItemCategory][ItemIndex].Name = (name); \
    ItemData[ItemCategory][ItemIndex].Price = (price); \
    ItemData[ItemCategory][ItemIndex].Rank = (rank); \
    ItemData[ItemCategory][ItemIndex].Rarity = (rarity); \
    ItemData[ItemCategory][ItemIndex].Sprite.Name = (sprite); \
    ItemData[ItemCategory][ItemIndex].Sprite.XOff = (xofs); \
    ItemData[ItemCategory][ItemIndex].Sprite.YOff = (yofs); \
    ItemData[ItemCategory][ItemIndex].Category = ItemCategory; \
    ItemData[ItemCategory][ItemIndex].Index = ItemIndex; \
    ItemIndex++;

#define ITEMDATA_CATEGORY_END \
    ItemMax[ItemCategory] = ItemIndex

extern bool RPGGlobal ItemsInitialized;
extern int RPGGlobal ItemCategories;
extern str RPGGlobal ItemCategoryNames[ITEM_CATEGORIES];
extern int RPGGlobal ItemCategoryFlags[ITEM_CATEGORIES];
extern int RPGGlobal ItemMax[ITEM_CATEGORIES];
extern ItemInfo RPGGlobal ItemData[ITEM_CATEGORIES][ITEM_MAX];
extern bool RPGGlobal ItemRanksRemoved;
extern ItemInfoPtr RewardList[MAX_DIFFICULTIES + 1][ITEM_CATEGORIES * ITEM_MAX];
extern bool RPGGlobal RewardsInit;
extern int RPGGlobal RewardsCount[MAX_DIFFICULTIES + 1];

NamedScript void BuildItemData();

void RemoveItemRanks();
int ShieldInversePriceSort(void const *, void const *);
ItemInfoPtr GetRewardItem(int);
ItemInfoPtr FindItem(str);
ItemInfoPtr FindItemInCategory(str, int);
ItemInfoPtr GetBlankItem();

#endif
