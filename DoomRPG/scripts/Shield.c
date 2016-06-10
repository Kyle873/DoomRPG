#include "RPG.h"

#include "Arena.h"
#include "Augs.h"
#include "Map.h"
#include "Menu.h"
#include "Popoffs.h"
#include "Shield.h"
#include "Shop.h"
#include "Stats.h"
#include "Utils.h"

int const ShieldPartsMax[3] =
{
    MAX_BODIES,
    MAX_BATTERIES,
    MAX_CAPACITORS
};

ShieldPart const ShieldParts[3][MAX_PARTS] =
{
    // Actor, Name, Icon, Description, Capacity, Charge Rate, Delay Rate

    /*  Shield Part Color Revamp by Yhollikins
        
        Basically, because each part kinda has a thing it tries to do the most, it'll default to that unless other stuff happens.
        I'm not sure that sentence made much sense. Whatever I DONT CAAAAARrrrreeee
        ~ how2english with Yholl
        
        Light Blue	\Cv		Increased Capacity
        Blue		\Ch		Decreased Capacity
        Green		\Cd		Increased Charge
        Dark Green	\Cq		Decreased Charge
        Dark Red	\Cr		Increased Delay
        Red			\Cg		Decreased Delay
        
    */

    // Bodies
    {
        { "DRPGShieldBody1",        "\CvUAC",               "SHBOA0", 25,   0,   0    },
        { "DRPGShieldBody2",        "\CvXTron",             "SHBOB0", 50,   0,   0    },
        { "DRPGShieldBody3",        "\CrBlack Mesa",        "SHBOC0", 150,  0,   2    },
        { "DRPGShieldBody4",        "\CvEDF",               "SHBOD0", 100,  0,   0    },
        { "DRPGShieldBody5",        "\CdCyberdyne Systems", "SHBOE0", 80,   2,   0    },
        { "DRPGShieldBody6",        "\CvMisfit Tech",       "SHBOF0", 150,  0,   0    },
        { "DRPGShieldBody7",        "\CqShadaloo",          "SHBOG0", 400,  -1,  4    },
        { "DRPGShieldBody8",        "\CvArkai",             "SHBOH0", 250,  0,   0    },
        { "DRPGShieldBody9",        "\CgIronclad Inc.",     "SHBOI0", 150,  0,   -2   },
        { "DRPGShieldBody10",       "\CdYholl",             "SHBOJ0", 50,   5,   -3   },
        { "DRPGShieldBody11",       "\CdHyperix",           "SHBOK0", 200,  1,   -1   },
        { "DRPGShieldBody12",       "\CrXaser Inc.",        "SHBOL0", 500,  0,   2.5  },
        { "DRPGShieldBody13",       "\CddataDyne",          "SHBOM0", 250,  3,   -1   },
        { "DRPGShieldBody14",       "\CdStarbright",        "SHBON0", 400,  2,   -1   },
        { "DRPGShieldBody15",       "\CqHellsing",          "SHBOO0", 666,  -1,  0    },
        { "DRPGShieldBody16",       "\CvS.H.I.E.L.D.",      "SHBOP0", 500,  0,   0    },
        { "DRPGShieldBody17",       "\CgUAC Elite",         "SHBOQ0", 400,  1,   -3   },
        { "DRPGShieldBody18",       "\CdStark Industries",  "SHBOR0", 550,  1,   -1   },
        { "DRPGShieldBody19",       "\CdWeyland-Yutani",    "SHBOS0", 100,  7,   0    },
        { "DRPGShieldBody20",       "\CrMegalith",          "SHBOT0", 750,  0,   5    },
        { "DRPGShieldBody21",       "\CgReaper Industries", "SHBOU0", 444,  4,   -4   },
        { "DRPGShieldBody22",       "\CrEternity Systems",  "SHBOV0", 2000, 0,   15   }
    },

    // Batteries
    {
        { "DRPGShieldBattery1",     "\CvCrappy",           "SHBAA0", 25,   0,   0     },
        { "DRPGShieldBattery2",     "\CdBullet",           "SHBAB0", 50,   1,   0     },
        { "DRPGShieldBattery3",     "\CgElegant",          "SHBAC0", 20,   0,   -3    },
        { "DRPGShieldBattery4",     "\CdSpiked",           "SHBAD0", 100,  1,   0     },
        { "DRPGShieldBattery5",     "\CvStubborn",         "SHBAE0", 250,  0,   0     },
        { "DRPGShieldBattery6",     "\CdMirrored",         "SHBAF0", 150,  2,   0     },
        { "DRPGShieldBattery7",     "\CdRefined",          "SHBAG0", 100,  2,   -1    },
        { "DRPGShieldBattery8",     "\CdClustered",        "SHBAH0", 200,  3,   0     },
        { "DRPGShieldBattery9",     "\CdWinged",           "SHBAI0", 250,  4,   0     },
        { "DRPGShieldBattery10",    "\CdOvercharged",      "SHBAJ0", 10,   5,   -2    },
        { "DRPGShieldBattery11",    "\CvSuperb",           "SHBAK0", 425,  1,   0     },
        { "DRPGShieldBattery12",    "\CrRedundant",        "SHBAL0", 50,   30,  15    },
        { "DRPGShieldBattery13",    "\CvReinforced",       "SHBAM0", 1000, 2,   2.5   }
    },

    // Capacitors
    {
        { "DRPGShieldCapacitor1",   "\CdStandard",         "SHCAA0", 0,     1,   0    },
        { "DRPGShieldCapacitor2",   "\CdOutdated",         "SHCAB0", 0,     3,   2    },
        { "DRPGShieldCapacitor3",   "\CdCooled",           "SHCAC0", 0,     2,   0    },
        { "DRPGShieldCapacitor4",   "\CvWarm",             "SHCAD0", 25,    1,   0    },
        { "DRPGShieldCapacitor5",   "\CrInefficient",      "SHCAE0", 0,     6,   5    },
        { "DRPGShieldCapacitor6",   "\CdEnergized",        "SHCAF0", 0,     3,   0    },
        { "DRPGShieldCapacitor7",   "\CdInfused",          "SHCAG0", 0,     4,   0    },
        { "DRPGShieldCapacitor8",   "\CvPlasmatic",        "SHCAH0", 100,   3,   0    },
        { "DRPGShieldCapacitor9",   "\CdBurning",          "SHCAI0", 0,     5,   0    },
        { "DRPGShieldCapacitor10",  "\CgPulsating",        "SHCAJ0", 0,     1,   -5   },
        { "DRPGShieldCapacitor11",  "\CdFiery",            "SHCAK0", 0,     5,   -1   },
        { "DRPGShieldCapacitor12",  "\CvEternal",          "SHCAL0", 500,   1,   3    },
        { "DRPGShieldCapacitor13",  "\CdOverloaded",       "SHCAM0", 0,     10,  1    },
        { "DRPGShieldCapacitor14",  "\CrDark",             "SHCAN0", 1000,  -1,  15   },
        { "DRPGShieldCapacitor15",  "\CgChaotic",          "SHCAO0", 0,     7,   -7   }
    }
};

