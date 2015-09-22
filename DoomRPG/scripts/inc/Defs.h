#ifndef DOOMRPG__SCRIPTS__DEFS_H
#define DOOMRPG__SCRIPTS__DEFS_H

#include <ACS_ZDoom.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdfix.h>

// Sanity pragmas
#pragma GDCC STRENT_LITERAL ON
#pragma GDCC FIXED_LITERAL  ON

// Aliases
#define ACS_EndHudMessage2      ACS_EndHudMessageX
#define ACS_EndHudMessage3      ACS_EndHudMessageXX
#define ACS_EndHudMessage4      ACS_EndHudMessageXXX
#define ACS_EndHudMessageBold2  ACS_EndHudMessageBoldX
#define ACS_EndHudMessageBold3  ACS_EndHudMessageBoldXX
#define ACS_EndHudMessageBold4  ACS_EndHudMessageBoldXXX

#define HudMessage(flags, id, color, x, y, hold, opt1, opt2, opt3, ...) \
    ( \
        ACS_BeginHudMessage(), \
        __nprintf_str(__VA_ARGS__), \
        ACS_MoreHudMessage(), \
        ACS_OptHudMessage(flags, id, color, x, y, hold), \
        ACS_EndHudMessage4(opt1, opt2, opt3) \
    )
#define PrintBold(...) \
    ( \
        ACS_BeginPrintBold(), \
        __nprintf_str(__VA_ARGS__), \
        ACS_EndPrint() \
    )
#define Print(...) \
    ( \
        ACS_BeginPrint(), \
        __nprintf_str(__VA_ARGS__), \
        ACS_EndPrint() \
    )
#define StrParam(...) \
    ( \
        ACS_BeginStrParam(), \
        __nprintf_str(__VA_ARGS__), \
        ACS_EndStrParam() \
    )
#define PrintSprite(spr, id, x, y, delay) \
    ( \
        ACS_SetFont(spr), \
        ACS_HudMessage(HUDMSG_PLAIN, id, CR_UNTRANSLATED, x, y, delay, 0.0, 0.0, 0.0, "A") \
    )
#define ClearMessage(id) \
    ( \
        ACS_HudMessage(HUDMSG_PLAIN, id, CR_UNTRANSLATED, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, "") \
    )
#define Log(...) \
    ( \
        ACS_BeginLog(), \
        __nprintf_str(__VA_ARGS__), \
        ACS_EndLog() \
    )
#define PlayerName(n) \
    ( \
        ACS_BeginPrint(), \
        ACS_PrintName(n), \
        ACS_EndStrParam() \
    )

// Script declaration stuff
#define far_ptr         __far
#define script_local    __loc
#define string_table    __str_ars

#define address_space       __addrdef
#define space_map_array     __map_arr
#define space_hub_array     __wld_arr
#define space_global_array  __gbl_arr

#define reserved_reg    __loc_reg
#define map_reg         __map_reg
#define hub_reg         __wld_reg
#define global_reg      __gbl_reg

#define reserved_array  __loc_ars
#define map_array       __map_ars
#define hub_array       __wld_ars
#define global_array    __gbl_ars

#define opt_args(N)     [[optional_args(N)]]

#define decorate        [[extern("ACS")]]
#define levelspec       [[extern("ACS")]]
#define keybind         [[extern("ACS"), script("Net")]]

#define number_script(N)        [[call("ScriptI"), address(N)]]
#define named_script            [[call("ScriptS")]]
#define number_script_sync(N)   [[call("SScriptI"), address(N)]]
#define named_script_sync       [[call("SScriptS")]]

#define type_open       [[script("Open")]]
#define type_unloading  [[script("Unloading")]]
#define type_lightning  [[script("Lightning")]]

#define type_enter      [[script("Enter")]]
#define type_return     [[script("Return")]]
#define type_respawn    [[script("Respawn")]]
#define type_death      [[script("Death")]]
#define type_disconnect [[script("Disconnect")]]

#define sflag_puke      [[script("Net")]]
#define sflag_client    [[script("Clientside")]]

// Macro functions
#define MAKE_ID(a, b, c, d) ((int)((a) | ((b) << 8) | ((c) << 16) | ((d) << 24)))

