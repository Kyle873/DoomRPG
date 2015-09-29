#ifndef DOOMRPG_STRUCTS_H
#define DOOMRPG_STRUCTS_H

// --------------------------------------------------
// Common Structures
//

// Generic

struct DynamicArray_S
{
    str Name;
    int Position;
    int Size;
    int ItemSize;
    void *Data;
};

struct InterpData_S
{
    long Value;
    long OldValue;

    long StartValue;
    long DisplayValue;

    int Timer;
    int TimerMax;
    int TimerMaxCap;
};

struct Position_S
{
    fixed X;
    fixed Y;
    fixed Z;
    fixed Angle;
    fixed Pitch;
};

// Used by DropEntireInventory()
struct DroppedItem_S
{
    str Actor;
    bool NoDrop;
    bool TakeAll;
    int Max;
};

// Augmentations

struct AugInfo_S
{
    str Name;
    int MaxLevel;
    str Description[MAX_AUG_LEVEL];
    str TokenActor;
};

// Charsave

struct CharSaveInfo_S
{
    // Version / Compatibility Flag
    int Version;
    int CompatMode;
    
    // Level / Rank Level
    int Level;
    int RankLevel;
    
    // Stats
    int Stats[STAT_MAX];
    
    // Skills
    int Skills[MAX_CATEGORIES][MAX_SKILLS];
    
    // Skill Wheel
    int SkillWheel[MAX_SKILLKEYS][2];
    
    // Augmentations
    int Augs[AUG_MAX];
    
    // Stims
    int Stims[STIM_MAX];
    
    // Turret Upgrades
    int TurretUpgrades[TU_MAX];
    
    // Misc
    int Credits;
    int Modules;
    int GoldChips;
    int PlatinumChips;
    int ShopCard;
    int Battery;
    int Toxicity;
    int PayBonus;
    int ArenaWave;
    
    // Locker
    int Locker[ITEM_CATEGORIES][ITEM_MAX];
    int WeaponMods[ITEM_MAX][DRLA_MODPACK_SIZE];
    
    // Auto-Sell
    int ItemAutoMode[ITEM_CATEGORIES][ITEM_MAX];
    
    // ----- COMPATIBILITY EXTENSIONS -----
    
    // DRLA Tokens
    bool DRLATokens[DRLA_MAX_TOKENS];
    
    // ------------------------------------
    
    // Checksum
    unsigned int Checksum;
};

// GUI

struct MouseInfo_S
{
    int X;
    int Y;
    int XAdd;
    int YAdd;
    int Buttons;
    int OldButtons;
    bool LeftButton;
    bool RightButton;
    bool LeftButtonDown;
    bool RightButtonDown;
};

// Pre-define control structs for the GUIWindow
extern struct GUIWindow_S;
extern struct GUILabel_S;
extern struct GUIIcon_S;
extern struct GUIButton_S;
extern struct GUIBar_S;
extern struct GUIList_S;
extern struct GUITooltip_S;
extern struct GUIContextMenu_S;

// GUI Event Function Pointers
typedef void (*LabelEventFunc)(struct _guilabel *);
typedef void (*IconEventFunc)(struct _guiicon *);
typedef void (*ButtonEventFunc)(struct _guibutton *);
typedef void (*BarEventFunc)(struct _guibar *);
typedef void (*ListEventFunc)(struct _guilist *);
typedef void (*ContextMenuEventFunc)(int);

struct GUIWindow_S
{
    str Title;
    int X;
    int Y;
    int Width;
    int Height;
    bool Dragging;
    bool Focused;
    bool Visible;
    bool RolledUp;
    bool CanClose;
    bool CanRoll;
    
    // Controls
    struct GUILabel_S  *Labels[MAX_CONTROLS];
    struct GUIIcon_S   *Icons[MAX_CONTROLS];
    struct GUIButton_S *Buttons[MAX_CONTROLS];
    struct GUIBar_S    *Bars[MAX_CONTROLS];
    struct GUIList_S   *Lists[MAX_CONTROLS];
};

struct GUILabel_S
{
    str Text;
    int Alignment;
    int X;
    int Y;
    int Width;
    int Height;
    int Color;
    bool Big;
    bool Visible;
    
    struct GUIWindow_S *Window;
    struct GUITooltip_S *Tooltip;
    struct GUIContextMenu_S *ContextMenu;
};

struct GUIIcon_S
{
    str Texture;
    int X;
    int Y;
    int XOff;
    int YOff;
    int Width;
    int Height;
    bool CalculateSize;
    bool Visible;
    
    struct GUIWindow_S *Window;
    struct GUITooltip_S *Tooltip;
    struct GUIContextMenu_S *ContextMenu;
    
    IconEventFunc OnClick;
};

struct GUIButton_S
{
    str Text;
    int X;
    int Y;
    int Width;
    int Height;
    int Color;
    int HoverColor;
    bool Big;
    bool Visible;
    
    struct GUIWindow_S *Window;
    struct GUITooltip_S *Tooltip;
    struct GUIContextMenu_S *ContextMenu;
    
    ButtonEventFunc OnClick;
};