ShieldAccessory const ShieldAccessories[MAX_ACCESSORIES] =
{
    /*
        [KS] For regular shield modifiers, the same convention applies as standard shield parts.
        For stat-based or mechanic-based shields, they're colored by their stats, as below
        
        Red         \Cg     Strength / Damaging Accessories
        Pink        \Ca     Vitality / Health Accessories
        Orange      \Ci     Agility / Speed Accessories
        Green       \Cd     Defense / Armor Accessories
        Gold        \Cf     Luck / Money / Converter Accessories
        Blue        \Cn     Energy and EP Accessories
        Purple      \Ct     Regeneration Accessories (None currently)
        Dark Blue   \Ch     Capacity and Ammo-related Accessories
        Yellow      \Ck     Rank-related Accessories
        Grey        \Cc     Augmentation-related Accessories
        Dark Green  \Cq     Powerup-related Accessories
        White       \Cj     Miscellaneous / Multi-Category Accessories
        
        White       \Cj     Bullet
        Grey        \Cc     Melee
        Red         \Cg     Fire
        Blue        \Cn     Plasma
        
        Sorry, there is no color for Propane and Propane Accessories
    */
    
    {
        "DRPGShieldAccessory1",
        "\CgX-7",       "SHACA0",   18000,
        "\Cg2x Melee Damage",
        SHIELD_PASS_NONE,
        X7Mod, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory2",
        "\CaSGENX-5b",  "SHACB0",   25000,
        "\CfConverter\C-: When full, restores \CgHealth\C-",
        SHIELD_PASS_NONE,
        NULL, NULL, NULL, NULL, NULL, NULL, HealthConversion, NULL, NULL,
    },
    {
        "DRPGShieldAccessory3",
        "\CgAMP-3000",  "SHACC0",   40000,
        "\Cg2x Damage\C- when full\nHalves \CvCapacity\C- on attack",
        SHIELD_PASS_NONE,
        AmpShieldMod, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory4",
        "\CgHRY-VP80",  "SHACD0",   20000,
        "\Cv-50% Capacity\n\Ca-50% Delay",
        SHIELD_PASS_NONE,
        HurryMod, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory5",
        "\CvDEF-2",     "SHACE0",   20000,
        "\Cv2x Capacity\n\Ca2x Delay",
        SHIELD_PASS_NONE,
        Def2Mod, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory6",
        "\CdB1-ZUT3",   "SHACF0",   20000,
        "\Cd2x Charge Rate\n\Cv-50% Capacity",
        SHIELD_PASS_NONE,
        BlzutMod, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory7",
        "\ChCNV-RT99",  "SHACG0",   12000,
        "Instead of fast charging with \CnEP\C-, uses 1 \CdCell\C- per 10 \CvCapacity",
        SHIELD_PASS_NONE,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, CellFastCharge, NULL,
    },
    {
        "DRPGShieldAccessory8",
        "\CfREK-T50",   "SHACH0",   15000,
        "\Cd-100% Damage Reduction\C-\nTriples monster killing \Cfpayout bonus",
        SHIELD_PASS_EPICMEGACASH,
        RektMod, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory9",
        "\CiUW-0t",     "SHACI0",   50000,
        "When your \Cisurvival bonus\C- goes off, your \CvShield\C- reactivates and is \Cdfully recharged",
        SHIELD_PASS_SURVIVECHARGE,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory10",
        "\CqCU-256",    "SHACJ0",   12000,
        "When full, gives \CqLight Amplification\C- power",
        SHIELD_PASS_NONE,
        LightAmpMod, NULL, LightAmpUnequip, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory11",
        "\CaTX-BGONN",  "SHACK0",   15000,
        "When full, immune to \CdToxicity",
        SHIELD_PASS_NOTOXIC,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory12",
        "\CqWRP30-LITE","SHACL0",   12000,
        "When full, gives \CqInvisibility\C- power",
        SHIELD_PASS_NONE,
        InvisibilityMod, NULL, InvisibilityUnequip, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory13",
        "\CgNOV-A2",    "SHACM0",   45000,
        "1 in 4 chance of emitting \CnBFG Balls\C- when \CvShield\C- is depleted",
        SHIELD_PASS_NONE,
        NULL, NULL, NULL, NULL, NovaShieldBreak, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory14",
        "\CdLZ-Y200",   "SHACN0",   20000,
        "\Cd2x Charge Rate\n\CgOnly charges while standing still",
        SHIELD_PASS_NONE,
        LazyMod, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory15",
        "\CvBST-700",   "SHACO0",   25000,
        "Randomly drops \CvShield Boosters\C- when hit",
        SHIELD_PASS_NONE,
        NULL, NULL, NULL, BoosterShieldDamage, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory16",
        "\CnPH-D88",    "SHACP0",   75000,
        "\CfConverter\C-: When full, recharges \CnEP\C-",
        SHIELD_PASS_NONE,
        NULL, NULL, NULL, NULL, NULL, NULL, EPConversion, NULL, NULL,
    },
    {
        "DRPGShieldAccessory17",
        "\CcBATT-B",    "SHACQ0",   120000,
        "\CfConverter\C-: When full, recharges \CkAugmentation Battery\C-",
        SHIELD_PASS_NONE,
        NULL, NULL, NULL, NULL, NULL, NULL, BatteryConversion, NULL, NULL,
    },
    {
        "DRPGShieldAccessory18",
        "\ChSHVR-Z7",   "SHACR0",   35000,
        "\CfConverter\C-: When full, produces \CcClips\C- and \CiShells\C-",
        SHIELD_PASS_NONE,
        NULL, NULL, NULL, NULL, NULL, NULL, AmmoConversion, NULL, NULL,
    },
    {
        "DRPGShieldAccessory19",
        "\CdMM-12",     "SHACS0",   28000,
        "\CdCharge Rate\C- scales based on current \CvShield Charge\C-\nThe higher, the faster",
        SHIELD_PASS_NONE,
        AccelerativeShieldMod, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory20",
        "\CgMRTE-KRAR", "SHACT0",   38000,
        "\Cv-50% Capacity\n\Cg1.5x Damage",
        SHIELD_PASS_NONE,
        TheKillingBoosterMod, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory21",
        "\CqSP-00k",    "SHACU0",   30000,
        "1 in 8 chance of getting \CqGhosted\C- when hit",
        SHIELD_PASS_NONE,
        NULL, NULL, NULL, SpookyDamage, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory22",
        "\CjRR-G0",     "SHACV0",   70000,
        "Scales your \CdCharge Rate\C- up and \CaDelay\C- down based on how long you've been in a level",
        SHIELD_PASS_NONE,
        MinuteMaidMod, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory23",
        "\CqE1N-T31",   "SHACW0",   90000,
        "1 second \CqTime Freeze\C- when hit",
        SHIELD_PASS_NONE,
        NULL, NULL, NULL, TimeyWimeyHurtyBall, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory24",
        "\CkPATR-0T",   "SHACX0",   45000,
        "Scales your \CvCapacity\C- based off your \CkRank",
        SHIELD_PASS_NONE,
        AmericaShieldMod, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory25",
        "\CfRNJSUS-2",  "SHACY0",   45000,
        "Scales off of your \CfLuck\C- inversely\nWith 100+ \CfLuck\C-, it has no effect\nwith 0 \CfLuck\C-, it's equivalent to having 50 \CfLuck",
        SHIELD_PASS_NONE,
        GhettoLuckMod, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory26",
        "\CnPWAA-9001", "SHACZ0",   80000,
        "Uses the \Cdnext level up\C- of your current \CnSkill\C- for the cost of the current",
        SHIELD_PASS_SKILLPLUS,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory27",
        "\CcAW-G01",    "SHA2A0",   80000,
        "Acts as an \CkAugmentation Slot Upgrade",
        SHIELD_PASS_AUGSLOT,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory28",
        "\CjSCL-AR53",  "SHA2B0",   200000,
        "Uses your stats as a percentage to modify \CvShield\C- stats\n\ChCapacity\C- for \CvCapacity\n\CnEnergy\C- for \CdCharge Rate\n\CtRegeneration\C- for reducing \CaDelay",
        SHIELD_PASS_NONE,
        SuperSqueezyScalarMod, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory29",
        "\CqRF-CT",     "SHA2C0",   125000,
        "\CqReflects\C- when hit",
        SHIELD_PASS_NONE,
        ReflectionMod, NULL, ReflectionUnequip, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory30",
        "\CdTEW-11",     "SHA2D0",  22000,
        "When your \CvShield\C- reaches \Cdfull charge\C-, it \Cnmemorizes\C- where you last were\nWhen your \CvShield\C- is \Cgdepleted\C-, it \Cdteleports\C- you to that location",
        SHIELD_PASS_NONE,
        NULL, NULL, NULL, NULL, TeleportBreak, NULL, NULL, NULL, TeleportFullCharge,
    },
    {
        "DRPGShieldAccessory31",
        "\CdNU-YU5",     "SHA2E0",  39000,
        "If you are killed with your \CvShield\C- active, you respawn with it full and \Cd90% Damage Reduction\C- for 6 seconds",
        SHIELD_PASS_HYPERION,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory32",
        "\CdADPT-V15",   "SHA2F0",  45000,
        "When your \CvShield\C- is \Cgdepleted\C-, it gives you \Cd50% Resistance\C- for 15 seconds against the damage type that finished it off",
        SHIELD_PASS_NONE,
        NULL, NULL, NULL, NULL, AdaptiveBreak, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory33",
        "\CdTENS-H11",   "SHA2G0",  55000,
        "The lower your shield is, the higher your \CdDamage Reduction\C- is\nIt scales up to \Cd75%\C- at \Cv1 Capacity\C-\nWhen \Cgfully depleted\C-, \Cd0% Damage Reduction",
        SHIELD_PASS_NONE,
        ScarletWeatherRhapsodyShieldMod, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory34",
        "\CdTEEM-AU5",   "SHA2H0",  50000,
        "While under the effects of an aura, each other person affected by that aura gains \Cd+20% Damage Reduction\C-\n\CuThis does not stack with multiple auras",
        SHIELD_PASS_DATAURA,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory35",
        "\CgVENG-R",     "SHA2I0",  62000,
        "When an ally is killed, you gain \Cg1.5x Damage\C- and \Cd+50% Damage Reduction\C- for 30 seconds",
        SHIELD_PASS_AVENGER,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory36",
        "\CiSANIC-S88",  "SHA2J0",  88000,
        "The faster you move, the faster your \CvShield\C- charges",
        SHIELD_PASS_NONE,
        SanicMod, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory37",
        "\CdNAKD-N0W",   "SHA2K0",  20000,
        "While you \Caaren't wearing armor\C-, you have \Cd+25% Damage Reduction\C-",
        SHIELD_PASS_NONE,
        NakedMod, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory38",
        "\CgHA3-L1N",   "SHA2L0",   65000,
        "Whenever you \Cgkill an enemy\C-, your shield recharges \Ct5x\C- as fast for 3 seconds",
        SHIELD_PASS_BLOODYSHIELDSOREAL,
        BloodyShieldSoRealMod, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory39",
        "\CqHAET-60",   "SHA2M0",   120000,
        "When you use a \CgBerserk Pack\C-, you gain \Cd99% Resistance\C- to \CcMelee Damage\C- for 60 seconds",
        SHIELD_PASS_HATEHATEHATE,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory40",
        "\CdPHA-LX2",   "SHA2N0",   33000,
        "You gain an additional \Cd+10% Damage Reduction\C- for every player using this accessory",
        SHIELD_PASS_FRIENDSHIPISDEFENSE,
        FriendshipShieldMod, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory41",
        "\CgIKU-N7",    "SHA2O0",   38000,
        "Whenever you \Catake damage\C-, you release a \Cnsmall electrical blast\C- that stuns enemies\nIf your \CvShield\C- is \Cgdepleted\C-, it releases a \Cnlarge blast\C-",
        SHIELD_PASS_NONE,
        NULL, NULL, NULL, StaticChargeShieldDamage, StaticChargeShieldBreak, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory42",
        "\CdREGN-ER8",  "SHA2P0",   52000,
        "\CdCharge Rate\C- scales based on how long since your \CvShield\C- took damage\nFrom \Cg0.5x\C- after being hit to \Cd4x\C-",
        SHIELD_PASS_NONE,
        RegenShieldMod, NULL, NULL, RegenShieldDamage, NULL, RegenShieldCharge, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory43",
        "\CgCOUN-TR20", "SHA2Q0",   46000,
        "Whenever you are struck with \CcMelee Damage\C-, you emit a powerful \CnRepulsion\C- blast",
        SHIELD_PASS_NONE,
        NULL, NULL, NULL, CounterDamage, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory44",
        "\CvPRO-100",   "SHA2R0",   83000,
        "Gives an additional \Cv+100 Capacity\C- for every stat at or over 100",
        SHIELD_PASS_NONE,
        MLGNoScopeShieldMod, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory45",
        "\CiRUS-ROU1",  "SHA2S0",   48000,
        "\Cd-1000% Damage Reduction\n\Ci5 In 6 Survival Bonus\C-",
        SHIELD_PASS_ROULETTE, // To bypass the 75% survival cap
        RussianRouletteMod, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory46",
        "\CjOCD-MX90",  "SHA2T0",   108000,
        "Every level you \Cd100% complete\C- gives you:\n\Cv+20 Capacity\n\Cd+0.5 Charge Rate\n\Ca-0.2 Delay",
        SHIELD_PASS_NONE,
        OCDShieldMod, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory47",
        "\CjMASTA-R4",  "SHA2U0",   100000,
        "Every new wave of \CaThe Arena\C- you complete gives you:\n\Cv+10 Capacity\n\Cd+0.25 Charge Rate\n\Ca-0.1 Delay",
        SHIELD_PASS_NONE,
        ArenaShieldMod, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory48",
        "\CjHOW-EV3N",  "SHA2V0",   500000,
        "Swaps \CaDelay\C- and \CdCharge Rate\C-",
        SHIELD_PASS_NONE,
        HowDidYouEvenMod, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory49",
        "\CgK00-LAYD",  "SHA2W0",   62000,
        "Upon entering a non-Outpost level, releases an \Cgexplosive blast\C- that kills most monsters around you",
        SHIELD_PASS_NONE,
        OhYeahMod, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory50",
        "\CvSKROO-G3",  "SHA2X0",   111111,
        "\Cv+50 Capacity\C- for every \Cf10000 Credits\C- you currently have\nCaps at a maximum of \Cf1000000 Credits\C- and \Cv+5000 Capacity",
        SHIELD_PASS_NONE,
        McDuckMod, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory51",
        "\ChINFI-NT1",  "SHA2Y0",   200000,
        "\Cg25% \CvCapacity\n\Cg50% \CdCharge Rate\n\Cg400% \CaDelay\nYou have \Cqinfinite ammo\C- while your \CvShield\C- is full",
        SHIELD_PASS_NONE,
        AmmoSpaceMod, NULL, AmmoSpaceUnequip, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory52",
        "\CgREMI-500",  "SHA2Z0",   110000,
        "\CgYour Shield does not recharge\nInstead, every kill charges \CvShield\C- for 10% of the enemy's \Camax health",
        SHIELD_PASS_KILLSCHARGE,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory53",
        "\CgFLAN-495",  "SHA2[0",   120000,
        "When your \CvShield\C- is \Cgdepleted\C- or \Cdreaches full charge\C-, enemies around you \Cgexplode\C-",
        SHIELD_PASS_NONE,
        NULL, NULL, NULL, NULL, FlanExplosion, NULL, NULL, NULL, FlanExplosion,
    },
    {
        "DRPGShieldAccessory54",
        "\CgTOJ1-K0",   "SHA2\\0",   55000,
        "Every time your \CvShield\C- charges, it emits \Cnlightning bolts\C-\nThe higher your \CdCharge Rate\C-, the more \Cnlightning\C- your \CvShield\C- emits",
        SHIELD_PASS_NONE,
        NULL, NULL, NULL, NULL, NULL, LightningCharge, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory55",
        "\CcTRANS-EB2S2",   "SHA2]0",   40000,
        "If your \CkAugmentation Battery\C- is full, \Cv2x Capacity\C-",
        SHIELD_PASS_NONE,
        TheAmazingBatteryShieldMod, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory56",
        "\CvLIL-ZZ8",   "SHA3A0",   13000,
        "Adds \CdCharge Rate\C- to \CvCapacity\C-",
        SHIELD_PASS_NONE,
        LilZiggyMod, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory57",
        "\CgMURD-BURD", "SHA3B0",   85000,
        "Every \Cgkill\C- made on the current level grants \Cv+10 Capacity\C-",
        SHIELD_PASS_NONE,
        MurderBurgerMod, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory58",
        "\CfLKY-BSTRD4",    "SHA3C0",   32000,
        "Adds \CfLuck\C- to \CiAgility\C- for the purpose of calculating \CiSurvival Bonus\C-",
        SHIELD_PASS_NONE,
        LuckyBastardMod, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory59",
        "\CaHEL-FY20",  "SHA3D0",   52000,
        "Every \Ca100 Health\C- you have adds \Cv+20 Capacity\C-",
        SHIELD_PASS_NONE,
        IronShieldMod, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory60",
        "\CnMUN3-MAG",  "SHA3E0",   33000,
        "Triples the amount of \CfCredits\C- gained from using \CnMagnetize\C-",
        SHIELD_PASS_DOSHMAGNET,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory61",
        "\CnEFF-C13",   "SHA3F0",   80000,
        "\Cn25%\C- of not using \CnEP\C- when using a \CnSkill\C-",
        SHIELD_PASS_MORESKILLS,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory62",
        "\CnSYN-C3P",   "SHA3G0",   95000,
        "\CnEP Regen\C- is substituted for \CdCharge Rate\C-",
        SHIELD_PASS_NONE,
        EPRegenSwapperMod, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory63",
        "\CnTUFF-MAG3", "SHA3H0",   54000,
        "\Cn10%\C- of the cost of a used \CnSkill\C- is added to your \CvShield\C-",
        SHIELD_PASS_SKILLTOSHIELD,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory64",
        "\CnUBR-MANZ5", "SHA3I0",   220000,
        "Whenever you gain \CnEP\C- with \CnEP\C- maxed, you gain the amount in \CaHealth\C- and \CvShield\C- instead",
        SHIELD_PASS_EPOVERFLOW,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory65",
        "\CqHORD-3RR",  "SHA3J0",   29000,
        "While a \Cqpowerup\C- is active, you gain 2x of your base \Cdcharge rate\C-\n\CdStacks with multiple different powerups\C-",
        SHIELD_PASS_NONE,
        HoarderMod, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    },
    {
        "DRPGShieldAccessory66",
        "\CdS-SP4G3TT", "SHA3K0",   36000,
        "Whenever your \CvShield\C- is \Cgdepleted\C-, your \CdArmor\C- is fully repaired\n\CgShield must fully recharge between uses",
        SHIELD_PASS_NONE,
        NULL, NULL, NULL, NULL, SpaghettiShieldBreak, NULL, NULL, NULL, SpaghettiShieldFullCharge,
    },
};

