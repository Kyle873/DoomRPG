#include "RPG.h"

#include <stdlib.h>
#include "ItemData.h"
#include "Shield.h"
#include "Utils.h"

bool RPGGlobal ItemsInitialized;

int RPGGlobal ItemCategories;

str RPGGlobal ItemCategoryNames[ITEM_CATEGORIES];
int RPGGlobal ItemCategoryFlags[ITEM_CATEGORIES];
int RPGGlobal ItemMax[ITEM_CATEGORIES];

ItemInfo RPGGlobal ItemData[ITEM_CATEGORIES][ITEM_MAX];

bool RPGGlobal ItemRanksRemoved;
ItemInfoPtr RewardList[MAX_DIFFICULTIES + 1][ITEM_CATEGORIES * ITEM_MAX];
bool RPGGlobal RewardsInit;
int RPGGlobal RewardsCount[(MAX_DIFFICULTIES + 1)];

NamedScriptSync void PopulateRewards()
{
    int Rarity;
    int Max;
    int i, j;
    
    // Populate the reward list
    for (i = 0; i < (MAX_DIFFICULTIES + 1); i++) { RewardsCount[i] = 0; }
    for (i = 0; i < ItemCategories; i++)
    {
        // Don't pick worthless ammo or loot
        if (i == 1 || i == 7)
            continue;
        
        for (j = 0; j < ItemMax[i]; j++)
        {
            Rarity = ItemData[i][j].Rarity;
            
            // Don't pick cheap stuff like a Pistol or Armor Bonus
            if (Rarity == -1 || ItemData[i][j].Price <= 100)
                continue;
            
            Max = RewardsCount[Rarity];
            RewardList[Rarity][Max] = &ItemData[i][j];
            RewardsCount[Rarity]++;
        }
    }
}

// Borrow the gnome sort method from the standard library because it's nice
NamedScriptSync bool SortRewards()
{
    int RewardIndex = 0;
    int Instructions = 0;
    ItemInfoPtr Temp;
    for (int i = 0; i < MAX_DIFFICULTIES + 1; i++)
    {
        while (RewardIndex < (RewardsCount[i] - 1))
        {
            if (RewardList[i][RewardIndex]->Price > RewardList[i][RewardIndex + 1]->Price)
            {
                Temp = RewardList[i][RewardIndex];
                RewardList[i][RewardIndex] = RewardList[i][RewardIndex + 1];
                RewardList[i][RewardIndex + 1] = Temp;
                
                RewardIndex -= 2;
                
                if (RewardIndex < 0) RewardIndex = 0;
            }
            else
                ++RewardIndex;
            
            // Because DRLA has a million weapons to sort
            if (Instructions++ >= 20000)
                return false;
        }
    }
    
    return true;
}

