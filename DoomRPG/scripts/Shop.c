#include "Defs.h"
#include "RPG.h"

#include "ItemData.h"
#include "Map.h"
#include "Menu.h"
#include "Minigame.h"
#include "Shield.h"
#include "Shop.h"
#include "Utils.h"

// Global Shop Card Rank
RPGGlobal int GlobalShopCard;

// Shop Special
RPGGlobal bool        ShopSpecialBought;
RPGGlobal int         ShopSpecialTimer;
RPGGlobal ItemInfoPtr ShopSpecialItem;

RPGMap int ShopSpotID = 1000;

// Open the Shop
NamedScript KeyBind void OpenShop(bool OpenLocker)
{
    // If you're dead, return
    if (GetActorProperty(0, APROP_Health) <= 0) return;
    
    // If you're in an Outpost menu, return
    if (Player.OutpostMenu > 0) return;
    
    // If you're in any minigames, return
    if (Player.InMinigame) return;
    
    // If you're looking inside a crate, return
    if (Player.CrateOpen) return;
    
    // Close the main menu if it's open
    Player.InMenu = false;
    
    // Sanity check for pressing use while the shop is open in front of the counter in the Outpost
    if (Player.InShop && GetPlayerInput(PlayerNumber(), INPUT_BUTTONS) & BT_USE) return;
    
    if (Player.InShop)
    {
        ActivatorSound("menu/leave", 127);
        SetPlayerProperty(0, 0, PROP_TOTALLYFROZEN);
        Player.InShop = false;
    }
    else
    {
        ActivatorSound("menu/shop", 127);
        Player.InShop = true;
        if (OpenLocker)
            Player.LockerMode = true;
    }
}

NamedScript void UpdateShopAutoList()
{
    ArrayCreate(&Player.AutoSellList,  "AUSL\x00", 64, sizeof(ItemInfoPtr));
    ArrayCreate(&Player.AutoStoreList, "AUST\x00", 64, sizeof(ItemInfoPtr));
    
    for (int i = 0; i < ItemCategories; i++)
        for (int j = 0; j < ItemMax[i]; j++)
        {
            ItemInfoPtr Item = &ItemData[i][j];
            
            if (Player.AutoSellList.Position == Player.AutoSellList.Size)
                ArrayResize(&Player.AutoSellList);
            if (Player.AutoStoreList.Position == Player.AutoStoreList.Size)
                ArrayResize(&Player.AutoStoreList);
            
            if (Player.ItemAutoMode[i][j] == AT_SELL)
                ((ItemInfoPtr *)Player.AutoSellList.Data)[Player.AutoSellList.Position++] = Item;
            else if (Player.ItemAutoMode[i][j] == AT_STORE)
                ((ItemInfoPtr *)Player.AutoStoreList.Data)[Player.AutoStoreList.Position++] = Item;
        }
}

void ShopItemTryAutoDeposit(ItemInfoPtr Item)
{
    bool deposited = false;
    
    // Special handling for DRLA weapons since you can only keep one weapon with mods in the locker
    if (CompatMode == COMPAT_DRLA && Item->Category == 0 && Player.Locker[Item->Category][Item->Index] > 0) return;
    
    while (CheckInventory(Item->Actor) > 0 && (Player.EP >= LOCKER_EPRATE || CurrentLevel->UACBase))
    {
        DepositItem(Item->Category, Item->Index, false, true);
        deposited = true;
    }
    
    if (deposited)
        ActivatorSound("shop/autostore", 127);
}