NamedScript DECORATE void AMShieldCharge()
{
    if (!Player.Shield.Active || !Player.Shield.Accessory || Player.Shield.Accessory->PassiveEffect != SHIELD_PASS_HATEHATEHATE)
        return;
    
    GiveInventory("DRPGShieldHateHateHateDefense", 1);
}

// Callback scripts

// Converters
NamedScript void HealthConversion(int Charge)
{
    Player.Shield.AccessoryBattery += Charge;
    
    while (Player.Shield.AccessoryBattery >= 5)
    {
        // FadeRange(255, 0, 255, 0.25, 255, 0, 255, 0, 0.25);
        AddHealthDirect(1, 100);
        Player.Shield.AccessoryBattery -= 5;
    }
}

NamedScript void EPConversion(int Charge)
{
    Player.Shield.AccessoryBattery += Charge;
    
    while (Player.Shield.AccessoryBattery >= 2)
    {
        // FadeRange(0, 255, 255, 0.25, 0, 255, 255, 0, 0.25);
        AddEP(1, true);
        Player.Shield.AccessoryBattery -= 2;
    }
}

NamedScript void BatteryConversion(int Charge)
{
    Player.Shield.AccessoryBattery += Charge;
    
    while (Player.Shield.AccessoryBattery >= 32)
    {
        // FadeRange(255, 255, 0, 0.25, 255, 255, 0, 0, 0.25);
        AddBattery(1);
        Player.Shield.AccessoryBattery -= 32;
    }
}