NamedScript void BuildItemData()
{
    if (ItemsInitialized) return;
    
    ItemCategories = 8; // 8 vanilla, 7 reserved for compatibility, 1 at the end for all the misc hidden stuff
    
    ITEMDATA_LIST;
    
    // Actor, Name, Price, Minimum Rank, Rarity, Sprite Name, X Offset, Y Offset
    
    // Weapons
    ITEMDATA_CATEGORY(0, "\CgWeapons", CF_NONE);
        ITEMDATA_DEF("DRPGChainsaw",        "Chainsaw",          300, 0, 0, "CSAWA0", 31, 23);
        ITEMDATA_DEF("DRPGPistol",          "Pistol",             25, 0, 0, "PISTA0", 11, 15);
        ITEMDATA_DEF("DRPGShotgun",         "Shotgun",           100, 0, 0, "SHOTA0", 31, 17);
        ITEMDATA_DEF("DRPGSuperShotgun",    "Super Shotgun",     500, 1, 1, "SGN2A0", 27, 15);
        ITEMDATA_DEF("DRPGChaingun",        "Chaingun",          750, 0, 0, "MGUNA0", 25, 18);
        ITEMDATA_DEF("DRPGRocketLauncher",  "Rocket Launcher",  1000, 1, 1, "LAUNA0", 31, 18);
        ITEMDATA_DEF("DRPGPlasmaRifle",     "Plasma Rifle",     2500, 1, 2, "PLASA0", 27, 19);
        ITEMDATA_DEF("DRPGBFG9000",         "BFG9000",          5000, 1, 3, "BFUGA0", 31, 38);
    ITEMDATA_CATEGORY_END;
    
    // Ammo
    ITEMDATA_CATEGORY(1, "\CeAmmo", CF_NOSELL);
        ITEMDATA_DEF("DRPGClip",            "Clip",               10, 0, -1, "CLIPA0",  2, 11);
        ITEMDATA_DEF("DRPGClipBox",         "Box of Bullets",     50, 0, -1, "AMMOA0", 12, 16);
        ITEMDATA_DEF("DRPGShell",           "Shells",             25, 0, -1, "SHELA0",  5,  7);
        ITEMDATA_DEF("DRPGShellBox",        "Box of Shells",     125, 0, -1, "SBOXA0", 16, 12);
        ITEMDATA_DEF("DRPGRocketAmmo",      "Rockets",            50, 1, -1, "ROCKA0",  6, 27);
        ITEMDATA_DEF("DRPGRocketBox",       "Box of Rockets",    250, 1, -1, "BROKA0", 27, 20);
        ITEMDATA_DEF("DRPGCell",            "Cells",             200, 1, -1, "CELLA0",  8, 12);
        ITEMDATA_DEF("DRPGCellPack",        "Cell Pack",        1000, 1, -1, "CELPA0", 15, 20);
        
        ITEMDATA_DEF("DRPGSmallBackpack",   "Ammo Satchel",     1000, 1, -1, "ASCHA0", 14, 30);
        ITEMDATA_DEF("DRPGBackpack",        "Backpack",         2500, 1, -1, "BPAKA0",  8, 25);
        ITEMDATA_DEF("DRPGBigBackpack",     "Big Backpack",     5000, 1, -1, "GPAKA0", 11, 29);
    ITEMDATA_CATEGORY_END;
    
    // Health
    ITEMDATA_CATEGORY(2, "\CaHealth", CF_NOSELL);
        ITEMDATA_DEF("DRPGMedkitRefill",    "Medkit",                5000, 2, 4, "MEDKA0", 14, 19);
        ITEMDATA_DEF("DRPGSoulsphere",      "Soulsphere",            2000, 2, 3, "SOULA0", 14, 39);
        ITEMDATA_DEF("DRPG1Up",             "1-Up",                 50000, 4, 7, "P1UPA0", 13, 74);
    ITEMDATA_CATEGORY_END;
    
    // Armor
    ITEMDATA_CATEGORY(3, "\CdArmor", CF_NONE);
        ITEMDATA_DEF("DRPGArmorBonus",              "Armor Bonus",                  1, 0, -1, "BON2A0",  7, 13);
        
        ITEMDATA_DEF("DRPGGreenArmor",              "Green Armor",                100, 0, 0, "ARM1A0", 15, 17);
        ITEMDATA_DEF("DRPGBlueArmor",               "Blue Armor",                 500, 0, 0, "ARM2A0", 15, 17);
        ITEMDATA_DEF("DRPGYellowArmor",             "Yellow Armor",              1000, 1, 1, "ARM3A0", 15, 17);
        ITEMDATA_DEF("DRPGRedArmor",                "Red Armor",                 5000, 2, 2, "ARM4A0", 15, 17);
        ITEMDATA_DEF("DRPGWhiteArmor",              "White Armor",              10000, 4, 4, "ARM5A0", 15, 17);
        
        ITEMDATA_DEF("DRPGReinforcedGreenArmor",    "Reinforced Green Armor",     200, 0, 1, "ARX1A0", 15, 17);
        ITEMDATA_DEF("DRPGReinforcedBlueArmor",     "Reinforced Blue Armor",     1000, 0, 1, "ARX2A0", 15, 17);
        ITEMDATA_DEF("DRPGReinforcedYellowArmor",   "Reinforced Yellow Armor",   2000, 1, 2, "ARX3A0", 15, 17);
        ITEMDATA_DEF("DRPGReinforcedRedArmor",      "Reinforced Red Armor",     10000, 2, 3, "ARX4A0", 15, 17);
        ITEMDATA_DEF("DRPGReinforcedWhiteArmor",    "Reinforced White Armor",   20000, 4, 5, "ARX5A0", 15, 17);
    ITEMDATA_CATEGORY_END;
    
    // Powerups
    ITEMDATA_CATEGORY(4, "\CqPowerups", CF_NONE);
        ITEMDATA_DEF("DRPGInvulnerabilityCharge",   "Invulnerability Charge",           25000, 2, 5, "CRG2A0",  6, 22);
        ITEMDATA_DEF("DRPGInvisibilityCharge",      "Invisibility Charge",              2500, 1, 1, "CRG1A0",  6, 22);
        ITEMDATA_DEF("DRPGTimeSphere",              "Time Sphere",                      1000, 4, 1, "TIMEA0", 16, 45);
        ITEMDATA_DEF("DRPGRegenSphere",             "Regeneration Sphere",              1000, 2, 1, "REGNA0", 12, 38);
        ITEMDATA_DEF("DRPGRadSuit",                 "Radiation Suit",                   250, 0, 0, "SUITA0", 11, 51);
        ITEMDATA_DEF("DRPGInfrared",                "IR Goggles",                       500, 0, 0, "PVISA0", 11,  9);
        ITEMDATA_DEF("DRPGBerserk",                 "Berserk Pack",                     1000, 1, 1, "PSTRA0", 12, 15);
        ITEMDATA_DEF("DRPGAllMap",                  "Computer Area Map",                1000, 1, 1, "PMAPA0", 13, 23);
        ITEMDATA_DEF("DRPGWings",                   "Wings",                            5000, 2, 2, "WINGA0", 13, 36);
        ITEMDATA_DEF("DRPGMegasphere",              "Megasphere",                       10000, 4, 4, "MEGAA0", 12, 32);
        ITEMDATA_DEF("DRPGImmunityCrystalMelee",    "Melee Immunity Crystal",           100000, 8, 8, "CRYSA0", 16, 48);
        ITEMDATA_DEF("DRPGImmunityCrystalBullet",   "Bullet Immunity Crystal",          100000, 8, 8, "CRYSB0", 16, 48);
        ITEMDATA_DEF("DRPGImmunityCrystalFire",     "Fire Immunity Crystal",            100000, 8, 8, "CRYSC0", 16, 48);
        ITEMDATA_DEF("DRPGImmunityCrystalPlasma",   "Plasma Immunity Crystal",          100000, 8, 8, "CRYSD0", 16, 48);
        ITEMDATA_DEF("DRPGImmunityCrystalLightning","Lightning Immunity Crystal",       100000, 8, 8, "CRYSE0", 16, 48);
        ITEMDATA_DEF("DRPGImmunityCrystalToxic",    "Toxic Immunity Crystal",           100000, 8, 8, "CRYSF0", 16, 48);
        ITEMDATA_DEF("DRPGImmunityCrystalRadiation","Radiation Immunity Crystal",       100000, 8, 8, "CRYSG0", 16, 48);
    ITEMDATA_CATEGORY_END;
    
    // Shield Parts - Built Dynamically
    ITEMDATA_CATEGORY(5, "\CvShield Parts", CF_NONE);
        ITEMDATA_DEF("DRPGBasicShieldPackage",      "Basic Shield Package",      5000, 0, 1, "SHPAA0", 16, 32);
    ITEMDATA_CATEGORY_END;
    
    // Shield Parts
    for (int i = 0; i < 3; i++)
    {
        str ShieldName;
        int ShieldPartCost;
        
        ItemMax[5] += ShieldPartsMax[i];
        
        switch (i)
        {
        case 0: ShieldName = "Shield Body - ";      break;
        case 1: ShieldName = "Shield Battery - ";   break;
        case 2: ShieldName = "Shield Capacitor - "; break;
        };
        
        for (int j = 0; j < ShieldPartsMax[i]; j++)
        {
            ShieldPartCost = 0;

            // Name
            ItemData[5][ItemIndex].Actor = StrParam("%S", ShieldParts[i][j].Actor);
            ItemData[5][ItemIndex].Name = StrParam("%S%S\C-", ShieldName, ShieldParts[i][j].Name);
            
            // Price
            ShieldPartPtr PartPtr = &ShieldParts[i][j];
            int Capacity = PartPtr->Capacity;
            int ChargeRate = PartPtr->ChargeRate;
            int DelayRate = PartPtr->DelayRate;
            
            // New Pricing Code, not perfect but...
            ChargeRate += 1; // Shifts range to 0 - 31
            DelayRate = (DelayRate - 15) * -1; // Shifts range to 0 - 20

            ShieldPartCost += Capacity * 50;
            ShieldPartCost += ChargeRate * 650;
            ShieldPartCost += DelayRate * 40;
            
            ShieldPartCost *= (Capacity / 500) + 1;
            ShieldPartCost *= (ChargeRate / 10) + 1;
            DelayRate -= 15;
            if (DelayRate > 0)
                ShieldPartCost *= DelayRate;
            if (i == 0) ShieldPartCost += (j * 10 / 21) * j * 950;  // 21 max index
            if (i == 1) ShieldPartCost += (j * 10 / 12) * j * 5000; // 12 max index
            if (i == 2) ShieldPartCost += (j * 10 / 14) * j * 4285; // 14 max index
            
            // Round to the nearest 50
            ShieldPartCost /= 50;
            ShieldPartCost *= 50;
            
            // Don't go below 1000 Credits
            if (ShieldPartCost < 1000)
                ShieldPartCost = 1000;

            // Apply Price
            ItemData[5][ItemIndex].Price = ShieldPartCost;
            
            // Item self-reference info for DRLA checks
            // [KS] How long has this been missing now? Holy hell.
            ItemData[5][ItemIndex].Category = 5;
            ItemData[5][ItemIndex].Index = ItemIndex;
            
            // Rank
            ItemData[5][ItemIndex].Rank = j / 1.5;
            
            //Rarity
            int rarity = 1;
            if (ShieldPartCost < 999999) rarity = 8;
            if (ShieldPartCost < 200000) rarity = 7;
            if (ShieldPartCost < 120000) rarity = 6;
            if (ShieldPartCost < 90000) rarity = 5;
            if (ShieldPartCost < 70000) rarity = 4;
            if (ShieldPartCost < 50000) rarity = 3;
            if (ShieldPartCost < 35000) rarity = 2;
            if (ShieldPartCost < 20000) rarity = 1;
            
            ItemData[5][ItemIndex].Rarity = rarity;
            
            // Sprite Info
            ItemData[5][ItemIndex].Sprite.Name = ShieldParts[i][j].Icon;
            ItemData[5][ItemIndex].Sprite.XOff = 16;
            ItemData[5][ItemIndex].Sprite.YOff = 32;
            
            ItemIndex++;
        };
    };

    // Shield Accessories
    auto ShieldAccsPtr ShieldAccessoriesSorted[MAX_ACCESSORIES];
    for (int i = 0; i < MAX_ACCESSORIES; i++)
        ShieldAccessoriesSorted[i] = &ShieldAccessories[i];
    
    qsort(ShieldAccessoriesSorted, MAX_ACCESSORIES, sizeof(ShieldAccsPtr), ShieldInversePriceSort);
    
    ItemMax[5] += MAX_ACCESSORIES;
    for (int i = 0; i < MAX_ACCESSORIES; i++)
    {
        ShieldAccsPtr Accessory = ShieldAccessoriesSorted[i];
        
        ItemData[5][ItemIndex].Actor = Accessory->Actor;
        ItemData[5][ItemIndex].Name = StrParam("Shield Accessory - %S", Accessory->Name);
        ItemData[5][ItemIndex].Price = Accessory->Price;
        ItemData[5][ItemIndex].Rank = i * (MAX_RANK / 2) / MAX_ACCESSORIES; // This makes all accessories available by SSgt +
        
        //Rarity
        int rarity = 1;
        if (Accessory->Price < 999999) rarity = 8;
        if (Accessory->Price < 200000) rarity = 7;
        if (Accessory->Price < 120000) rarity = 6;
        if (Accessory->Price < 90000) rarity = 5;
        if (Accessory->Price < 70000) rarity = 4;
        if (Accessory->Price < 50000) rarity = 3;
        if (Accessory->Price < 35000) rarity = 2;
        if (Accessory->Price < 20000) rarity = 1;
        
        ItemData[5][ItemIndex].Rarity = rarity;
        
        ItemData[5][ItemIndex].Category = 5;
        ItemData[5][ItemIndex].Index = ItemIndex;
        
        // Sprite Info
        ItemData[5][ItemIndex].Sprite.Name = Accessory->Icon;
        ItemData[5][ItemIndex].Sprite.XOff = 16;
        ItemData[5][ItemIndex].Sprite.YOff = 32;
        
        ItemIndex++;
    };
    
    // Stims/Augmentations/Turret Parts
    ITEMDATA_CATEGORY(6, "\CkStims/Augs/Turret", CF_NONE);
        ITEMDATA_DEF("DRPGStimSmall",           "Small Stim",                         1000, 0, 1, "STIMB0", 16, 29);
        ITEMDATA_DEF("DRPGStimMedium",          "Medium Stim",                        2500, 2, 2, "STIMB0", 16, 29);
        ITEMDATA_DEF("DRPGStimLarge",           "Large Stim",                         5000, 4, 4, "STIMB0", 16, 29);
        ITEMDATA_DEF("DRPGStimXL",              "Extra-Large Stim",                  10000, 8, 6, "STIMB0", 16, 29);
        ITEMDATA_DEF("DRPGStimDetox",           "\CdDetox\C- Hypospray",              2500, 1, 2, "STIMC0",  6, 31);
        
        ITEMDATA_DEF("DRPGVialStrength",        "\CgStrength\C- Vial",                 500, 4, 0, "STVLA0",  4, 16);
        ITEMDATA_DEF("DRPGVialDefense",         "\CdDefense\C- Vial",                  500, 4, 0, "STVLB0",  4, 16);
        ITEMDATA_DEF("DRPGVialVitality",        "\CaVitality\C- Vial",                 500, 4, 0, "STVLC0",  4, 16);
        ITEMDATA_DEF("DRPGVialEnergy",          "\CnEnergy\C- Vial",                   500, 4, 0, "STVLD0",  4, 16);
        ITEMDATA_DEF("DRPGVialRegeneration",    "\CtRegeneration\C- Vial",             500, 4, 0, "STVLE0",  4, 16);
        ITEMDATA_DEF("DRPGVialAgility",         "\CiAgility\C- Vial",                  500, 4, 0, "STVLF0",  4, 16);
        ITEMDATA_DEF("DRPGVialCapacity",        "\ChCapacity\C- Vial",                 500, 4, 0, "STVLG0",  4, 16);
        ITEMDATA_DEF("DRPGVialLuck",            "\CfLuck\C- Vial",                     500, 4, 0, "STVLH0",  4, 16);
        ITEMDATA_DEF("DRPGVialPurifier",        "\CcPurifier\C- Vial",                1000, 4, 1, "STVLI0",  4, 16);
        ITEMDATA_DEF("DRPGVialPotency",         "\CjPotency\C- Vial",                 1000, 4, 1, "STVLJ0",  4, 16);
        ITEMDATA_DEF("DRPGVialIndestructible",  "\CqIndestructible\C- Vial",          1000, 4, 1, "STVLK0",  4, 16);
        ITEMDATA_DEF("DRPGVialShadow",          "\CrShadow\C- Vial",                  1000, 4, 1, "STVLL0",  4, 16);
        ITEMDATA_DEF("DRPGVialInfinity",        "\CkInfinity\C- Vial",                1000, 4, 1, "STVLM0",  4, 16);
        ITEMDATA_DEF("DRPGVialChrono",          "\CdChrono\C- Vial",                  1000, 4, 1, "STVLN0",  4, 16);
        ITEMDATA_DEF("DRPGVialAdrenaline",      "\CtAdrenaline\C- Vial",              1000, 4, 1, "STVLO0",  4, 16);
        ITEMDATA_DEF("DRPGVialGravity",         "\CiGravity\C- Vial",                 1000, 4, 1, "STVLP0",  4, 16);
        ITEMDATA_DEF("DRPGVialVampire",         "\CaVampire\C- Vial",                 1000, 4, 1, "STVLQ0",  4, 16);
        ITEMDATA_DEF("DRPGVialRage",            "\CmRage\C- Vial",                    1000, 4, 1, "STVLR0",  4, 16);
        ITEMDATA_DEF("DRPGVialMagnetic",        "\CcMagnetic\C- Vial",                1000, 4, 1, "STVLS0",  4, 16);
        ITEMDATA_DEF("DRPGStimPackageStat",     "Stat Stim Package",                  5000, 4, 5, "STPAA0", 30, 16);
        ITEMDATA_DEF("DRPGStimPackagePowerup",  "Powerup Stim Package",              10000, 4, 7, "STPAB0", 27, 16);
        
        ITEMDATA_DEF("DRPGAugCanister",         "Augmentation Canister",            100000, 4, 8, "AUGCA0", 12, 24);
        ITEMDATA_DEF("DRPGAugUpgradeCanister",  "Augmentation Upgrade Canister",    100000, 4, 8, "AUGUA0", 12, 24);
        ITEMDATA_DEF("DRPGAugSlotUpgrade",      "Augmentation Slot Upgrade",        250000, 8, 8, "AUGUB0", 16, 25);
        ITEMDATA_DEF("DRPGBatterySmall",        "Small Battery",                      1000, 4, 1, "BATTA0",  5, 13);
        ITEMDATA_DEF("DRPGBatteryLarge",        "Large Battery",                      2500, 8, 2, "BATTB0", 14, 21);
        
        ITEMDATA_DEF("DRPGTurretPart",          "Turret Part",                        1000, 1, 1, "TPRTA0", 29, 21);
        ITEMDATA_DEF("DRPGTurretPartCrate",     "Turret Parts Crate",                50000, 4, 4, "TCRTA0", 29, 26);
    ITEMDATA_CATEGORY_END;
    
    // Generic Loot
    ITEMDATA_CATEGORY(7, "\CfLoot", CF_NOBUY | CF_NODROP);
        ITEMDATA_DEF("DRPGLootMedicalSupplies",     "Medical Supplies",     100, 0, -1, "LT01A0",  7, 15);
        ITEMDATA_DEF("DRPGLootChemicals",           "Chemicals",            250, 0, -1, "LT02A0", 11, 34);
        ITEMDATA_DEF("DRPGLootHazardousMaterials",  "Hazardous Materials",  250, 0, -1, "LT03A0", 14, 19);
        ITEMDATA_DEF("DRPGLootAnomalousMaterials",  "Anomalous Materials",  250, 0, -1, "LT04A0",  5, 20);
        ITEMDATA_DEF("DRPGLootBriefcase",           "Briefcase Data",       500, 0, -1, "LT05A0", 14, 18);
        ITEMDATA_DEF("DRPGLootComputerData",        "Computer Data",        500, 0, -1, "LT06A0",  6, 23);
        ITEMDATA_DEF("DRPGLootGunParts",            "Gun Parts",            250, 0, -1, "LT07A0", 10, 24);
        ITEMDATA_DEF("DRPGLootAmmoCasings",         "Ammo Casings",          50, 0, -1, "LT08A0", 12,  8);
        ITEMDATA_DEF("DRPGLootFuelCapsule",         "Fuel Capsule",         100, 0, -1, "LT09A0",  7, 19);
        ITEMDATA_DEF("DRPGLootScrapMetals",         "Scrap Metals",         100, 0, -1, "LT10A0", 12, 15);
        ITEMDATA_DEF("DRPGLootScrapElectronics",    "Scrap Electronics",    100, 0, -1, "LT11A0",  8, 22);
        ITEMDATA_DEF("DRPGLootExperimentalParts",   "Experimental Parts",   500, 0, -1, "LT12A0", 15, 21);
        ITEMDATA_DEF("DRPGLootDemonArtifact",       "Demon Artifacts",      500, 0, -1, "LT13A0", 12, 22);
    ITEMDATA_CATEGORY_END;
    
    // Compatibility handling - Extras
    if (CompatMode == COMPAT_EXTRAS)
    {
        // Weapons
        ItemData[0][0].Actor = "DRPGChainsawExtras";
        ItemData[0][1].Actor = "DRPGPistolExtras";
        ItemData[0][2].Actor = "DRPGShotgunExtras";
        ItemData[0][3].Actor = "DRPGSuperShotgunExtras";
        ItemData[0][4].Actor = "DRPGChaingunExtras";
        ItemData[0][5].Actor = "DRPGRocketLauncherExtras";
        ItemData[0][6].Actor = "DRPGPlasmaRifleExtras";
        ItemData[0][6].Sprite.Name = "PLASA0";
        ItemData[0][6].Sprite.XOff = 27;
        ItemData[0][6].Sprite.YOff = 12;
        ItemData[0][7].Actor = "DRPGBFG9000Extras";
        
        // Ammo
        ItemData[1][0].Actor = "Clip2";
        ItemData[1][1].Actor = "ClipBox2";
        ItemData[1][2].Actor = "Shell2";
        ItemData[1][2].Sprite.Name = "SHELA0";
        ItemData[1][2].Sprite.XOff = 8;
        ItemData[1][2].Sprite.YOff = 8;
        ItemData[1][3].Actor = "ShellBox2";
        ItemData[1][4].Actor = "RocketAmmo2";
        ItemData[1][4].Sprite.Name = "ROCKA0";
        ItemData[1][4].Sprite.XOff = 8;
        ItemData[1][4].Sprite.YOff = 36;
        ItemData[1][5].Actor = "RocketBox2";
        ItemData[1][5].Sprite.Name = "BROKA0";
        ItemData[1][5].Sprite.XOff = 27;
        ItemData[1][5].Sprite.YOff = 26;
        ItemData[1][6].Actor = "Cell2";
        ItemData[1][7].Actor = "CellPack2";
    }
    
    // Compatibility Handling - DoomRL
    if (CompatMode == COMPAT_DRLA)
    {
        // Categories
        ItemCategories = 10;
        
        // Weapons
        ITEMDATA_CATEGORY(0, "\CgWeapons", CF_NONE);
            // Common Weapons
         // ITEMDATA_DEF("RLCombatKnife",                           "CombatKnife",                                              20,  0, "CKNIX0", 31, 23);
            ITEMDATA_DEF("RLChainsaw",                              "Chainsaw",                                                300,  0, 0, "NSAWX0", 31, 23);
            ITEMDATA_DEF("RLPistol",                                "Pistol",                                                   25,  0, 0, "PISGX0", 11, 13);
            ITEMDATA_DEF("RLShotgun",                               "Shotgun",                                                 100,  0, 0, "PKSGX0", 31, 17);
            ITEMDATA_DEF("RLCombatShotgun",                         "Combat Shotgun",                                          100,  0, 0, "CSHOX0", 25, 17);
            ITEMDATA_DEF("RLDoubleShotgun",                         "Double Shotgun",                                          350,  1, 0, "DBLSX0", 14,  8);
            ITEMDATA_DEF("RLChaingun",                              "Chaingun",                                                750,  0, 0, "PKCGX0", 25, 18);
            ITEMDATA_DEF("RLBattleRifle",                           "Battle Rifle",                                            750,  1, 0, "UACRX0", 23, 15);
            ITEMDATA_DEF("RLRocketLauncher",                        "Rocket Launcher",                                        1000,  1, 1, "RLAUX0", 31, 18);
            ITEMDATA_DEF("RLPlasmaRifle",                           "Plasma Rifle",                                           2500,  1, 2, "PLSRX0", 27, 19);
            ITEMDATA_DEF("RLBFG9000",                               "BFG9000",                                                5000,  2, 3, "BFGGX0", 31, 38);
            
            // Exotic Weapons
            ITEMDATA_DEF("RLBlaster",                               "Blaster \Ct[Exotic]\C-",                                  550,  2, 0, "BLASX0", 12, 14);
            ITEMDATA_DEF("RLCombatPistol",                          "Combat Pistol \Ct[Exotic]\C-",                           1350,  3, 1, "OLOKX0", 10, 13);
            ITEMDATA_DEF("RLHandCannon",                            "Handcannon \Ct[Exotic]\C-",                              1800,  4, 1, "DEAPX0", 11, 14);
            ITEMDATA_DEF("RLMarksmanPistol",                        "Marksman Pistol \Ct[Exotic]\C-",                         2500,  4, 2, "MRKPX0",  9, 12);
            ITEMDATA_DEF("RLSuperShotgun",                          "Super Shotgun \Ct[Exotic]\C-",                           2500,  4, 2, "NSSGX0", 27,  9);
            ITEMDATA_DEF("RLAssaultShotgun",                        "Assault Shotgun \Ct[Exotic]\C-",                         3000,  4, 3, "ASHOX0", 31, 27);
            ITEMDATA_DEF("RLUzi",                                   "Uzi \Ct[Exotic]\C-",                                     1900,  3, 1, "RUZIX0", 20, 26);
            ITEMDATA_DEF("RLMinigun",                               "Minigun \Ct[Exotic]\C-",                                15000,  6, 5, "ZGGGX0", 30, 20);
            ITEMDATA_DEF("RLMissileLauncher",                       "Missile Launcher \Ct[Exotic]\C-",                        5000,  5, 3, "CLAUX0", 45, 24);
            ITEMDATA_DEF("RLNapalmLauncher",                        "Napalm Launcher \Ct[Exotic]\C-",                         8500,  6, 4, "NAPAX0", 22, 20);
            ITEMDATA_DEF("RLLaserRifle",                            "Laser Rifle \Ct[Exotic]\C-",                             4500,  4, 3, "LASRX0", 18, 11);
            ITEMDATA_DEF("RLPlasmaShotgun",                         "Plasma Shotgun \Ct[Exotic]\C-",                         10000,  5, 4, "PSHOX0", 22, 14);
            ITEMDATA_DEF("RLTristarBlaster",                        "Tristar Blaster \Ct[Exotic]\C-",                        12500,  5, 4, "TRISX0", 35, 35);
            ITEMDATA_DEF("RLCombatTranslocator",                    "Combat Translocator \Ct[Exotic]\C-",                     7000,  5, 3, "CTLOX0", 18, 11);
            ITEMDATA_DEF("RLNuclearPlasmaPistol",                   "Nuclear Plasma Pistol \Ct[Exotic]\C-",                  30000,  7, 6, "NUPPX0", 11, 14);
            ITEMDATA_DEF("RLNuclearPlasmaRifle",                    "Nuclear Plasma Rifle \Ct[Exotic]\C-",                   50000,  9, 7, "NUKPX0", 23, 14);
            ITEMDATA_DEF("RLNuclearBFG9000",                        "Nuclear BFG9000 \Ct[Exotic]\C-",                        90000, 10, 8, "NUKBX0", 28, 18);
            
            // Superior Weapons
            ITEMDATA_DEF("RLMarksmanRifle",                         "Marksman Rifle \Ci[Superior]\C-",                       18000, 12, 5, "MRKRX0", 26, 18);
            ITEMDATA_DEF("RLVanguardRifle",                         "Vanguard Rifle \Ci[Superior]\C-",                       17500, 12, 5, "VANRX0", 26, 13);
            ITEMDATA_DEF("RLHuntingRevolver",                       "Hunting Revolver \Ci[Superior]\C-",                     25000, 12, 5, "HREVX0", 12, 14);
            ITEMDATA_DEF("RLThompson",                              "Tommy Gun \Ci[Superior]\C-",                            16000, 12, 5, "TGUNX0", 23, 17);
            ITEMDATA_DEF("RLPP7",                                   "PP7 \Ci[Superior]\C-",                                  15000, 12, 5, "BPP7X0", 8, 10);
            ITEMDATA_DEF("RLHuntingShotgun",                        "Hunting Shotgun \Ci[Superior]\C-",                      28000, 12, 5, "HUNTX0", 32, 12);
            ITEMDATA_DEF("RLRCP90",                                 "RC-P90 \Ci[Superior]\C-",                               26000, 12, 5, "RCP9X0", 24, 15);
            
            // Unique Weapons
            ITEMDATA_DEF("RLJackhammer",                            "Jackhammer \Cd[Unique]\C-",                             32000, -1, 6, "SMAGX0", 27, 14);
            ITEMDATA_DEF("RLRailgun",                               "Railgun \Cd[Unique]\C-",                                38000, -1, 6, "RAILX0", 23, 13);
            ITEMDATA_DEF("RLMysteriousMagnum",                      "Mysterious Magnum \Cd[Unique]\C-",                      50000, -1, 7, "MMAGX0", 15, 12);
            ITEMDATA_DEF("RLBFG10k",                                "BFG10k \Cd[Unique]\C-",                                 75000, -1, 8, "BFG4X0", 34, 24);
            ITEMDATA_DEF("RLUnknownHerald",                         "Unknown Herald \Cd[Unique]\C-",                         60000, -1, 7, "UNKHX0",  8, 10);
            ITEMDATA_DEF("RLFragShotgun",                           "Frag Shotgun \Cd[Unique]\C-",                           30000, -1, 6, "FRSHX0", 28, 11);
            ITEMDATA_DEF("RLQuadShotgun",                           "Quad Shotgun \Cd[Unique]\C-",                           64000, -1, 7, "SHT4X0", 26, 16);
            ITEMDATA_DEF("RLLightweaver",                           "Lightweaver \Cd[Unique]\C-",                           220000, -1, 8, "KARAX0", 16, 10);
            ITEMDATA_DEF("RLTrigun",                                "Trigun \Cd[Unique]\C-",                                 44000, -1, 6, "TRIGX0", 15, 12);
            ITEMDATA_DEF("RLGrammatonClericBeretta",                "Grammaton Cleric Beretta \Cd[Unique]\C-",               33000, -1, 6, "GCBPX0", 12, 13);
            ITEMDATA_DEF("RLAntiFreakJackal",                       "Anti-Freak Jackal \Cd[Unique]\C-",                      56000, -1, 7, "AFJKX0", 15, 14);
            ITEMDATA_DEF("RLHellsingARMSCasull",                    "Hellsing ARMS Casull \Cd[Unique]\C-",                   52000, -1, 7, "HSACX0", 15, 14);
            ITEMDATA_DEF("RLTantrumCannon",                         "Quantum Tantrum Cannon \Cd[Unique]\C-",                 36000, -1, 6, "QTCWX0", 14, 13);
            ITEMDATA_DEF("RLRevenantsLauncher",                     "Revenant's Launcher \Cd[Unique]\C-",                    32000, -1, 6, "REVLX0", 22, 13);
            ITEMDATA_DEF("RLNullPointer",                           "Charch's Null Pointer \Cd[Unique]\C-",                  50000, -1, 7, "NULPX0", 23, 14);
            ITEMDATA_DEF("RLParticleBeamCannon",                    "Particle Beam Cannon \Cd[Unique]\C-",                   75000, -1, 8, "PBCNX0", 26, 16);
            ITEMDATA_DEF("RLSteelBeast",                            "Steel Beast \Cd[Unique]\C-",                            30000, -1, 6, "STBEX0", 36, 11);
            ITEMDATA_DEF("RLPlasmaRedirectionCannon",               "Plasma Redirection Cannon \Cd[Unique]\C-",              35000, -1, 6, "PRDCX0", 32, 24);
            ITEMDATA_DEF("RLSussGun",                               "Suss Gun \Cd[Unique]\C-",                               50000, -1, 7, "SUSSX0", 38, 37);
            ITEMDATA_DEF("RLMIRVLauncher",                          "MIRV Launcher \Cd[Unique]\C-",                          75000, -1, 8, "MIRVX0", 20, 16);
            ITEMDATA_DEF("RLMarathonAssaultRifle",                  "MA-75B Assault Rifle \Cd[Unique]\C-",                   52000, -1, 7, "MA75Y0",  0,  0);
            ITEMDATA_DEF("RLMarathonShotguns",                      "WSTE-M5 Shotgun \Cd[Unique]\C-",                        70000, -1, 8, "WSTEY0",  6,  6);
            ITEMDATA_DEF("RLWidowmakerSMG",                         "Widowmaker SMG \Cd[Unique]\C-",                         30000, -1, 6, "WSMGX0", 24, 20);
            ITEMDATA_DEF("RLChameleonRifle",                        "Chameleon Rifle \Cd[Unique]\C-",                       160000, -1, 8, "CRM1X0", 26, 18);
            ITEMDATA_DEF("RLNanomachicArmamentGenerator",           "Nanomachic Armament Generator \Cd[Unique]\C-",         200000, -1, 8, "NAG0X0", 13, 19);
            ITEMDATA_DEF("RLNuclearOnslaught",                      "Nuclear Onslaught \Cd[Unique]\C-",                     380000, -1, 8, "NKO0X0", 29, 54);
         // ITEMDATA_DEF("RLSubtleKnife",                           "Subtle Knife \Cd[Unique]\C-",                           30000, -1, "SUBKX0", 38, 37);
         // ITEMDATA_DEF("RLFusionMortar",                          "Fusion Mortar \Cd[Unique]\C-",                          90000, -1, "FMORX0", 38, 37);
         // ITEMDATA_DEF("RLSpectreRevolver",                       "The Spectre \Cd[Unique]\C-",                            31000, -1, "SPERX0", 38, 37);
            
            // Demonic Weapons
         // ITEMDATA_DEF("RLMonsterFrisbee",                        "Monster Frisbee \Cg[Demonic]\C-",                       78000, -1, "MFRSX0", 37, 21);
            ITEMDATA_DEF("RLDeathsGaze",                            "Death's Gaze \Cg[Demonic]\C-",                          50000, -1, 9, "DGAZX0", 10, 13);
            ITEMDATA_DEF("RLHellsReign",                            "Hell's Reign \Cg[Demonic]\C-",                          45000, -1, 9, "HELRX0", 37, 21);
            ITEMDATA_DEF("RLSoulstormRifle",                        "Soulstorm Rifle \Cg[Demonic]\C-",                       60000, -1, 9, "SOLDX0", 27, 17);
         // ITEMDATA_DEF("RLMortalyzer",                            "Mortalyzer \Cg[Demonic]\C-",                            58000, -1, "MRTZX0", 37, 21);
         // ITEMDATA_DEF("RLDreadshotMortar",                       "Dreadshot Mortar \Cg[Demonic]\C-",                      60000, -1, "DSMTX0", 37, 21);
            ITEMDATA_DEF("RLUnmaker",                               "Unmaker \Cg[Demonic]\C-",                             6666666, -1, 9, "UNMAX0", 39, 17);
                        
            // Legendary Weapons
         // ITEMDATA_DEF("RLDragonslayer",                          "Dragonslayer \Cf[Legendary]\C-",                      5000000, -1, "DSLYX0", 38, 37);
            ITEMDATA_DEF("RLJudgeOfTheDead",                        "Judge Of The Dead \Cf[Legendary]\C-",                 2500000, -1, 10, "JOTDX0", 19, 12);
            ITEMDATA_DEF("RLHurricaneCannon",                       "Hurricane Cannon \Cf[Legendary]\C-",                  2200000, -1, 10, "HURRX0", 20, 18);
            ITEMDATA_DEF("RLNeuralStunner",                         "Neural Stunner \Cf[Legendary]\C-",                    2000000, -1, 10, "NEURB0",  7, 13);
            ITEMDATA_DEF("RLBaronBlaster",                          "Baron Blaster \Cf[Legendary]\C-",                     1600000, -1, 10, "BABLX0", 11, 14);
            ITEMDATA_DEF("RLDuke2Rifle",                            "Rigelatin Assault Weapon \Cf[Legendary]\C-",          3000000, -1, 10, "DN2RX0", 28,  9);
            ITEMDATA_DEF("RLBFGInfinity",                           "BFG Infinity \Cf[Legendary]\C-",                     75000000, -1, 10, "BFGIX0", 25, 20);
            ITEMDATA_DEF("RLRealityDistortionArray",                "Reality Distortion Array \Cf[Legendary]\C-",        123456789, -1, 10, "RD1NX0", 25, 20);
            
            // Basic Assembled Weapons
            ITEMDATA_DEF("RLSpeedloaderPistol",                     "Revolver \Cv[Assembled]\C-",                              800, -1, -1, "REVOX0", 16, 20);
            ITEMDATA_DEF("RLSilencedPistol",                        "Silenced Pistol \Cv[Assembled]\C-",                       500, -1, -1, "SILPX0", 17, 15);
            ITEMDATA_DEF("RLStealthRifle",                          "Stealth Rifle \Cv[Assembled]\C-",                        1800, -1, -1, "STELX0", 25, 14);
            ITEMDATA_DEF("RLShredderPistol",                        "Shredder Pistol \Cv[Assembled]\C-",                      1200, -1, -1, "SHRPX0", 10, 13);
            ITEMDATA_DEF("RLShredderShotgun",                       "Shredder Shotgun \Cv[Assembled]\C-",                     6000, -1, -1, "SHRSX0", 23, 12);
            ITEMDATA_DEF("RLElephantGun",                           "Elephant Gun \Cv[Assembled]\C-",                         1800, -1, -1, "ELEGX0", 21, 13);
            ITEMDATA_DEF("RLGatlingGun",                            "Gatling Gun \Cv[Assembled]\C-",                          2500, -1, -1, "DGTGX0", 38, 19);
            ITEMDATA_DEF("RLMicroLauncher",                         "Micro Launcher \Cv[Assembled]\C-",                       3000, -1, -1, "MICFX0", 21,  8);
            ITEMDATA_DEF("RLTacticalShotgun",                       "Tactical Shotgun \Cv[Assembled]\C-",                     2800, -1, -1, "ASHOX0", 31, 27);
            ITEMDATA_DEF("RLFlamethrower",                          "Flamethrower \Cv[Assembled]\C-",                         2800, -1, -1, "FLAMX0", 31, 27);
            ITEMDATA_DEF("RLShrapnelCannon",                        "Shrapnel Cannon \Cv[Assembled]\C-",                      4200, -1, -1, "SHRCX0", 30, 23);
            ITEMDATA_DEF("RLSniperRifle",                           "Sniper Rifle \Cv[Assembled]\C-",                         3200, -1, -1, "SNPRX0", 40, 15);
            ITEMDATA_DEF("RLNuclearPlasmaRevolver",                 "Nuclear Plasma Revolver \Cv[Assembled]\C-",             52000, -1, -1, "NPRVX0", 13, 13);
            ITEMDATA_DEF("RLHeavyShotgun",                          "Heavy Shotgun \Cv[Assembled]\C-",                        1800, -1, -1, "HSHOX0", 31, 15);
            ITEMDATA_DEF("RLHeavyCombatShotgun",                    "Heavy Combat Shotgun \Cv[Assembled]\C-",                 1800, -1, -1, "CSHOX0", 25, 17);
            ITEMDATA_DEF("RLHeavyDoubleShotgun",                    "Heavy Double Shotgun \Cv[Assembled]\C-",                 2600, -1, -1, "HDSHX0", 22, 13);
            ITEMDATA_DEF("RLHeavySuperShotgun",                     "Heavy Super Shotgun \Cv[Assembled]\C-",                  5200, -1, -1, "HSSGX0", 27, 11);
            ITEMDATA_DEF("RLHeavyAssaultShotgun",                   "Heavy Assault Shotgun \Cv[Assembled]\C-",                3500, -1, -1, "ASHOX0", 31, 27);
            ITEMDATA_DEF("RLHeavyPlasmaShotgun",                    "Heavy Plasma Shotgun \Cv[Assembled]\C-",                 8500, -1, -1, "PSHOX0", 22, 14);
            ITEMDATA_DEF("RLHeavyHuntingShotgun",                   "Heavy Hunting Shotgun \Cv[Assembled]\C-",               36000, -1, -1, "HUNTX0", 32, 12);
            
            // Piercing Blade Assembled Weapons
         // ITEMDATA_DEF("RLPiercingCombatKnife",                   "Piercing Blade \Cv[Assembled]\C-",                       1000, -1, "PKNIX0", 11, 13);
            ITEMDATA_DEF("RLPiercingChainsaw",                      "Piercing Chainsaw \Cv[Assembled]\C-",                    1500, -1, -1, "PSAWX0", 31, 23);
         // ITEMDATA_DEF("RLPiercingAxe",                           "Piercing Axe \Cv[Assembled]\C-",                         2500, -1, "PAXEX0", 11, 13);
         // ITEMDATA_DEF("RLPiercingMachete",                       "Piercing Machete \Cv[Assembled]\C-",                     2200, -1, "PMACX0", 11, 13);
         // ITEMDATA_DEF("RLPiercingMace",                          "Piercing Mace \Cv[Assembled]\C-",                        2800, -1, "PMCEX0", 11, 13);
            
            // High Power Assembled Weapons
            ITEMDATA_DEF("RLHighPowerPistol",                       "High Power Pistol \Cv[Assembled]\C-",                     700, -1, -1, "QPISX0", 16, 15);
            ITEMDATA_DEF("RLHighPowerChaingun",                     "High Power Chaingun \Cv[Assembled]\C-",                  2100, -1, -1, "QCHGX0", 26, 20);
            ITEMDATA_DEF("RLHighPowerBattleRifle",                  "High Power Battle Rifle \Cv[Assembled]\C-",              2100, -1, -1, "QRIFX0", 23, 15);
            ITEMDATA_DEF("RLHighPowerPlasmaRifle",                  "High Power Plasma Rifle \Cv[Assembled]\C-",              7000, -1, -1, "QPLSX0", 28, 22);
            ITEMDATA_DEF("RLHighPowerBFG9000",                      "High Power BFG9000 \Cv[Assembled]\C-",                  11000, -1, -1, "BFGGX0", 31, 38);
            ITEMDATA_DEF("RLHighPowerBlaster",                      "High Power Blaster \Cv[Assembled]\C-",                   1600, -1, -1, "QBLAX0", 12, 15);
            ITEMDATA_DEF("RLHighPowerCombatPistol",                 "High Power Combat Pistol \Cv[Assembled]\C-",             2000, -1, -1, "QCPSX0", 10, 13);
            ITEMDATA_DEF("RLHighPowerHandCannon",                   "High Power Handcannon \Cv[Assembled]\C-",                4200, -1, -1, "QDEAX0", 12, 15);
            ITEMDATA_DEF("RLHighPowerMarksmanPistol",               "High Power Marksman Pistol \Cv[Assembled]\C-",           5000, -1, -1, "QMRKX0", 11, 14);
            ITEMDATA_DEF("RLHighPowerUzi",                          "High Power Uzi \Cv[Assembled]\C-",                       3600, -1, -1, "QUZIX0", 20, 26);
            ITEMDATA_DEF("RLHighPowerMinigun",                      "High Power Minigun \Cv[Assembled]\C-",                  38000, -1, -1, "QMINX0", 23, 20);
            ITEMDATA_DEF("RLHighPowerLaserRifle",                   "High Power Laser Rifle \Cv[Assembled]\C-",               6000, -1, -1, "LASRX0", 18, 11);
            ITEMDATA_DEF("RLHighPowerTristarBlaster",               "High Power Tristar Blaster \Cv[Assembled]\C-",          20000, -1, -1, "TRISX0", 35, 35);
            ITEMDATA_DEF("RLHighPowerNuclearPlasmaPistol",          "High Power Nuclear Plasma Pistol \Cv[Assembled]\C-",    70000, -1, -1, "NUPPX0", 11, 14);
            ITEMDATA_DEF("RLHighPowerNuclearPlasmaRifle",           "High Power Nuclear Plasma Rifle \Cv[Assembled]\C-",    110000, -1, -1, "QNPLX0", 29, 19);
            ITEMDATA_DEF("RLHighPowerNuclearBFG9000",               "High Power Nuclear BFG9000 \Cv[Assembled]\C-",         180000, -1, -1, "NUKBX0", 28, 18);
            
            ITEMDATA_DEF("RLHighPowerMarksmanRifle",                "High Power Marksman Rifle \Cv[Assembled]\C-",           22500, -1, -1, "MRKRX0", 26, 18);
            ITEMDATA_DEF("RLHighPowerVanguardRifle",                "High Power Vanguard Rifle \Cv[Assembled]\C-",           21000, -1, -1, "QVANX0", 20, 15);
            ITEMDATA_DEF("RLHighPowerHuntingRevolver",              "High Power Hunting Revolver \Cv[Assembled]\C-",         35000, -1, -1, "HREVX0", 12, 14);
            ITEMDATA_DEF("RLHighPowerThompson",                     "High Power Tommy Gun \Cv[Assembled]\C-",                20000, -1, -1, "TGUNX0", 23, 17);
            ITEMDATA_DEF("RLHighPowerPP7",                          "High Power PP7 \Cv[Assembled]\C-",                      18000, -1, -1, "BPP7X0", 10, 12);
            ITEMDATA_DEF("RLHighPowerRCP90",                        "RC-P120 \Cv[Assembled]\C-",                             50000, -1, -1, "RCP1X0", 17, 16);
            
            // Plasmatic Shrapnel Assembled Weapons
            ITEMDATA_DEF("RLPlasmaticShrapnelShotgun",              "Plasmatic Shotgun \Cv[Assembled]\C-",                    4000, -1, -1, "PKSGX0", 31, 17);
            ITEMDATA_DEF("RLPlasmaticShrapnelCombatShotgun",        "Plasmatic Combat Shotgun \Cv[Assembled]\C-",             4000, -1, -1, "CSHOX0", 25, 17);
            ITEMDATA_DEF("RLPlasmaticShrapnelDoubleShotgun",        "Plasmatic Double Shotgun \Cv[Assembled]\C-",             6500, -1, -1, "DBLSX0", 14,  8);
            ITEMDATA_DEF("RLPlasmaticShrapnelSuperShotgun",         "Plasmatic Super Shotgun \Cv[Assembled]\C-",             10000, -1, -1, "NSSGX0", 27,  9);
            ITEMDATA_DEF("RLPlasmaticShrapnelAssaultShotgun",       "Plasmatic Assault Shotgun \Cv[Assembled]\C-",            8000, -1, -1, "ASHOX0", 31, 27);
            ITEMDATA_DEF("RLPlasmaticShrapnelPlasmaShotgun",        "Overcharged Plasma Shotgun \Cv[Assembled]\C-",          22000, -1, -1, "PSHOX0", 22, 14);
            ITEMDATA_DEF("RLPlasmaticShrapnelHuntingShotgun",       "Plasmatic Hunting Shotgun \Cv[Assembled]\C-",           36000, -1, -1, "HUNTX0", 32, 12);
            
            // Advanced Assembled Weapons
            ITEMDATA_DEF("RLDoubleChainsaw",                        "Double Chainsaw \Cv[Assembled]\C-",                      4500, -1, -1, "DSAWX0", 31, 23);
            ITEMDATA_DEF("RLTacticalRocketLauncher",                "Tactical Rocket Launcher \Cv[Assembled]\C-",            12000, -1, -1, "TROKX0", 27, 14);
            ITEMDATA_DEF("RLStormPistol",                           "Storm Pistol \Cv[Assembled]\C-",                         2600, -1, -1, "SPISX0", 10, 12);
            ITEMDATA_DEF("RLStormCombatPistol",                     "Storm Combat Pistol \Cv[Assembled]\C-",                  4500, -1, -1, "SPISX0", 10, 12);
            ITEMDATA_DEF("RLStormHandCannon",                       "Storm Handcannon \Cv[Assembled]\C-",                     9000, -1, -1, "SDEAX0", 11, 16);
            ITEMDATA_DEF("RLStormMarksmanPistol",                   "Storm Marksman Pistol \Cv[Assembled]\C-",               10000, -1, -1, "MRKPX0",  9, 12);
            ITEMDATA_DEF("RLStormUzi",                              "Dual Uzis \Cv[Assembled]\C-",                           24000, -1, -1, "SUZIX0", 22, 30);
            ITEMDATA_DEF("RLStormBlaster",                          "Storm Blaster \Cv[Assembled]\C-",                        4200, -1, -1, "BLASX0", 12, 14);
            ITEMDATA_DEF("RLStormNuclearPlasmaPistol",              "Storm Nuclear Plasma Pistol \Cv[Assembled]\C-",         75000, -1, -1, "NUSPX0", 13, 15);
            ITEMDATA_DEF("RLPlasmaPistol",                          "Plasma Pistol \Cv[Assembled]\C-",                        3200, -1, -1, "CTPPX0", 11, 15);
            ITEMDATA_DEF("RLPlasmaCombatPistol",                    "Plasma Combat Pistol \Cv[Assembled]\C-",                 5800, -1, -1, "CPP1X0", 11, 15);
            ITEMDATA_DEF("RLPlasmaHandCannon",                      "Plasma Handcannon \Cv[Assembled]\C-",                   15000, -1, -1, "PDEAX0", 12, 14);
            ITEMDATA_DEF("RLPlasmaUzi",                             "Plasma Uzi \Cv[Assembled]\C-",                          16000, -1, -1, "PUZIX0", 21, 26);
            ITEMDATA_DEF("RLPlasmaMarksmanPistol",                  "Plasma Marksman Pistol \Cv[Assembled]\C-",              20000, -1, -1, "PMRPX0", 12, 11);
            ITEMDATA_DEF("RLOverchargedBlaster",                    "Overcharged Blaster \Cv[Assembled]\C-",                 35000, -1, -1, "OBLAX0", 14, 14);
            ITEMDATA_DEF("RLSuperchargedNuclearPlasmaPistol",       "Supercharged Nuclear Plasma Pistol \Cv[Assembled]\C-", 110000, -1, -1, "NUPPX0", 11, 14);
            ITEMDATA_DEF("RLVBFG9000",                              "VBFG9000 \Cv[Assembled]\C-",                            30000, -1, -1, "DBFGX0", 27, 24);
            ITEMDATA_DEF("RLNuclearVBFG9000",                       "Nuclear VBFG9000 \Cv[Assembled]\C-",                   120000, -1, -1, "DBFGX0", 27, 24);
            ITEMDATA_DEF("RLFocusedDoubleShotgun",                  "Focused Double Shotgun \Cv[Assembled]\C-",               7500, -1, -1, "FOCDX0", 19,  9);
            ITEMDATA_DEF("RLHyperBlaster",                          "Hyperblaster \Cv[Assembled]\C-",                         6500, -1, -1, "HYPEX0", 28, 16);
            ITEMDATA_DEF("RLBulletstormChaingun",                   "Bulletstorm Chaingun \Cv[Assembled]\C-",                11500, -1, -1, "BSCHX0", 33, 23);
            ITEMDATA_DEF("RLBulletstormRifle",                      "Bulletstorm Rifle \Cv[Assembled]\C-",                   11500, -1, -1, "BULRX0", 27, 14);
            ITEMDATA_DEF("RLAutoshotgun",                           "Auto Shotgun \Cv[Assembled]\C-",                        20000, -1, -1, "AUTSX0", 25, 11);
            ITEMDATA_DEF("RLAutoDoubleShotgun",                     "Auto Double Shotgun \Cv[Assembled]\C-",                 35000, -1, -1, "AUTDX0", 27, 12);
            ITEMDATA_DEF("RLMiniMissilePistol",                     "Mini-Missile Pistol \Cv[Assembled]\C-",                 14000, -1, -1, "FRGNX0", 12, 11);
            ITEMDATA_DEF("RLPlasmaRifleMkII",                       "Plasma Rifle Mk.II \Cv[Assembled]\C-",                  11000, -1, -1, "2PLAX0", 24, 15);
            ITEMDATA_DEF("RLPlasmaShotgunMkII",                     "Plasma Shotgun Mk.II \Cv[Assembled]\C-",                11000, -1, -1, "P2SHX0", 21, 11);
            ITEMDATA_DEF("RLNuclearPlasmaRifleMkII",                "Nuclear Plasma Rifle Mk.II \Cv[Assembled]\C-",         100000, -1, -1, "NPIIX0", 22, 13);
            ITEMDATA_DEF("RLNuclearPlasmaShotgun",                  "Nuclear Plasma Shotgun \Cv[Assembled]\C-",              85000, -1, -1, "NPSHX0", 24, 12);
            ITEMDATA_DEF("RLLaserShotgun",                          "Laser Shotgun \Cv[Assembled]\C-",                        7500, -1, -1, "LSHTX0", 21,  9);
            ITEMDATA_DEF("RLGrenadeLauncher",                       "Grenade Launcher \Cv[Assembled]\C-",                     6000, -1, -1, "GLSRX0", 27, 14);
            
            // Assault Assembled Weapons
            ITEMDATA_DEF("RLAssaultRifleChaingun",                  "Assault Chaingun \Cv[Assembled]\C-",                     2250, -1, -1, "ACHGX0", 25, 18);
            ITEMDATA_DEF("RLAssaultRifleBattleRifle",               "Scoped Rifle \Cv[Assembled]\C-",                         2250, -1, -1, "SCOPX0", 25, 17);
            ITEMDATA_DEF("RLAssaultRiflePlasmaRifle",               "Assault Plasma Rifle \Cv[Assembled]\C-",                 7500, -1, -1, "APLRX0", 23, 12);
            ITEMDATA_DEF("RLAssaultRifleUzi",                       "Assault Uzi \Cv[Assembled]\C-",                          5700, -1, -1, "RUZIX0", 20, 26);
            ITEMDATA_DEF("RLAssaultRifleMinigun",                   "Assault Minigun \Cv[Assembled]\C-",                     45000, -1, -1, "ZGGGX0", 30, 20);
            ITEMDATA_DEF("RLAssaultRifleLaserRifle",                "Assault Laser Rifle \Cv[Assembled]\C-",                 13500, -1, -1, "LASRX0", 18, 11);
            ITEMDATA_DEF("RLAssaultRifleNuclearPlasmaRifle",        "Assault Nuclear Plasma Rifle \Cv[Assembled]\C-",        90000, -1, -1, "NUKPX0", 23, 14);
            
            // Burst Assembled Weapons
            ITEMDATA_DEF("RLBurstCannonChaingun",                   "Burst Chaingun \Cv[Assembled]\C-",                       3000, -1, -1, "PKCGX0", 25, 18);
            ITEMDATA_DEF("RLBurstCannonBattleRifle",                "Burst-Fire Rifle \Cv[Assembled]\C-",                     3000, -1, -1, "BRIFX0", 22, 14);
            ITEMDATA_DEF("RLBurstCannonPlasmaRifle",                "Burst Plasma Rifle \Cv[Assembled]\C-",                  10000, -1, -1, "BPLSX0", 25, 11);
            ITEMDATA_DEF("RLBurstCannonUzi",                        "Burst Uzi \Cv[Assembled]\C-",                            7600, -1, -1, "BUZIX0", 20, 23);
            ITEMDATA_DEF("RLBurstCannonMinigun",                    "Burst Minigun \Cv[Assembled]\C-",                       60000, -1, -1, "ZGGGX0", 30, 20);
            ITEMDATA_DEF("RLBurstCannonLaserRifle",                 "Burst Laser Rifle \Cv[Assembled]\C-",                   18000, -1, -1, "LASRX0", 18, 11);
            ITEMDATA_DEF("RLBurstCannonNuclearPlasmaRifle",         "Burst Nuclear Plasma Rifle \Cv[Assembled]\C-",         120000, -1, -1, "NUKPX0", 23, 14);
            
            // Nano Shrapnel Assembled Weapons
            ITEMDATA_DEF("RLNanoShrapnelShotgun",                   "Nano Shotgun \Cv[Assembled]\C-",                        50000, -1, -1, "MSHOX0", 31, 10);
            ITEMDATA_DEF("RLNanoShrapnelCombatShotgun",             "Nano Combat Shotgun \Cv[Assembled]\C-",                 47500, -1, -1, "CSHOX0", 25, 17);
            ITEMDATA_DEF("RLNanoShrapnelDoubleShotgun",             "Nano Double Shotgun \Cv[Assembled]\C-",                 80000, -1, -1, "DBLSX0", 14,  8);
            ITEMDATA_DEF("RLNanoShrapnelSuperShotgun",              "Nano Super Shotgun \Cv[Assembled]\C-",                 150000, -1, -1, "NSSGX0", 27,  9);
            ITEMDATA_DEF("RLNanoShrapnelAssaultShotgun",            "Nano Assault Shotgun \Cv[Assembled]\C-",                50000, -1, -1, "ASHOX0", 31, 27);
            ITEMDATA_DEF("RLNanoShrapnelPlasmaShotgun",             "Nano Plasma Shotgun \Cv[Assembled]\C-",                120000, -1, -1, "PSHOX0", 22, 14);
            
            // Master Assembled Weapons
            ITEMDATA_DEF("RLRipper",                                "Ripper \Cv[Assembled]\C-",                              75000, -1, -1, "RIPPX0", 42, 19);
            ITEMDATA_DEF("RLBiggestFuckingGun",                     "Biggest Fucking Gun \Cv[Assembled]\C-",                100000, -1, -1, "PRCGX0", 26, 23);
            ITEMDATA_DEF("RLNuclearBiggestFuckingGun",              "Biggest Fucking Nuclear Gun \Cv[Assembled]\C-",        500000, -1, -1, "PRCGX0", 26, 23);
            ITEMDATA_DEF("RLMotherInLaw",                           "Mother-In-Law \Cv[Assembled]\C-",                      300000, -1, -1, "MOTHX0", 31, 18);
            ITEMDATA_DEF("RLAutocannon",                            "Autocannon \Cv[Assembled]\C-",                         200000, -1, -1, "AUTOX0", 36, 22);
            ITEMDATA_DEF("RLPlasmaRefractor",                       "Plasma Refractor \Cv[Assembled]\C-",                    90000, -1, -1, "PLRFX0", 26, 15);
            ITEMDATA_DEF("RLMegatonShotgun",                        "Megaton Shotgun \Cv[Assembled]\C-",                    250000, -1, -1, "MEGSX0", 24, 18);
            ITEMDATA_DEF("RLConquerorShotgun",                      "Conqueror Shotgun \Cv[Assembled]\C-",                  160000, -1, -1, "CONQX0", 27, 22);
            ITEMDATA_DEF("RLVoltgun",                               "Voltgun \Cv[Assembled]\C-",                            180000, -1, -1, "VOLTX0", 26, 15);
            ITEMDATA_DEF("RLSuperMachinegun",                       "Super Machinegun \Cv[Assembled]\C-",                   300000, -1, -1, "SMACX0", 29, 10);
            ITEMDATA_DEF("RLClusterBombLauncher",                   "Cluster Bomb Launcher \Cv[Assembled]\C-",              280000, -1, -1, "CLUBX0", 26, 15);
            ITEMDATA_DEF("RLGaussRifle",                            "Gauss Rifle \Cv[Assembled]\C-",                        250000, -1, -1, "GAUSX0", 26, 15);
            ITEMDATA_DEF("RLAntimaterielRifle",                     "Anti-materiel Rifle \Cv[Assembled]\C-",                200000, -1, -1, "AMRFX0", 26, 15);
            ITEMDATA_DEF("RLZeusCannon",                            "Zeus Cannon \Cv[Assembled]\C-",                        250000, -1, -1, "ZEUSX0", 28, 28);
         
            // Plasma Infusion Assembled Weapons
         // ITEMDATA_DEF("RLEnergyBlade",                           "Energy Blade \Cv[Assembled]\C-",                        70000, -1, "EKNIX0", 43, 19);
            ITEMDATA_DEF("RLEnergysaw",                             "Energysaw \Cv[Assembled]\C-",                           90000, -1, -1, "ESAWX0", 22, 23);
            ITEMDATA_DEF("RLLaserMinigun",                          "Laser Minigun \Cv[Assembled]\C-",                       60000, -1, -1, "LMINX0", 28, 13);
            ITEMDATA_DEF("RLPlasmaCannon",                          "Plasma Cannon \Cv[Assembled]\C-",                       75000, -1, -1, "PLSCX0", 33, 13);
            ITEMDATA_DEF("RLHeavyPulseBlaster",                     "Heavy Pulse Blaster \Cv[Assembled]\C-",                 65000, -1, -1, "HBLAX0", 14, 12);
            ITEMDATA_DEF("RLInfusionLauncher",                      "Plascharge Launcher \Cv[Assembled]\C-",                110000, -1, -1, "RLAUX0", 43, 19);
            ITEMDATA_DEF("RLLaserPulseLauncher",                    "Defence Drone Launcher \Cv[Assembled]\C-",             180000, -1, -1, "DDRLX0", 19, 18);
            ITEMDATA_DEF("RLIncinerationDeviceLauncher",            "Incineration Device Launcher \Cv[Assembled]\C-",       180000, -1, -1, "IDLAX0", 23, 21);
            
            // Nanomanufacture Assembled Weapons
            ITEMDATA_DEF("RLNanoManufactureAmmoPistol",             "Nanomachic Pistol \Cv[Assembled]\C-",                   50000, -1, -1, "MPISX0", 11, 13);
            ITEMDATA_DEF("RLNanoManufactureAmmoChaingun",           "Nanomachic Chaingun \Cv[Assembled]\C-",                 75000, -1, -1, "PKCGX0", 25, 18);
            ITEMDATA_DEF("RLNanomanufactureAmmoBattleRifle",        "Nanomachic Battle Rifle \Cv[Assembled]\C-",             78000, -1, -1, "UACRX0", 23, 15);
            ITEMDATA_DEF("RLNanoManufactureAmmoRocketLauncher",     "Nanomachic Rocket Launcher \Cv[Assembled]\C-",         100000, -1, -1, "MROKX0", 31, 14);
            ITEMDATA_DEF("RLNanoManufactureAmmoPlasmaRifle",        "Nanomachic Plasma Rifle \Cv[Assembled]\C-",             70000, -1, -1, "PLSRX0", 27, 19);
            ITEMDATA_DEF("RLNanoManufactureAmmoBlaster",            "Nanomachic Blaster \Cv[Assembled]\C-",                  55000, -1, -1, "BLASX0", 12, 14);
            ITEMDATA_DEF("RLNanoManufactureAmmoCombatPistol",       "Nanomachic Combat Pistol \Cv[Assembled]\C-",            55000, -1, -1, "OLOKX0", 10, 13);
            ITEMDATA_DEF("RLNanoManufactureAmmoHandCannon",         "Nanomachic Handcannon \Cv[Assembled]\C-",               55000, -1, -1, "DEAPX0", 11, 14);
            ITEMDATA_DEF("RLNanoManufactureAmmoMarksmanPistol",     "Nanomachic Marksman Pistol \Cv[Assembled]\C-",          60000, -1, -1, "MRKPX0",  9, 12);
            ITEMDATA_DEF("RLNanoManufactureAmmoUzi",                "Nanomachic Uzi \Cv[Assembled]\C-",                     120000, -1, -1, "RUZIX0", 20, 26);
            ITEMDATA_DEF("RLNanoManufactureAmmoMinigun",            "Nanomachic Minigun \Cv[Assembled]\C-",                 150000, -1, -1, "ZGGGX0", 30, 20);
            ITEMDATA_DEF("RLNanoManufactureAmmoLaserRifle",         "Nanomachic Laser Rifle \Cv[Assembled]\C-",              80000, -1, -1, "LASRX0", 18, 11);
            ITEMDATA_DEF("RLNanoManufactureAmmoTristarBlaster",     "Nanomachic Tristar Blaster \Cv[Assembled]\C-",         110000, -1, -1, "TRISX0", 35, 35);
            ITEMDATA_DEF("RLNanoManufactureAmmoMissileLauncher",    "Nanomachic Missile Launcher \Cv[Assembled]\C-",        140000, -1, -1, "CLAUX0", 45, 24);
            ITEMDATA_DEF("RLNanoManufactureAmmoNapalmLauncher",     "Nanomachic Napalm Launcher \Cv[Assembled]\C-",         200000, -1, -1, "NAPAX0", 22, 20);
            
            // Demolition Ammo Assembled Weapons
            ITEMDATA_DEF("RLDemolitionAmmoPistol",                  "Demolition Ammo Pistol \Cv[Assembled]\C-",             180000, -1, -1, "DPISX0", 11, 13);
            ITEMDATA_DEF("RLDemolitionAmmoChaingun",                "Demolition Ammo Chaingun \Cv[Assembled]\C-",           150000, -1, -1, "DCHGX0", 27, 15);
            ITEMDATA_DEF("RLDemolitionAmmoBattleRifle",             "Demolition Ammo Battle Rifle \Cv[Assembled]\C-",       150000, -1, -1, "DEMRX0", 23, 15);
            ITEMDATA_DEF("RLDemolitionAmmoCombatPistol",            "Demolition Ammo Combat Pistol \Cv[Assembled]\C-",      160000, -1, -1, "DGLKX0", 10, 13);
            ITEMDATA_DEF("RLDemolitionAmmoHandCannon",              "Demolition Ammo Handcannon \Cv[Assembled]\C-",         180000, -1, -1, "DDEAX0", 11, 14);
            ITEMDATA_DEF("RLDemolitionAmmoMarksmanPistol",          "Demolition Marksman Pistol \Cv[Assembled]\C-",         160000, -1, -1, "MRKPX0",  9, 12);
            ITEMDATA_DEF("RLDemolitionAmmoUzi",                     "Demolition Ammo Uzi \Cv[Assembled]\C-",                150000, -1, -1, "DUZIX0", 20, 26);
            ITEMDATA_DEF("RLDemolitionAmmoMinigun",                 "Demolition Ammo Minigun \Cv[Assembled]\C-",            200000, -1, -1, "ZGGGX0", 30, 20);
        ITEMDATA_CATEGORY_END;
        
        int TID = UniqueTID();
        bool Success = false;
        for (int i = 0; i < ItemMax[0]; i++)
        {
            str Name = StrParam("%S", ItemData[0][i].Actor);
            
            str Mod = StrParam("%SModLimit", Name);
            Success = SpawnForced(Mod, 0, 0, 0, TID, 0);
            if (Success)
            {
                ItemData[0][i].CompatMods |= RL_MOD_LIMIT;
                Thing_Remove(TID);
            }
            str Mod = StrParam("%SPowerMod", Name);
            Success = SpawnForced(Mod, 0, 0, 0, TID, 0);
            if (Success)
            {
                ItemData[0][i].CompatMods |= RL_POWER_MOD;
                Thing_Remove(TID);
            }
            str Mod = StrParam("%SBulkMod", Name);
            Success = SpawnForced(Mod, 0, 0, 0, TID, 0);
            if (Success)
            {
                ItemData[0][i].CompatMods |= RL_BULK_MOD;
                Thing_Remove(TID);
            }
            str Mod = StrParam("%SAgilityMod", Name);
            Success = SpawnForced(Mod, 0, 0, 0, TID, 0);
            if (Success)
            {
                ItemData[0][i].CompatMods |= RL_AGILITY_MOD;
                Thing_Remove(TID);
            }
            str Mod = StrParam("%STechnicalMod", Name);
            Success = SpawnForced(Mod, 0, 0, 0, TID, 0);
            if (Success)
            {
                ItemData[0][i].CompatMods |= RL_TECH_MOD;
                Thing_Remove(TID);
            }
            str Mod = StrParam("%SSniperMod", Name);
            Success = SpawnForced(Mod, 0, 0, 0, TID, 0);
            if (Success)
            {
                ItemData[0][i].CompatMods |= RL_SNIPER_MOD;
                Thing_Remove(TID);
            }
            str Mod = StrParam("%SFirestormMod", Name);
            Success = SpawnForced(Mod, 0, 0, 0, TID, 0);
            if (Success)
            {
                ItemData[0][i].CompatMods |= RL_FIREST_MOD;
                Thing_Remove(TID);
            }
            str Mod = StrParam("%SNanoMod", Name);
            Success = SpawnForced(Mod, 0, 0, 0, TID, 0);
            if (Success)
            {
                ItemData[0][i].CompatMods |= RL_NANO_MOD;
                Thing_Remove(TID);
            }
            str Mod = StrParam("%SDemonArtifacts", Name);
            Success = SpawnForced(Mod, 0, 0, 0, TID, 0);
            if (Success)
            {
                ItemData[0][i].CompatMods |= RL_DEMON_MOD;
                Thing_Remove(TID);
            }
        }
        
        // Ammo
        ItemData[1][0].Actor = "DRPGClip2";
        ItemData[1][1].Actor = "DRPGClipBox2";
        ItemData[1][3].Actor = "DRPGShellBox2";
        ItemData[1][5].Actor = "DRPGRocketBox2";
        ItemData[1][7].Actor = "DRPGCellPack2";
        
        // Armors
        ITEMDATA_CATEGORY(3, "\CdArmor", CF_NONE);
            // Common Armors
            ITEMDATA_DEF("RLArmorBonusPickup",                              "Armor Bonus",                                         100, 0, -1, "BON2A0",  7, 13);
            ITEMDATA_DEF("RLGreenArmorPickup",                              "Security Armor",                                      250, 0, 0, "ARM1A0", 15, 17);
            ITEMDATA_DEF("RLBlueArmorPickup",                               "Combat Armor",                                        500, 0, 0, "ARM2A0", 15, 17);
            ITEMDATA_DEF("RLRedArmorPickup",                                "Commando Armor",                                     1000, 0, 0, "ARM3A0", 16, 18);
            
            // Assembled Armors
            ITEMDATA_DEF("RLCerberusArmorPickup",                           "Cerberus Armor \Cv[Assembled]\C-",                  18000, 8, 4, "CERAA0", 15, 30);
            ITEMDATA_DEF("RLFireShieldArmorPickup",                         "Fire Shield \Cv[Assembled]\C-",                     10000, 7, 3, "FSHDA0", 15, 25);
            ITEMDATA_DEF("RLTacticalArmorPickup",                           "Tactical Armor \Cv[Assembled]\C-",                  14000, 8, 3, "TACAA0", 15, 21);
            ITEMDATA_DEF("RLTowerShieldArmorPickup",                        "Tower Shield \Cv[Assembled]\C-",                    10000, 5, 3, "TSHDA0", 14, 47);
			
            ITEMDATA_DEF("RLAblativeGreenArmorPickup",                      "Ablative Security Armor \Cv[Assembled]\C-",          7000, 4, 2, "ABL1A0", 16, 19);
            ITEMDATA_DEF("RLAblativeBlueArmorPickup",                       "Ablative Combat Armor \Cv[Assembled]\C-",            8000, 4, 2, "ABL2A0", 16, 19);
            ITEMDATA_DEF("RLAblativeRedArmorPickup",                        "Ablative Commando Armor \Cv[Assembled]\C-",          9000, 4, 2, "ABL3A0", 16, 19);
            ITEMDATA_DEF("RLBallisticGreenArmorPickup",                     "Ballistic Security Armor \Cv[Assembled]\C-",         1250, 1, 1, "BLA1A0", 15, 18);
            ITEMDATA_DEF("RLBallisticBlueArmorPickup",                      "Ballistic Combat Armor \Cv[Assembled]\C-",           1500, 1, 1, "BLA2A0", 15, 18);
            ITEMDATA_DEF("RLBallisticRedArmorPickup",                       "Ballistic Commando Armor \Cv[Assembled]\C-",         2000, 1, 1, "BLA3A0", 15, 18);
            ITEMDATA_DEF("RLCyberNanoGreenArmorPickup",                     "Cybernano Security Armor \Cv[Assembled]\C-",        20000, 8, 4, "CYN1A0", 16, 30);
            ITEMDATA_DEF("RLCyberNanoBlueArmorPickup",                      "Cybernano Combat Armor \Cv[Assembled]\C-",          25000, 8, 4, "CYN2A0", 16, 30);
            ITEMDATA_DEF("RLCyberNanoRedArmorPickup",                       "Cybernano Commando Armor \Cv[Assembled]\C-",        40000, 8, 7, "CYN3A0", 16, 30);
            ITEMDATA_DEF("RLFireproofGreenArmorPickup",                     "Fireproof Security Armor \Cv[Assembled]\C-",         2000, 2, 1, "FPA1A0", 15, 56);
            ITEMDATA_DEF("RLFireproofBlueArmorPickup",                      "Fireproof Combat Armor \Cv[Assembled]\C-",           2500, 2, 1, "FPA2A0", 15, 56);
            ITEMDATA_DEF("RLFireproofRedArmorPickup",                       "Fireproof Commando Armor \Cv[Assembled]\C-",         4000, 2, 1, "FPA3A0", 15, 56);
            ITEMDATA_DEF("RLNanofiberGreenArmorPickup",                     "Nanofiber Security Armor \Cv[Assembled]\C-",          500, 1, 1, "NFA1A0", 15, 18);
            ITEMDATA_DEF("RLNanofiberBlueArmorPickup",                      "Nanofiber Combat Armor \Cv[Assembled]\C-",            750, 1, 1, "NFA2A0", 15, 18);
            ITEMDATA_DEF("RLNanofiberRedArmorPickup",                       "Nanofiber Commando Armor \Cv[Assembled]\C-",         1500, 1, 1, "NFA3A0", 15, 18);
            ITEMDATA_DEF("RLNanofiberSkinGreenArmorPickup",                 "Nanofiber Skin Security Armor \Cv[Assembled]\C-",   15000, 6, 3, "NFS1A0", 12, 47);
            ITEMDATA_DEF("RLNanofiberSkinBlueArmorPickup",                  "Nanofiber Skin Combat Armor \Cv[Assembled]\C-",     20000, 6, 4, "NFS2A0", 12, 47);
            ITEMDATA_DEF("RLNanofiberSkinRedArmorPickup",                   "Nanofiber Skin Commando Armor \Cv[Assembled]\C-",   30000, 6, 5, "NFS3A0", 12, 47);
            ITEMDATA_DEF("RLPowerGreenArmorPickup",                         "Powered Security Armor \Cv[Assembled]\C-",           8000, 6, 2, "PWR1A0", 16, 22);
            ITEMDATA_DEF("RLPowerBlueArmorPickup",                          "Powered Combat Armor \Cv[Assembled]\C-",            14000, 6, 3, "PWR2A0", 16, 22);
            ITEMDATA_DEF("RLPowerRedArmorPickup",                           "Powered Commando Armor \Cv[Assembled]\C-",          22000, 6, 4, "PWR3A0", 16, 22);
            
            // Exotic Armors
            ITEMDATA_DEF("RLBallisticShieldArmorPickup",                    "Ballistic Shield \Ct[Exotic]\C-",                   12500, 7, 3, "BSHDA0", 15, 21);
            ITEMDATA_DEF("RLBallisticVestArmorPickup",                      "Ballistic Vest \Ct[Exotic]\C-",                      4000, 2, 2, "BALVA0", 10, 18);
            ITEMDATA_DEF("RLBulletproofVestArmorPickup",                    "Bulletproof Vest \Ct[Exotic]\C-",                    6500, 3, 2, "BPFVA0",  9, 18);
            ITEMDATA_DEF("RLDuelistArmorPickup",                            "Duelist Armor \Ct[Exotic]\C-",                       4500, 2, 2, "DUEAA0", 12, 24);
            ITEMDATA_DEF("RLEnergyShieldedVestArmorPickup",                 "Energy-Shielded Vest \Ct[Exotic]\C-",               10000, 5, 3, "ESVAA0", 10, 21);
            ITEMDATA_DEF("RLEnergyShieldArmorPickup",                       "Energy Shield \Ct[Exotic]\C-",                      12500, 7, 3, "ESHDA0", 10, 21);
            ITEMDATA_DEF("RLGothicArmorPickup",                             "Gothic Armor \Ct[Exotic]\C-",                       20000, 8, 4, "GOTAA0", 16, 32);
            ITEMDATA_DEF("RLMedicalArmorPickup",                            "Medical Armor \Ct[Exotic]\C-",                       7000, 6, 2, "MED1A0", 10, 20);
            ITEMDATA_DEF("RLPhaseshiftArmorPickup",                         "Phaseshift Armor \Ct[Exotic]\C-",                   25000, 8, 4, "PSHAA0", 15, 29);
            ITEMDATA_DEF("RLPlasmaShieldArmorPickup",                       "Plasma Shield \Ct[Exotic]\C-",                      12500, 7, 3, "PSHDA0", 10, 21);
            ITEMDATA_DEF("RLOnyxArmorPickup",                               "Onyx Armor \Ct[Exotic]\C-",                          2200, 4, 2, "ONXAA0", 15, 18);
            ITEMDATA_DEF("RLOverchargeSystemArmorPickup",                   "Overcharge System \Ct[Exotic]\C-",                   4000, 6, 2, "OVESA0", 21, 16);
            ITEMDATA_DEF("RLRepulsionWaveSuitArmorPickup",                  "Repulsion Wave Suit \Ct[Exotic]\C-",                 4500, 5, 2, "REPWA0", 11, 23);
            ITEMDATA_DEF("RLSurvivalMediArmorPickup",                       "Survival MediArmor \Ct[Exotic]\C-",                 10000, 6, 3, "SURVA0", 11, 14);
            ITEMDATA_DEF("RLCyberwarriorArmorPickup",                       "Cyberwarrior Armor \Ct[Exotic]\C-",                 12500, 6, 3, "CYWAA0", 16, 29);
			
            // Superior Armors
            ITEMDATA_DEF("RLNuclearArmorPickup",                            "Nuclear Armor \Ci[Superior]\C-",                    35000, 8, 6, "NUKAA0", 15, 18);
            ITEMDATA_DEF("RLRechargeableEnergyShieldArmorPickup",           "Rechargeable Energy Shield \Ci[Superior]\C-",       28000, 7, 5, "RESHA0", 11, 21);
            
            // Onyx-Modded Armors
            ITEMDATA_DEF("RLOModGreenArmorPickup",                          "Security Armor \Cc[Onyx]\C-",                         375, -1, -1, "ONYAA0", 15, 17);
            ITEMDATA_DEF("RLOModBlueArmorPickup",                           "Combat Armor \Cc[Onyx]\C-",                           750, -1, -1, "ONYAB0", 15, 17);
            ITEMDATA_DEF("RLOModRedArmorPickup",                            "Commando Armor \Cc[Onyx]\C-",                        1500, -1, -1, "ONYAC0", 16, 18);
            ITEMDATA_DEF("RLOModBallisticVestArmorPickup",                  "Ballistic Vest \Ct[Exotic] \Cc[Onyx]\C-",            6000, -1, -1, "ONYAD0", 10, 18);
            ITEMDATA_DEF("RLOModBulletProofVestArmorPickup",                "Bulletproof Vest \Ct[Exotic] \Cc[Onyx]\C-",          9750, -1, -1, "ONYAE0",  9, 18);
            ITEMDATA_DEF("RLOModCyberWarriorArmorPickup",                   "Cyberwarrior Armor \Ct[Exotic] \Cc[Onyx]\C-",       18750, -1, -1, "ONYAF0", 16, 29);
            ITEMDATA_DEF("RLOModDuelistArmorPickup",                        "Duelist Armor \Ct[Exotic] \Cc[Onyx]\C-",             6750, -1, -1, "ONYAG0", 12, 24);
            ITEMDATA_DEF("RLOModEnergyShieldedVestArmorPickup",             "Energy-Shielded Vest \Ct[Exotic] \Cc[Onyx]\C-",     15000, -1, -1, "ONYAH0", 10, 21);
            ITEMDATA_DEF("RLOModGothicArmorPickup",                         "Gothic Armor \Ct[Exotic] \Cc[Onyx]\C-",             30000, -1, -1, "ONYAJ0", 16, 32);
            ITEMDATA_DEF("RLOModMedicalArmorPickup",                        "Medical Armor \Ct[Exotic] \Cc[Onyx]\C-",            10500, -1, -1, "ONYAK0", 10, 20);
            ITEMDATA_DEF("RLOModPhaseshiftArmorPickup",                     "Phaseshift Armor \Ct[Exotic] \Cc[Onyx]\C-",         37500, -1, -1, "ONYAL0", 15, 29);
            ITEMDATA_DEF("RLOModRepulsionWaveSuitArmorPickup",              "Repulsion Wave Suit \Ct[Exotic] \Cc[Onyx]\C-",       6750, -1, -1, "ONYAM0", 11, 23);
            ITEMDATA_DEF("RLOModSurvivalMediArmorPickup",                   "Survival MediArmor \Ct[Exotic] \Cc[Onyx]\C-",       15000, -1, -1, "ONYAN0", 11, 14);
            
            // Unique Armors
         // ITEMDATA_DEF("RLBerserkerArmorPickup",                          "Berserker Armor \Cd[Unique]\C-",                    30000, -1, "BERZA0", 15, 31);
            ITEMDATA_DEF("RLBerserkPowersuitArmorPickup",                   "Berserk Powersuit \Cd[Unique]\C-",                  35000, -1, 6, "BEPSB0", 16, 30);
            ITEMDATA_DEF("RLBlazingPhoenixDeviceSuitArmorPickup",           "Phoenix-B Device Suit \Cd[Unique]\C-",              39000, -1, 6, "BPHDA0", 16, 21);
            ITEMDATA_DEF("RLCyberneticArmorPickup",                         "Cybernetic Armor \Cd[Unique]\C-",                   30000, -1, 5, "CYNAA0", 15, 31);
            ITEMDATA_DEF("RLEnergyDischargeHarnessArmorPickup",             "Energy Discharge Harness \Cd[Unique]\C-",           27500, -1, 5, "EDHXA0", 11, 22);
            ITEMDATA_DEF("RLFrontlineEngineerSuitArmorPickup",              "Frontline Engineer Suit \Cd[Unique]\C-",            36000, -1, 6, "BLUAA0",  9, 39);
            ITEMDATA_DEF("RLGeosGoldenGauntletArmorPickup",                 "Geo's Golden Gauntlet \Cd[Unique]\C-",              30000, -1, 5, "GGGXA0",  8, 26);
            ITEMDATA_DEF("RLJetpackArmorPickup",                            "Jetpack \Cd[Unique]\C-",                            42000, -1, 7, "JETPA0", 14, 36);
            ITEMDATA_DEF("RLKateMatterstormHarnessArmorPickup",             "K-8 Matterstorm Harness \Cd[Unique]\C-",            41000, -1, 7, "K8MHA0", 16, 18);
            ITEMDATA_DEF("RLKyleTeslaboltArmorPickup",                      "K1-L3 Teslabolt Armor \Cd[Unique]\C-",              56000, -1, 8, "KTESA0", 17, 30);
            ITEMDATA_DEF("RLLavaArmorPickup",                               "Lava Armor \Cd[Unique]\C-",                         65000, -1, 8, "LAVUA0", 15, 18);
            ITEMDATA_DEF("RLMaleksArmorPickup",                             "Malek's Armor \Cd[Unique]\C-",                      50000, -1, 8, "MALKA0", 15, 31);
            ITEMDATA_DEF("RLMedicalPowerArmorPickup",                       "Medical Power Armor \Cd[Unique]\C-",                17500, -1, 4, "MED2A0", 10, 24);
            ITEMDATA_DEF("RLNanoAblativeArmorPickup",                       "Nano Ablative Armor \Cd[Unique]\C-",                38000, -1, 6, "NABLA0", 16, 19);
            ITEMDATA_DEF("RLNecroArmorPickup",                              "Necro Armor \Cd[Unique]\C-",                        15500, -1, 4, "NECRA0", 16, 28);
            ITEMDATA_DEF("RLNuclearPowerArmorPickup",                       "Nuclear Powerarmor \Cd[Unique]\C-",                 65000, -1, 8, "ENUKA0", 16, 27);
            ITEMDATA_DEF("RLPrototypeAssaultShieldArmorPickup",             "Prototype Assault Shield \Cd[Unique]\C-",           45000, -1, 8, "PASSA0", 12, 18);
            ITEMDATA_DEF("RLRyanCordellPsychicAmplifierSuitArmorPickup",    "R11-n Psychic Amplifier Suit \Cd[Unique]\C-",       33000, -1, 5, "RCPAA0", 14, 23);
            ITEMDATA_DEF("RLRoystensCommandArmorPickup",                    "Roysten's Command Armor \Cd[Unique]\C-",            31000, -1, 5, "ROYAA0", 16, 21);
            ITEMDATA_DEF("RLShieldedArmorPickup",                           "Shielded Armor \Cd[Unique]\C-",                     40000, -1, 7, "SSHDA0", 16, 25);
            ITEMDATA_DEF("RLSoloOperativeSuitArmorPickup",                  "Solo Operative Suit \Cd[Unique]\C-",                44444, -1, 7, "SSOSA0", 11, 35);
            ITEMDATA_DEF("RLTacticalAssemblerSuitArmorPickup",              "Tactical Assembler Suit \Cd[Unique]\C-",            36000, -1, 6, "REDAA0",  9, 39);
            ITEMDATA_DEF("RLTerminusEst13BattlesuitArmorPickup",            "Terminus Battlesuit \Cd[Unique]\C-",                41000, -1, 7, "TEBSA0", 17, 30);
            ITEMDATA_DEF("RLTorgueBlastplateArmorPickup",                   "Torgue Blastplate Armor \Cd[Unique]\C-",            60000, -1, 8, "TORAA0", 17, 21);
            ITEMDATA_DEF("RLWildWeaselPeacekeeperArmorPickup",              "WW-41 Peacekeeper Armor \Cd[Unique]\C-",            42000, -1, 7, "WWPKA0", 16, 34);
            ITEMDATA_DEF("RLXaserPowerarmorPickup",                         "Xaser Inc. Powerarmor \Cd[Unique]\C-",              85000, -1, 8, "XASPA0", 16, 26);
            ITEMDATA_DEF("RLZeroDiamondAssaultforceArmorPickup",            "0D-1a Assaultforce Armor \Cd[Unique]\C-",           47000, -1, 8, "0DAFA0", 15, 32);
			
            // Demonic Armors
            ITEMDATA_DEF("RLDemonicCarapaceArmorPickup",                    "Demonic Carapace \Cg[Demonic]\C-",                  32000, -1, 9, "DEMAA0", 22, 31);
            ITEMDATA_DEF("RLSoulshatterArmorPickup",                        "Soulshatter Armor \Cg[Demonic]\C-",                 34000, -1, 9, "SOLSA0", 17, 24);
            
            // Legendary Armors
            ITEMDATA_DEF("RLAngelicArmorPickup",                            "Angelic Armor \Cf[Legendary]\C-",                  200000, -1, 10, "ANGAA0", 14, 27);
            ITEMDATA_DEF("RLChronotrooperArmorPickup",                      "Chronotrooper Armor \Cf[Legendary]\C-",            140000, -1, 10, "CHROA0", 11, 29);
            ITEMDATA_DEF("RLReactiveShieldSystemArmorPickup",               "Reactive Shield System \Cf[Legendary]\C-",         220000, -1, 10, "RSSDA0", 16, 22);
            ITEMDATA_DEF("RLTheBeeArmorPickup",                             "The Bee \Cf[Legendary]\C-",                        250000, -1, 10, "BEESA0", 12, 21);
        ITEMDATA_CATEGORY_END;
        
        // Powerups
        ITEMDATA_CATEGORY(4, "\CqPowerups", CF_NONE);
            ITEMDATA_DEF("InvulnerabilityCharge2",      "Invulnerability Charge",       25000, 2, 7, "CRG2A0",  6, 22);
            ITEMDATA_DEF("InvisibilityCharge2",         "Invisibility Charge",           2500, 1, 2, "CRG1A0",  6, 22);
            ITEMDATA_DEF("DRPGTimeSphere",              "Time Sphere",                   1000, 4, 1, "TIMEA0", 16, 45);
            ITEMDATA_DEF("DRPGRegenSphere",             "Regeneration Sphere",           1000, 2, 1, "REGNA0", 12, 38);
            ITEMDATA_DEF("RadSuit2",                    "Radiation Suit",                 250, 0, 0, "SUITA0", 11, 51);
            ITEMDATA_DEF("Infrared2",                   "IR Goggles",                     500, 0, 0, "PVISA0", 11,  9);
            ITEMDATA_DEF("Berserk2",                    "Berserk Pack",                  1000, 1, 1, "PSTRA0", 12, 15);
            ITEMDATA_DEF("DRPGAllMap",                  "Computer Area Map",             1000, 1, 1, "PMAPA0", 13, 23);
            ITEMDATA_DEF("DRPGWings",                   "Wings",                         5000, 2, 5, "WINGA0", 13, 36);
            ITEMDATA_DEF("Megasphere2",                 "Megasphere",                   10000, 4, 7, "MEGAA0", 12, 32);
            ITEMDATA_DEF("DRPGImmunityCrystalMelee",    "Melee Immunity Crystal",       100000, 8, 8, "CRYSA0", 16, 48);
            ITEMDATA_DEF("DRPGImmunityCrystalBullet",   "Bullet Immunity Crystal",      100000, 8, 8, "CRYSB0", 16, 48);
            ITEMDATA_DEF("DRPGImmunityCrystalFire",     "Fire Immunity Crystal",        100000, 8, 8, "CRYSC0", 16, 48);
            ITEMDATA_DEF("DRPGImmunityCrystalPlasma",   "Plasma Immunity Crystal",      100000, 8, 8, "CRYSD0", 16, 48);
            ITEMDATA_DEF("DRPGImmunityCrystalLightning","Lightning Immunity Crystal",   100000, 8, 8, "CRYSE0", 16, 48);
            ITEMDATA_DEF("DRPGImmunityCrystalToxic",    "Toxic Immunity Crystal",       100000, 8, 8, "CRYSF0", 16, 48);
            ITEMDATA_DEF("DRPGImmunityCrystalRadiation","Radiation Immunity Crystal",   100000, 8, 8, "CRYSG0", 16, 48);
            ITEMDATA_DEF("RLTrackingMap",               "Tracking Map",                  2000, 4, 2, "MMAPA0", 14, 23);
            ITEMDATA_DEF("RLBlueprintComputer",         "Blueprint Computer",            3000, 4, 3, "BLUPA0", 14, 23);
            ITEMDATA_DEF("RLHatredSkull",               "Hatred Skull",                  6666, 6, 6, "ISKLA0", 10, 18);
            ITEMDATA_DEF("RLBloodSkull",                "Blood Skull",                   4444, 6, 4, "ISKLC0", 10, 18);
            ITEMDATA_DEF("RLFireSkull",                 "Fire Skull",                    5555, 6, 5, "ISKLE0", 10, 18);
            ITEMDATA_DEF("RLPhaseDevice",               "Phase Device",                  1000, 1, 1, "PHS1I0", -9, -2);
            ITEMDATA_DEF("RLHomingPhaseDevice",         "Homing Phase Device",           2500, 2, 2, "PHS2I0", -9, -2);
            ITEMDATA_DEF("RLRecallPhaseDevice",         "Recall Phase Device",           2500, 2, 2, "PHS3I0", -9, -5);
            ITEMDATA_DEF("RLExperimentalPhaseDevice",   "Experimental Phase Device",    60000,12, 8, "PHS4I0", -9, -4);
        ITEMDATA_CATEGORY_END;
        
        // Mod Packs
        ITEMDATA_CATEGORY(8, "\CtMod Packs", CF_NONE);
            // Normal Modpacks
            ITEMDATA_DEF("RLPowerModItem",          "Power Modpack",         20000, 0, 2, "PMODA0",  8, 17);
            ITEMDATA_DEF("RLBulkModItem",           "Bulk Modpack",          20000, 0, 2, "BMODA0",  8, 17);
            ITEMDATA_DEF("RLAgilityModItem",        "Agility Modpack",       20000, 0, 2, "AMODA0",  8, 17);
            ITEMDATA_DEF("RLTechnicalModItem",      "Technical Modpack",     20000, 0, 2, "TMODA0",  8, 17);
            
            // Exotic Modpacks
            ITEMDATA_DEF("RLSniperModItem",         "Sniper Modpack",       50000, 2, 4, "SMODA0",  8, 17);
            ITEMDATA_DEF("RLFirestormModItem",      "Firestorm Modpack",    50000, 2, 4, "FMODA0",  8, 17);
            ITEMDATA_DEF("RLNanoModItem",           "Nano Modpack",         50000, 2, 4, "NMODA0",  8, 17);
            ITEMDATA_DEF("RLOnyxModItem",           "Onyx Modpack",         50000, 2, 4, "OMODA0",  8, 17);
            ITEMDATA_DEF("RLArmorModItem",          "Armor Modpack",        50000, 2, 4, "AMK1A0", 10, 20);
            
            // Demon Artifact
            ITEMDATA_DEF("RLDemonArtifactItem",     "Demon Artifact",       100000, 4, 6, "DMNAA0", 19, 48);
        ITEMDATA_CATEGORY_END;
        
        // Boots
        ITEMDATA_CATEGORY(9, "\CcBoots", CF_NONE);
            // Common Boots
            ITEMDATA_DEF("RLSteelBootsPickup",                  "Steel Boots",                                             250, 0, 0, "BOOTS0", 13, 26);
            ITEMDATA_DEF("RLProtectiveBootsPickup",             "Protective Boots",                                        500, 0, 0, "BOOTG0", 13, 26);
            ITEMDATA_DEF("RLPlasteelBootsPickup",               "Plasteel Boots",                                          750, 0, 0, "BOOTB0", 13, 26);
            
            // Assembled Boots
            ITEMDATA_DEF("RLCerberusBootsPickup",               "Cerberus Boots \Cv[Assembled]\C-",                      18000, 4, 6, "CERBA0", 13, 24);
            ITEMDATA_DEF("RLTacticalBootsPickup",               "Tactical Boots \Cv[Assembled]\C-",                      14000, 4, 6, "TACBA0", 14, 21);
			
            ITEMDATA_DEF("RLAntigravSteelBootsPickup",          "Anti-Grav Steel Boots \Cv[Assembled]\C-",                2000, 1, 2, "AGSBA0", 14, 27);
            ITEMDATA_DEF("RLAntigravProtectiveBootsPickup",     "Anti-Grav Protective Boots \Cv[Assembled]\C-",           3000, 1, 3, "AGGBA0", 14, 27);
            ITEMDATA_DEF("RLAntigravPlasteelBootsPickup",       "Anti-Grav Plasteel Boots \Cv[Assembled]\C-",             4000, 1, 4, "AGBBA0", 14, 27);
            ITEMDATA_DEF("RLEnviromentalSteelBootsPickup",      "Environmental Steel Boots \Cv[Assembled]\C-",            1000, 1, 1, "ENVOS0", 14, 18);
            ITEMDATA_DEF("RLEnviromentalProtectiveBootsPickup", "Environmental Protective Boots \Cv[Assembled]\C-",       2000, 1, 2, "ENVOG0", 14, 18);
            ITEMDATA_DEF("RLEnviromentalPlasteelBootsPickup",   "Environmental Plasteel Boots \Cv[Assembled]\C-",         3000, 1, 3, "ENVOB0", 14, 18);
            ITEMDATA_DEF("RLFireproofSteelBootsPickup",         "Fireproof Steel Boots \Cv[Assembled]\C-",                1000, 1, 1, "FIRBS0", 14, 23);
            ITEMDATA_DEF("RLFireproofProtectiveBootsPickup",    "Fireproof Protective Boots \Cv[Assembled]\C-",           1500, 1, 2, "FIRBG0", 14, 23);
            ITEMDATA_DEF("RLFireproofPlasteelBootsPickup",      "Fireproof Plasteel Boots \Cv[Assembled]\C-",             2000, 1, 2, "FIRBB0", 14, 23);
            ITEMDATA_DEF("RLGrapplingSteelBootsPickup",         "Grappling Steel Boots \Cv[Assembled]\C-",                1000, 1, 1, "GRAPS0", 21, 23);
            ITEMDATA_DEF("RLGrapplingProtectiveBootsPickup",    "Grappling Protective Boots \Cv[Assembled]\C-",           1500, 1, 2, "GRAPG0", 21, 23);
            ITEMDATA_DEF("RLGrapplingPlasteelBootsPickup",      "Grappling Plasteel Boots \Cv[Assembled]\C-",             2000, 1, 2, "GRAPB0", 21, 23);
            
            // Exotic Boots
            ITEMDATA_DEF("RLAcidProofBootsPickup",              "Acid-Proof Boots \Ct[Exotic]\C-",                        5000, 4, 5, "ACPBA0", 14, 23);
            ITEMDATA_DEF("RLGothicBootsPickup",                 "Gothic Boots \Ct[Exotic]\C-",                           20000, 4, 7, "GOTBA0", 13, 26);
            ITEMDATA_DEF("RLPhaseshiftBootsPickup",             "Phaseshift Boots \Ct[Exotic]\C-",                       25000, 4, 7, "PSHBA0", 13, 20);
            ITEMDATA_DEF("RLShockwaveBootsPickup",              "Shockwave Boots \Ct[Exotic]\C-",                         3500, 4, 3, "SHKBA0", 14, 27);

            // Unique Boots
            ITEMDATA_DEF("RLEnviroBootsPickup",                 "Enviro Boots \Cd[Unique]\C-",                            5000, -1, 5, "ENVBA0", 14, 27);
            ITEMDATA_DEF("RLFrontlineEngineerBootsPickup",      "Frontline Engineer Boots \Cd[Unique]\C-",                4500, -1, 4, "FLEBA0", 13, 19);
            ITEMDATA_DEF("RLLavaBootsPickup",                   "Lava Boots \Cd[Unique]\C-",                             65000, -1, 8, "LAVBA0", 13, 20);
            ITEMDATA_DEF("RLLeonidasBootsPickup",               "Leonidas' Boots \Cd[Unique]\C-",                        10000, -1, 6, "SPARA0", 13, 26);
            ITEMDATA_DEF("RLNuclearPowerBootsPickup",           "Nuclear Powerboots \Cd[Unique]\C-",                     65000, -1, 8, "ENUKC0", 13, 24);
            ITEMDATA_DEF("RLNyarlaptotepsBootsPickup",          "Nyarlaptotep's Boots \Cd[Unique]\C-",                   50000, -1, 8, "NYABA0", 14, 21);
            ITEMDATA_DEF("RLRoystensCombatBootsPickup",         "Roysten's Combat Boots \Cd[Unique]\C-",                 31000, -1, 7, "ROYBA0", 13, 18);
            ITEMDATA_DEF("RLSoloOperativeBootsPickup",          "Solo Operative Boots \Cd[Unique]\C-",                   44444, -1, 7, "SSOBA0", 13, 21);
            ITEMDATA_DEF("RLTacticalAssemblerBootsPickup",      "Tactical Assembler Boots \Cd[Unique]\C-",                4500, -1, 4, "TCABA0", 13, 19);
            ITEMDATA_DEF("RLTorgueBlastBootsPickup",            "Torgue Blastboots \Cd[Unique]\C-",                      60000, -1, 8, "TORBA0", 14, 26);
			
            // Demonic Boots
            ITEMDATA_DEF("RLDemonicBootsPickup",                "Demonic Boots \Cg[Demonic]\C-",                          32000, -1, 9, "DEMBA0", 15, 31);
            
            // Legendary Boots
            ITEMDATA_DEF("RLAngelicBootsPickup",                "Angelic Boots \Cf[Legendary]\C-",                      200000, -1, 10, "ANGBA0", 15, 25);
        ITEMDATA_CATEGORY_END;
    }
    
    // Compatibility Handling - LegenDoom
    if (CompatMode == COMPAT_LEGENDOOM)
    {
        // Weapons
        ITEMDATA_CATEGORY(0, "\CgWeapons", CF_NONE);
            ITEMDATA_DEF("LDFistsPickupLegendary",          "Fists",             2500, 0, 0, "SFISZ0", 14, 17);
            ITEMDATA_DEF("LDChainsawPickupLegendary",       "Chainsaw",          5000, 1, 1, "SSAWZ0", 31, 24);
            ITEMDATA_DEF("LDPistolPickupLegendary",         "Pistol",            2500, 0, 0, "PISTA0", 11, 15);
            ITEMDATA_DEF("LDShotgunPickupLegendary",        "Shotgun",           5000, 1, 1, "SHOTA0", 31, 17);
            ITEMDATA_DEF("LDSuperShotgunPickupLegendary",   "Super Shotgun",    10000, 2, 2, "SGN2A0", 27, 15);
            ITEMDATA_DEF("LDChaingunPickupLegendary",       "Chaingun",         15000, 1, 1, "MGUNA0", 25, 18);
            ITEMDATA_DEF("LDRocketLauncherPickupLegendary", "Rocket Launcher",  25000, 3, 3, "LAUNA0", 31, 18);
            ITEMDATA_DEF("LDPlasmaRiflePickupLegendary",    "Plasma Rifle",     50000, 4, 4, "PLASA0", 27, 19);
            ITEMDATA_DEF("LDBFG9000PickupLegendary",        "BFG9000",         100000, 5, 5, "BFUGA0", 31, 38);
        ITEMDATA_CATEGORY_END;
        
        // Powerups
        ItemData[4][0].Actor = "LDInvulnerabilitySpherePickupRPG";
        ItemData[4][1].Actor = "LDBlurSpherePickupRPG";
        ItemData[4][4].Actor = "LDRadsuitPickupRPG";
        ItemData[4][5].Actor = "LDInfraredPickupRPG";
    }
    
    // Misc Hidden Stuff
    ITEMDATA_CATEGORY(ItemCategories, "Misc", CF_NOBUY | CF_NOSELL | CF_NOSTORE);
        ITEMDATA_DEF("None",                    "\CaUnknown Item\C-",           0, -1, -1, "SprNone", 0, 0);
        
        ITEMDATA_DEF("DRPGEPCapsule",           "\CnEP Capsule\C-",             0, -1, -1, "EPUPA0", 16, 24);
        ITEMDATA_DEF("DRPGBigEPCapsule",        "\CnBig EP Capsule\C-",         0, -1, -1, "EPUPA0", 16, 24);
        
        ITEMDATA_DEF("DRPGChipGold",            "\CfGold Chip\C-",              0, -1, -1, "CHPGA0", 16, 32);
        ITEMDATA_DEF("DRPGChipPlatinum",        "Platinum Chip",                0, -1, -1, "CHPPA0", 16, 32);
        
        ITEMDATA_DEF("DRPGUACCard",             "UAC Card",                     0, -1, -1, "UCRDA0", 26, 26);
        ITEMDATA_DEF("DRPGDiamondUACCard",      "Diamond UAC Card",             0, -1, -1, "UCRDE0", 26, 26);
        
        ITEMDATA_DEF("DRPGNukeKey1",            "\ChBlue\C- Nuke Key",          0, -1, -1, "NKEYA0",  6, 20);
        ITEMDATA_DEF("DRPGNukeKey2",            "\CmBlack\C- Nuke Key",         0, -1, -1, "NKEYB0",  6, 20);
        ITEMDATA_DEF("DRPGNukeKey3",            "\CsBrown\C- Nuke Key",         0, -1, -1, "NKEYC0",  6, 20);
        ITEMDATA_DEF("DRPGNukeKey4",            "\CdGreen\C- Nuke Key",         0, -1, -1, "NKEYD0",  6, 20);
        ITEMDATA_DEF("DRPGNukeKey5",            "\CiOrange\C- Nuke Key",        0, -1, -1, "NKEYE0",  6, 20);
        ITEMDATA_DEF("DRPGNukeKey6",            "\CgRed\C- Nuke Key",           0, -1, -1, "NKEYF0",  6, 20);
        ITEMDATA_DEF("DRPGNukeKey7",            "\CtPurple\C- Nuke Key",        0, -1, -1, "NKEYG0",  6, 20);
        ITEMDATA_DEF("DRPGNukeKey8",            "\CjWhite\C- Nuke Key",         0, -1, -1, "NKEYH0",  6, 20);
        ITEMDATA_DEF("DRPGNukeKey9",            "\CkYellow\C- Nuke Key",        0, -1, -1, "NKEYI0",  6, 20);
        
        ITEMDATA_DEF("DRPGGeneratorCell",       "Generator Cell",               0, -1, -1, "GCELA0",  8, 33);
        ITEMDATA_DEF("DRPGGeneratorCellDead",   "Dead Generator Cell",          0, -1, -1, "GCELH0",  8, 33);
        
        ITEMDATA_DEF("DRPGNeutralizerFuel",     "Radiation Neutralizer Fuel",   0, -1, -1, "RADMB0",  9, 20);
    ITEMDATA_CATEGORY_END;
    
    // Remove rank limitations in Debug Mode
    if (GetCVar("drpg_debug"))
        RemoveItemRanks();
    
    PopulateRewards();
    while (!SortRewards()) Delay(1);
    
    // Reward List is done processing
    RewardsInit = true;
    if (GetCVar("drpg_debug"))
        Log("\CdDEBUG: \C-Finished Processing Rewards List (%d Tics Taken)", Timer());
    
    ItemsInitialized = true;
}

