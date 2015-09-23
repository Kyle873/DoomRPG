#ifndef _RPG_DH_
#define _RPG_DH_

#include "Defs.h"
//#include "GUI.h"
#include "ItemData.h"
#include "Skills.h"
#include "Shield.h"
#include "Monsters.h"

// Forward Declarations

AddressSpace extern GlobalArraySpace ItemSpace;
AddressSpace extern MapArraySpace MonsterSpace;
AddressSpace extern GlobalArraySpace ShieldSpace;

typedef struct
{
    // Basic
    bool Active;
    int Type;
    int Difficulty;
    
    // Reward
    long int RewardXP;
    long int RewardRank;
    int RewardCredits;
    int RewardModules;
    ItemInfo ItemSpace *RewardItem;
    
    // Mission Data
    ItemInfo ItemSpace *Item;
    MonsterInfo MonsterSpace const *Monster;
    int Current;
    int Amount;
} MissionInfo;

typedef struct _turretupgrade
{
    str Name;
    int MaxLevel;
    int Cost;
    
    str Description;
    str UpgradeInfo;
    str CommandInfo;
    
    struct _turretupgrade *Prereq;
} TurretUpgrade;

typedef struct
{
    int TID;
    int PlayerView;
    
    // Flags
    bool FirstRun;
    bool InMenu;
    bool InShop;
    bool InMinigame;
    bool CrateOpen;
    bool LastLegs;      // You're about to die, do something about it!
    
    // Primary Stats
    int Strength;       // Increases Damage
    int Defense;        // Reduces Damage taken
    int Vitality;       // Increases max Health and HP regen rate
    int PrevVitality;   // Player's Vitality from last tic
    int Energy;         // Increases max EP and EP regen rate
    int PrevEnergy;     // Player's Energy from last tic
    int Regeneration;   // Increases both HP/EP regen rate
    int Agility;        // Increases movement speed, jump height and survival bonus (and optionally weapon speed)
    int Capacity;       // Increases max ammo capacities
    int Luck;           // Increases drop chances
    int ActualHealth;   // The player's real, actual Health
    int HealthMax;      // Max player Health
    int PrevHealth;     // Player's Health from last tic
    int PrevCredits;    // Player's held Credits from last tic
    
    // Stat Bonuses
    int StrengthBonus;
    int DefenseBonus;
    int VitalityBonus;
    int EnergyBonus;
    int RegenerationBonus;
    int AgilityBonus;
    int CapacityBonus;
    int LuckBonus;
    
    // Stat XP Levels
    long int StrengthXP;
    long int DefenseXP;
    long int VitalityXP;
    long int EnergyXP;
    long int RegenerationXP;
    long int AgilityXP;
    long int CapacityXP;
    long int LuckXP;
    
    // Stat Perks
    bool Perks[STAT_MAX];
    int AgilityTimer;
    
    // Secondary Stats
    int LevelDamage;            // Damage dependent on the player's level
    int BonusDamage;            // Damage bonus given by the Strength stat
    fixed DamageMult;           // Damage multiplier from Red Aura and Strength Aug
    int TotalDamage;            // Combined LevelDamage and BonusDamage
    fixed DamageFactor;         // General damage the player will defend against
    int Mass;                   // Player mass, for preventing knockback
    fixed StatusEffectResist;   // Chance to resist a status effect
    int AuraRange;              // The reach of your auras to affect other players
    int ToxicityRegenBonus;     // Speed at which Toxicity dissipates over time
    fixed Speed;                // Movement Speed
    fixed JumpHeight;           // Jump Height
    int WeaponSpeed;            // Weapon Speed Increase bsed on Agility
    fixed SurvivalBonus;        // Chance that you will survive a fatal hit
    int InvItems;               // How many inventory items you are currently carrying
    int StatCap;                // Current Stat Cap
    
    // Energy Points (EP)
    int EP;
    int EPMax;
    
    // Level
    int Level;
    long int XP;
    long int XPNext;
    
    // Rank
    str RankString;
    int RankLevel;
    long int Rank;
    long int RankNext;
    int PayTimer;
    int PayKills;
    int PayBonus;
    
    // Combo System
    int Combo;
    int ComboTimer;
    int BonusGained;
    int XPGained;
    int RankGained;

    // HP/EP Regen Timers
    int HPRate;
    int HPTime;
    int HPAmount;
    int EPRate;
    int EPTime;
    int EPAmount;
    int RegenBoostTimer;

    // Can Drop / Drop Chance Percentages
    bool HealthDrop;
    bool EPDrop;
    bool ArmorDrop;
    bool PowerupDrop;
    bool WeaponDrop;
    bool ModuleDrop;
    bool AugDrop;
    bool ShieldDrop;
    bool StimDrop;
    fixed HealthChance;
    fixed EPChance;
    fixed ArmorChance;
    fixed PowerupChance;
    fixed WeaponChance;
    fixed ModuleChance;
    fixed AugChance;
    fixed ShieldChance;
    fixed StimChance;
    
    // Menu Data
    bool MenuBlock;
    int Menu;
    int OutpostMenu;
    int MenuIndex;
    int StatPage;
    int SkillPage;
    int ShieldPage;
    bool NewShieldParts[3][MAX_PARTS];
    bool NewShieldAccessoryParts[MAX_ACCESSORIES];
    int StimSelected;
    int TurretPage;
    int ShopIndex;
    int ShopPage;
    
    // Skill Info
    SkillLevelInfo SkillLevel[MAX_CATEGORIES][MAX_SKILLS];
    AuraInfo Aura;
    bool AuraBonus;
    fixed SkillRefundMult;
    bool SkillWheelOpen;
    int WheelSelection;
    int SkillSelected;
    int SkillCategory[MAX_SKILLKEYS];
    int SkillIndex[MAX_SKILLKEYS];
    int Summons;
    int SummonTID[MAX_SUMMONS];
    bool SoulActive[SOUL_MAX];
    bool OverHeal;
    int SkillCostMult;
    int SkillPowerupCooldown;
    int SkillSupplyCooldown;
    bool Focusing;
    
    // Status Effects
    bool StatusType[SE_MAX];
    int StatusTypeHUD;
    int StatusIntensity[SE_MAX];
    int StatusTimer[SE_MAX];
    int StatusTimerMax[SE_MAX];
    int Toxicity;
    
    // Locker
    bool LockerMode;
    int Locker[ITEM_CATEGORIES][ITEM_MAX];
    struct DRLAWeapon
    {
        int Total;
        int Power;
        int Bulk;
        int Agility;
        int Technical;
        int Sniper;
        int Firestorm;
        int Nano;
        int Artifacts;
    } WeaponMods[ITEM_MAX];
    
    // GUI
    bool GUIOpen;
    //MouseInfo Mouse;
    //GUIWindow * Window[MAX_WINDOWS];
    
    // Auto-Sell/Auto-Store
    int ItemAutoMode[ITEM_CATEGORIES][ITEM_MAX];
    DynamicArray AutoSellList;
    DynamicArray AutoStoreList;
    
    // Toxicity Meter
    int ToxicTimer;
    int ToxicOffset;
    int ToxicStage;
    
    // Crate
    int CrateID;
    int CrateIndex;
    bool CrateHacking;
    
    // Damage
    int DamageTID;
    int DamageType;
    
    // Misc
    int StimImmunity;
    int ShopDiscount;
    int ShopCard;
    int DelayTimer;
    bool AutosaveTimerReset;
    bool SeenEventTip[MAPEVENT_MAX];
    
    // Associated Drops
    DynamicArray DropTID;
    
    // Structception
    struct
    {
        fixed Battery;
        fixed BatteryMax;
        fixed BatteryDrain;
        int BaseSlots;
        int Slots;
        int SlotsUsed;
        bool Active[AUG_MAX];
        int Level[AUG_MAX];
    } Augs;
    
    struct
    {
        // Current Parts
        ShieldPart ShieldSpace *Body;
        ShieldPart ShieldSpace *Battery;
        ShieldPart ShieldSpace *Capacitor;
        ShieldAccessory ShieldSpace *Accessory;
        
        // Flags
        bool Active;
        bool Full;
        
        // Stats
        int Charge;
        int Capacity;
        int Interval;
        int ChargeRate;
        fixed DelayRate;
        int Timer;
        
        // Accessories
        int AccessoryBattery;
        int AccessoryTimer;
        Position AccessoryPosition;
        
        // Armor
        str ArmorType;
        int ArmorAmount;
        int ArmorMax;
    } Shield;
    
    struct
    {
        int Vials[STIM_MAX];
        bool ActiveBonus[STIM_MAX];
        int Current[STIM_MAX];
        int Last[STIM_MAX];

        int PowerupTimer[STIM_MAX];
        int PowerupTimerMax[STIM_MAX];
        
        int PrevStats[STAT_MAX];
        
        bool Active;
        int Size;
        int Amount;
        int Capacity;
        int VialMax;
        int Timer;
        int TimerMax;
        int Toxicity;
    } Stim;
    
    struct
    {
        // Flags
        bool Init;
        bool Active;
        bool Destroyed;
        bool Maintenance;
        bool PaidForRepair;
        
        // TID
        int TID;
        
        // Command Wheel
        bool WheelOpen;
        int WheelCommand;
        
        // Upgrades
        int Upgrade[MAX_UPGRADES];
        
        // Health
        int Health;
        int HealthMax;
        
        // Weapons/Ammo
        int Weapon;
        int BulletAmmo;
        int BulletAmmoMax;
        int ShellAmmo;
        int ShellAmmoMax;
        int RocketAmmo;
        int RocketAmmoMax;
        int PlasmaAmmo;
        int PlasmaAmmoMax;
        int RailAmmo;
        int RailAmmoMax;
        bool Autoload;
        bool SelfDestruct;
        
        // Assist
        bool TeleportEnabled;
        bool StimFocused;
        bool StimPicked;
        int StimTimer;
        int StimVialType;
        
        // Sensors
        bool SensorsActive;
        int SensorMode;
        int SensorPercent;
        int ModulesCollected;
        
        struct
        {
            bool Enabled;
            DynamicArray Array;
            int CurrentPosition;
            int PulseDelay;
            int CheckDelay;
        } SensorItemData;
        
        struct
        {
            bool Enabled;
            DynamicArray Array;
            int CurrentPosition;
            int PulseDelay;
            int CheckDelay;
        } SensorCrateData;
        
        // Command
        int Command;
        
        // Battery
        int Battery;
        int BatteryMax;
        
        // Timers
        int HitTimer;
        int TeleportTimer;
        int ChargeTimer;
        int RepairTimer;
        int RefitTimer;
        
        // Offsets
        fixed AngleOffset;
        fixed DistanceOffset;
        fixed HeightOffset;
    } Turret;
    
    MissionInfo Mission;
} PlayerData;