NamedScript void ShopItemAutoHandler()
{
    int Items[ITEM_CATEGORIES][ITEM_MAX];
    int PrevItems[ITEM_CATEGORIES][ITEM_MAX];
    
    UpdateShopAutoList();
    
    while (true)
    {
        int Buttons = GetPlayerInput(PlayerNumber(), INPUT_BUTTONS);
        
        // For post-checks
        if (GetActivatorCVar("drpg_pickup_behavior") > 0)
            for (int i = 0; i < ItemCategories; i++)
                for (int j = 0; j < ItemMax[i]; j++)
                    Items[i][j] = CheckInventory(ItemData[i][j].Actor);
        
        // Auto-Sell
        bool CanSellItems = Player.RankLevel > 0 || CurrentLevel->UACBase;
        bool UseAutoDepositFallback = GetActivatorCVar("drpg_autosell_lockerfallback");
        if (CanSellItems || UseAutoDepositFallback)
            for (int i = 0; i < Player.AutoSellList.Position; i++)
            {
                ItemInfoPtr Item = ((ItemInfoPtr *)Player.AutoSellList.Data)[i];
                
                if (CheckInventory(Item->Actor) > 0)
                {
                    if (CanSellItems)
                        SellItem(Item->Actor, true, true);
                    else if (UseAutoDepositFallback)
                        ShopItemTryAutoDeposit(Item);
                }
            }
        
        // Auto-Store
        if (Player.EP >= LOCKER_EPRATE || CurrentLevel->UACBase)
            for (int i = 0; i < Player.AutoStoreList.Position; i++)
            {
                ItemInfoPtr Item = ((ItemInfoPtr *)Player.AutoStoreList.Data)[i];
                
                if (CheckInventory(Item->Actor) > 0)
                    ShopItemTryAutoDeposit(Item);
            }
        
        // Run-pickup behavior stuff
        if (GetActivatorCVar("drpg_pickup_behavior") > 0 && Buttons & BT_SPEED)
        {
            for (int i = 0; i < ItemCategories; i++)
                for (int j = 0; j < ItemMax[i]; j++)
                {
                    ItemInfoPtr Item = &ItemData[i][j];
                    
                    // Auto-Sell
                    if (!Player.InShop && GetActivatorCVar("drpg_pickup_behavior") == 1 && Items[i][j] > PrevItems[i][j])
                        if (CheckInventory(Item->Actor) > 0)
                            SellItem(Item->Actor, true, true);
                    
                    // Auto-Store
                    if (!Player.InShop && GetActivatorCVar("drpg_pickup_behavior") == 2 && Items[i][j] > PrevItems[i][j])
                        ShopItemTryAutoDeposit(Item);
                }
        }
        
        Delay(4);
        
        if (GetActivatorCVar("drpg_pickup_behavior") > 0)
            for (int i = 0; i < ItemCategories; i++)
                for (int j = 0; j < ItemMax[i]; j++)
                    PrevItems[i][j] = Items[i][j];
    }
}

