#ifndef _SHOP_DH_
#define _SHOP_DH_

#include "Defs.h"

// Global Shop Card Rank
extern int GlobalShopCard;

// Shop Special
extern bool      ShopSpecialBought;
extern int       ShopSpecialTimer;
extern ItemInfo *ShopSpecialItem;

extern int MapRegister ShopSpotID;

NamedScript MapSpecial void OpenShop(bool);

NamedScript void UpdateShopAutoList();
NamedScript void ShopItemAutoHandler();

void ShopLoop();
int GetAmmoAmount(str);
void BuyItem(str);
int GetSellPrice(str, int);
int SellItem(str, bool, bool);
void DepositItem(int, int, bool, bool);
void WithdrawItem(int, int);
void DrawItemGrid();
void CheckShopCard();

#endif