// Constants
#define MAX_PLAYERS             8
#define PLAYER_TID              31337
#define PI                      3.14159265359

// Type definitions
typedef __str string;

// --------------------------------------------------
// Arena
//

#define ARENA_HOLDTIME (35)

enum EArenaStates
{
    ARENA_INTERMISSION,
    ARENA_WAITING,
    ARENA_READY,
    ARENA_ACTIVE,
};

enum EArenaModTypes
{
    AMOD_NONE,
    AMOD_NOREGEN,
    AMOD_MAX,
};

enum EArenaEventTypes
{
    AEVENT_RANDOM = -1,
    AEVENT_NONE = 0,
    AEVENT_BLACKOUT,
    AEVENT_FOGGY,
    AEVENT_LAVA,
    AEVENT_GRAYSCALE,
    AEVENT_MAX,
};

enum EArenaBonusTypes
{
    ABONUS_SELECT,
    ABONUS_FULLEP,
    ABONUS_MONEYDROP,
    ABONUS_CHIPDROP,
    ABONUS_AMMODROP,
    ABONUS_HEALTHDROP,
    ABONUS_ARMORDROP,
    ABONUS_WEAPONDROP,
    ABONUS_POWERUPDROP,
    ABONUS_STIMDROP,
    ABONUS_CRATEDROP,
    ABONUS_MODDROP,
    ABONUS_KEYDROP,
    ABONUS_MAX,
};

enum EArenaKeyTimerTypes
{
    AKTIMER_STOP,
    AKTIMER_CONTINUE,
};

// --------------------------------------------------
// Augmentations
//

#define MAX_AUG_LEVEL (9)

enum EAugTypes
{
    AUG_STRENGTH,
    AUG_DEFENSE,
    AUG_VITALITY,
    AUG_ENERGY,
    AUG_REGENERATION,
    AUG_AGILITY,
    AUG_CAPACITY,
    AUG_LUCK,
    AUG_BATTERY,
    AUG_MAX,
};

// --------------------------------------------------
// CharSave
//

#define CHARSAVE_VERSION        14
#define CHARSAVE_MAXSIZE        224
#define CHARSAVE_MAXCVARS       16
#define DRLA_MODPACK_SIZE       9
#define DRLA_MAX_TOKENS         164
#define DEPOSIT_ID              MAKE_ID('D', 'P', 'S', 'T')

// --------------------------------------------------
// Crate
//

#define CRATE_MAX               256
#define CRATE_MAX_ITEMS         54
#define MAX_DRLA_SETS           18
#define MAX_NODES               32

enum ENodeTypes
{
    NODE_CRITFAIL,  // Red
    NODE_EXPLODE,   // Orange
    NODE_UNLOCK,    // Blue
    NODE_XP,        // White
    NODE_RANK,      // Yellow
    NODE_RETRY,     // Dark Blue
    NODE_ADD,       // Light Blue
    NODE_RARITY,    // Purple
    NODE_MAX,
};

// --------------------------------------------------
// Health Bars
//

#define HBAR_ID                 (MAKE_ID('H', 'B', 'A', 'R'))

// --------------------------------------------------
// HUD
//

#define STAT_ID                 (MAKE_ID('S', 'T', 'A', 'T'))

// --------------------------------------------------
// Item Data
//

#define ITEM_CATEGORIES         16
#define ITEM_MAX                256

enum ECategoryFlags
{
    CF_NONE     = 0x0,
    CF_NOSELL   = 0x1,
    CF_NOBUY    = 0x2,
    CF_NOSTORE  = 0x4,
    CF_NODROP   = 0x8,
};

// --------------------------------------------------
// Map
//

#define NUKE_ID                 (MAKE_ID('N', 'U', 'K', 'E'))
#define MAX_NUKE_KEYS           9

#define MAP_EXIT_SCRIPTNUM      30000

enum EMapEvents
{
    MAPEVENT_NONE,