void ShopLoop()
{
    ItemInfoPtr ItemPtr = &ItemData[Player.ShopPage][Player.ShopIndex];
    int Buttons = GetPlayerInput(PlayerNumber(), INPUT_BUTTONS);
    int OldButtons = GetPlayerInput(PlayerNumber(), INPUT_OLDBUTTONS);
    int Cost = ItemPtr->Price - ItemPtr->Price * Player.ShopDiscount / 100;
    int Rank = ItemPtr->Rank;
    int SellPrice;
    int Color;
    
    // Freeze the Player
    SetPlayerProperty(0, 1, PROP_TOTALLYFROZEN);

    // Get the sell price
    SellPrice = GetSellPrice(NULL, 1);
    
    // Set the HUD Size
    SetHudSize(GetActivatorCVar("drpg_menu_width"), GetActivatorCVar("drpg_menu_height"), true);

    // Force Locker mode if the Shop Anywhere CVAR is off
    if (!GetCVar("drpg_shoptype") && !CurrentLevel->UACBase)
        Player.LockerMode = true;
    
    SetFont("BIGFONT");
    if (Player.LockerMode)
    {
        // Title and Page
        HudMessage("\ChLocker \C-- %S\C- \Cd(%d/%d)", ItemCategoryNames[Player.ShopPage], Player.ShopPage + 1, ItemCategories);
        EndHudMessage(HUDMSG_PLAIN, 0, "White", 24.1, 24.0, 0.05);
        
        // EP Cost/Inventory Count
        if (GetCVar("drpg_inv_capacity"))
        {
            HudMessage("%S%d EP \C-(Inventory: %d/%d)", (CurrentLevel->UACBase ? "\Cc" : "\Cn"), LOCKER_EPRATE, Player.InvItems, CheckInventoryMax());
            EndHudMessage(HUDMSG_PLAIN, 0, "White", 24.1, 38.0, 0.05);
        }
        else
        {
            HudMessage("%S%d EP", (CurrentLevel->UACBase ? "\Cc" : "\Cn"), LOCKER_EPRATE);
            EndHudMessage(HUDMSG_PLAIN, 0, "Gold", 24.1, 38.0, 0.05);
        }
    }
    else
    {
        // Title and Page
        HudMessage("\CfShop \C-- %S\C- \Cd(%d/%d)", ItemCategoryNames[Player.ShopPage], Player.ShopPage + 1, ItemCategories);
        EndHudMessage(HUDMSG_PLAIN, 0, "White", 24.1, 24.0, 0.05);
        
        // Price
        if (ItemCategoryFlags[Player.ShopPage] & CF_NOBUY && ItemCategoryFlags[Player.ShopPage] & CF_NOSELL) // No Buying or Selling
        {
            HudMessage("(Discount: %d%%)", Player.ShopDiscount);
            EndHudMessage(HUDMSG_PLAIN, 0, "Gold", 24.1, 38.0, 0.05);
        }
        else if (ItemCategoryFlags[Player.ShopPage] & CF_NOBUY || Rank == -1) // No Buying
        {
            HudMessage("\Ci%d C \Ck(Discount: %d%%)", SellPrice, Player.ShopDiscount);
            EndHudMessage(HUDMSG_PLAIN, 0, "Gold", 24.1, 38.0, 0.05);
        }
        else if (ItemCategoryFlags[Player.ShopPage] & CF_NOSELL) // No Selling
        {
            HudMessage("\Cj%d C \Ck(Discount: %d%%)", Cost, Player.ShopDiscount);
            EndHudMessage(HUDMSG_PLAIN, 0, "Gold", 24.1, 38.0, 0.05);
        }
        else // Normal
        {
            HudMessage("\Cj%d C \Ci(%d C) \Ck(Discount: %d%%)", Cost, SellPrice, Player.ShopDiscount);
            EndHudMessage(HUDMSG_PLAIN, 0, "Gold", 24.1, 38.0, 0.05);
        }
    }
    
    // Item Grid
    DrawItemGrid();
    
    // Draw Shop Card
    if (Player.ShopCard > 0)
    {
        str CardSprite;
        
        SetFont("BIGFONT");
        HudMessage("+%d%%", Player.ShopCard * 5);
        EndHudMessage(HUDMSG_PLAIN, 0, (CurrentLevel->UACBase ? "Yellow" : "Gray"), 436.4, 364.0, 0.05);
        if (ItemRanksRemoved)
        {
            SetFont("SMALLFONT");
            HudMessage("No Rank\nLimits");
            EndHudMessage(HUDMSG_PLAIN, 0, "Cyan", 433.4, 382.0, 0.05);
        }
        
        if (Player.ShopCard == 1)
            CardSprite = "UCRDA0";
        else if (Player.ShopCard == 2)
            CardSprite = "UCRDB0";
        else if (Player.ShopCard == 3)
            CardSprite = "UCRDC0";
        else if (Player.ShopCard == 4)
            CardSprite = "UCRDD0";
        else if (Player.ShopCard == 5)
            CardSprite = "UCRDE0";
        
        if (CurrentLevel->UACBase)
            PrintSprite(CardSprite, 0, 458.0, 384.0, 0.05);
        else
            PrintSpritePulse(CardSprite, 0, 458.0, 384.0, 0.5, 64.0, 0.5);
    }
    
    // Check Input
    if (Buttons & BT_FORWARD && !(OldButtons & BT_FORWARD))
    {
        ActivatorSound("menu/move", 127);
        if (Buttons & BT_SPEED)
            Player.ShopIndex -= 54;
        else
            Player.ShopIndex -= 9;
        if (Player.ShopIndex < 0) Player.ShopIndex = 0;
    };
    if (Buttons & BT_BACK && !(OldButtons & BT_BACK))
    {
        ActivatorSound("menu/move", 127);
        if (Buttons & BT_SPEED)
            Player.ShopIndex += 54;
        else
            Player.ShopIndex += 9;
        if (Player.ShopIndex > ItemMax[Player.ShopPage] - 1) Player.ShopIndex = ItemMax[Player.ShopPage] - 1;
    }
    if ((Buttons & BT_LEFT && !(OldButtons & BT_LEFT)) ||
        (Buttons & BT_MOVELEFT && !(OldButtons & BT_MOVELEFT)))
        if (Buttons & BT_SPEED)
        {
            ActivatorSound("menu/move", 127);
            Player.ShopPage--;
            Player.ShopIndex = 0;
            if (Player.ShopPage < 0) Player.ShopPage = (GetCVar("drpg_debug") ? ItemCategories : ItemCategories - 1);
        }
        else
        {
            ActivatorSound("menu/move", 127);
            Player.ShopIndex--;
            if (Player.ShopIndex < 0) Player.ShopIndex = 0;
        }
    if ((Buttons & BT_RIGHT && !(OldButtons & BT_RIGHT)) ||
        (Buttons & BT_MOVERIGHT && !(OldButtons & BT_MOVERIGHT)))
        if (Buttons & BT_SPEED)
        {
            ActivatorSound("menu/move", 127);
            Player.ShopPage++;
            Player.ShopIndex = 0;
            if (Player.ShopPage > (GetCVar("drpg_debug") ? ItemCategories : ItemCategories - 1)) Player.ShopPage = 0;
        }
        else
        {
            ActivatorSound("menu/move", 127);
            Player.ShopIndex++;
            if (Player.ShopIndex > ItemMax[Player.ShopPage] - 1) Player.ShopIndex = ItemMax[Player.ShopPage] - 1;
        }
    if (Buttons & BT_USE && (Player.DelayTimer > 35.0 * GetActivatorCVarFixed("drpg_menu_repeat") ? true : !(OldButtons & BT_USE)) && !Player.MenuBlock)
        if (Buttons & BT_SPEED)
        {
            if (Player.LockerMode)
                WithdrawItem(Player.ShopPage, Player.ShopIndex);
            else
                SellItem(ItemPtr->Actor, false, false);
        }
        else
        {
            if (Player.LockerMode)
                DepositItem(Player.ShopPage, Player.ShopIndex, false, false);
            else if (Player.ItemAutoMode[Player.ShopPage][Player.ShopIndex] != AT_SELL)
                BuyItem(ItemPtr->Actor);
        }
    if (Buttons & BT_JUMP && !(OldButtons & BT_JUMP) && (GetCVar("drpg_shoptype") || CurrentLevel->UACBase))
    {
        Player.LockerMode = !Player.LockerMode;
        ActivatorSound("menu/move", 127);
    }
    if (Buttons & BT_ZOOM && !(OldButtons & BT_ZOOM))
        if (!(ItemCategoryFlags[Player.ShopPage] & CF_NODROP) && CheckInventory(ItemPtr->Actor) > 0 && !(CompatMode == COMPAT_DRLA && (Player.ShopPage == 0 || Player.ShopPage == 3 || Player.ShopPage == 8 || Player.ShopPage == 9)))
        {
            int Success = DropPlayerItem(ItemPtr->Actor);
            if (Success)
                TakeInventory(ItemPtr->Actor, 1);
            else
            {
                PrintError("You cannot drop this item here");
                ActivatorSound("menu/error", 127);
            }
        }
    if (Buttons & BT_USE || (Buttons & BT_USE && Buttons & BT_SPEED))
        Player.DelayTimer++;
    if (Buttons == BT_ATTACK && OldButtons != BT_ATTACK)
    {
        if (Player.LockerMode)
        {
            if (Player.ItemAutoMode[Player.ShopPage][Player.ShopIndex] != AT_STORE)
                Player.ItemAutoMode[Player.ShopPage][Player.ShopIndex] = AT_STORE;
            else
                Player.ItemAutoMode[Player.ShopPage][Player.ShopIndex] = AT_NONE;
            ActivatorSound("menu/move", 127);
        }
        else if (!(ItemCategoryFlags[Player.ShopPage] & CF_NOSELL))
        {
            if (Player.ItemAutoMode[Player.ShopPage][Player.ShopIndex] != AT_SELL)
                Player.ItemAutoMode[Player.ShopPage][Player.ShopIndex] = AT_SELL;
            else
                Player.ItemAutoMode[Player.ShopPage][Player.ShopIndex] = AT_NONE;
            ActivatorSound("menu/move", 127);
        }
        
        UpdateShopAutoList();
    }
    if (Buttons == BT_ALTATTACK && OldButtons != BT_ALTATTACK && Player.LockerMode)
    {
        if (CurrentLevel->UACBase)
        {
            for (int i = 0; i < ItemMax[Player.ShopPage]; i++)
                while (Player.Locker[Player.ShopPage][i] > 0)
                    WithdrawItem(Player.ShopPage, i);
        }
        else
        {
            PrintError("You can only bulk withdraw while in the Outpost");
            ActivatorSound("menu/error", 127);
        }
    }
    
    // Reset the Delay Timer if no buttons are pressed
    if (Buttons == 0 && OldButtons == 0)
        Player.DelayTimer = 0;
    
    // Reset the menu block
    Player.MenuBlock = false;   
}

