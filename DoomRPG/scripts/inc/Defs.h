#ifndef DOOMRPG__SCRIPTS__DEFS_H
#define DOOMRPG__SCRIPTS__DEFS_H

// We need this
#define ACS_SHORT_NAMES

#include <ACS_ZDoom.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdfix.h>

// Sanity pragmas
#pragma GDCC STRENT_LITERAL ON
#pragma GDCC FIXED_LITERAL  ON

// Aliases
#define EndHudMessage2      EndHudMessageX
#define EndHudMessage3      EndHudMessageXX
#define EndHudMessage4      EndHudMessageXXX
#define EndHudMessageBold2  EndHudMessageBoldX
#define EndHudMessageBold3  EndHudMessageBoldXX
#define EndHudMessageBold4  EndHudMessageBoldXXX

#define PrintBold(...) \
    ( \
        BeginPrintBold(), \
        __nprintf_str(__VA_ARGS__), \
        EndPrint() \
    )
#define Print(...) \
    ( \
        BeginPrint(), \
        __nprintf_str(__VA_ARGS__), \
        EndPrint() \
    )
#define StrParam(...) \
    ( \
        BeginStrParam(), \
        __nprintf_str(__VA_ARGS__), \
        EndStrParam() \
    )
#define PrintSprite(spr, id, x, y, delay) \
    ( \
        SetFont(spr), \
        HudMessage(HUDMSG_PLAIN, id, CR_UNTRANSLATED, x, y, delay, 0.0, 0.0, 0.0, "A") \
    )
#define ClearMessage(id) \
    ( \
        HudMessage(HUDMSG_PLAIN, id, CR_UNTRANSLATED, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, "") \
    )
#define Log(...) \
    ( \
        BeginLog(), \
        __nprintf_str(__VA_ARGS__), \
        EndLog() \
    )
#define PlayerName(n) \
    ( \
        BeginPrint(), \
        PrintName(n), \
        EndStrParam() \
    )

// Script declaration stuff
#define FarPtr      __far
#define ScriptLocal __loc
#define StringTable __str_ars

#define AddressSpace        __addrdef
#define MapArraySpace       __map_arr
#define WorldArraySpace     __wld_arr
#define GlobalArraySpace    __gbl_arr

#define AutoRegister    __loc_reg
#define MapRegister     __map_reg
#define WorldRegister   __wld_reg
#define GlobalRegister  __gbl_reg

#define AutoArray       __loc_ars
#define MapArray        __map_ars
#define WorldArray      __wld_ars
#define GlobalArray     __gbl_ars

#define Address(N)      [[address(N)]]

#define OptionalArgs(N) [[optional_args(N)]]

#define DECORATE        [[extern("ACS")]]
#define MapSpecial      [[extern("ACS")]]
#define Console         [[extern("ACS")]]
#define KeyBind         [[extern("ACS"), script("Net")]]

#define NumberedScript(N)       [[call("ScriptI"), address(N)]]
#define NamedScript             [[call("ScriptS")]]
#define NumberedScriptSync(N)   [[call("SScriptI"), address(N)]]
#define NamedScriptSync         [[call("SScriptS")]]

#define Type_OPEN       [[script("Open")]]
#define Type_UNLOADING  [[script("Unloading")]]
#define Type_LIGHTNING  [[script("Lightning")]]

#define Type_ENTER      [[script("Enter")]]
#define Type_RETURN     [[script("Return")]]
#define Type_RESPAWN    [[script("Respawn")]]
#define Type_DEATH      [[script("Death")]]
#define Type_DISCONNECT [[script("Disconnect")]]

#define Flag_Puke       [[script("Net")]]
#define Flag_ClientSide [[script("Clientside")]]

// Macro functions
#define MAKE_ID(a, b, c, d) ((int)((a) | ((b) << 8) | ((c) << 16) | ((d) << 24)))