    MAPEVENT_MEGABOSS,
    MAPEVENT_TOXICHAZARD,
    MAPEVENT_NUCLEARBOMB,
    MAPEVENT_LOWPOWER,
    MAPEVENT_ALLAURAS,
    MAPEVENT_ONEMONSTER,
    MAPEVENT_HELLUNLEASHED,
    MAPEVENT_HARMONIZEDAURAS,
    MAPEVENT_TELEPORTCRACKS,
    MAPEVENT_DOOMSDAY,
    MAPEVENT_ACIDRAIN,
    MAPEVENT_DARKZONE,

    MAPEVENT_DRLA_FEEDINGFRENZY,
    MAPEVENT_DRLA_OVERMIND,

    MAPEVENT_BONUS_RAINBOWS,

    MAPEVENT_SKILL_HELL,
    MAPEVENT_SKILL_ARMAGEDDON,

    MAPEVENT_SPECIAL_SINSTORM,

    MAPEVENT_MAX
};

enum EUACOutpostEvents
{
    UACEVENT_NONE,

    UACEVENT_INVASION,
    UACEVENT_LOWPOWER,

    UACEVENT_MAX
};

// --------------------------------------------------
// Menu
//

#define MAX_MENU                7
#define TURRET_PAGE_MAX         36
#define MENU_ID                 (MAKE_ID('M', 'E', 'N', 'U'))
#define TOXMETER_ID             (MAKE_ID('T', 'O', 'X', 'I'))

enum EMenuPages
{
    MENUPAGE_MAIN,
    MENUPAGE_STATS,
    MENUPAGE_AUGS,
    MENUPAGE_SKILLS,
    MENUPAGE_SHIELD,
    MENUPAGE_STIMS,
    MENUPAGE_TURRET,
    MENUPAGE_MAX
};

enum EStatPages
{
    STATPAGE_STATS,
    STATPAGE_STATXP,
    STATPAGE_PERKS,
    STATPAGE_TEAM,
    STATPAGE_MAX
};

enum ESHieldPages
{
    SHIELDPAGE_BODY,
    SHIELDPAGE_BATTERY,
    SHIELDPAGE_CAPACITOR,
    SHIELDPAGE_ACCESSORY,
    SHIELDPAGE_MAX
};

enum ETurretPages
{
    TURRETPAGE_COMMAND,
    TURRETPAGE_UPGRADE,
    TURRETPAGE_MAX
};

// --------------------------------------------------
// Minigame
//

#define MINIGAME_ID             12000
#define MAX_ROULETTE_ITEMS      20

// --------------------------------------------------
// Mission
//

#define MAX_MISSIONS            30
#define MISSION_ID              (MAKE_ID('M', 'I', 'S', 'S'))
#define MAX_DIFFICULTIES        9
#define MAX_LOOT                13

enum EMissionTypes
{
    MT_COLLECT,
    MT_KILL,
    MT_KILLAURAS,
    MT_REINFORCEMENTS,
    MT_ASSASSINATION,
    MT_SECRETS,
    MT_ITEMS,
    MT_COMBO,
    MT_MAX
};

// --------------------------------------------------
// Monsters
//
#define MAX_MONSTERS            16384
#define MAX_DEF_MONSTERS        17
#define MAX_DEF_MONSTERS_DRLA   71
#define MAX_TEMP_MONSTERS       100
#define MAX_MEGABOSSES          2

enum EMonsterFlags
{
    MF_BOSS         = 0x0001,
    MF_NOXP         = 0x0002,
    MF_NOSTATS      = 0x0004,
    MF_NOAURA       = 0x0008,
    MF_NOPAYKILL    = 0x0010,
    MF_NODROPS      = 0x0020,
    MF_NOHEALTHBAR  = 0x0040,
    MF_NOWEAKEN     = 0x0080,
    MF_MEGABOSS     = 0x0100,
    MF_NAMEGEN      = 0x0200,
    MF_NOAURAGEN    = 0x0400, // [KS] Separate from NoAura to tell MonsterInit that we've acquired an aura through other means.
    MF_RANKLOSS     = 0x0800
};

enum EMonsterStatFlags
{
    SF_PLAYERTARGET = 0x01,
    SF_RECREATE     = 0x02
};

// --------------------------------------------------
// Namegen
//