void BuyItem(str Item)
{
    ItemInfoPtr ItemPtr = &ItemData[Player.ShopPage][Player.ShopIndex];
    int Cost = ItemPtr->Price - ItemPtr->Price * Player.ShopDiscount / 100;
    int Spawned;
    
    // If you're not the required rank, return
    if (ItemPtr->Rank > Player.RankLevel)
    {
        if (Player.DelayTimer <= 35.0 * GetActivatorCVarFixed("drpg_menu_repeat"))
        {
            PrintError("You are not a high enough Rank to buy this item");
            ActivatorSound("menu/error", 127);
        }
        
        return;
    }
    
    // If the item (or category) is flagged to never be buyable, return
    if (ItemPtr->Rank == -1 || ItemCategoryFlags[Player.ShopPage] & CF_NOBUY)
    {
        if (Player.DelayTimer <= 35.0 * GetActivatorCVarFixed("drpg_menu_repeat"))
        {
            PrintError("You cannot buy this item");
            ActivatorSound("menu/error", 127);
        }
        
        return;
    }
    
    // If you don't have enough Credits, return
    if (CheckInventory("DRPGCredits") < ItemPtr->Price - ItemPtr->Price * Player.ShopDiscount / 100)
    {
        if (Player.DelayTimer <= 35.0 * GetActivatorCVarFixed("drpg_menu_repeat"))
        {
            PrintError("You don't have enough Credits to buy this item");
            ActivatorSound("menu/error", 127);
        }
        
        return;
    }
    
    // If the item has no cost, return
    if (Cost == 0)
    {
        if (Player.DelayTimer <= 35.0 * GetActivatorCVarFixed("drpg_menu_repeat"))
            ActivatorSound("menu/error", 127);
        
        return;
    }
    
    if (CurrentLevel->UACBase && !GetCVar("drpg_shoptype"))
        Spawned = SpawnSpotForced(Item, ShopSpotID, 0, 0);
    else
    {
        Spawned = SpawnForced(Item, GetActorX(0), GetActorY(0), GetActorZ(0), 0, 0);
        SetActorVelocity(Player.TID, 0.01, 0.01, 0, true, false);
    }
    
    if (Spawned > 0)
    {
        ActivatorSound("menu/buy", 127);
        TakeInventory("DRPGCredits", Cost);
    }
    else if (Player.DelayTimer <= 35.0 * GetActivatorCVarFixed("drpg_menu_repeat"))
    {
        PrintError("Could not teleport the requested item to your location");
        ActivatorSound("menu/error", 127);
    }
}