NamedScript void AmmoConversion(int Charge)
{
    Player.Shield.AccessoryBattery += Charge;
    
    while (Player.Shield.AccessoryBattery >= 4)
    {
        // FadeRange(0, 0, 255, 0.25, 0, 0, 255, 0, 0.25);
        GiveInventory("Clip", 2);
        GiveInventory("Shell", 1);
        Player.Shield.AccessoryBattery -= 4;
    }
}

// Standard Charging
NamedScript int LightningCharge(int ChargeAmount)
{
    if (Player.Shield.Full) return ChargeAmount;
    
    int NumBolts = 0;
    for (int i = 0; i < ChargeAmount; i++)
        if (!Random(0, 3))
            NumBolts++;
    
    if (!NumBolts) return ChargeAmount;
    
    for (; NumBolts > 0; NumBolts--)
        GiveInventory("DRPGShieldLightningAttack", 1);
    
    PlaySound(0, "shield/lightning", CHAN_AUTO, 1.0, false, 1.0);
    return ChargeAmount;
}

NamedScript int RegenShieldCharge(int ChargeAmount)
{
    if (Player.Shield.AccessoryBattery < 20)
        Player.Shield.AccessoryBattery++;
    
    return ChargeAmount;
}
// Fast Charging
NamedScript bool CellFastCharge()
{
    if (CheckInventory("Cell") < 1) return true;
    
    TakeInventory("Cell", 1);
    FadeRange(0, 255, 255, 0.1, 0, 255, 255, 0.0, 0.5);
    ActivatorSound("regen/shield", 64);
    AddShield(10);
    
    return true;
}

// Shield Damage
NamedScript void BoosterShieldDamage(int DamageAmount)
{
    int Chance = 6;
    Chance += 19 * DamageAmount / 65;
    if (Chance > 25)
        Chance = 25;
    
    if (Random(1, 100) <= Chance)
    {
        int TID = UniqueTID();
        fixed Angle = GetActorAngle(0);
        fixed X = GetActorX(0) + Cos(Angle) * 48.0;
        fixed Y = GetActorY(0) + Sin(Angle) * 48.0;
        fixed DirX = Cos(Angle);
        fixed DirY = Sin(Angle);
        fixed Z = GetActorZ(0);
        
        Spawn("DRPGShieldBooster", X, Y, Z, TID, Angle);
        SetActorVelocity(TID, DirX * RandomFixed(8.0, 16.0), DirY * RandomFixed(8.0, 16.0), RandomFixed(4.0, 8.0), false, false);
    }
}

