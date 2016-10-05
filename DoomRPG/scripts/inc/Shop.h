#ifndef _SHOP_DH_
#define _SHOP_DH_

#include "Defs.h"

// Global Shop Card Rank
extern RPGGlobal int GlobalShopCard;

// Shop Special
extern RPGGlobal bool        ShopSpecialBought;
extern RPGGlobal int         ShopSpecialTimer;
extern RPGGlobal ItemInfoPtr ShopSpecialItem;

extern RPGMap int ShopSpotID;

NamedScript MapSpecial void OpenShop(bool);

NamedScript void UpdateShopAutoList();
NamedScript void ShopItemAutoHandler();

void ShopLoop();
int GetAmmoAmount(str);
void BuyItem(str);
int GetSellPrice(str, int);
int SellItem(str, int, bool);
void DepositItem(int, int, bool, bool);
void WithdrawItem(int, int);
void DrawItemGrid();
void CheckShopCard();

#endif