int GetSellPrice(str Item, int Amount)
{
    ItemInfoPtr ItemPtr = &ItemData[Player.ShopPage][Player.ShopIndex];
    int SellCost;
    
    // Just use the current index if item is blank
    if (Item == NULL)
        SellCost = ItemPtr->Price;
    
    // Iterate to find the item
    for (int i = 0; i < ItemCategories; i++)
        for (int j = 0; j < ItemMax[i]; j++)
        {
            ItemInfoPtr ItemIterPtr = &ItemData[i][j];
            
            if (ItemIterPtr->Actor == Item)
            {
                SellCost = ItemIterPtr->Price;
                break;
            }
        }
    
    // 1/10th normal buying price
    SellCost /= 10;
    
    // Multiply by amount
    SellCost *= Amount;
    
    // Make sure you always get at least 1 Credit from a sale
    if (SellCost == 0) SellCost = 1;
    
    return SellCost;
}

int SellItem(str Item, bool SellAll, bool AutoSold)
{
    int Amount = 1;
    int SellCost;

    // You must be at least Rank 1 or in the Outpost to sell items
    if (Player.RankLevel == 0 && !CurrentLevel->UACBase)
    {
        if (Player.DelayTimer <= 35.0 * GetActivatorCVarFixed("drpg_menu_repeat"))
        {
            PrintError("You cannot sell items outside the Outpost until you reach the first rank");
            ActivatorSound("menu/error", 127);
        }
        
        return 0;
    }
    
    // If you're on a page that doesn't allow selling or you don't have any of the required item, fail
    if (!AutoSold && (CheckInventory(Item) == 0 || ItemCategoryFlags[Player.ShopPage] & CF_NOSELL))
    {
        if (Player.DelayTimer <= 35.0 * GetActivatorCVarFixed("drpg_menu_repeat"))
        {
            PrintError("You cannot sell these items");
            ActivatorSound("menu/error", 127);
        }
        
        return 0;
    }
    
    if (SellAll)
        Amount = CheckInventory(Item);
    
    ItemInfoPtr Info = FindItem(Item);
    
    // Get Sell Price
    SellCost = GetSellPrice(Item, Amount);
    
    // Sell the Item
    if (CheckInventory(Item) >= Amount)
    {
        if (AutoSold)
            ActivatorSound("shop/autosell", 127);
        else
            ActivatorSound("credits/payout", 127);
        TakeInventory(Item, Amount);
        
        // DoomRL Compatibility
        if (CompatMode == COMPAT_DRLA)
            for (int i = 0; i < Amount; i++)
                RemoveDRLAItem(Info->Category, Info->Index);
        
        GiveInventory("DRPGCredits", SellCost);
    }
    else if (Player.DelayTimer <= 35.0 * GetActivatorCVarFixed("drpg_menu_repeat"))
    {
        PrintError("You are not carrying any of the specified item");
        ActivatorSound("menu/error", 127);
    }
    
    return SellCost;
}