#define NAME_MAX_SHARED         91
#define NAME_MAX_DEMON_NAMES    107
#define NAME_MAX_BOSS_SUFFIXES  27
#define NAME_MAX_COLORS         20
#define NAME_MAX_ZOMBIE_RANK    9
#define NAME_MAX_MARINE_RANK    24
#define NAME_MAX_MALE           56
#define NAME_MAX_FEMALE         57
#define NAME_MAX_LAST           97
#define NAME_MAX_SUIT           4

// --------------------------------------------------
// Outpost
// 

#define MAX_OUTPOST_ID          201
#define MAX_OUTPOST_MUSIC       2
#define MAX_COMBAT_MUSIC        5
#define MAX_BOSS_MUSIC          5
#define MAX_CREDITS_MUSIC       3

// TODO: 0-based
enum EOutpostMenu
{
    OMENU_LEVELTRANSPORT = 1,
    OMENU_SKILLCOMPUTER,
    OMENU_MODULECONVERTER,
    OMENU_WAVESELECTOR,
    OMENU_SHOPSPECIAL,
    OMENU_BONUSSELECTOR,
    OMENU_BBS,
    OMENU_MINIGAMES,
    OMENU_STIMINJECTOR,
    OMENU_MAX
};

enum EOutpostMusicType
{
    OUTPOST_MUSIC_NORMAL,
    OUTPOST_MUSIC_COMBAT,
    OUTPOST_MUSIC_BOSS,
    OUTPOST_MUSIC_CREDITS,
    OUTPOST_MUSIC_MAX
};

// TODO: 0-based
enum EOutpostRegenType
{
    OREGEN_HEALTH = 1,
    OREGEN_ARMOR,
    OREGEN_EP,
    OREGEN_AUG,
    OREGEN_MAX
};

enum EShopSPecialType
{
    SHOPSPECIAL_MINMAX,
    SHOPSPECIAL_LEVEL,
    SHOPSPECIAL_RANK,
    SHOPSPECIAL_CREDITS,
    SHOPSPECIAL_LUCK
};

// --------------------------------------------------
// Popoffs
// 

#define DNUM_DIGITS             7
#define DNUM_MONSTER_DIV        500

enum EDamageNumberTypes
{
    DNUM_NORMAL,
    DNUM_CRITICAL,
    DNUM_HEAL,
    DNUM_SCRATCH,
    DNUM_CREDGAIN,
    DNUM_CREDLOSS,
    DNUM_EPGAIN,
    DNUM_EPLOSS,
    DNUM_SHIELDGAIN,
    DNUM_SHIELDLOSS
};

// --------------------------------------------------
// RPG
// 

#define ASAVE_SAFETIME          20 * 35
#define ASAVE_RETRYTIME         5 * 35
#define MAX_ITEMS               65535
#define MAX_TIPS                76

#define LOADOUT_WEAPONS         8
#define LOADOUT_ARMORS          10
#define LOADOUT_SHIELDPARTS     6
#define LOADOUT_SHIELDACCS      12
#define LOADOUT_DRLAWEAPONS     7
#define LOADOUT_DRLAARMORS      6
#define LOADOUT_DRLAMODPACKS    8

enum ECompatibilityMode
{
    COMPAT_NONE,
    COMPAT_EXTRAS,
    COMPAT_DRLA
};

enum EDamageTypes
{
    DT_NONE = -1,
    DT_NORMAL = 0,
    DT_TOXIC,
    DT_RADIATION,
    DT_MELEE,
    DT_FIRE,
    DT_PLASMA,
    DT_LIGHTNING,
    DT_MAX
};

enum EDebugDRLAMode
{
    DDM_NOLIMITS = 0x01,
};

// --------------------------------------------------
// Shield
// 

#define SHIELD_HEALTH           1000000
#define MAX_PARTS               22
#define MAX_BODIES              22
#define MAX_BATTERIES           13
#define MAX_CAPACITORS          15
#define MAX_ACCESSORIES         66