struct GUIBar_S
{
    int X;
    int Y;
    int Width;
    int Height;
    int Value;
    int ValueMax;
    str Texture;
    bool Visible;
    
    struct GUIWindow_S *Window;
    struct GUITooltip_S *Tooltip;
    struct GUIContextMenu_S *ContextMenu;
};

struct GUIList_S
{
    int X;
    int Y;
    int Shown;
    int Offset;
    int Selected;
    str Entries[MAX_LIST];
    int Colors[MAX_LIST];
    int HoverColors[MAX_LIST];
    bool Visible;
    
    struct GUIWindow_S *Window;
    struct GUITooltip_S *Tooltip;
    struct GUIContextMenu_S *ContextMenu;
    
    ListEventFunc OnClick;
};

struct GUITooltip_S
{
    int Type;
    str Title;
    str Text;
    int Color;
    int Width;
    int Height;
    str Icon;
    int IconXOff;
    int IconYOff;
    bool NoBack;
};

struct GUIContextMenu_S
{
    int X;
    int Y;
    
    str Name[MAX_OPTIONS];
    ContextMenuEventFunc OnClick[MAX_OPTIONS];
    
    int Data;
};

// Items

// Item Definition
struct ItemInfo_S
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

// Crates

struct HackNode_S
{
    bool Active;
    int Type;
    int Start;
    int End;
};

struct CrateInfo_S
{
    bool Generated;
    bool SupplyDrop;
    bool Firewall;
    bool Empty;
    int TID;
    int Amount;
    int Rarity;
    
    bool Active[CRATE_MAX_ITEMS];
    struct ItemInfo_S RPGGlobal *Item[CRATE_MAX_ITEMS];
    
    // Hacking Minigame
    bool HacksGenerated;
    int Hacking;
    int HackingCooldown;
    
    int Tries;
    
    int NodeMax[NODE_MAX];
    
    struct HackNode_S Nodes[MAX_NODES];
    int GenTotal;
    int GenType;
    int GenNodes[NODE_MAX];
};

// Skills

struct SkillLevelInfo_S
{
    int CurrentLevel;
    int Level;
};

typedef bool (*SkillUseScript NamedScript Console)(struct _skilllevelinfo *, void *);

struct Skill_S
{
    str Name;
    int Cost;
    int MaxLevel;
    SkillUseScript Use;
    str Description[MAX_LEVELS];
    str Icon;
};

struct AuraInfo_S
{
    int Time;
    fixed Range;
    bool Team;
    bool DefenseBoost;

    struct
    {
        bool Active;
        int Level;
    } Type[AURA_MAX];
};

// Shield

struct ShieldPart_S
{
    str Actor;
    str Name;
    str Icon;
    
    int Capacity;
    int ChargeRate;
    fixed DelayRate;
};

typedef void (*ShieldAccModScript NamedScript)();
typedef void (*ShieldAccEquipScript NamedScript)();
typedef void (*ShieldAccUnequipScript NamedScript)(bool);
typedef void (*ShieldAccDamageScript NamedScript)(int);
typedef void (*ShieldAccBreakScript NamedScript)();
typedef int  (*ShieldAccChargeScript NamedScript)(int);
typedef void (*ShieldAccOverchargeScript NamedScript)(int);
typedef bool (*ShieldAccFastChargeScript NamedScript)();
typedef void (*ShieldAccFullChargeScript NamedScript)();

struct ShieldAccessory_S
{
    str Actor;
    str Name;
    str Icon;
    int Price;
    str Description;
    EShieldPassive PassiveEffect;
    
    ShieldAccModScript          Modifier;
    ShieldAccEquipScript        Equip;
    ShieldAccUnequipScript      Unequip;
    ShieldAccDamageScript       Damage;
    ShieldAccBreakScript        Break;
    ShieldAccChargeScript       Charge;
    ShieldAccOverchargeScript   Overcharge;
    ShieldAccFastChargeScript   FastCharge;
    ShieldAccFullChargeScript   FullCharge;
};

// Monsters

struct MonsterStats_S
{
    // Basic
    int TID;
    str Actor;
    str ReplaceActor;
    struct Position_S spawnPos;
    int Flags;
    int RenderStyle;
    int SpawnHealth;
    int HealthMax;
    int RegenHealth;
    
    // Properties
    fixed Speed;
    fixed Height;
    fixed Radius;
    
    // Flags
    bool Init;
    bool NeedReinit;
    bool HealthBar;
    bool Named;
    bool Reinforcement;
    bool MegaBoss;
    
    // Missions
    int Target;
    
    // Stats
    int Level;
    int Threat;
    int Strength;
    int Defense;
    int Vitality;
    int Energy;
    int Regeneration;
    int Agility;
    int Capacity;
    int Luck;
    
    // Auras
    struct AuraInfo_S Aura;
};

struct MonsterInfo_S
{
    str Actor;
    str Name;
    
    // This monster's relative threat level as a percentage
    int Difficulty;
    int ThreatLevel;
    // These guys are in short supply
    bool Boss;
    
    // Special event text for One Monster level events
    str Feeling;
};