void DepositItem(int Page, int Index, bool CharSave, bool NoSound)
{
    ItemInfoPtr ItemPtr = &ItemData[Page][Index];
    int *LockerAmount = &Player.Locker[Page][Index];
    
    // Stop if this item cannot be deposited
    if (ItemCategoryFlags[Page] & CF_NOSTORE) return;
    
    if ((Player.EP >= LOCKER_EPRATE || CurrentLevel->UACBase || CharSave) && CheckInventory(ItemPtr->Actor) > 0)
    {
       // DoomRL Compatibility
       if (CompatMode == COMPAT_DRLA)
       {
           if (Page == 0) // Weapons
           {
                // You can only store one of a weapon type
                if (*LockerAmount > 0 && !CharSave)
                {
                    PrintError("You can only store one of a weapon type in the Locker");
                    ActivatorSound("menu/error", 127);
                    return;
                }
                
                // Store the weapons modpack data
                /*
                Player.WeaponMods[Index][0] = CheckInventory(StrParam("%SModLimit", ItemPtr->Actor));
                Player.WeaponMods[Index][1] = CheckInventory(StrParam("%SPowerMod", ItemPtr->Actor));
                Player.WeaponMods[Index][2] = CheckInventory(StrParam("%SBulkMod", ItemPtr->Actor));
                Player.WeaponMods[Index][3] = CheckInventory(StrParam("%SAgilityMod", ItemPtr->Actor));
                Player.WeaponMods[Index][4] = CheckInventory(StrParam("%STechnicalMod", ItemPtr->Actor));
                Player.WeaponMods[Index][5] = CheckInventory(StrParam("%SSniperMod", ItemPtr->Actor));
                Player.WeaponMods[Index][6] = CheckInventory(StrParam("%SFirestormMod", ItemPtr->Actor));
                Player.WeaponMods[Index][7] = CheckInventory(StrParam("%SNanoMod", ItemPtr->Actor));
                Player.WeaponMods[Index][8] = CheckInventory(StrParam("%SDemonArtifacts", ItemPtr->Actor));
                */
                
                // Check DRLA set bonuses
                CheckDRLASetWeapons();
            }
            
            RemoveDRLAItem(Page, Index);
        }
        
        TakeInventory(ItemPtr->Actor, 1);
        if (!CurrentLevel->UACBase && !CharSave)
            Player.EP -= LOCKER_EPRATE;
        (*LockerAmount)++;
        if (CharSave && CompatMode == COMPAT_DRLA && Page == 0 && *LockerAmount > 1) // Prevent dumping multiple weapons in the locker in DRLA saves
            *LockerAmount = 1;
        if (!NoSound)
            ActivatorSound("menu/move", 127);
    }
    else if (Player.DelayTimer <= 35.0 * GetActivatorCVarFixed("drpg_menu_repeat") && !NoSound)
    {
        if (Player.EP < LOCKER_EPRATE)
            PrintError("Not enough EP to deposit this item");
        else
            PrintError("You're not carrying any of the specified item");
        ActivatorSound("menu/error", 127);
    }
}