enum EShieldPassive
{
    SHIELD_PASS_NONE,
    SHIELD_PASS_KILLSCHARGE,
    SHIELD_PASS_AUGSLOT,
    SHIELD_PASS_HYPERION,
    SHIELD_PASS_DATAURA,
    SHIELD_PASS_AVENGER,
    SHIELD_PASS_EPICMEGACASH,
    SHIELD_PASS_SURVIVECHARGE,
    SHIELD_PASS_SKILLPLUS,
    SHIELD_PASS_NOTOXIC,
    SHIELD_PASS_FRIENDSHIPISDEFENSE,
    SHIELD_PASS_ROULETTE,
    SHIELD_PASS_DOSHMAGNET,
    SHIELD_PASS_MORESKILLS,
    SHIELD_PASS_SKILLTOSHIELD,
    SHIELD_PASS_EPOVERFLOW,
    SHIELD_PASS_BLOODYSHIELDSOREAL,
    SHIELD_PASS_HATEHATEHATE,
    SHIELD_PASS_MAX
};

// --------------------------------------------------
// Shop
// 

#define LOCKER_EPRATE           (Player.EPMax * 100 / 10000)

enum EItemAutoTypes
{
    AT_NONE,
    AT_SELL,
    AT_STORE,
    AT_MAX
};

// --------------------------------------------------
// Skills
// 

#define MAX_CATEGORIES          6
#define MAX_SKILLS              17
#define MAX_LEVELS              16
#define MAX_SUMMONS             10
#define MAX_SKILLKEYS           8

enum EAuraTypes
{
    AURA_RED,
    AURA_GREEN,
    AURA_WHITE,
    AURA_PINK,
    AURA_BLUE,
    AURA_PURPLE,
    AURA_ORANGE,
    AURA_DARKBLUE,
    AURA_YELLOW,
    AURA_MAX
};

enum ESoulTypes
{
    SOUL_RED,
    SOUL_GREEN,
    SOUL_WHITE,
    SOUL_PINK,
    SOUL_BLUE,
    SOUL_PURPLE,
    SOUL_ORANGE,
    SOUL_DARKBLUE,
    SOUL_YELLOW,
    SOUL_MAX
};

// --------------------------------------------------
// Stats
//

#define MAX_LEVEL               100
#define MAX_RANK                24
#define COMBO_MAX               (35 * 4)
#define COMBO_STOP              (35 * 2)
#define LEVELUP_ID              (MAKE_ID('L', 'V', 'U', 'P'))
#define RANKUP_ID               (MAKE_ID('R', 'K', 'U', 'P'))
#define CONFUSION_ID            (MAKE_ID('C', 'O', 'N', 'F'))
#define CONFUSION_NONSENSE_ID   (MAKE_ID('C', 'O', 'N', '2'))

#define MODULE_STAT_MULT        25
#define MODULE_SKILL_MULT       250

#define LUCK_HEALTHDROP         10
#define LUCK_EPDROP             15
#define LUCK_ARMORDROP          20
#define LUCK_WEAPONDROP         25
#define LUCK_POWERUPDROP        50
#define LUCK_STIMDROP           75
#define LUCK_MODULEDROP         100
#define LUCK_SHIELDDROP         125
#define LUCK_AUGDROP            150

#define LUCK_HEALTHCHANCE       0.025
#define LUCK_EPCHANCE           0.025
#define LUCK_ARMORCHANCE        0.025
#define LUCK_WEAPONCHANCE       0.0125
#define LUCK_POWERUPCHANCE      0.0125
#define LUCK_STIMCHANCE         0.0125
#define LUCK_MODULECHANCE       0.01
#define LUCK_SHIELDCHANCE       0.005
#define LUCK_AUGCHANCE          0.0025

#define LUCK_MAXHEALTHCHANCE    16.163076
#define LUCK_MAXEPCHANCE        14.641911
#define LUCK_MAXARMORCHANCE     13.064138
#define LUCK_MAXWEAPONCHANCE    5.712424
#define LUCK_MAXPOWERUPCHANCE   5.3415475
#define LUCK_MAXSTIMCHANCE      4.9230437
#define LUCK_MAXMODULECHANCE    3.5358825
#define LUCK_MAXSHIELDCHANCE    0.73634326
#define LUCK_MAXAUGCHANCE       1.0753031

#define LUCK_HEALTHINC          0.0025
#define LUCK_EPINC              0.0025
#define LUCK_ARMORINC           0.0025
#define LUCK_WEAPONINC          0.00125
#define LUCK_POWERUPINC         0.00125
#define LUCK_STIMINC            0.00125
#define LUCK_MODULEINC          0.001
#define LUCK_SHIELDINC          0.0005
#define LUCK_AUGINC             0.00025