// Aliases
#define CallACS(script)         ACS_NamedExecuteWithResult((script))
#define Arbitrator              (PlayerNumber() == 0)
#define InMultiplayer           (GameType() == GAME_NET_COOPERATIVE)
#define InTitle                 (GameType() == GAME_TITLE_MAP)
#define GetMonsterID(N)         GetActorProperty((N), APROP_Score)
#define SetMonsterID(N, O)      SetActorProperty((N), APROP_Score, (O))
#define Clamp(Low, N, High)     (N < Low ? Low : N > High ? High : N)
#define GetActivatorCVar(i)     GetUserCVar(PlayerNumber(), (i))
#define SetActivatorCVar(i, j)  SetUserCVar(PlayerNumber(), (i), (j))
#define GetActivatorCVarFixed(i)    GetUserCVarFixed(PlayerNumber(), (i))
#define SetActivatorCVarFixed(i, j) SetUserCVarFixed(PlayerNumber(), (i), (j))
#define GetActivatorCVarString(i)       GetUserCVarString(PlayerNumber(), (i))
#define SetActivatorCVarString(i, j)    SetUserCVarString(PlayerNumber(), (i), (j))

// Constants
#define MAX_PLAYERS             8
#define PLAYER_TID              31337
#define PI                      3.14159265359

// Struct Aliases
#define Players(N)              _PlayerData[(N)]
#define Player                  _PlayerData[PlayerNumber()]
#define Skills                  SkillData // Temporary until I'm not lazy

// Type definitions
typedef __str str;

// --------------------------------------------------
// Arena
//

#define ARENA_HOLDTIME (35)

typedef enum
{
    ARENA_INTERMISSION,
    ARENA_WAITING,
    ARENA_READY,
    ARENA_ACTIVE,
} EArenaStates;

typedef enum
{
    AMOD_NONE,
    AMOD_NOREGEN,
    AMOD_MAX,
} EArenaModTypes;

typedef enum
{
    AEVENT_RANDOM = -1,
    AEVENT_NONE = 0,
    AEVENT_BLACKOUT,
    AEVENT_FOGGY,
    AEVENT_LAVA,
    AEVENT_GRAYSCALE,
    AEVENT_MAX,
} EArenaEventTypes;

typedef enum
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
} EArenaBonusTypes;

typedef enum
{
    AKTIMER_STOP,
    AKTIMER_CONTINUE,
} EArenaKeyTimerTypes;

// --------------------------------------------------
// Augmentations
//

#define MAX_AUG_LEVEL (9)

typedef enum
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
} EAugTypes;

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

#define CRATE_MAX       256
#define CRATE_MAX_ITEMS 54
#define MAX_DRLA_SETS   18
#define MAX_NODES       32

typedef enum
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
} ENodeTypes;

// --------------------------------------------------
// GUI
//

#define MAX_WINDOWS     16
#define MAX_CONTROLS    64
#define MAX_LIST        256
#define MAX_OPTIONS     16

#define WINDOW_MAIN     0
#define WINDOW_STATS    1
#define WINDOW_AUGS     2
#define WINDOW_SKILLS   3

// Label Alignments
typedef enum
{
    LA_CENTER,
    LA_LEFT,
    LA_RIGHT,
    LA_CENTERTOP,
    LA_LEFTTOP,
    LA_RIGHTTOP
} ELabelAlignment;

// Tooltip Types
typedef enum
{
    TT_BASIC,
    TT_TITLE,
    TT_COMPLEX
} ETooltipType;

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

typedef enum
{
    CF_NONE     = 0x0,
    CF_NOSELL   = 0x1,
    CF_NOBUY    = 0x2,
    CF_NOSTORE  = 0x4,
    CF_NODROP   = 0x8,
} ECategoryFlags;

// --------------------------------------------------
// Map
//

#define NUKE_ID                 (MAKE_ID('N', 'U', 'K', 'E'))
#define MAX_NUKE_KEYS           9

#define MAP_EXIT_SCRIPTNUM      30000

typedef enum
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
} EMapEvents;

typedef enum
{
    UACEVENT_NONE,

    UACEVENT_INVASION,
    UACEVENT_LOWPOWER,

    UACEVENT_MAX
} EUACOutpostEvents;

// --------------------------------------------------
// Menu
//

#define MAX_MENU                7
#define TURRET_PAGE_MAX         36
#define MENU_ID                 (MAKE_ID('M', 'E', 'N', 'U'))
#define TOXMETER_ID             (MAKE_ID('T', 'O', 'X', 'I'))