void WithdrawItem(int Page, int Index)
{
    ItemInfoPtr ItemPtr = &ItemData[Page][Index];
    int *LockerAmount = &Player.Locker[Page][Index];
    
    // Stop if this item cannot be withdrawn
    if (ItemCategoryFlags[Page] & CF_NOSTORE) return;
    
    // Spawning
    if ((Player.EP >= LOCKER_EPRATE || CurrentLevel->UACBase) && *LockerAmount > 0)
    {
        if (CompatMode == COMPAT_DRLA && Page == 0) // Weapons
        {
            // Don't let you withdraw the weapon if you're already holding one
            if (CheckInventory(ItemPtr->Actor))
            {
                PrintError("You are already carrying this type of weapon");
                ActivatorSound("menu/error", 127);
                return;
            }
            
            int WeaponTID = UniqueTID();
            if (Player.WeaponMods[Player.ShopIndex].Total > 0 || Player.WeaponMods[Player.ShopIndex].Artifacts > 0) // Weapon was modded
            {
                // Re-add the mods onto the weapon
                SpawnForced(StrParam("%SPickupModded", ItemPtr->Actor), GetActorX(0), GetActorY(0), GetActorZ(0), WeaponTID, 0);
                
                GiveActorInventory(WeaponTID, StrParam("%SModLimit", ItemPtr->Actor), Player.WeaponMods[Player.ShopIndex].Total);
                GiveActorInventory(WeaponTID, StrParam("%SPowerMod", ItemPtr->Actor), Player.WeaponMods[Player.ShopIndex].Power);
                GiveActorInventory(WeaponTID, StrParam("%SBulkMod", ItemPtr->Actor), Player.WeaponMods[Player.ShopIndex].Bulk);
                GiveActorInventory(WeaponTID, StrParam("%SAgilityMod", ItemPtr->Actor), Player.WeaponMods[Player.ShopIndex].Agility);
                GiveActorInventory(WeaponTID, StrParam("%STechnicalMod", ItemPtr->Actor), Player.WeaponMods[Player.ShopIndex].Technical);
                GiveActorInventory(WeaponTID, StrParam("%SSniperMod", ItemPtr->Actor), Player.WeaponMods[Player.ShopIndex].Sniper);
                GiveActorInventory(WeaponTID, StrParam("%SFirestormMod", ItemPtr->Actor), Player.WeaponMods[Player.ShopIndex].Firestorm);
                GiveActorInventory(WeaponTID, StrParam("%SNanoMod", ItemPtr->Actor), Player.WeaponMods[Player.ShopIndex].Nano);
                GiveActorInventory(WeaponTID, StrParam("%SDemonArtifacts", ItemPtr->Actor), Player.WeaponMods[Player.ShopIndex].Artifacts);
            }
            else
            {
                SpawnForced(ItemPtr->Actor, GetActorX(0), GetActorY(0), GetActorZ(0), 0, 0);
            }
        }
        else if (Page == 1) // Ammo
            GiveInventory(ItemPtr->Actor, 1);
        else // Everything else
            SpawnForced(ItemPtr->Actor, GetActorX(0), GetActorY(0), GetActorZ(0), 0, 0);
        
        SetActorVelocity(Player.TID, 0.01, 0.01, 0, true, false);
        (*LockerAmount)--;
        if (!CurrentLevel->UACBase)
            Player.EP -= LOCKER_EPRATE;
        ActivatorSound("menu/move", 127);
    }
    else if (Player.DelayTimer <= 35.0 * GetActivatorCVarFixed("drpg_menu_repeat"))
    {
        if (Player.EP < LOCKER_EPRATE)
            PrintError("Not enough EP to withdraw this item");
        else
            PrintError("Locker does not contain any of the specified item");
        ActivatorSound("menu/error", 127);
    }
}