struct MegabossInfo_S
{
    str Actor;
    str Music;
};

// Health Bars

struct HUDBarInfo_S
{
    // Is this referencing a player or enemy?
    bool IsPlayer;
    // Is the actor friendly?
    bool Friendly;
    
    // Basic
    str Actor;
    str NameColor;
    str Name;
    int Level;
    int Rank;
    int Flags;
    struct AuraInfo_S Aura;
    
    // Health, Armor, Shield
    int Health;
    int HealthMax;
    int SpawnHealth;
    int Armor;
    int ArmorMax;
    bool ShieldActive;
    int Shield;
    int ShieldMax;
    
    // Stats
    int Strength;
    int Defense;
    int Vitality;
    int Energy;
    int Regeneration;
    int Agility;
    int Capacity;
    int Luck;
    
    // Position
    fixed X;
    fixed Y;
    fixed Z;
    fixed Height;
};

// Missions

struct MissionInfo_S
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
    struct ItemInfo_S const *RewardItem;
    
    // Mission Data
    struct ItemInfo_S const *Item;
    struct MonsterInfo_S const *Monster;
    int Current;
    int Amount;
};

// Minigames

struct MinigameData_S
{
    bool Ingame;
};

// Turret

struct TurretUpgrade_S
{
    str Name;
    int MaxLevel;
    int Cost;
    
    str Description;
    str UpgradeInfo;
    str CommandInfo;
    
    struct TurretUpgrade_S *Prereq;
};

struct TurretSensorItem_S
{
    int TID;
    int Category;
};

// Map

struct LevelInfo_S
{
    // MAPINFO Level Number
    int LevelNum;
    
    // If we start in the Outpost, we set this on MAP01 to tell ourselves that
    // we need to replace the placeholder info with real info.
    bool NeedsRealInfo;
    
    // Map is an Outpost or an Arena
    bool UACBase;
    bool UACArena;
    
    // Name data
    str LumpName;
    str NiceName;
    
    // Level stats
    bool Completed;
    
    int MaxMonstersKilled;
    int MaxTotalMonsters;
    int MaxMonsterPercentage;
    int MaxItemsFound;
    int MaxTotalItems;
    int MaxItemPercentage;
    int MaxSecretsFound;
    int MaxTotalSecrets;
    int MaxSecretPercentage;
    int ShortestTime;
    int UniqueSecrets;
    
    // Par/Sucks time
    int Par;
    int Sucks;
    
    // 100% Bonuses
    bool KillBonus;
    bool ItemsBonus;
    bool SecretsBonus;
    bool AllBonus;
    bool ParBonus;
    
    // Miscellaneous
    int AdditionalMonsters;
    bool SecretMap;
    
    // Event stuff
    struct DynamicArray_S MonsterPositions;
    unsigned int Event;
    bool EventCompleted;
    
    // Megaboss Event
    struct MegabossInfo_S *MegabossActor;
    
    // Environmental Hazard Event
    int HazardLevel;
    int RadLeft;
    int GeneratorFuel;
    
    // Thermonuclear Bomb event
    int BombTime;
    bool BombExplode;
    bool BombAnnouncing;
    bool BombKeyActive[MAX_NUKE_KEYS];
    bool BombKeyDisarming[MAX_NUKE_KEYS];
    int BombKeyTimer[MAX_NUKE_KEYS];
    
    // Low Power Event
    bool PowerGeneratorActive;
    
    // One Monster Event
    struct MonsterInfo_S *SelectedMonster;
    
    // Hell Unleashed Event
    int HellUnleashedActive;
    int PandoraBoxTID;
    fixed LevelAdd;
    fixed RareAdd;
    
    // Harmonized Destruction event
    int AuraType;
    
    // Doomsday Event
    int DoomTime;
};

// PDA

struct PDAMessage_S
{
    str Text;
    fixed X;
    fixed Y;
    int ID;
};

// RPG

struct PlayerData_S
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
    struct SkillLevelInfo_S SkillLevel[MAX_CATEGORIES][MAX_SKILLS];
    struct AuraInfo_S Aura;
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
    struct
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
    struct MouseInfo_S Mouse;
    struct GUIWindow_S *Window[MAX_WINDOWS];
    
    // Auto-Sell/Auto-Store
    int ItemAutoMode[ITEM_CATEGORIES][ITEM_MAX];
    struct DynamicArray_S AutoSellList;
    struct DynamicArray_S AutoStoreList;
    
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
    struct DynamicArray_S DropTID;
    
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
        struct ShieldPart_S *Body;
        struct ShieldPart_S *Battery;
        struct ShieldPart_S *Capacitor;
        struct ShieldAccessory_S *Accessory;
        
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
        struct Position_S AccessoryPosition;
        
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
            struct DynamicArray_S Array;
            int CurrentPosition;
            int PulseDelay;
            int CheckDelay;
        } SensorItemData;
        
        struct
        {
            bool Enabled;
            struct DynamicArray_S Array;
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
    
    struct MissionInfo_S Mission;
};

#endif // DOOMRPG_STRUCTS_H