NamedScript void SpookyDamage(int DamageAmount)
{
    if (Random(1, 8) == 1)
        GiveInventory("PowerShieldGhost", 1);
}

NamedScript void TimeyWimeyHurtyBallZDoomSucks()
{
    // Note for future endeavours: PowerTimeFreezer will always work on an even tic, but never odd ones.
    // See: https://github.com/rheit/zdoom/blob/master/src/g_shared/a_artifacts.cpp#L1502
    
    while (Timer() & 1) Delay(1);
    
    GiveInventory("DRPGShieldTimePause", 1);
    Delay(35);
    TakeInventory("PowerShieldTimeFreezer", 1);
}

NamedScript void TimeyWimeyHurtyBall(int DamageAmount)
{
    TimeyWimeyHurtyBallZDoomSucks();
}

NamedScript void StaticChargeShieldDamage(int DamageAmount)
{
    int projtid = UniqueTID();
    SpawnProjectile(0, "DRPGStaticChargeShieldExplosion", 0, 0, 0, false, projtid);
    SetActorPosition(projtid, GetActorX(0), GetActorY(0), GetActorZ(0) + 32.0, false);
}

NamedScript void CounterDamage(int DamageAmount)
{
    if (Player.DamageType == DT_MELEE)
        GiveInventory("DRPGShieldCounterBlast", 1);
}

NamedScript void RegenShieldDamage(int DamageAmount)
{
    Player.Shield.AccessoryBattery = 0;
}

// Shield Depletion
NamedScript void NovaShieldBreak()
{
    if (Random(1, 4) == 1)
        Nova("BFGBall", Random(4, 16));
}

NamedScript void TeleportPostDamageStop()
{
    Delay(1);
    SetActorVelocity(0, 0, 0, 0, false, true);
}

NamedScript void TeleportBreak()
{
    if (Player.Shield.AccessoryBattery)
    {
        FadeRange(118, 255, 112, 0.5, 118, 255, 112, 0, 1.0);
        SetActorPosition(0, Player.Shield.AccessoryPosition.X, Player.Shield.AccessoryPosition.Y, Player.Shield.AccessoryPosition.Z, true);
        SetActorAngle(0, Player.Shield.AccessoryPosition.Angle);
        SetActorPitch(0, Player.Shield.AccessoryPosition.Pitch);
        TeleportPostDamageStop();
    }
}

NamedScript void AdaptiveBreak()
{
    switch (Player.DamageType)
    {
    case DT_NORMAL:     GiveInventory("DRPGShieldAdaptiveNormalResist", 1);     break;
    case DT_TOXIC:      GiveInventory("DRPGShieldAdaptiveToxicResist", 1);      break;
    case DT_MELEE:      GiveInventory("DRPGShieldAdaptiveMeleeResist", 1);      break;
    case DT_FIRE:       GiveInventory("DRPGShieldAdaptiveFireResist", 1);       break;
    case DT_PLASMA:     GiveInventory("DRPGShieldAdaptivePlasmaResist", 1);     break;
    case DT_LIGHTNING:  GiveInventory("DRPGShieldAdaptiveLightningResist", 1);  break;
    }
}

NamedScript void StaticChargeShieldBreak()
{
    int projtid = UniqueTID();
    SpawnProjectile(0, "DRPGStaticChargeShieldLargeExplosion", 0, 0, 0, false, projtid);
    SetActorPosition(projtid, GetActorX(0), GetActorY(0), GetActorZ(0) + 32.0, false);
}

NamedScript void FlanExplosion() // This gets called on full charge too
{
    if (CurrentLevel->UACBase && !ArenaActive) return;
    
    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        GiveActorInventory(Players(i).TID, "DRPGShieldRadialExplosionResist", 1);
        
        // Turret needs protection too
        if (Players(i).Turret.Active)
            GiveActorInventory(Players(i).Turret.TID, "DRPGShieldRadialExplosionResist", 1);
    }
    
    GiveInventory("DRPGShieldRadialExplosionMaker", 1);
}

NamedScript void SpaghettiShieldBreak()
{
    if (GetCVar("drpg_shield_armorremove"))
    {
        if (Player.Shield.ArmorType == "None" || !Player.Shield.AccessoryBattery)
            return;
    }
    else
    {
        if (CheckInventory("Armor") == 0 || CheckInventory("Armor") >= GetArmorInfo(ARMORINFO_SAVEAMOUNT) || !Player.Shield.AccessoryBattery)
            return;
    }
    
    FadeRange(0, 255, 0, 0.5, 0, 255, 0, 0, 1.0);
    if (GetCVar("drpg_shield_armorremove"))
        Player.Shield.ArmorAmount = Player.Shield.ArmorMax;
    else
        GiveInventory(GetArmorInfoString(ARMORINFO_CLASSNAME), 1);
    ActivatorSound("skills/repair", 127);
    Player.Shield.AccessoryBattery = 0;
}

// Shield Recharge
NamedScript void SpaghettiShieldFullCharge()
{
    Player.Shield.AccessoryBattery = 1;
}

NamedScript void TeleportFullCharge()
{
    Player.Shield.AccessoryBattery = 1; // Indicate we have a spot
    Player.Shield.AccessoryPosition.X = GetActorX(0);
    Player.Shield.AccessoryPosition.Y = GetActorY(0);
    Player.Shield.AccessoryPosition.Z = GetActorZ(0);
    Player.Shield.AccessoryPosition.Angle = GetActorAngle(0);
    Player.Shield.AccessoryPosition.Pitch = GetActorPitch(0);
}

// Stat Modifiers / Shield Maintenance
NamedScript void X7Mod()
{
    if (Player.Shield.Active)
        if (CheckWeapon("Fist") || CheckWeapon("Knuckle") || CheckWeapon("RLFistRedux"))
            Player.TotalDamage *= 2;
}

NamedScript void AmpShieldMod()
{
    if (Player.Shield.Active)
    {
        if (Player.Shield.AccessoryBattery > 0)
        {
            Player.TotalDamage *= 2;
            Player.Shield.AccessoryBattery--;
        }
        
        if (Player.Shield.Charge >= Player.Shield.Capacity)
        {
            int Buttons = GetPlayerInput(PlayerNumber(), INPUT_BUTTONS);

            if (Buttons & BT_ATTACK && !Player.InMenu && !Player.InShop && !Player.OutpostMenu)
            {
                PlaySound(0, "shield/amp", 5, 1.0, false, 1.0);
                FadeRange(255, 255, 255, 0.25, 255, 255, 255, 0.0, 0.5);
                Player.Shield.Charge /= 2;
                Player.Shield.AccessoryBattery = 70;
            }
        }
    }
}

NamedScript void HurryMod()
{
    Player.Shield.Capacity /= 2;
    Player.Shield.DelayRate /= 2;
}

NamedScript void Def2Mod()
{
    Player.Shield.Capacity *= 2;
    Player.Shield.DelayRate *= 2;
}

NamedScript void BlzutMod()
{
    Player.Shield.Capacity /= 2;
    Player.Shield.ChargeRate *= 2;
}

NamedScript void RektMod()
{
    Player.DamageFactor *= 2;
}

NamedScript void LightAmpMod()
{
    if (Player.Shield.Active && Player.Shield.Charge >= Player.Shield.Capacity)
        SetInventory("PowerShieldLightAmp", 1);
    else
        TakeInventory("PowerShieldLightAmp", 1);
}

NamedScript void LightAmpUnequip(bool EMP)
{
    TakeInventory("PowerShieldLightAmp", 1);
}