#define AURA_CALCTIME           (((35 * 30) + (Player.Energy * 5.25)) * (Player.AuraBonus + 1))
#define DRLA_WEAPON_MAX         6
#define DRLA_ARMOR_MAX          2 + (Player.Capacity / 25)
#define DRLA_SKULL_MAX          DRLA_ARMOR_MAX
#define DRLA_DEVICE_MAX         4 + (Player.Capacity / 50)

enum EStatTypes
{
    STAT_STRENGTH,
    STAT_DEFENSE,
    STAT_VITALITY,
    STAT_ENERGY,
    STAT_REGENERATION,
    STAT_AGILITY,
    STAT_CAPACITY,
    STAT_LUCK,
    STAT_MAX
};

enum EStatusEffects
{
    SE_NONE = -1,
    SE_BLIND,
    SE_CONFUSION,
    SE_POISON,
    SE_CORROSION,
    SE_FATIGUE,
    SE_VIRUS,
    SE_SILENCE,
    SE_CURSE,
    SE_EMP,
    SE_RADIATION,
    SE_MAX
};

// --------------------------------------------------
// Stim
//

enum EStimCompounds
{
    STIM_STRENGTH,
    STIM_DEFENSE,
    STIM_VITALITY,
    STIM_ENERGY,
    STIM_REGENERATION,
    STIM_AGILITY,
    STIM_CAPACITY,
    STIM_LUCK,
    STIM_PURIFIER,
    STIM_POTENCY,
    STIM_INDESTRUCTIBLE,
    STIM_SHADOW,
    STIM_INFINITY,
    STIM_CHRONO,
    STIM_ADRENALINE,
    STIM_GRAVITY,
    STIM_VAMPIRE,
    STIM_RAGE,
    STIM_MAGNETIC,
    STIM_MAX
};

// --------------------------------------------------
// Turret
//

#define MAX_UPGRADES            70
#define MAX_COMMANDS            20
#define TURRET_BATTERY_CHARGE   60 * 3

enum ETurretUpgrades
{
    // Build
    TU_BUILD,

    // Weapons
    TU_WEAPON_BULLET,
    TU_WEAPON_BULLET_DAMAGE,
    TU_WEAPON_BULLET_CAPACITY,
    TU_WEAPON_BULLET_ROF,
    TU_WEAPON_PELLET,
    TU_WEAPON_PELLET_DAMAGE,
    TU_WEAPON_PELLET_CAPACITY,
    TU_WEAPON_PELLET_ROF,
    TU_WEAPON_PELLET_SPREAD,
    TU_WEAPON_PELLET_AMOUNT,
    TU_WEAPON_ROCKET,
    TU_WEAPON_ROCKET_DAMAGE,
    TU_WEAPON_ROCKET_CAPACITY,
    TU_WEAPON_ROCKET_ROF,
    TU_WEAPON_ROCKET_SEEKING,
    TU_WEAPON_PLASMA,
    TU_WEAPON_PLASMA_DAMAGE,
    TU_WEAPON_PLASMA_CAPACITY,
    TU_WEAPON_PLASMA_ROF,
    TU_WEAPON_RAILGUN,
    TU_WEAPON_RAILGUN_DAMAGE,
    TU_WEAPON_RAILGUN_CAPACITY,
    TU_WEAPON_RAILGUN_ROF,
    TU_WEAPON_RAILGUN_RIPPING,
    TU_AMMO_AUTOLOADER,
    TU_AMMO_NANOGEN,
    TU_AMMO_NANOGEN_BULLET,
    TU_AMMO_NANOGEN_SHELL,
    TU_AMMO_NANOGEN_ROCKET,
    TU_AMMO_NANOGEN_CELL,
    TU_WEAPON_SELFDESTRUCT,