int ShieldInversePriceSort(void const *Left, void const *Right)
{
    ShieldAccsPtr LeftPart = *((ShieldAccsPtr *)Left);
    ShieldAccsPtr RightPart = *((ShieldAccsPtr *)Right);
    
    if (LeftPart->Price > RightPart->Price) return 1;
    if (LeftPart->Price < RightPart->Price) return -1;
    
    return 0;
}

void RemoveItemRanks()
{
    for (int i = 0; i < ItemCategories; i++)
        for (int j = 0; j < ItemMax[i]; j++)
            if (ItemData[i][j].Price > 0)
                ItemData[i][j].Rank = 0;
    
    ItemRanksRemoved = true;
}

ItemInfoPtr GetRewardItem(int Difficulty)
{
    ItemInfoPtr Reward;
    int Index;
    int Cap;
    int DiffPick;
    
    if (Difficulty < 10)
    {
        DiffPick = Random(0, 100);
        
        if (DiffPick < 20) Difficulty--; // Unlucky, item will be a rank lower
        if (DiffPick > 95) Difficulty++; // Lucky, item will be a rank higher
        
        // Prevent under/overflow
        if (Difficulty < 0) Difficulty = 0;
        if (Difficulty > 9) Difficulty = 9;
        
        // Higher chance for modpacks if we're playing with DRLA
        if (CompatMode == COMPAT_DRLA && Difficulty > 1)
        {
            if (Difficulty <= 4) Cap = 9;   // Exclude demon artifact
            if (Difficulty == 2) Cap = 4;   // Basic modpacks only
            else                 Cap = 10;  // All modpacks
            
            if (Random(0, 100) < 25)
            {
                Index = Random(0, Cap - 1);
                Reward = &ItemData[8][Index];
                
                if (GetCVar("drpg_debug"))
                    Log("\CdDEBUG: \C-Reward Item %S\C- (%S) picked - Rarity %d Item %d", Reward->Name, Reward->Actor, Difficulty, Index);
                
                return Reward;
            }
        }
        else if (Random(0, 100) < 20) // Stims/Augs/Turret
        {
            Cap = 0;
            
            switch (Difficulty)
            {
                case 0: Cap = 8; break;
                case 1: Cap = 22; break;
                case 2:
                case 3: Cap = 25; break;
                case 4: Cap = 26; break;
                case 5: Cap = 27; break;
                case 6: Cap = 28; break;
                case 7: Cap = 29; break;
                case 8: Cap = 31; break;
                case 9: Cap = 32; break;
            }
            
            Index = Random(0, Cap - 1);
            Reward = &ItemData[6][Index];
            
            if (GetCVar("drpg_debug"))
                Log("\CdDEBUG: \C-Reward Item %S\C- (%S) picked - Rarity %d Item %d", Reward->Name, Reward->Actor, Difficulty, Index);
            
            return Reward;
        }
    }
    
    Index = Random(0, RewardsCount[Difficulty] - 1);
    Reward = RewardList[Difficulty][Index];
    
    if (GetCVar("drpg_debug"))
        Log("\CdDEBUG: \C-Reward Item %S\C- (%S) picked - Rarity %d Item %d", Reward->Name, Reward->Actor, Difficulty, Index);
    
    return Reward;
}