NamedScript void InvisibilityMod()
{
    if (Player.Shield.Active && Player.Shield.Charge >= Player.Shield.Capacity)
        SetInventory("PowerShieldInvisibility", 1);
    else
        TakeInventory("PowerShieldInvisibility", 1);
}

NamedScript void InvisibilityUnequip(bool EMP)
{
    TakeInventory("PowerShieldInvisibility", 1);
}

NamedScript void LazyMod()
{
    if (!IsPlayerMoving())
        Player.Shield.ChargeRate *= 2;
    else
        Player.Shield.ChargeRate = 0;
}

NamedScript void AccelerativeShieldMod()
{
    if (Player.Shield.Capacity < 1)
        return;

    int AccelCharge = Player.Shield.ChargeRate;
    AccelCharge += (Player.Shield.ChargeRate * 3) * Player.Shield.Charge / Player.Shield.Capacity;
    Player.Shield.ChargeRate = AccelCharge;
}

NamedScript void TheKillingBoosterMod()
{
    Player.Shield.Capacity /= 2;
    if (Player.Shield.Active)
        Player.TotalDamage = Player.TotalDamage * 1.5;
}

NamedScript void MinuteMaidMod()
{
    int Minutes = Timer() / (35 * 60);
    Player.Shield.ChargeRate += Minutes;
    Player.Shield.DelayRate -= Minutes * 0.1;
}

NamedScript void AmericaShieldMod()
{
    int ExtraCapacity = (Player.Shield.Capacity * 3) * Player.RankLevel / MAX_RANK;
    Player.Shield.Capacity += ExtraCapacity;
}

NamedScript void GhettoLuckMod()
{
    int Luck = 50 - (Player.Luck / 2);
    
    Player.HealthChance += Luck * LUCK_HEALTHCHANCE;
    Player.EPChance += Luck * LUCK_EPCHANCE;
    Player.ArmorChance += Luck * LUCK_ARMORCHANCE;
    Player.PowerupChance += Luck * LUCK_POWERUPCHANCE;
    Player.WeaponChance += Luck * LUCK_WEAPONCHANCE;
    Player.ModuleChance += Luck * LUCK_MODULECHANCE;
    Player.AugChance += Luck * LUCK_AUGCHANCE;
    Player.ShieldChance += Luck * LUCK_SHIELDCHANCE;
    Player.StimChance += Luck * LUCK_STIMCHANCE;
}

NamedScript void SuperSqueezyScalarMod()
{
    Player.Shield.Capacity = Player.Shield.Capacity * (1.0 + (Player.Capacity * 0.005)) + 1;
    Player.Shield.ChargeRate += (Player.Energy / 10);
    Player.Shield.DelayRate = Player.Shield.DelayRate - ((fixed)Player.Regeneration / 50.0);
}

NamedScript void ReflectionMod()
{
    if (Player.Shield.Active && Player.Shield.Charge)
        GiveInventory("DRPGShieldReflection", 1);
    else
        GiveInventory("DRPGShieldReflectionOff", 1);
}

NamedScript void ReflectionUnequip(bool EMP)
{
    GiveInventory("DRPGShieldReflectionOff", 1);
}

NamedScript void ScarletWeatherRhapsodyShieldMod()
{
    if (!Player.Shield.Active || Player.Shield.Capacity < 1)
        return;
    
    if (Player.Shield.Charge < 1)
    {
        Player.DamageFactor = 1.0;
        return;
    }
    
    fixed BaseFactorMinus = 1.0 - Player.DamageFactor;
    Player.DamageFactor -= (0.75 - BaseFactorMinus) - ((0.75 - BaseFactorMinus) * ((fixed)(Player.Shield.Charge - 1) / (fixed)(Player.Shield.Capacity - 1)));
}

NamedScript void SanicMod()
{
    int Movement = VectorLength(GetActorVelX(0), GetActorVelY(0));
    
    if (Movement > 30)
        Movement = 30;
    
    Player.Shield.Interval -= Movement;
}

NamedScript void NakedMod()
{
    if (Player.Shield.Active && CheckInventory("Armor") > 0)
        GiveInventory("DRPGShieldNakedResist", 1);
}

NamedScript void BloodyShieldSoRealMod()
{
    if (Player.Shield.AccessoryBattery)
    {
        Player.Shield.Interval /= 5;
        Player.Shield.AccessoryBattery--;
    }
}

NamedScript void FriendshipShieldMod()
{
    fixed TotalDefense = 0;
    
    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        if (!PlayerInGame(i))
            continue;
        if (!Players(i).Shield.Active)
            continue;
        if (!Players(i).Shield.Accessory || Players(i).Shield.Accessory->PassiveEffect != SHIELD_PASS_FRIENDSHIPISDEFENSE)
            continue;
        
        TotalDefense += 0.1;
    }
    
    Player.DamageFactor -= TotalDefense;
}

NamedScript void RegenShieldMod()
{
    int BaseCharge = Player.Shield.ChargeRate / 2;
    int AddCharge = Player.Shield.ChargeRate * 4 - BaseCharge;
    Player.Shield.ChargeRate = AddCharge * Player.Shield.AccessoryBattery / 20 + BaseCharge;
}

NamedScript void MLGNoScopeShieldMod()
{
    int Extra = 0;
    if (Player.Strength     >= 100) Extra += 100;
    if (Player.Defense      >= 100) Extra += 100;
    if (Player.Vitality     >= 100) Extra += 100;
    if (Player.Energy       >= 100) Extra += 100;
    if (Player.Regeneration >= 100) Extra += 100;
    if (Player.Agility      >= 100) Extra += 100;
    if (Player.Capacity     >= 100) Extra += 100;
    if (Player.Luck         >= 100) Extra += 100;
    
    Player.Shield.Capacity += Extra;
}

NamedScript void RussianRouletteMod()
{
    if (Player.Shield.Active)
    {
        Player.DamageFactor = 11.0; // Let's crank this up to eleven
        Player.SurvivalBonus = (5.0 / 6.0) * 100.0;
    }
}

NamedScript void OCDShieldMod()
{
    Player.Shield.Capacity += AllBonusMaps * 20;
    Player.Shield.ChargeRate += AllBonusMaps / 2;
    Player.Shield.DelayRate -= (fixed)AllBonusMaps * 0.2;
}

NamedScript void ArenaShieldMod()
{
    int ArenaCompletes = ArenaMaxWave - 1;
    if (ArenaCompletes > 100)
        ArenaCompletes = 100;
    Player.Shield.Capacity += ArenaCompletes * 10;
    Player.Shield.ChargeRate += ArenaCompletes / 4;
    Player.Shield.DelayRate -= (fixed)ArenaCompletes * 0.1;
}

NamedScript void HowDidYouEvenMod()
{
    int DelayRate = Player.Shield.DelayRate;
    Player.Shield.DelayRate = Player.Shield.ChargeRate;
    Player.Shield.ChargeRate = DelayRate;
}

NamedScript void SayItOhYeahOhBaby() // OH YEEEEEEEEAH!
{
    Delay(8);
    ActivatorSound("shield/ohyeah", 127);
}

NamedScript void OhYeahMod()
{
    if (Timer() == 10 && !CurrentLevel->UACBase)
    {
        FadeRange(255, 128, 0, 0.5, 255, 128, 0, 0.0, 0.5);
        GiveInventory("DRPGShieldRadialExplosion", 1);
        for (int i = 0; i < MAX_PLAYERS; i++)
            GiveActorInventory(Players(i).TID, "DRPGShieldRadialExplosionResist", 1);
        SayItOhYeahOhBaby();
    }
}

NamedScript void McDuckMod()
{
    int Capacity = CheckInventory("DRPGCredits") / 10000 * 50;
    
    if (Capacity > 5000)
        Capacity = 5000;
    
    Player.Shield.Capacity += Capacity;
}