    // Armor
    TU_ARMOR_PLATING,
    TU_ARMOR_PLATING_MELEE,
    TU_ARMOR_PLATING_BULLET,
    TU_ARMOR_PLATING_FIRE,
    TU_ARMOR_PLATING_PLASMA,
    TU_ARMOR_PLATING_BLAST,
    TU_ARMOR_MODULE_REFLECT,
    TU_ARMOR_MODULE_REPAIR,
    TU_ARMOR_MODULE_PHASE,

    // Assist
    TU_ASSIST_HEALTH,
    TU_ASSIST_ARMOR,
    TU_ASSIST_AUG,
    TU_ASSIST_SHIELD,
    TU_ASSIST_INJECTOR,
    TU_ASSIST_INJECTOR_TYPE,
    TU_ASSIST_INJECTOR_AMOUNT,
    TU_ASSIST_INJECTOR_POTENCY,
    TU_ASSIST_TELEPORT,
    TU_ASSIST_TEAM,

    // Sensors
    TU_SENSORS,
    TU_SENSORS_MODULEFINDER,
    TU_SENSORS_ITEMFINDER,
    TU_SENSORS_SUPPLYFINDER,

    // Battery
    TU_BATTERY_CAPACITY,
    TU_BATTERY_GENERATOR_KINETIC,
    TU_BATTERY_GENERATOR_ILLUMINATION,
    TU_BATTERY_GENERATOR_FORCE,
    TU_BATTERY_GENERATOR_THERMAL,
    TU_BATTERY_GENERATOR_PLASMA,
    TU_BATTERY_GENERATOR_NUCLEAR,

    // Hardware
    TU_HARDWARE_BATTERY,
    TU_HARDWARE_BUILD,
    TU_HARDWARE_PART,
    TU_HARDWARE_SPECS,
    TU_HARDWARE_FABRICATION,

    // Commands
    TU_COMMAND_RECALL,
    TU_COMMAND_DRAW_FIRE,
    TU_COMMAND_HOLD_POSITION,

    // Maximum
    TU_MAX
};

enum ETurretWeapon
{
    TW_NONE,
    TW_BULLET,
    TW_PELLET,
    TW_ROCKET,
    TW_PLASMA,
    TW_RAILGUN,
    TW_MAX
};

enum ETurretProjectile
{
    TP_ROCKET,
    TP_PLASMA,
    TP_MAX
};

enum ETurretSensorModes
{
    TSM_NONE,
    TSM_MODULES,
    TSM_ITEMS,
    TSM_CRATE
};

enum ETurretCommands
{
    TC_NONE,
    TC_DRAW_FIRE,
    TC_HOLD_POSITION,
    TC_MAX
};

// --------------------------------------------------
// Utils
//

#define STAT_LEVELUP_ID         (MAKE_ID('S', 'T', 'U', 'P'))
#define ERROR_ID                (MAKE_ID('E', 'R', 'O', 'R'))
#define PAY_ID                  (MAKE_ID('P', 'A', 'Y', 'O'))
#define BATTERY_ID              (MAKE_ID('B', 'A', 'T', 'T'))

enum EAmmoTypes
{
    AMMO_CLIP = 1,
    AMMO_SHELL,
    AMMO_ROCKET,
    AMMO_CELL
};

enum EImmunityCrystalTypes
{
    IC_RANDOM,
    IC_BULLET,
    IC_MELEE,
    IC_FIRE,
    IC_PLASMA,
    IC_MAX
};

enum EKeyStates
{
    KEY_PRESSED,
    KEY_ONLYPRESSED,
    KEY_UP,
    KEY_DOWN
};

enum ELogLevels
{
    LOG_NORMAL,
    LOG_DEBUG,
    LOG_WARNING,
    LOG_ERROR
};

// --------------------------------------------------
// Common Structures
//

struct DynamicArray
{
    char Name[5];
    int Position;
    int Size;
    int ItemSize;
    void *Data;
};

struct InterpData
{
    long Value;
    long OldValue;

    long StartValue;
    long DisplayValue;

    int Timer;
    int TimerMax;
    int TimerMaxCap;
};

struct Position
{
    fixed X;
    fixed Y;
    fixed Z;
    fixed Angle;
    fixed Pitch;
};

struct AuraInfo
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

struct TurretSensorItem
{
    int TID;
    int Category;
};

#endif // DOOMRPG__SCRIPTS__DEFS_H