typedef enum
{
    MENUPAGE_MAIN,
    MENUPAGE_STATS,
    MENUPAGE_AUGS,
    MENUPAGE_SKILLS,
    MENUPAGE_SHIELD,
    MENUPAGE_STIMS,
    MENUPAGE_TURRET,
    MENUPAGE_MAX
} EMenuPages;

typedef enum
{
    STATPAGE_STATS,
    STATPAGE_STATXP,
    STATPAGE_PERKS,
    STATPAGE_TEAM,
    STATPAGE_MAX
} EStatPages;

typedef enum
{
    SHIELDPAGE_BODY,
    SHIELDPAGE_BATTERY,
    SHIELDPAGE_CAPACITOR,
    SHIELDPAGE_ACCESSORY,
    SHIELDPAGE_MAX
} EShieldPages;

typedef enum
{
    TURRETPAGE_COMMAND,
    TURRETPAGE_UPGRADE,
    TURRETPAGE_MAX
} ETurretPages;

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

typedef enum
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
} EMissionTypes;

// --------------------------------------------------
// Monsters
//
#define MAX_MONSTERS            16384
#define MAX_DEF_MONSTERS        17
#define MAX_DEF_MONSTERS_DRLA   71
#define MAX_TEMP_MONSTERS       100
#define MAX_MEGABOSSES          2

typedef enum
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
} EMonsterFlags;

typedef enum
{
    SF_PLAYERTARGET = 0x01,
    SF_RECREATE     = 0x02
} EMonsterStatFlags;

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
typedef enum
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
} EOutpostMenu;

typedef enum
{
    OUTPOST_MUSIC_NORMAL,
    OUTPOST_MUSIC_COMBAT,
    OUTPOST_MUSIC_BOSS,
    OUTPOST_MUSIC_CREDITS,
    OUTPOST_MUSIC_MAX
} EOutpostMusicType;

// TODO: 0-based
typedef enum
{
    OREGEN_HEALTH = 1,
    OREGEN_ARMOR,
    OREGEN_EP,
    OREGEN_AUG,
    OREGEN_MAX
} EOutpostRegenType;

typedef enum
{
    SHOPSPECIAL_MINMAX,
    SHOPSPECIAL_LEVEL,
    SHOPSPECIAL_RANK,
    SHOPSPECIAL_CREDITS,
    SHOPSPECIAL_LUCK
} EShopSpecialType;

// --------------------------------------------------
// Popoffs
// 

#define DNUM_DIGITS             7
#define DNUM_MONSTER_DIV        500

typedef enum
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
} EDamageNumberTypes;

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

typedef enum
{
    COMPAT_NONE,
    COMPAT_EXTRAS,
    COMPAT_DRLA
} ECompatibilityMode;

typedef enum
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
} EDamageTypes;

typedef enum
{
    DDM_NOLIMITS = 0x01,
} EDebugDRLAMode;

// --------------------------------------------------
// Shield
// 

#define SHIELD_HEALTH           1000000
#define MAX_PARTS               22
#define MAX_BODIES              22
#define MAX_BATTERIES           13
#define MAX_CAPACITORS          15
#define MAX_ACCESSORIES         66

typedef enum
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
} EShieldPassive;

// --------------------------------------------------
// Shop
// 

#define LOCKER_EPRATE           (Player.EPMax * 100 / 10000)

typedef enum
{
    AT_NONE,
    AT_SELL,
    AT_STORE,
    AT_MAX
} EItemAutoTypes;

// --------------------------------------------------
// Skills
// 

#define MAX_CATEGORIES          6
#define MAX_SKILLS              17
#define MAX_LEVELS              16
#define MAX_SUMMONS             10
#define MAX_SKILLKEYS           8

typedef enum
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
} EAuraTypes;

typedef enum
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
} ESoulTypes;

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

typedef enum
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
} EStatTypes;

typedef enum
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
} EStatusEffects;

// --------------------------------------------------
// Stim
//

typedef enum
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
} EStimCompounds;

// --------------------------------------------------
// Turret
//

#define MAX_UPGRADES            70
#define MAX_COMMANDS            20
#define TURRET_BATTERY_CHARGE   60 * 3

typedef enum
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
} ETurretUpgrades;

typedef enum
{
    TW_NONE,
    TW_BULLET,
    TW_PELLET,
    TW_ROCKET,
    TW_PLASMA,
    TW_RAILGUN,
    TW_MAX
} ETurretWeapon;