NamedScript void AmmoSpaceMod()
{
    Player.Shield.Capacity /= 4;
    Player.Shield.ChargeRate /= 2;
    Player.Shield.DelayRate *= 4;
    if (Player.Shield.Active && Player.Shield.Charge >= Player.Shield.Capacity)
        SetInventory("PowerShieldInfiniteAmmo", 1);
    else
        TakeInventory("PowerShieldInfiniteAmmo", 1);
}

NamedScript void AmmoSpaceUnequip(bool EMP)
{
    TakeInventory("PowerShieldInfiniteAmmo", 1);
}

NamedScript void TheAmazingBatteryShieldMod()
{
    if (Player.Augs.Battery >= 100)
        Player.Shield.Capacity *= 2;
}

NamedScript void LilZiggyMod()
{
    Player.Shield.Capacity += Player.Shield.ChargeRate;
}

NamedScript void MurderBurgerMod()
{
    int MonstersKilled = GetLevelInfo(LEVELINFO_KILLED_MONSTERS);
    if (MonstersKilled > 250)
        MonstersKilled = 250;
    Player.Shield.Capacity += MonstersKilled * 10;
}

NamedScript void LuckyBastardMod()
{
    if (Player.Shield.Active)
    {
        int CombinedStat = Player.Agility + Player.Luck;
        
        Player.SurvivalBonus = (fixed)CombinedStat / 10.0;
        
        if (Player.Augs.Level[AUG_AGILITY] >= 4)
            Player.SurvivalBonus *= 2;
        
        if (Player.Perks[STAT_AGILITY])
            Player.SurvivalBonus += 30;
    }
}

NamedScript void IronShieldMod()
{
    Player.Shield.Capacity += Player.ActualHealth / 100 * 20;
}

NamedScript void EPRegenSwapperMod()
{
    if (Player.Shield.Active)
        Player.EPAmount = Player.Shield.ChargeRate;
}

NamedScript void HoarderMod()
{
    int BaseCharge = Player.Shield.ChargeRate;
    int AddCharge;
    
    if (CheckInventory("PowerInvulnerable"))
        AddCharge += BaseCharge;
    if (CheckInventory("PowerInvisibility") || CheckInventory("PowerShadow"))
        AddCharge += BaseCharge;
    if (CheckInventory("PowerTimeFreezer"))
        AddCharge += BaseCharge;
    if (CheckInventory("PowerIronFeet"))
        AddCharge += BaseCharge;
    if (CheckInventory("PowerLightAmp"))
        AddCharge += BaseCharge;
    if (CheckInventory("PowerStrength"))
        AddCharge += BaseCharge;
    
    Player.Shield.ChargeRate += AddCharge;
}

NamedScript void ShieldTimer()
{
    while (true)
    {
        if (Player.Shield.Active)
        {
            // Inventory items for multiplayer/health bar handling
            SetInventory("DRPGShieldCharge", Player.Shield.Charge);
            SetInventory("DRPGShieldChargeMax", Player.Shield.Capacity);
            
            if (Player.Shield.Charge < Player.Shield.Capacity)
                Player.Shield.Full = false;
            
            // Increase Charge
            if (Player.Shield.Timer <= 0)
            {
                int ChargeRate = Player.Shield.ChargeRate;
                if (Player.Shield.Accessory && Player.Shield.Accessory->Charge)
                    ChargeRate = Player.Shield.Accessory->Charge(ChargeRate);
                
                if (ChargeRate && (!Player.Shield.Accessory || Player.Shield.Accessory->PassiveEffect != SHIELD_PASS_KILLSCHARGE))
                {
                    if (Player.Shield.Charge < 1)
                        PlaySound(0, "shield/restart", 5, 1.0, false, 1.0);
                    else if (Player.Shield.Charge < Player.Shield.Capacity)
                        PlaySound(0, "shield/charge", 5, 0.25, false, 2.0);
                    Player.Shield.Charge += ChargeRate;
                }
                
                Player.Shield.Timer = Player.Shield.Interval;
                
                if (Player.Shield.Charge >= Player.Shield.Capacity)
                {
                    // Shield is Full
                    if (!Player.Shield.Full)
                    {
                        Player.Shield.Full = true;
                        PlaySound(0, "shield/full", 5, 1.0, false, 1.0);
                        if (Player.Shield.Accessory && Player.Shield.Accessory->FullCharge)
                            Player.Shield.Accessory->FullCharge();
                    }
                    
                    int OverCharge = Player.Shield.Charge - Player.Shield.Capacity;

                    if (OverCharge > 0 && Player.Shield.Accessory && Player.Shield.Accessory->Overcharge)
                        Player.Shield.Accessory->Overcharge(OverCharge);
                    
                    Player.Shield.Charge = Player.Shield.Capacity;
                }
            }
            
            // Shield Timer
            if (Player.Shield.Timer > 0)
                Player.Shield.Timer--;
        }
        
        // Terminate if you are dead
        if (GetActorProperty(0, APROP_Health) <= 0) return;
        
        Delay(1);
    }
}

NamedScript void ShieldDamage(int Amount)
{
    Player.Shield.Full = false;
    
    PlaySound(0, "shield/hit", 5, 1.0, false, 1.0);
    if (Player.Shield.Accessory && Player.Shield.Accessory->Damage)
        Player.Shield.Accessory->Damage(Amount);
    
    // Payout
    Player.Payout.ShieldDamage += Amount;
}

NamedScript void ShieldBroken()
{
    PlaySound(0, "shield/empty", 5, 1.0, false, 1.0);
    
    if (Player.Shield.Accessory && Player.Shield.Accessory->Break)
        Player.Shield.Accessory->Break();
    
    // Payout
    Player.Payout.ShieldBreaks++;
}

NamedScript void ShieldTimerReset()
{
    Player.Shield.Timer = 35.0 * Player.Shield.DelayRate;
}

NamedScript bool ActivateShield()
{
    if (Player.Shield.Active)
        return true;
    
    if (!Player.Shield.Body || !Player.Shield.Battery || !Player.Shield.Capacitor)
    {
        PrintError("Your shield is incomplete and is missing one or more parts");
        ActivatorSound("menu/error", 127);
        return false;
    }
    
    if (Player.StatusType[SE_EMP])
    {
        PrintError("Your shield cannot be activated while EMP is active");
        ActivatorSound("menu/error", 127);
        return false;
    }
    
    if (Player.Shield.Capacity <= 0)
    {
        PrintError("Your shield has no charge capacity and cannot be activated");
        ActivatorSound("menu/error", 127);
        return false;
    }

    FadeRange(255, 255, 255, 0.25, 255, 255, 255, 0.0, 0.25);
    
    if (Player.Shield.Accessory && Player.Shield.Accessory->Equip)
        Player.Shield.Accessory->Equip();
    
    GiveInventory("DRPGShieldOn", 1);
    PlaySound(0, "shield/on", 5, 1.0, false, 1.0);
    Player.Shield.Active = true;
    if (GetCVar("drpg_shield_armorremove"))
    {
        Player.Shield.ArmorType = GetArmorInfoString(ARMORINFO_CLASSNAME);
        Player.Shield.ArmorAmount = CheckInventory("Armor");
        Player.Shield.ArmorMax = GetArmorInfo(ARMORINFO_SAVEAMOUNT);
        
        // DRLA Compatibility
        if (CompatMode != COMPAT_DRLA)
            TakeInventory("BasicArmor", Player.Shield.ArmorAmount);
        if (CompatMode == COMPAT_DRLA && !Contains(Player.Shield.ArmorType, "Shield") && !Contains(Player.Shield.ArmorType, "Cybernetic"))
        {
            TakeInventory("BasicArmor", Player.Shield.ArmorAmount);
            RemoveDRLAArmorToken(Player.Shield.ArmorType);
            
            TakeInventory("RL100ArmorWorn", 1);
            TakeInventory("RL150ArmorWorn", 1);
            TakeInventory("RL200ArmorWorn", 1);
            TakeInventory("RL100RegenArmorWorn", 1);
            TakeInventory("RLIndestructibleArmorWorn", 1);
        }
    }
    ShieldTimerReset();
    
    return true;
}