// Version
extern str MapRegister Version;

// Flags
extern bool Transported;
extern bool GlobalsInitialized;
extern int CompatMode;

// Arrays
extern str PlayerWeapon[MAX_PLAYERS];

// Structs
extern PlayerData _PlayerData[MAX_PLAYERS];

// Item TIDs
extern bool MapRegister ItemTIDsInitialized;
extern int MapArray ItemTIDs[MAX_ITEMS];

// --------------------------------------------------
// Multiplayer HUD
// 

// HUD Item Counts
extern int GlobalArray Address(18) Credits[MAX_PLAYERS];

// Energy Points (EP)
extern int GlobalArray Address(2) EP[MAX_PLAYERS];

// Shield
extern int GlobalArray Address(50) Shield[MAX_PLAYERS];
extern int GlobalArray Address(51) ShieldCapacity[MAX_PLAYERS];
extern int GlobalArray Address(52) ShieldHealth[MAX_PLAYERS];

NamedScript KeyBind void QuickHeal(bool);
NamedScript KeyBind void ToggleFocusMode();
NamedScript KeyBind void FocusMode();
NamedScript void StatusEffect(int, int, int);
NamedScript int AddHealth(int, int);
NamedScript int AddHealthDirect(int, int);
NamedScript void GiveTip();

NamedScript Type_OPEN void GlobalInit();
NamedScript Type_ENTER void Init();
NamedScript void Loop();
NamedScript void WeaponSpeed();
NamedScript void PlayerDamage();
NamedScript void StatRandomizer();
NamedScript void AutosaveHandler();
NamedScript Type_OPEN void ShopSpecialHandler();
NamedScript void ItemHandler();
NamedScript void ItemInit();
NamedScript OptionalArgs(1) void DynamicLootGenerator(str, int);
NamedScript Type_DEATH void Dead();
NamedScript Type_RESPAWN void Respawn();
NamedScript void SortStartingItems();
NamedScript void DefaultLoadout();

void CheckHUD();
void CheckKeys();
void CheckCompatibility();
void AssignTIDs();

#endif