void DrawItemGrid()
{
    // Width/Height
    int Width = 9;
    int Height = 6;
    
    // Coordinates
    fixed BaseX;
    fixed BaseY;
    fixed BoxX;
    fixed BoxY;
    fixed X;
    fixed Y;
    fixed IconX;
    fixed IconY;
    
    for (int i = 0; i < Height; i++)
    {
        // Reset base X
        BaseX = 0.0;
        
        for (int j = 0; j < Width; j++)
        {
            int Index = j + (i * Width);
            
            // Calculate offset
            if (Player.ShopIndex >= Height * Width)
                Index += (Player.ShopIndex / (Height * Width)) * (Height * Width);
            
            ItemInfoPtr Item = &ItemData[Player.ShopPage][Index];
            str Icon = Item->Sprite.Name;
            str Name = Item->Name;
            int IconXOff = Item->Sprite.XOff;
            int IconYOff = Item->Sprite.YOff;
            int Held = CheckInventory(Item->Actor);
            int Stored = Player.Locker[Player.ShopPage][Index];
            int Rank = Item->Rank;
            int Price = Item->Price;
            bool Unlocked = !((Rank > 0 && Player.RankLevel < Rank));
            bool CanBuy = !(Rank == -1);
            bool CanAfford = (CheckInventory("DRPGCredits") >= Price - Price * Player.ShopDiscount / 100);
            
            // Stop if we're at the end of the list
            if (Index > ItemMax[Player.ShopPage] - 1) break;
            
            // Placeholder Icon
            if (StrLen(Icon) == 0)
                Icon = "SprNone";
            
            // Setup X and Y
            X = 26.0 + BaseX;
            Y = 50.0 + BaseY;
            BoxX = 48.0 + BaseX;
            BoxY = 72.0 + BaseY;
            IconX = 48.0 + BaseX;
            IconY = 72.0 + BaseY;
            IconX += IconXOff;
            IconY += IconYOff;
            
            // Amount
            if (Held > 0)
            {
                SetFont("BIGFONT");
                HudMessage("%d", Held);
                EndHudMessage(HUDMSG_PLAIN, 0, "Green", X + 44.2, Y + 44.2, 0.05);
            }
            if (Stored > 0)
            {
                SetFont("BIGFONT");
                HudMessage("%d", Stored);
                EndHudMessage(HUDMSG_PLAIN, 0, "Yellow", X + 44.2, Y + 12.2, 0.05);
            }
            
            // Auto-Sell/Auto-Store Icon
            if (Player.ItemAutoMode[Player.ShopPage][Index] == AT_SELL)
                PrintSpritePulse("SELLICN", 0, X - 2.0 + 0.1, Y + 0.1, 0.75, 128.0, 0.25, false);
            else if (Player.ItemAutoMode[Player.ShopPage][Index] == AT_STORE)
                PrintSpritePulse("STORICN", 0, X - 2.0 + 0.1, Y + 0.1, 0.75, 128.0, 0.25, false);
            
            // Mod Info
            if (CompatMode == COMPAT_DRLA && Player.LockerMode && Player.ShopPage == 0 && Player.Locker[Player.ShopPage][Index] > 0)
            {
                SetFont("SMALLFONT");
                HudMessage("%d", Player.WeaponMods[Index].Power);     EndHudMessage(HUDMSG_PLAIN, 0, "Red", X + 4.0, Y + 38.2, 0.05);
                HudMessage("%d", Player.WeaponMods[Index].Bulk);      EndHudMessage(HUDMSG_PLAIN, 0, "Blue", X + 12.0, Y + 38.2, 0.05);
                HudMessage("%d", Player.WeaponMods[Index].Agility);   EndHudMessage(HUDMSG_PLAIN, 0, "Green", X + 20.0, Y + 38.2, 0.05);
                HudMessage("%d", Player.WeaponMods[Index].Technical); EndHudMessage(HUDMSG_PLAIN, 0, "Yellow", X + 28.0, Y + 38.2, 0.05);
                HudMessage("%d", Player.WeaponMods[Index].Sniper);    EndHudMessage(HUDMSG_PLAIN, 0, "Purple", X + 4.0, Y + 46.2, 0.05);
                HudMessage("%d", Player.WeaponMods[Index].Firestorm); EndHudMessage(HUDMSG_PLAIN, 0, "Orange", X + 12.0, Y + 46.2, 0.05);
                HudMessage("%d", Player.WeaponMods[Index].Nano);      EndHudMessage(HUDMSG_PLAIN, 0, "White", X + 20.0, Y + 46.2, 0.05);
                HudMessage("%d", Player.WeaponMods[Index].Artifacts); EndHudMessage(HUDMSG_PLAIN, 0, "DarkRed", X + 28.0, Y + 46.2, 0.05);
            }
            
            // Icon
            SetHudClipRect(X, Y, 44, 44);
            if (Player.ShopIndex == Index)
            {
                if (Unlocked || Player.LockerMode)
                    PrintSpritePulse(Icon, 0, IconX, IconY, 0.75, 32.0, 0.25);
                else
                    PrintSpritePulse(Icon, 0, IconX, IconY, 0.25, 32.0, 0.25);
            }
            else
            {
                if (Unlocked || Player.LockerMode)
                    PrintSprite(Icon, 0, IconX, IconY, 0.05);
                else
                    PrintSpriteAlpha(Icon, 0, IconX, IconY, 0.05, 0.25);
            }
            SetHudClipRect(0, 0, 0, 0);
            
            // Box
            if (Player.ShopIndex == Index)
                if ((!CanAfford || !Unlocked || !CanBuy) && !Player.LockerMode)
                    PrintSprite("ItemBoxR", 0, BoxX, BoxY, 0.05);
                else if (Player.LockerMode)
                    PrintSprite("ItemBoxL", 0, BoxX, BoxY, 0.05);
                else
                    PrintSprite("ItemBoxH", 0, BoxX, BoxY, 0.05);
            PrintSprite("ItemBoxB", 0, BoxX, BoxY, 0.05);
            
            // Item Name
            if (Player.ShopIndex == Index)
            {
                SetFont("BIGFONT");
                HudMessage("%S", Name);
                EndHudMessage(HUDMSG_PLAIN, 0, ((!Player.LockerMode && CanAfford) || Player.LockerMode ? "White" : "Red"), 24.1, 344.1, 0.05);
            }
            
            // Increment X
            BaseX += 48.0;
        }
        
        // Increment Y
        BaseY += 48.0;
    }
}

void CheckShopCard()
{
    Player.ShopCard = CheckInventory("DRPGUACCard");
    if (CheckInventory("DRPGDiamondUACCard"))
        Player.ShopCard = 5;
    
    if (Player.ShopCard == 5 && !ItemRanksRemoved)
        RemoveItemRanks();
    
    for (int i = 0; i < MAX_PLAYERS; i++)
        if (Players(i).ShopCard > GlobalShopCard)
            GlobalShopCard = Players(i).ShopCard;
}