typedef enum
{
    TP_ROCKET,
    TP_PLASMA,
    TP_MAX
} ETurretProjectile;

typedef enum
{
    TSM_NONE,
    TSM_MODULES,
    TSM_ITEMS,
    TSM_CRATE
} ETurretSensorModes;

typedef enum
{
    TC_NONE,
    TC_DRAW_FIRE,
    TC_HOLD_POSITION,
    TC_MAX
} ETurretCommands;

// --------------------------------------------------
// Utils
//

#define STAT_LEVELUP_ID         (MAKE_ID('S', 'T', 'U', 'P'))
#define ERROR_ID                (MAKE_ID('E', 'R', 'O', 'R'))
#define PAY_ID                  (MAKE_ID('P', 'A', 'Y', 'O'))
#define BATTERY_ID              (MAKE_ID('B', 'A', 'T', 'T'))

typedef enum
{
    AMMO_CLIP = 1,
    AMMO_SHELL,
    AMMO_ROCKET,
    AMMO_CELL
} EAmmoTypes;

typedef enum
{
    IC_RANDOM,
    IC_BULLET,
    IC_MELEE,
    IC_FIRE,
    IC_PLASMA,
    IC_MAX
} EImmunityCrystalTypes;

typedef enum
{
    KEY_PRESSED,
    KEY_ONLYPRESSED,
    KEY_UP,
    KEY_DOWN
} EKeyStates;

typedef enum
{
    LOG_NORMAL,
    LOG_DEBUG,
    LOG_WARNING,
    LOG_ERROR
} ELogLevels;

// --------------------------------------------------
// Address Spaces
//

AddressSpace extern MapArraySpace       RPGMap;
AddressSpace extern WorldArraySpace     RPGWorld;
AddressSpace extern GlobalArraySpace    RPGGlobal;

// --------------------------------------------------
// Common Structures
//

// Generic

typedef struct
{
    str Name;
    int Position;
    int Size;
    int ItemSize;
    void *Data;
} DynamicArray;

typedef struct
{
    long Value;
    long OldValue;

    long StartValue;
    long DisplayValue;

    int Timer;
    int TimerMax;
    int TimerMaxCap;
} InterpData;

typedef struct
{
    fixed X;
    fixed Y;
    fixed Z;
    fixed Angle;
    fixed Pitch;
} Position;

// Used by DropEntireInventory()
typedef struct
{
    str Actor;
    bool NoDrop;
    bool TakeAll;
    int Max;
} DroppedItem;

// Augmentations

typedef struct
{
    str Name;
    int MaxLevel;
    str Description[MAX_AUG_LEVEL];
    str TokenActor;
} AugInfo;

typedef AugInfo RPGMap *AugInfoPtr;

// Charsave

typedef struct
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
} CharSaveInfo;

// GUI

struct MouseInfo
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
extern struct _guiwindow;
extern struct _guilabel;
extern struct _guiicon;
extern struct _guibutton;
extern struct _guibar;
extern struct _guilist;
extern struct _guitooltip;
extern struct _guicontextmenu;

// GUI Event Function Pointers
typedef void (*LabelEventFunc)(struct _guilabel *);
typedef void (*IconEventFunc)(struct _guiicon *);
typedef void (*ButtonEventFunc)(struct _guibutton *);
typedef void (*BarEventFunc)(struct _guibar *);
typedef void (*ListEventFunc)(struct _guilist *);
typedef void (*ContextMenuEventFunc)(int);

typedef struct _guiwindow
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
    struct _guilabel    * Labels[MAX_CONTROLS];
    struct _guiicon     * Icons[MAX_CONTROLS];
    struct _guibutton   * Buttons[MAX_CONTROLS];
    struct _guibar      * Bars[MAX_CONTROLS];
    struct _guilist     * Lists[MAX_CONTROLS];
} GUIWindow;

typedef struct _guilabel
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
    
    struct _guiwindow *Window;
    struct _guitooltip *Tooltip;
    struct _guicontextmenu *ContextMenu;
} GUILabel;

typedef struct _guiicon
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
    
    struct _guiwindow *Window;
    struct _guitooltip *Tooltip;
    struct _guicontextmenu *ContextMenu;
    
    IconEventFunc OnClick;
} GUIIcon;