ItemInfoPtr FindItem(str Item)
{
    for (int i = 0; i <= ItemCategories; i++)
        for (int j = 0; j < ItemMax[i]; j++)
            if (!StrICmp(ItemData[i][j].Actor, Item))
                return &ItemData[i][j];
    
    return GetBlankItem();
}

ItemInfoPtr FindItemInCategory(str Item, int Category)
{
    for (int i = 0; i < ItemMax[Category]; i++)
        if (!StrICmp(ItemData[Category][i].Actor, Item))
            return &ItemData[Category][i];
    
    return GetBlankItem();
}

ItemInfoPtr GetBlankItem()
{
    return &ItemData[ItemCategories][0];
}

NamedScript DECORATE void SpawnLuckItem()
{
    int Luck = AveragePlayerLuck();
    str ActorToSpawn;
    
    ActorToSpawn = "DRPGMoneyDropper";
    
    if (Luck >= LUCK_EPDROP      && RandomFixed(0.0, 100.0) <= 30.57) ActorToSpawn = "DRPGAmmoDropper";
    if (Luck >= LUCK_EPDROP      && RandomFixed(0.0, 100.0) <= 23.35) ActorToSpawn = "DRPGChipDropper";
    if (Luck >= LUCK_WEAPONDROP  && RandomFixed(0.0, 100.0) <= 17.12) ActorToSpawn = "DRPGBatteryDropper";
    if (Luck >= LUCK_WEAPONDROP  && RandomFixed(0.0, 100.0) <= 12.25) ActorToSpawn = "DRPGTurretDropper";
    if (/* Crates always appear  */ RandomFixed(0.0, 100.0) <=  6.13) ActorToSpawn = "DRPGCrate";
    
    if (Luck >= LUCK_HEALTHDROP  && RandomFixed(0.0, 100.0) <= LUCK_MAXHEALTHCHANCE)  ActorToSpawn = "DRPGHealthDropper";
    if (Luck >= LUCK_EPDROP      && RandomFixed(0.0, 100.0) <= LUCK_MAXEPCHANCE)      ActorToSpawn = "DRPGEPDropper";
    if (Luck >= LUCK_ARMORDROP   && RandomFixed(0.0, 100.0) <= LUCK_MAXARMORCHANCE)   ActorToSpawn = "DRPGArmorDropper";
    if (Luck >= LUCK_WEAPONDROP  && RandomFixed(0.0, 100.0) <= LUCK_MAXWEAPONCHANCE)  ActorToSpawn = "DRPGWeaponDropper";
    if (Luck >= LUCK_POWERUPDROP && RandomFixed(0.0, 100.0) <= LUCK_MAXPOWERUPCHANCE) ActorToSpawn = "DRPGPowerupDropper";
    if (Luck >= LUCK_STIMDROP    && RandomFixed(0.0, 100.0) <= LUCK_MAXSTIMCHANCE)    ActorToSpawn = Random(0, 3) ? "DRPGVialDropper" : "DRPGStimDropper";
    if (Luck >= LUCK_MODULEDROP  && RandomFixed(0.0, 100.0) <= LUCK_MAXMODULECHANCE)  ActorToSpawn = "DRPGModuleDropper";
    if (Luck >= LUCK_AUGDROP     && RandomFixed(0.0, 100.0) <= LUCK_MAXAUGCHANCE)     ActorToSpawn = "DRPGAugDropper";
    if (Luck >= LUCK_SHIELDDROP  && RandomFixed(0.0, 100.0) <= LUCK_MAXSHIELDCHANCE)  ActorToSpawn = "DRPGShieldDropper";
    
    SpawnSpotFacingForced(ActorToSpawn, 0, ActivatorTID());
    
    Thing_Remove(0);
}

/*
NamedScript Console void DumpItemData()
{
    Log("\Cd---------- BEGIN ITEMDATA DUMP ----------");
    for (int i = 0; i < ITEM_CATEGORIES; i++)
    {
        Log("\Cd---------- %S ----------", ItemCategoryNames[i]);
        
        for (int j = 0; j < ItemMax[i]; j++)
            Log("%S, %d, %d",ItemData[i][j].Actor, ItemData[i][j].Price, ItemData[i][j].Rank);
    };
    
    Log("\Cd---------- END ITEMDATA DUMP ----------");
    
    Log("\Cd---------- BEGIN REWARDLIST DUMP ----------");
    
    for (int i = 0; i < (MAX_DIFFICULTIES + 2); i++) //+1 is demonic, +2 is legendary
        for (int j = 0; j < MaxRewards[i]; j++)
             Log("%S, %d, %d",RewardList[i][j]->Actor, j, RewardList[i][j]->Rarity);
    
    Log("\Cd---------- END REWARDLIST DUMP ----------");
}
*/