NamedScript bool DeactivateShield()
{
    if (!Player.Shield.Active)
        return true;
    
    FadeRange(255, 255, 255, 0.25, 255, 255, 255, 0.0, 0.25);
    
    if (Player.Shield.Accessory && Player.Shield.Accessory->Unequip)
        Player.Shield.Accessory->Unequip(Player.StatusType[SE_EMP]);

    GiveInventory("DRPGShieldOff", 1);
    PlaySound(0, "shield/off", 5, 1.0, false, 1.0);
    Player.Shield.Active = false;
    Player.Shield.AccessoryBattery = 0;
    if (GetCVar("drpg_shield_armorremove") && Player.Shield.ArmorType != "None" && !Contains(Player.Shield.ArmorType, "Shield") && !Contains(Player.Shield.ArmorType, "Cybernetic"))
    {
        GiveInventory(Player.Shield.ArmorType, 1);
        TakeInventory("BasicArmor", Player.Shield.ArmorMax - Player.Shield.ArmorAmount);
                
        // DRLA Compatibility
        if (CompatMode == COMPAT_DRLA)
        {
            GiveDRLAArmorToken(Player.Shield.ArmorType);
            
            if (Player.Shield.ArmorMax == 100)
                GiveInventory("RL100ArmorWorn", 1);
            else if (Player.Shield.ArmorMax == 150)
                GiveInventory("RL150ArmorWorn", 1);
            else if (Player.Shield.ArmorMax == 200)
                GiveInventory("RL200ArmorWorn", 1);
            else if (Contains(Player.Shield.ArmorType, "Ablative") ||
                     Contains(Player.Shield.ArmorType, "PoweredArmor") ||
                     Contains(Player.Shield.ArmorType, "Tactical"))
                GiveInventory("RL100RegenArmorWorn", 1);
            else if (Player.Shield.ArmorMax == 99999)
                GiveInventory("RLIndestructibleArmorWorn", 1);
        }
    }
    if (GetCVar("drpg_shield_reset") || Player.StatusType[SE_EMP])
        Player.Shield.Charge = 0;
    
    return true;
}

NamedScript KeyBind void ToggleShield()
{
    // If you're dead, terminate
    if (GetActorProperty(0, APROP_Health) <= 0) return;
    
    if (!Player.Shield.Active)
        ActivateShield();
    else
        DeactivateShield();
}

void RemoveShieldAccessory()
{
    //this if statement always passes, causes P_StartScript: Unknown script 0
    //needs fixing
    if (Player.Shield.Accessory->Unequip)
        Player.Shield.Accessory->Unequip(false);
    
    Player.Shield.AccessoryBattery = 0;
    Player.Shield.Accessory = NULL;
}

void SetShieldAccessory(ShieldAccsPtr Accessory)
{
    if (Player.Shield.Accessory)
        RemoveShieldAccessory();

    Player.Shield.Accessory = Accessory;
    if (Player.Shield.Accessory->Equip)
        Player.Shield.Accessory->Equip();
}

NamedScript DECORATE void AddShield(int Amount)
{
    if (Player.Shield.Charge >= Player.Shield.Capacity) return;
    
    if (Player.Shield.Active)
    {
        if (Player.Shield.Charge < 1)
            PlaySound(0, "shield/restart", 5, 1.0, false, 1.0);
        else
            PlaySound(0, "shield/charge", 5, 0.25, false, 2.0);
    };
    FadeRange(0, 255, 255, 0.25, 0, 255, 255, 0, 0.25);
    if (Player.Shield.Charge + Amount > Player.Shield.Capacity)
        Amount = Player.Shield.Capacity - Player.Shield.Charge;
    
    Player.Shield.Charge += Amount;
}

NamedScript DECORATE void AddRemoteShield(int TID, int Amount)
{
    SetActivator(TID);
    if (PlayerNumber() < 0) return;
    AddShield(Amount);
}

void CheckShields()
{
    ShieldPartPtr BodyPtr = Player.Shield.Body;
    ShieldPartPtr BatteryPtr = Player.Shield.Battery;
    ShieldPartPtr CapacitorPtr = Player.Shield.Capacitor;
    ShieldAccsPtr AccessoryPtr = Player.Shield.Accessory;
    
    // Check to make sure the Shield has components
    if (!CheckShieldValid())
        if (Player.Shield.Active)
            DeactivateShield();
    
    // EP -> Shield Charging
    int Buttons = GetPlayerInput(PlayerNumber(), INPUT_BUTTONS);
    if (Player.Shield.Active && (!Player.InMenu && !Player.InShop) && Buttons & BT_SPEED && Buttons & BT_USE && Player.Shield.Charge < Player.Shield.Capacity)
    {
        bool SkipEPCharge = false;
        
        if (Player.Shield.Accessory && Player.Shield.Accessory->FastCharge)
            SkipEPCharge = Player.Shield.Accessory->FastCharge();
        
        if (!SkipEPCharge && Player.EP > 0)
        {
            FadeRange(0, 255, 255, 0.1, 0, 255, 255, 0.0, 0.5);
            ActivatorSound("regen/shield", 64);
            Player.EP--;
            Player.Shield.Charge++;
        }
    }
    
    // If a part is sold/dropped/nuked from orbit/etc, unequip it
    if (BodyPtr &&      !CheckInventory(BodyPtr->Actor))        Player.Shield.Body = NULL;
    if (BatteryPtr &&   !CheckInventory(BatteryPtr->Actor))     Player.Shield.Battery = NULL;
    if (CapacitorPtr && !CheckInventory(CapacitorPtr->Actor))   Player.Shield.Capacitor = NULL;
    if (AccessoryPtr && !CheckInventory(AccessoryPtr->Actor))   RemoveShieldAccessory();
    
    // Apply Components stats to Shield
    Player.Shield.Capacity = (BodyPtr ? BodyPtr->Capacity : 0) + (BatteryPtr ? BatteryPtr->Capacity : 0) + (CapacitorPtr ? CapacitorPtr->Capacity : 0);
    Player.Shield.ChargeRate = (BodyPtr ? BodyPtr->ChargeRate : 0) + (BatteryPtr ? BatteryPtr->ChargeRate : 0) + (CapacitorPtr ? CapacitorPtr->ChargeRate : 0);
    Player.Shield.DelayRate = 5.0 + (BodyPtr ? BodyPtr->DelayRate : 0) + (BatteryPtr ? BatteryPtr->DelayRate : 0) + (CapacitorPtr ? CapacitorPtr->DelayRate : 0);
    Player.Shield.Interval = 35;
}

void CheckShieldAccessory()
{
    if (Player.Shield.Accessory && Player.Shield.Accessory->Modifier)
        Player.Shield.Accessory->Modifier();
}

bool CheckShieldValid()
{
    ShieldPartPtr BodyPtr = Player.Shield.Body;
    ShieldPartPtr BatteryPtr = Player.Shield.Battery;
    ShieldPartPtr CapacitorPtr = Player.Shield.Capacitor;
    
    return (BodyPtr && BatteryPtr && CapacitorPtr);
}