typedef struct _guibutton
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
    
    struct _guiwindow *Window;
    struct _guitooltip *Tooltip;
    struct _guicontextmenu *ContextMenu;
    
    ButtonEventFunc OnClick;
} GUIButton;

typedef struct _guibar
{
    int X;
    int Y;
    int Width;
    int Height;
    int Value;
    int ValueMax;
    str Texture;
    bool Visible;
    
    struct _guiwindow *Window;
    struct _guitooltip *Tooltip;
    struct _guicontextmenu *ContextMenu;
} GUIBar;

typedef struct _guilist
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
    
    struct _guiwindow *Window;
    struct _guitooltip *Tooltip;
    struct _guicontextmenu *ContextMenu;
    
    ListEventFunc OnClick;
} GUIList;

typedef struct _guitooltip
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
} GUITooltip;

typedef struct _guicontextmenu
{
    int X;
    int Y;
    
    str Name[MAX_OPTIONS];
    ContextMenuEventFunc OnClick[MAX_OPTIONS];
    
    int Data;
} GUIContextMenu;

// Items

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

typedef ItemInfo RPGGlobal *ItemInfoPtr;

// Crates

typedef struct
{
    bool Active;
    int Type;
    int Start;
    int End;
} HackNode;

typedef struct
{
    bool Generated;
    bool SupplyDrop;
    bool Firewall;
    bool Empty;
    int TID;
    int Amount;
    int Rarity;
    
    bool Active[CRATE_MAX_ITEMS];
    ItemInfoPtr Item[CRATE_MAX_ITEMS];
    
    // Hacking Minigame
    bool HacksGenerated;
    int Hacking;
    int HackingCooldown;
    
    int Tries;
    
    int NodeMax[NODE_MAX];
    
    HackNode Nodes[MAX_NODES];
    int GenTotal;
    int GenType;
    int GenNodes[NODE_MAX];
} CrateInfo;

// Skills

typedef struct
{
    int CurrentLevel;
    int Level;
} SkillLevelInfo;

typedef bool (*SkillUseScript NamedScript Console)(SkillLevelInfo *, void *);

typedef struct
{
    str Name;
    int Cost;
    int MaxLevel;
    SkillUseScript Use;
    str Description[MAX_LEVELS];
    str Icon;
} Skill;

typedef struct
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
} AuraInfo;

// Shield

typedef struct
{
    str Actor;
    str Name;
    str Icon;
    
    int Capacity;
    int ChargeRate;
    fixed DelayRate;
} ShieldPart;

typedef void (*ShieldAccModScript NamedScript)();
typedef void (*ShieldAccEquipScript NamedScript)();
typedef void (*ShieldAccUnequipScript NamedScript)(bool);
typedef void (*ShieldAccDamageScript NamedScript)(int);
typedef void (*ShieldAccBreakScript NamedScript)();
typedef int  (*ShieldAccChargeScript NamedScript)(int);
typedef void (*ShieldAccOverchargeScript NamedScript)(int);
typedef bool (*ShieldAccFastChargeScript NamedScript)();
typedef void (*ShieldAccFullChargeScript NamedScript)();

typedef struct
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
} ShieldAccessory;

typedef ShieldPart const *ShieldPartPtr;
typedef ShieldAccessory const *ShieldAccsPtr;

// Monsters

typedef struct
{
    // Basic
    int TID;
    str Actor;
    str ReplaceActor;
    Position position;
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
    AuraInfo Aura;
} MonsterStats;

typedef struct
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
} MonsterInfo;

typedef struct
{
    str Actor;
    str Music;
} MegabossInfo;

typedef MonsterInfo const *MonsterInfoPtr;
typedef MegabossInfo const *MegabossInfoPtr;

typedef MonsterStats RPGMap *MonsterStatsPtr;

// Missions

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
    ItemInfo *RewardItem;
    
    // Mission Data
    ItemInfo *Item;
    MonsterInfo const *Monster;
    int Current;
    int Amount;
} MissionInfo;

// Turret

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
    int Category;
} TurretSensorItem;

// RPG

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
        ShieldPart *Body;
        ShieldPart *Battery;
        ShieldPart *Capacitor;
        ShieldAccessory *Accessory;
        
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

#endif // DOOMRPG__SCRIPTS__DEFS_H

