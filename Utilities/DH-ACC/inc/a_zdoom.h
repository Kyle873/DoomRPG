//-----------------------------------------------------------------------------
//
// Copyright(C) 2012 David Hill
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//
//-----------------------------------------------------------------------------
//
// ZDoom scripting functions and definitions.
//
// Identifiers beginning with A_ or ACS_ followed by a capital letter are
// reserved for use by this header.
//
//-----------------------------------------------------------------------------

#ifndef __HEADER__A_ZDOOM_H__
#define __HEADER__A_ZDOOM_H__


//----------------------------------------------------------------------------|
// Macros                                                                     |
//

//
// defs.acs defines.
//

#define A_LINE_FRONT 0
#define A_LINE_BACK  1

#define A_SIDE_FRONT 0
#define A_SIDE_BACK  1

#define A_TEXTURE_TOP    0
#define A_TEXTURE_MIDDLE 1
#define A_TEXTURE_BOTTOM 2

#define A_GAME_SINGLE_PLAYER   0
#define A_GAME_NET_COOPERATIVE 1
#define A_GAME_NET_DEATHMATCH  2

#define A_CLASS_FIGHTER 0
#define A_CLASS_CLERIC  1
#define A_CLASS_MAGE    2

#define A_SKILL_VERY_EASY 0
#define A_SKILL_EASY      1
#define A_SKILL_NORMAL    2
#define A_SKILL_HARD      3
#define A_SKILL_VERY_HARD 4

//
// zdefs.acs defines.
//

#define A_TEXFLAG_TOP       0x00000001
#define A_TEXFLAG_MIDDLE    0x00000002
#define A_TEXFLAG_BOTTOM    0x00000004
#define A_TEXFLAG_ADDOFFSET 0x00000008

#define A_BLOCK_NOTHING    0
#define A_BLOCK_CREATURES  1
#define A_BLOCK_EVERYTHING 2
#define A_BLOCK_RAILING    3
#define A_BLOCK_PLAYERS    4

#define A_SCROLL           0
#define A_CARRY            1
#define A_SCROLL_AND_CARRY 2

#define A_MOD_UNKNOWN       0
#define A_MOD_ROCKET        5
#define A_MOD_R_SPLASH      6
#define A_MOD_PLASMARIFLE   7
#define A_MOD_BFG_BOOM      8
#define A_MOD_BFG_SPLASH    9
#define A_MOD_CHAINSAW     10
#define A_MOD_SSHOTGUN     11
#define A_MOD_WATER        12
#define A_MOD_SLIME        13
#define A_MOD_LAVA         14
#define A_MOD_CRUSH        15
#define A_MOD_TELEFRAG     16
#define A_MOD_FALLING      17
#define A_MOD_SUICIDE      18
#define A_MOD_BARREL       19
#define A_MOD_EXIT         20
#define A_MOD_SPLASH       21
#define A_MOD_HIT          22
#define A_MOD_RAILGUN      23
#define A_MOD_ICE          24
#define A_MOD_DISINTEGRATE 25
#define A_MOD_POISON       26
#define A_MOD_ELECTRIC     27

#define A_PROP_FROZEN               0
#define A_PROP_NOTARGET             1
#define A_PROP_INSTANTWEAPONSWITCH  2
#define A_PROP_FLY                  3
#define A_PROP_TOTALLYFROZEN        4
#define A_PROP_INVULNERABILITY      5
#define A_PROP_STRENGTH             6
#define A_PROP_INVISIBILITY         7
#define A_PROP_RADIATIONSUIT        8
#define A_PROP_ALLMAP               9
#define A_PROP_INFRARED            10
#define A_PROP_WEAPONLEVEL2        11
#define A_PROP_FLIGHT              12
#define A_PROP_SPEED               15
#define A_PROP_BUDDHA              16

#define    A_INPUT_OLDBUTTONS   0
#define    A_INPUT_BUTTONS      1
#define    A_INPUT_PITCH        2
#define    A_INPUT_YAW          3
#define    A_INPUT_ROLL         4
#define    A_INPUT_FORWARDMOVE  5
#define    A_INPUT_SIDEMOVE     6
#define    A_INPUT_UPMOVE       7
#define A_MODINPUT_OLDBUTTONS   8
#define A_MODINPUT_BUTTONS      9
#define A_MODINPUT_PITCH       10
#define A_MODINPUT_YAW         11
#define A_MODINPUT_ROLL        12
#define A_MODINPUT_FORWARDMOVE 13
#define A_MODINPUT_SIDEMOVE    14
#define A_MODINPUT_UPMOVE      15

#define A_BT_ATTACK     0x00000001
#define A_BT_USE        0x00000002
#define A_BT_JUMP       0x00000004
#define A_BT_CROUCH     0x00000008
#define A_BT_TURN180    0x00000010
#define A_BT_ALTATTACK  0x00000020
#define A_BT_RELOAD     0x00000040
#define A_BT_ZOOM       0x00000080
#define A_BT_SPEED      0x00000100
#define A_BT_STRAFE     0x00000200
#define A_BT_MOVERIGHT  0x00000400
#define A_BT_MOVELEFT   0x00000800
#define A_BT_BACK       0x00001000
#define A_BT_FORWARD    0x00002000
#define A_BT_RIGHT      0x00004000
#define A_BT_LEFT       0x00008000
#define A_BT_LOOKUP     0x00010000
#define A_BT_LOOKDOWN   0x00020000
#define A_BT_MOVEUP     0x00040000
#define A_BT_MOVEDOWN   0x00080000
#define A_BT_SHOWSCORES 0x00100000
#define A_BT_USER1      0x00200000
#define A_BT_USER2      0x00400000
#define A_BT_USER3      0x00800000
#define A_BT_USER4      0x01000000

#define A_CR_UNTRANSLATED -1
#define A_CR_BRICK         0
#define A_CR_TAN           1
#define A_CR_GRAY          2
#define A_CR_GREY          2
#define A_CR_GREEN         3
#define A_CR_BROWN         4
#define A_CR_GOLD          5
#define A_CR_RED           6
#define A_CR_BLUE          7
#define A_CR_ORANGE        8
#define A_CR_WHITE         9
#define A_CR_YELLOW       10
#define A_CR_BLACK        12
#define A_CR_LIGHTBLUE    13
#define A_CR_CREAM        14
#define A_CR_OLIVE        15
#define A_CR_DARKGREEN    16
#define A_CR_DARKRED      17
#define A_CR_DARKBROWN    18
#define A_CR_PURPLE       19
#define A_CR_DARKGRAY     20
#define A_CR_DARKGREY     20
#define A_CR_CYAN         21

#define A_HUDMSG_PLAIN             0x00000000
#define A_HUDMSG_FADEOUT           0x00000001
#define A_HUDMSG_TYPEON            0x00000002
#define A_HUDMSG_FADEINOUT         0x00000003
#define A_HUDMSG_LAYER_OVERHUD     0x00000000
#define A_HUDMSG_LAYER_UNDERHUD    0x00001000
#define A_HUDMSG_LAYER_OVERMAP     0x00002000
#define A_HUDMSG_NOTWITH3DVIEW     0x00010000
#define A_HUDMSG_NOTWITHFULLMAP    0x00020000
#define A_HUDMSG_NOTWITHOVERLAYMAP 0x00040000
#define A_HUDMSG_NOWRAP            0x08000000
#define A_HUDMSG_ALPHA             0x10000000
#define A_HUDMSG_ADDBLEND          0x20000000
#define A_HUDMSG_COLORSTRING       0x40000000
#define A_HUDMSG_LOG               0x80000000

#define A_MARINEWEAPON_Dummy           0
#define A_MARINEWEAPON_Fist            1
#define A_MARINEWEAPON_BerserkFist     2
#define A_MARINEWEAPON_Chainsaw        3
#define A_MARINEWEAPON_Pistol          4
#define A_MARINEWEAPON_Shotgun         5
#define A_MARINEWEAPON_SuperShotgun    6
#define A_MARINEWEAPON_Chaingun        7
#define A_MARINEWEAPON_RocketLauncher  8
#define A_MARINEWEAPON_PlasmaRifle     9
#define A_MARINEWEAPON_Railgun        10
#define A_MARINEWEAPON_BFG            11

#define A_APROP_Health        0
#define A_APROP_Speed         1
#define A_APROP_Damage        2
#define A_APROP_Alpha         3
#define A_APROP_RenderStyle   4
#define A_APROP_SeeSound      5
#define A_APROP_AttackSound   6
#define A_APROP_PainSound     7
#define A_APROP_DeathSound    8
#define A_APROP_ActiveSound   9
#define A_APROP_Ambush       10
#define A_APROP_Invulnerable 11
#define A_APROP_JumpZ        12
#define A_APROP_ChaseGoal    13
#define A_APROP_Frightened   14
#define A_APROP_Gravity      15
#define A_APROP_Friendly     16
#define A_APROP_SpawnHealth  17
#define A_APROP_Dropped      18
#define A_APROP_Notarget     19
#define A_APROP_Species      20
#define A_APROP_Nametag      21
#define A_APROP_Score        22
#define A_APROP_Notrigger    23
#define A_APROP_DamageFactor 24
#define A_APROP_MasterTID    25
#define A_APROP_TargetTID    26
#define A_APROP_TracerTID    27
#define A_APROP_Waterlevel   28
#define A_APROP_ScaleX       29
#define A_APROP_ScaleY       30
#define A_APROP_Dormant      31
#define A_APROP_Mass         32
#define A_APROP_Accuracy     33
#define A_APROP_Stamina      34
#define A_APROP_Height       35
#define A_APROP_Radius       36

#define A_STYLE_None                0
#define A_STYLE_Normal              1
#define A_STYLE_Fuzzy               2
#define A_STYLE_SoulTrans           3
#define A_STYLE_OptFuzzy            4
#define A_STYLE_Stencil             5
#define A_STYLE_Translucent        64
#define A_STYLE_Add                65
#define A_STYLE_Shaded             66
#define A_STYLE_TranslucentStencil 67

#define A_LEVELINFO_PAR_TIME        0
#define A_LEVELINFO_CLUSTERNUM      1
#define A_LEVELINFO_LEVELNUM        2
#define A_LEVELINFO_TOTAL_SECRETS   3
#define A_LEVELINFO_FOUND_SECRETS   4
#define A_LEVELINFO_TOTAL_ITEMS     5
#define A_LEVELINFO_FOUND_ITEMS     6
#define A_LEVELINFO_TOTAL_MONSTERS  7
#define A_LEVELINFO_KILLED_MONSTERS 8
#define A_LEVELINFO_SUCK_TIME       9

#define A_PLAYERINFO_TEAM        0
#define A_PLAYERINFO_AIMDIST     1
#define A_PLAYERINFO_COLOR       2
#define A_PLAYERINFO_GENDER      3
#define A_PLAYERINFO_NEVERSWITCH 4
#define A_PLAYERINFO_MOVEBOB     5
#define A_PLAYERINFO_STILLBOB    6
#define A_PLAYERINFO_PLAYERCLASS 7
#define A_PLAYERINFO_FOV         8
#define A_PLAYERINFO_DESIREDFOV  9

#define A_NOT_BOTTOM  0x00000001
#define A_NOT_MIDDLE  0x00000002
#define A_NOT_TOP     0x00000004
#define A_NOT_FLOOR   0x00000008
#define A_NOT_CEILING 0x00000010

#define A_DAMAGE_PLAYERS            0x00000001
#define A_DAMAGE_NONPLAYERS         0x00000002
#define A_DAMAGE_IN_AIR             0x00000004
#define A_DAMAGE_SUBCLASSES_PROTECT 0x00000008

#define A_MRF_OLDEFFECTS        0x00000000
#define A_MRF_ADDSTAMINA        0x00000001
#define A_MRF_FULLHEALTH        0x00000002
#define A_MRF_UNDOBYTOMEOFPOWER 0x00000004
#define A_MRF_UNDOBYCHAOSDEVICE 0x00000008
#define A_MRF_FAILNOTELEFRAG    0x00000010
#define A_MRF_FAILNOLAUGH       0x00000020
#define A_MRF_WHENINVULNERABLE  0x00000040
#define A_MRF_LOSEACTUALWEAPON  0x00000080
#define A_MRF_NEWTIDBEHAVIOUR   0x00000100
#define A_MRF_UNDOBYDEATH       0x00000200
#define A_MRF_UNDOBYDEATHFORCED 0x00000400
#define A_MRF_UNDOBYDEATHSAVES  0x00000800

#define A_ACTOR_NONE       0x00000000
#define A_ACTOR_WORLD      0x00000001
#define A_ACTOR_PLAYER     0x00000002
#define A_ACTOR_BOT        0x00000004
#define A_ACTOR_VOODOODOLL 0x00000008
#define A_ACTOR_MONSTER    0x00000010
#define A_ACTOR_ALIVE      0x00000020
#define A_ACTOR_DEAD       0x00000040
#define A_ACTOR_MISSILE    0x00000080
#define A_ACTOR_GENERIC    0x00000100

#define A_SECSEQ_FLOOR      1
#define A_SECSEQ_CEILING    2
#define A_SECSEQ_FULLHEIGHT 3
#define A_SECSEQ_INTERIOR   4

#define A_AAPTR_DEFAULT                0x00000000
#define A_AAPTR_NULL                   0x00000001
#define A_AAPTR_TARGET                 0x00000002
#define A_AAPTR_MASTER                 0x00000004
#define A_AAPTR_TRACER                 0x00000008
#define A_AAPTR_PLAYER_GETTARGET       0x00000010
#define A_AAPTR_PLAYER_GETCONVERSATION 0x00000020
#define A_AAPTR_PLAYER1                0x00000040
#define A_AAPTR_PLAYER2                0x00000080
#define A_AAPTR_PLAYER3                0x00000100
#define A_AAPTR_PLAYER4                0x00000200
#define A_AAPTR_PLAYER5                0x00000400
#define A_AAPTR_PLAYER6                0x00000800
#define A_AAPTR_PLAYER7                0x00001000
#define A_AAPTR_PLAYER8                0x00002000
#define A_AAPTR_FRIENDPLAYER           0x00004000

#define A_PTROP_UNSAFETARGET 0x00000001
#define A_PTROP_UNSAFEMASTER 0x00000002
#define A_PTROP_NOSAFEGUARDS (PTROP_UNSAFETARGET | PTROP_UNSAFEMASTER)

#define A_TEAM_BLUE 0
#define A_TEAM_RED  1
#define A_NO_TEAM   2

#define A_IS_WAITINGFORPLAYERS 0
#define A_IS_FIRSTCOUNTDOWN    1
#define A_IS_INPROGRESS        2
#define A_IS_BOSSFIGHT         3
#define A_IS_WAVECOMPLETE      4
#define A_IS_COUNTDOWN         5

#define A_CHANGELEVEL_KEEPFACING     0x00000001
#define A_CHANGELEVEL_RESETINVENTORY 0x00000002
#define A_CHANGELEVEL_NOMONSTERS     0x00000004
#define A_CHANGELEVEL_CHANGESKILL    0x00000008
#define A_CHANGELEVEL_NOINTERMISSION 0x00000010
#define A_CHANGELEVEL_RESETHEALTH    0x00000020

#define A_NO_CHANGE 32767.0

#define A_SECF_SILENT          0x00000001
#define A_SECF_NOFALLINGDAMAGE 0x00000002
#define A_SECF_FLOORDROP       0x00000004
#define A_SECF_NORESPAWN       0x00000008

#define A_BLOCKF_CREATURES   0x00000001
#define A_BLOCKF_MONSTERS    0x00000002
#define A_BLOCKF_PLAYERS     0x00000004
#define A_BLOCKF_FLOATERS    0x00000008
#define A_BLOCKF_PROJECTILES 0x00000010
#define A_BLOCKF_EVERYTHING  0x00000020
#define A_BLOCKF_RAILING     0x00000040
#define A_BLOCKF_USE         0x00000080
#define A_BLOCKF_SIGHT       0x00000100

#define A_FOGP_DENSITY        0
#define A_FOGP_OUTSIDEDENSITY 1
#define A_FOGP_SKYFOG         2

#define A_PRINTNAME_LEVELNAME -1
#define A_PRINTNAME_LEVEL     -2
#define A_PRINTNAME_SKILL     -3

#define A_CSF_NOFAKEFLOORS 1
#define A_CSF_NOBLOCKALL   2

// Zandronum Team Property values.
#define A_TPROP_Name           0
#define A_TPROP_Score          1
#define A_TPROP_IsValid        2
#define A_TPROP_NumPlayers     3
#define A_TPROP_NumLivePlayers 4
#define A_TPROP_TextColor      5
#define A_TPROP_PlayerStartNum 6
#define A_TPROP_Spread         7
#define A_TPROP_Carrier        8
#define A_TPROP_Assister       9
#define A_TPROP_FragCount     10
#define A_TPROP_DeathCount    11
#define A_TPROP_WinCount      12
#define A_TPROP_PointCount    13
#define A_TPROP_ReturnTics    14
#define A_TPROP_TeamItem      15
#define A_TPROP_WinnerTheme   16
#define A_TPROP_LoserTheme    17

//
// _A
//
#ifdef __LANG_C__
#define _A(N)
#else
#define _A(N) = (N)
#endif

//
// __asmfunc
//
#ifdef __LANG_DS__
#define __asmfunc __asmfunc
#define __asmcode(CODE) @ __ocode(CODE)
#define __asmcode_imm(CODE) @ __ocode(CODE, CODE##_IMM)
#else
#define __asmfunc
#define __asmcode(CODE) __attribute__((__asmfunc__(CODE)))
#define __asmcode_imm(CODE) __attribute__((__asmfunc__(CODE, CODE##_IMM)))
#endif

//
// __linespec
//
#ifdef __LANG_DS__
#define __linespec __linespec
#define __linecode(N) @ (N)
#else
#define __linespec
#define __linecode(N) __attribute__((__linespec__(N)))
#endif

//
// __native
//
#ifdef __LANG_DS__
#define __native __native
#define __nacode(N) @ (N)
#else
#define __native
#define __nacode(N) __attribute__((__native__(N)))
#endif


//----------------------------------------------------------------------------|
// Global Functions                                                           |
//

//
// Builtins
//

// Actors
__asmfunc int      A_ActivatorTID(void) __asmcode(ACSE_THING_GET_MTAG);
__asmfunc _Bool    A_CheckActorCeilingTexture(int, __string) __asmcode(ACSE_MTAG_CHK_TEXTURE_CEILING);
__asmfunc _Bool    A_CheckActorFloorTexture(int, __string) __asmcode(ACSE_MTAG_CHK_TEXTURE_FLOOR);
__asmfunc int      A_ClassifyActor(int _A(0)) __asmcode(ACSE_MTAG_GET_CLASSIFICATION);
__asmfunc _Accum   A_GetActorAngle(int _A(0)) __asmcode(ACSE_MTAG_GET_ANGLE);
__asmfunc _Accum   A_GetActorCeilingZ(int _A(0)) __asmcode(ACSE_MTAG_GET_CEILINGZ);
__asmfunc _Accum   A_GetActorFloorZ(int _A(0)) __asmcode(ACSE_MTAG_GET_FLOORZ);
__asmfunc int      A_GetActorLightLevel(int _A(0)) __asmcode(ACSE_MTAG_GET_LIGHTLEVEL);
__asmfunc _Accum   A_GetActorPitch(int _A(0)) __asmcode(ACSE_MTAG_GET_PITCH);
__asmfunc int      A_GetActorProperty(int, int) __asmcode(ACSE_MTAG_GET);
__asmfunc _Accum   A_GetActorPropertyFixed(int, int) __asmcode(ACSE_MTAG_GET);
__asmfunc __string A_GetActorPropertyString(int, int) __asmcode(ACSE_MTAG_GET);
__asmfunc _Accum   A_GetActorX(int _A(0)) __asmcode(ACSE_MTAG_GET_X);
__asmfunc _Accum   A_GetActorY(int _A(0)) __asmcode(ACSE_MTAG_GET_Y);
__asmfunc _Accum   A_GetActorZ(int _A(0)) __asmcode(ACSE_MTAG_GET_Z);
__asmfunc int      A_MorphActor(int _A(0), __string _A(""), __string _A(""), int _A(0), int _A(0), __string _A(""), __string _A("")) __asmcode(ACSE_MTAG_MORPH);
__asmfunc void     A_SetActorAngle(int, _Accum) __asmcode(ACSE_MTAG_SET_ANGLE);
__asmfunc void     A_SetActorPitch(int, _Accum) __asmcode(ACSE_MTAG_SET_PITCH);
__asmfunc _Bool    A_SetActorPosition(int, _Accum, _Accum, _Accum, _Bool _A(0)) __asmcode(ACSE_MTAG_SET_XYZ);
__asmfunc void     A_SetActorProperty(int, int, int) __asmcode(ACSE_MTAG_SET);
__asmfunc void     A_SetActorPropertyFixed(int, int, _Accum) __asmcode(ACSE_MTAG_SET);
__asmfunc void     A_SetActorPropertyString(int, int, __string) __asmcode(ACSE_MTAG_SET);
__asmfunc int      A_SetActorState(int, __string, _Bool _A(0)) __asmcode(ACSE_MTAG_SET_STATE);
__asmfunc void     A_SetCameraToTexture(int, __string, int) __asmcode(ACSE_MTAG_SET_CAMERATEXTURE);
__asmfunc void     A_SetMarineSprite(int, __string) __asmcode(ACSE_MTAG_SET_MARINESPRITE);
__asmfunc void     A_SetMarineWeapon(int, int) __asmcode(ACSE_MTAG_SET_MARINEWEAPON);
__asmfunc void     A_SetThingSpecial(int _A(0), int _A(0), int _A(0), int _A(0), int _A(0), int _A(0), int _A(0)) __asmcode(ACSE_MTAG_SET_SPECIAL);
__asmfunc int      A_Thing_Damage2(int, int, __string) __asmcode(ACSE_MTAG_DAMAGE);
__asmfunc int      A_UnMorphActor(int _A(0), _Bool _A(0)) __asmcode(ACSE_MTAG_UNMORPH);

// Display
__asmfunc void     A_CancelFade(void) __asmcode(ACSE_SCREEN_FADE_STOP);
__asmfunc void     A_FadeRange(int, int, int, _Accum, int, int, int, _Accum, _Accum) __asmcode(ACSE_SCREEN_FADE_RANGE);
__asmfunc void     A_FadeTo(int, int, int, _Accum, _Accum) __asmcode(ACSE_SCREEN_FADE_START);
__asmfunc int      A_GetScreenHeight(void) __asmcode(ACSE_SCREEN_GET_HEIGHT);
__asmfunc int      A_GetScreenWidth(void) __asmcode(ACSE_SCREEN_GET_WIDTH);
__asmfunc void     A_SetFont(__string) __asmcode_imm(ACSP_SET_FONT);
__asmfunc void     A_SetHudSize(int, int, int _A(0)) __asmcode(ACSE_SCREEN_SET_HUDSIZE);
__asmfunc void     A_SetMugShotState(__string) __asmcode(ACSE_THING_SET_MUGSHOT);

// Inventory
__asmfunc int      A_CheckActorInventory(int, __string) __asmcode(ACSE_MTAG_GET_INVENTORY);
__asmfunc int      A_CheckInventory(__string) __asmcode_imm(ACSE_THING_GET_INVENTORY);
__asmfunc _Bool    A_CheckWeapon(__string) __asmcode(ACSE_THING_CHK_WEAPON);
__asmfunc void     A_ClearActorInventory(int _A(0)) __asmcode(ACSE_MTAG_CLR_INVENTORY);
__asmfunc void     A_ClearInventory(void) __asmcode(ACSE_THING_CLR_INVENTORY);
__asmfunc int      A_GetAmmoCapacity(__string) __asmcode(ACSE_THING_GET_AMMOCAP);
__asmfunc void     A_GiveActorInventory(int, __string, int) __asmcode(ACSE_MTAG_ADD_INVENTORY);
__asmfunc void     A_GiveInventory(__string, int) __asmcode_imm(ACSE_THING_ADD_INVENTORY);
__asmfunc void     A_SetAmmoCapacity(__string, int) __asmcode(ACSE_THING_SET_AMMOCAP);
__asmfunc _Bool    A_SetWeapon(__string) __asmcode(ACSE_THING_SET_WEAPON);
__asmfunc void     A_TakeActorInventory(int, __string, int) __asmcode(ACSE_MTAG_SUB_INVENTORY);
__asmfunc void     A_TakeInventory(__string, int) __asmcode_imm(ACSE_THING_SUB_INVENTORY);
__asmfunc int      A_UseActorInventory(int, __string) __asmcode(ACSE_MTAG_USEINVENTORY);
__asmfunc _Bool    A_UseInventory(__string) __asmcode(ACSE_THING_USEINVENTORY);

// Level/Game
__asmfunc void     A_ChangeLevel(__string, int _A(0), int _A(0), int _A(-1)) __asmcode(ACSE_GAME_SET_LEVEL);
__asmfunc void     A_ChangeSky(__string, __string) __asmcode(ACSE_GAME_SET_SKY);
__asmfunc int      A_GameSkill(void) __asmcode(ACS_GAME_GET_SKILL);
__asmfunc int      A_GameType(void) __asmcode(ACS_GAME_GET_TYPE);
__asmfunc int      A_GetCVar(__string) __asmcode(ACSE_GAME_GET_CVAR);
__asmfunc _Accum   A_GetCVarFixed(__string) __asmcode(ACSE_GAME_GET_CVAR);
__asmfunc __string A_GetCVarString(__string) __asmcode(ACSE_GAME_GET_CVAR);
__asmfunc int      A_GetLevelInfo(int) __asmcode(ACSE_GAME_GET_LEVELINFO);
__asmfunc int      A_PlayerCount(void) __asmcode(ACS_GAME_GET_PLAYERCOUNT);
__asmfunc void     A_ReplaceTextures(__string, __string, int _A(0)) __asmcode(ACSE_GAME_REPLACETEXTURES);
__asmfunc void     A_SetAirControl(_Accum) __asmcode_imm(ACSE_GAME_SET_AIRCONTROL);
__asmfunc void     A_SetGravity(_Accum) __asmcode_imm(ACSE_GAME_SET_GRAVITY);
__asmfunc int      A_ThingCount(int _A(0), int _A(0)) __asmcode_imm(ACS_GAME_GET_THINGCOUNT_SID);
__asmfunc int      A_ThingCountName(__string, int _A(0)) __asmcode(ACSE_GAME_GET_THINGCOUNT_STR);
__asmfunc int      A_Timer(void) __asmcode(ACS_GAME_GET_TIME);

// Lines
__asmfunc void     A_ClearLineSpecial(void) __asmcode(ACS_LINE_CLR_SPECIAL);
__asmfunc int      A_GetLineRowOffset(void) __asmcode(ACSE_LINE_GET_OFFSETY);
__asmfunc void     A_SetLineBlocking(int, int _A(0)) __asmcode(ACS_LTAG_SET_BLOCK);
__asmfunc int      A_LineSide(void) __asmcode(ACS_LINE_GET_SIDE);
__asmfunc void     A_SetLineMonsterBlocking(int, int _A(0)) __asmcode(ACSE_LTAG_SET_BLOCKMONSTER);
__asmfunc void     A_SetLineSpecial(int, int _A(0), int _A(0), int _A(0), int _A(0), int _A(0), int _A(0)) __asmcode(ACS_LTAG_SET_SPECIAL);
__asmfunc void     A_SetLineTexture(int, int, int, __string) __asmcode(ACS_LTAG_SET_TEXTURE);

// Math
__asmfunc _Accum   A_Cos(_Accum) __asmcode(TRIG_COS_X);
__asmfunc _Accum   A_FixedDiv(_Accum, _Accum) __asmcode(DIV_STK_X);
__asmfunc _Accum   A_FixedMul(_Accum, _Accum) __asmcode(MUL_STK_X);
__asmfunc int      A_Random(int, int) __asmcode_imm(ACS_MISC_RANDOM);
__asmfunc _Accum   A_RandomFixed(_Accum, _Accum) __asmcode_imm(ACS_MISC_RANDOM);
__asmfunc _Accum   A_Sin(_Accum) __asmcode(TRIG_SIN_X);
__asmfunc _Accum   A_VectorAngle(_Accum, _Accum) __asmcode(ACSE_TRIG_VECTORANGLE);

// Miscellaneous
__asmfunc void     A_CreateTranslationStart(int transnumber) __asmcode(ACSE_TRANSLATION_START);
__asmfunc void     A_CreateTranslationDesat(int a, int b, _Accum r1, _Accum g1, _Accum b1, _Accum r2, _Accum g2, _Accum b2) __asmcode(ACSE_TRANSLATION_DESAT);
__asmfunc void     A_CreateTranslationPalette(int a, int b, int c, int d) __asmcode(ACSE_TRANSLATION_PALETTE);
__asmfunc void     A_CreateTranslationRGB(int a, int b, int r1, int g1, int b1, int r2, int g2, int b2) __asmcode(ACSE_TRANSLATION_RGB);
__asmfunc void     A_CreateTranslationEnd(void) __asmcode(ACSE_TRANSLATION_END);
__asmfunc void     A_SetResultValue(int) __asmcode(SET_SCRRET);

// Players
__asmfunc int      A_CheckPlayerCamera(int) __asmcode(ACSE_PLAYER_GET_CAMERA);
__asmfunc int      A_GetPlayerInfo(int, int) __asmcode(ACSE_PLAYER_GET_INFO);
__asmfunc int      A_GetPlayerInput(int, int) __asmcode(ACSE_PLAYER_GET_INPUT);
__asmfunc _Accum   A_GetPlayerInputFixed(int, int) __asmcode(ACSE_PLAYER_GET_INPUT);
__asmfunc int      A_PlayerClass(int) __asmcode(ACSE_PLAYER_GET_CLASS);
__asmfunc int      A_PlayerFrags(void) __asmcode(ACSE_THING_GET_FRAGS);
__asmfunc _Bool    A_PlayerInGame(int) __asmcode(ACSE_PLAYER_GET_INGAME);
__asmfunc _Bool    A_PlayerIsBot(int) __asmcode(ACSE_PLAYER_GET_ISBOT);
__asmfunc int      A_PlayerNumber(void) __asmcode(ACSE_THING_GET_PLAYERNUMBER);

// Sectors
__asmfunc void     A_ChangeCeiling(int, __string) __asmcode_imm(ACS_STAG_SET_TEXTURE_CEILING);
__asmfunc void     A_ChangeFloor(int, __string) __asmcode_imm(ACS_STAG_SET_TEXTURE_FLOOR);
__asmfunc _Accum   A_GetSectorCeilingZ(int, int _A(0), int _A(0)) __asmcode(ACSE_STAG_GET_Z_CEILING);
__asmfunc _Accum   A_GetSectorFloorZ(int, int _A(0), int _A(0)) __asmcode(ACSE_STAG_GET_Z_FLOOR);
__asmfunc int      A_GetSectorLightLevel(int) __asmcode(ACSE_STAG_GET_LIGHTLEVEL);
__asmfunc void     A_SectorDamage(int, int, __string, __string, int) __asmcode(ACSE_STAG_DAMAGE);
__asmfunc void     A_SetCeilingTrigger(int, int, int _A(0), int _A(0), int _A(0), int _A(0), int _A(0), int _A(0)) __asmcode(ACSE_STAG_SET_TRIGGER_CEILING);
__asmfunc void     A_SetFloorTrigger(int, int, int _A(0), int _A(0), int _A(0), int _A(0), int _A(0), int _A(0)) __asmcode(ACSE_STAG_SET_TRIGGER_FLOOR);
__asmfunc int      A_ThingCountNameSector(__string, int, int) __asmcode(ACSE_STAG_GET_THINGCOUNT_STR);
__asmfunc int      A_ThingCountSector(int, int, int) __asmcode(ACSE_STAG_GET_THINGCOUNT_SID);

// Sounds
__asmfunc void     A_ActivatorSound(__string, int _A(127)) __asmcode(ACSE_SOUND_THING);
__asmfunc void     A_AmbientSound(__string, int _A(127)) __asmcode(ACS_SOUND_AMBIENT);
__asmfunc void     A_LocalAmbientSound(__string, int _A(127)) __asmcode(ACSE_SOUND_AMBIENTLOCAL);
__asmfunc void     A_LocalSetMusic(__string, int _A(0), int _A(0)) __asmcode_imm(ACSE_GAME_SET_MUSICLOCAL);
__asmfunc void     A_SectorSound(__string, int _A(127)) __asmcode(ACS_SOUND_SECTOR);
__asmfunc void     A_SetMusic(__string, int _A(0), int _A(0)) __asmcode_imm(ACSE_GAME_SET_MUSIC);
__asmfunc void     A_SoundSequence(__string) __asmcode(ACS_SOUND_SEQUENCE);
__asmfunc void     A_ThingSound(int, __string, int _A(127)) __asmcode(ACS_SOUND_MTAG);

// Spawning
__asmfunc int      A_Spawn(__string, _Accum, _Accum, _Accum, int _A(0), int _A(0)) __asmcode_imm(ACSE_SPAWN_POINT);
__asmfunc void     A_SpawnProjectile(int, __string, int, int, int _A(0), int _A(0), int _A(0)) __asmcode(ACSE_SPAWN_PROJECTILE_STR);
__asmfunc int      A_SpawnSpot(__string, int, int _A(0), int _A(0)) __asmcode_imm(ACSE_SPAWN_SPOT_ANGLE);
__asmfunc int      A_SpawnSpotFacing(__string, int, int _A(0)) __asmcode(ACSE_SPAWN_SPOT);
__asmfunc void     A_Thing_Projectile2(int, int, int, int, int _A(0), int _A(0), int _A(0)) __asmcode(ACSE_SPAWN_PROJECTILE_SID);

// Strings
__asmfunc _Bool    A_StrCpy(char *dst, int dstArray, int, int dstSize, __string src, int srcOffset _A(0)) __asmcode(ACSE_STRING_COPY_GLOBALRANGE);
__asmfunc _Bool    A_StrCpyMap(int dstIndex, int dstArray, int, int dstSize, __string src, int srcOffset _A(0)) __asmcode(ACSE_STRING_COPY_MAPRANGE);
__asmfunc _Bool    A_StrCpyWorld(int dstIndex, int dstArray, int, int dstSize, __string src, int srcOffset _A(0)) __asmcode(ACSE_STRING_COPY_WORLDRANGE);
__asmfunc _Bool    A_StrCpyGlobal(int dstIndex, int dstArray, int, int dstSize, __string src, int srcOffset _A(0)) __asmcode(ACSE_STRING_COPY_GLOBALRANGE);
__asmfunc _Bool    A_StrLen(__string) __asmcode(ACSE_STRING_GET_LENGTH);

// Waiting
__asmfunc void     A_Delay(int) __asmcode_imm(ACS_WAIT_TICS);
__asmfunc void     A_PolyWait(int) __asmcode_imm(ACS_WAIT_POLYOBJECT);
__asmfunc void     A_ScriptWait(int) __asmcode_imm(ACS_WAIT_SCRIPT);
__asmfunc void     A_Suspend(void) __asmcode(JMP_HLT);
__asmfunc void     A_TagWait(int) __asmcode_imm(ACS_WAIT_STAG);

//
// Line Specials
//

//linespec void     A_Polyobj_StartLine(int, int, int, int) __linecode(1);
__linespec void     A_Polyobj_RotateLeft(int, int, int) __linecode(2);
__linespec void     A_Polyobj_RotateRight(int, int, int) __linecode(3);
__linespec void     A_Polyobj_Move(int, int, int, int) __linecode(4);
//linespec void     A_PolyObj_ExplicitLine(int, int, int, int, int) __linecode(5);
__linespec void     A_PolyObj_MoveTimes8(int, int, int, int) __linecode(6);
__linespec void     A_PolyObj_DoorSwing(int, int, int, int) __linecode(7);
__linespec void     A_PolyObj_DoorSlide(int, int, int, int, int) __linecode(8);
//linespec void     A_Line_Horizon(void) __linecode(9);
__linespec void     A_Door_Close(int, int) __linecode(10);
__linespec void     A_Door_Open(int, int) __linecode(11);
__linespec void     A_Door_Open(int, int, int) __linecode(11);
__linespec void     A_Door_Raise(int, int, int) __linecode(12);
__linespec void     A_Door_Raise(int, int, int, int) __linecode(12);
__linespec void     A_Door_LockedRaise(int, int, int, int) __linecode(13);
__linespec void     A_Door_LockedRaise(int, int, int, int, int) __linecode(13);
__linespec void     A_Door_Animated(int, int, int) __linecode(14);
__linespec void     A_Autosave(void) __linecode(15);
//linespec void     A_Transfer_WallLight(int, int) __linecode(16);
__linespec void     A_Thing_Raise(int) __linecode(17);
__linespec void     A_StartConversation(int) __linecode(18);
__linespec void     A_StartConversation(int, int) __linecode(18);
__linespec void     A_Thing_Stop(int) __linecode(19);
__linespec void     A_Floor_LowerByValue(int, int, int) __linecode(20);
__linespec void     A_Floor_LowerToLowest(int, int) __linecode(21);
__linespec void     A_Floor_LowerToNearest(int, int) __linecode(22);
__linespec void     A_Floor_RaiseByValue(int, int, int) __linecode(23);
__linespec void     A_Floor_RaiseToHighest(int, int) __linecode(24);
__linespec void     A_Floor_RaiseToNearest(int, int) __linecode(25);
__linespec void     A_Stairs_BuildDown(int, int, int, int, int) __linecode(26);
__linespec void     A_Stairs_BuildUp(int, int, int, int, int) __linecode(27);
__linespec void     A_Floor_RaiseAndCrush(int, int, int) __linecode(28);
__linespec void     A_Floor_RaiseAndCrush(int, int, int, int) __linecode(28);
__linespec void     A_Pillar_Build(int, int, int) __linecode(29);
__linespec void     A_Pillar_Open(int, int, int, int) __linecode(30);
__linespec void     A_Stairs_BuildDownSync(int, int, int, int) __linecode(31);
__linespec void     A_Stairs_BuildUpSync(int, int, int, int) __linecode(32);
__linespec void     A_ForceField(void) __linecode(33);
__linespec void     A_ClearForceField(int) __linecode(34);
__linespec void     A_Floor_RaiseByValueTimes8(int, int, int) __linecode(35);
__linespec void     A_Floor_LowerByValueTimes8(int, int, int) __linecode(36);
__linespec void     A_Floor_MoveToValue(int, int, int) __linecode(37);
__linespec void     A_Floor_MoveToValue(int, int, int, int) __linecode(37);
__linespec void     A_Ceiling_Waggle(int, int, int, int, int) __linecode(38);
__linespec void     A_Teleport_ZombieChanger(int, int) __linecode(39);
__linespec void     A_Ceiling_LowerByValue(int, int, int) __linecode(40);
__linespec void     A_Ceiling_RaiseByValue(int, int, int) __linecode(41);
__linespec void     A_Ceiling_CrushAndRaise(int, int, int) __linecode(42);
__linespec void     A_Ceiling_CrushAndRaise(int, int, int, int) __linecode(42);
__linespec void     A_Ceiling_LowerAndCrush(int, int, int) __linecode(43);
__linespec void     A_Ceiling_LowerAndCrush(int, int, int, int) __linecode(43);
__linespec void     A_Ceiling_CrushStop(int) __linecode(44);
__linespec void     A_Ceiling_CrushRaiseAndStay(int, int, int) __linecode(45);
__linespec void     A_Ceiling_CrushRaiseAndStay(int, int, int, int) __linecode(45);
__linespec void     A_Floor_CrushStop(int) __linecode(46);
__linespec void     A_Ceiling_MoveToValue(int, int, int) __linecode(47);
__linespec void     A_Ceiling_MoveToValue(int, int, int, int) __linecode(47);
//linespec void     A_Sector_Attach3dMidtex(int, int, int) __linecode(48);
__linespec void     A_GlassBreak(void) __linecode(49);
__linespec void     A_GlassBreak(int) __linecode(49);
//linespec void     A_ExtraFloor_LightOnly(int, int) __linecode(50);
__linespec void     A_Sector_SetLink(int, int, int, int) __linecode(51);
__linespec void     A_Scroll_Wall(int, int, int, int, int) __linecode(52);
__linespec void     A_Line_SetTextureOffset(int, int, int, int, int) __linecode(53);
__linespec void     A_Sector_ChangeFlags(int, int, int) __linecode(54);
__linespec void     A_Line_SetBlocking(int, int, int) __linecode(55);
__linespec void     A_Line_SetTextureScale(int, int, int, int, int) __linecode(56);
//linespec void     A_Sector_SetPortal(int, int, int, int, int) __linecode(57);
//linespec void     A_Sector_CopyScroller(int, int) __linecode(58);
__linespec void     A_Polyobj_OR_MoveToSpot(int, int, int) __linecode(59);
__linespec void     A_Plat_PerpetualRaise(int, int, int) __linecode(60);
__linespec void     A_Plat_Stop(int) __linecode(61);
__linespec void     A_Plat_DownWaitUpStay(int, int, int) __linecode(62);
__linespec void     A_Plat_DownByValue(int, int, int, int) __linecode(63);
__linespec void     A_Plat_UpWaitDownStay(int, int, int) __linecode(64);
__linespec void     A_PlatUpByValue(int, int, int, int) __linecode(65);
__linespec void     A_Floor_LowerInsant(int, int, int) __linecode(66);
__linespec void     A_Floor_RaiseInsant(int, int, int) __linecode(67);
__linespec void     A_Floor_MoveToValueTimes8(int, int, int, int) __linecode(68);
__linespec void     A_Ceiling_MoveToValueTimes8(int, int, int, int) __linecode(69);
__linespec void     A_Teleport(int) __linecode(70);
__linespec void     A_Teleport(int, int) __linecode(70);
__linespec void     A_Teleport(int, int, int) __linecode(70);
__linespec void     A_Teleport_NoFog(int) __linecode(71);
__linespec void     A_Teleport_NoFog(int, int) __linecode(71);
__linespec void     A_Teleport_NoFog(int, int, int) __linecode(71);
__linespec void     A_ThrustThing(int, int) __linecode(72);
__linespec void     A_ThrustThing(int, int, int) __linecode(72);
__linespec void     A_ThrustThing(int, int, int, int) __linecode(72);
__linespec void     A_DamageThing(int) __linecode(73);
__linespec void     A_DamageThing(int, int) __linecode(73);
__linespec void     A_Teleport_NewMap(int, int) __linecode(74);
__linespec void     A_Teleport_NewMap(int, int, int) __linecode(74);
__linespec void     A_Teleport_EndGame(void) __linecode(75);
__linespec void     A_TeleportOther(int, int, int) __linecode(76);
__linespec void     A_TeleportGroup(int, int, int, int, int) __linecode(77);
__linespec void     A_TeleportInSector(int, int, int, int) __linecode(78);
__linespec void     A_TeleportInSector(int, int, int, int, int) __linecode(78);
__linespec void     A_Thing_SetConversation(int, int) __linecode(79);
__linespec void     ACS_Execute(int, int) __linecode(80);
__linespec void     ACS_Execute(int, int, int) __linecode(80);
__linespec void     ACS_Execute(int, int, int, int) __linecode(80);
__linespec void     ACS_Execute(int, int, int, int, int) __linecode(80);
__linespec void     ACS_Suspend(int, int) __linecode(81);
__linespec void     ACS_Terminate(int, int) __linecode(82);
__linespec void     ACS_LockedExecute(int, int, int, int, int) __linecode(83);
__linespec int      ACS_ExecuteWithResult(int) __linecode(84);
__linespec int      ACS_ExecuteWithResult(int, int) __linecode(84);
__linespec int      ACS_ExecuteWithResult(int, int, int) __linecode(84);
__linespec int      ACS_ExecuteWithResult(int, int, int, int) __linecode(84);
__linespec int      ACS_ExecuteWithResult(int, int, int, int, int) __linecode(84);
__linespec _Accum   ACS_ExecuteWithResultFixed(int) __linecode(84);
__linespec _Accum   ACS_ExecuteWithResultFixed(int, int) __linecode(84);
__linespec _Accum   ACS_ExecuteWithResultFixed(int, int, int) __linecode(84);
__linespec _Accum   ACS_ExecuteWithResultFixed(int, int, int, int) __linecode(84);
__linespec _Accum   ACS_ExecuteWithResultFixed(int, int, int, int, int) __linecode(84);
__linespec void     ACS_LockedExecuteDoor(int, int, int, int, int) __linecode(85);
__linespec void     A_Polyobj_MoveToSpot(int, int, int) __linecode(86);
__linespec void     A_Polyobj_Stop(int) __linecode(87);
__linespec void     A_Polyobj_MoveTo(int, int, int, int) __linecode(88);
__linespec void     A_Polyobj_OR_MoveTo(int, int, int, int) __linecode(89);
__linespec void     A_Polyobj_OR_RotateLeft(int, int, int) __linecode(90);
__linespec void     A_Polyobj_OR_RotateRight(int, int, int) __linecode(91);
__linespec void     A_Polyobj_OR_Move(int, int, int, int) __linecode(92);
__linespec void     A_Polyobj_OR_MoveTimes8(int, int, int, int) __linecode(93);
__linespec void     A_Pillar_BuildAndCrush(int, int, int, int) __linecode(94);
__linespec void     A_Pillar_BuildAndCrush(int, int, int, int, int) __linecode(94);
__linespec void     A_FloorAndCeiling_LowerByValue(int, int, int) __linecode(95);
__linespec void     A_FloorAndCeiling_RaiseByValue(int, int, int) __linecode(96);
__linespec void     A_Ceiling_LowerAndCrushDist(int, int, int) __linecode(97);
__linespec void     A_Ceiling_LowerAndCrushDist(int, int, int, int) __linecode(97);
__linespec void     A_Ceiling_LowerAndCrushDist(int, int, int, int, int) __linecode(97);
__linespec void     A_Sector_SetTranslucent(int, int, int) __linecode(98);
__linespec void     A_Sector_SetTranslucent(int, int, int, int) __linecode(98);

//linespec void     A_Scroll_Texture_Left(int, int) __linecode(100);
//linespec void     A_Scroll_Texture_Right(int, int) __linecode(101);
//linespec void     A_Scroll_Texture_Up(int, int) __linecode(102);
//linespec void     A_Scroll_Texture_Down(int, int) __linecode(103);

__linespec void     A_Light_ForceLightning(int) __linecode(109);
__linespec void     A_Light_RaiseByValue(int, int) __linecode(110);
__linespec void     A_Light_LowerByValue(int, int) __linecode(111);
__linespec void     A_Light_ChangeToValue(int, int) __linecode(112);
__linespec void     A_Light_Fade(int, int, int) __linecode(113);
__linespec void     A_Light_Glow(int, int, int, int) __linecode(114);
__linespec void     A_Light_Flicker(int, int, int) __linecode(115);
__linespec void     A_Light_Strobe(int, int, int, int, int) __linecode(116);
__linespec void     A_Light_Stop(int) __linecode(117);
//linespec void     A_Plane_Copy(int, int, int, int, int) __linecode(118);
__linespec void     A_Thing_Damage(int, int) __linecode(119);
__linespec void     A_Thing_Damage(int, int, int) __linecode(119);
__linespec void     A_Radius_Quake(int, int, int, int, int) __linecode(120);
//linespec void     A_Line_SetIdentification(int) __linecode(121);
//linespec void     A_Line_SetIdentification(int, int) __linecode(121);
//linespec void     A_Line_SetIdentification(int, int, int, int, int) __linecode(121);

__linespec void     A_Thing_Move(int, int) __linecode(125);
__linespec void     A_Thing_Move(int, int, int) __linecode(125);

__linespec void     A_Thing_SetSpecial(int, int) __linecode(127);
__linespec void     A_Thing_SetSpecial(int, int, int) __linecode(127);
__linespec void     A_Thing_SetSpecial(int, int, int, int) __linecode(127);
__linespec void     A_Thing_SetSpecial(int, int, int, int, int) __linecode(127);
__linespec void     A_ThrustThingZ(int, int, int, int) __linecode(128);
//linespec void     A_UsePuzzleItem(int, int) __linecode(129);
//linespec void     A_UsePuzzleItem(int, int, int) __linecode(129);
//linespec void     A_UsePuzzleItem(int, int, int, int) __linecode(129);
//linespec void     A_UsePuzzleItem(int, int, int, int, int) __linecode(129);
__linespec void     A_Thing_Activate(int) __linecode(130);
__linespec void     A_Thing_Deactivate(int) __linecode(131);
__linespec void     A_Thing_Remove(int) __linecode(132);
__linespec void     A_Thing_Destroy(int) __linecode(133);
__linespec void     A_Thing_Destroy(int, int) __linecode(133);
__linespec void     A_Thing_Destroy(int, int, int) __linecode(133);
__linespec void     A_Thing_Projectile(int, int, int, int, int) __linecode(134);
__linespec void     A_Thing_Spawn(int, int, int) __linecode(135);
__linespec void     A_Thing_Spawn(int, int, int, int) __linecode(135);
__linespec void     A_Thing_ProjectileGravity(int, int, int, int, int) __linecode(136);
__linespec void     A_Thing_SpawnNoFog(int, int, int) __linecode(137);
__linespec void     A_Thing_SpawnNoFog(int, int, int, int) __linecode(137);
__linespec void     A_Floor_Waggle(int, int, int, int, int) __linecode(138);
__linespec void     A_Thing_SpawnFacing(int, int) __linecode(139);
__linespec void     A_Thing_SpawnFacing(int, int, int) __linecode(139);
__linespec void     A_Thing_SpawnFacing(int, int, int, int) __linecode(139);
__linespec void     A_Sector_ChangeSound(int, int) __linecode(140);

__linespec void     A_Player_RemoveItem(int, int) __linecode(143);
__linespec void     A_Player_GiveItem(int, int) __linecode(144);
__linespec void     A_Player_SetTeam(int) __linecode(145);

__linespec void     A_Team_Score(int, int) __linecode(152);
__linespec void     A_Team_GivePoints(int, int, int) __linecode(153);
__linespec void     A_Teleport_NoStop(int, int) __linecode(154);
__linespec void     A_Teleport_NoStop(int, int, int) __linecode(154);

__linespec void     A_SetGlobalFogParameter(int, int) __linecode(157);
__linespec void     A_FS_Execute(int) __linecode(158);
__linespec void     A_FS_Execute(int, int) __linecode(158);
__linespec void     A_FS_Execute(int, int, int) __linecode(158);
__linespec void     A_FS_Execute(int, int, int, int) __linecode(158);
__linespec void     A_Sector_SetPlaneReflection(int, int, int) __linecode(159);
//linespec void     A_Sector_Set3DFloor(int, int, int, int, int) __linecode(160);
//linespec void     A_Sector_SetContents(int, int, int) __linecode(161);

__linespec void     A_Ceiling_CrushAndRaiseDist(int, int, int) __linecode(168);
__linespec void     A_Ceiling_CrushAndRaiseDist(int, int, int, int) __linecode(168);
__linespec void     A_Ceiling_CrushAndRaiseDist(int, int, int, int, int) __linecode(168);
__linespec void     A_Generic_Crusher2(int, int, int, int, int) __linecode(169);
__linespec void     A_Sector_SetCeilingScale2(int, int, int) __linecode(170);
__linespec void     A_SectorSetFloorScale2(int, int, int) __linecode(171);
__linespec void     A_Plat_UpNearestWaitDownStay(int, int, int) __linecode(172);
__linespec void     A_NoiseAlert(int, int) __linecode(173);
__linespec void     A_SendToCommunicator(int, int, int, int) __linecode(174);
__linespec void     A_Thing_ProjectileIntercept(int, int, int, int, int) __linecode(175);
__linespec void     A_Thing_ChangeTID(int, int) __linecode(176);
__linespec void     A_Thing_Hate(int, int) __linecode(177);
__linespec void     A_Thing_Hate(int, int, int) __linecode(177);
__linespec void     A_Thing_ProjectileAimed(int, int, int, int) __linecode(178);
__linespec void     A_Thing_ProjectileAimed(int, int, int, int, int) __linecode(178);
__linespec void     A_ChangeSkill(int) __linecode(179);
__linespec void     A_Thing_SetTranslation(int, int) __linecode(180);
//linespec void     A_Plane_Align(int, int, int) __linecode(181);
//linespec void     A_Line_Mirror(void) __linecode(182);
__linespec void     A_Line_AlignCeiling(int, int) __linecode(183);
__linespec void     A_Line_AlignFloor(int, int) __linecode(184);
__linespec void     A_Sector_SetRotation(int, int, int) __linecode(185);
__linespec void     A_Sector_SetCeilingPanning(int, int, int, int, int) __linecode(186);
__linespec void     A_Sector_SetFloorPanning(int, int, int, int, int) __linecode(187);
__linespec void     A_Sector_SetCeilingScale(int, int, int, int, int) __linecode(188);
__linespec void     A_Sector_SetFloorScale(int, int, int, int, int) __linecode(189);
//linespec void     A_Static_Init(int, int, int, int) __linecode(190);
__linespec void     A_SetPlayerProperty(int, int, int) __linecode(191);
__linespec void     A_Ceiling_LowerToHighestFloor(int, int) __linecode(192);
__linespec void     A_Ceiling_LowerInstant(int, int, int) __linecode(193);
__linespec void     A_Ceiling_RaiseInstant(int, int, int) __linecode(194);
__linespec void     A_Ceiling_CrushRaiseAndStayA(int, int, int, int) __linecode(195);
__linespec void     A_Ceiling_CrushRaiseAndStayA(int, int, int, int, int) __linecode(195);
__linespec void     A_Ceiling_CrushAndRaiseA(int, int, int, int) __linecode(196);
__linespec void     A_Ceiling_CrushAndRaiseA(int, int, int, int, int) __linecode(196);
__linespec void     A_Ceiling_CrushAndRaiseSilentA(int, int, int, int) __linecode(197);
__linespec void     A_Ceiling_CrushAndRaiseSilentA(int, int, int, int, int) __linecode(197);
__linespec void     A_Ceiling_RaiseByValueTimes8(int, int, int) __linecode(198);
__linespec void     A_Ceiling_LowerByValueTimes8(int, int, int) __linecode(199);
__linespec void     A_Generic_Floor(int, int, int, int, int) __linecode(200);
__linespec void     A_Generic_Ceiling(int, int, int, int, int) __linecode(201);
__linespec void     A_Generic_Door(int, int, int, int, int) __linecode(202);
__linespec void     A_Generic_Lift(int, int, int, int, int) __linecode(203);
__linespec void     A_Generic_Stairs(int, int, int, int, int) __linecode(204);
__linespec void     A_Generic_Crusher(int, int, int, int, int) __linecode(205);
__linespec void     A_Plat_DownWaitUpStayLip(int, int, int, int) __linecode(206);
__linespec void     A_Plat_DownWaitUpStayLip(int, int, int, int, int) __linecode(206);
__linespec void     A_Plat_PerpetualRaiseLip(int, int, int, int) __linecode(207);
__linespec void     A_TranslucentLine(int, int) __linecode(208);
__linespec void     A_TranslucentLine(int, int, int) __linecode(208);
//linespec void     A_Transfer_Heights(int, int) __linecode(209);
//linespec void     A_Transfer_FloorLight(int) __linecode(210);
//linespec void     A_Transfer_CeilingLight(int) __linecode(211);
__linespec void     A_Sector_SetColor(int, int, int, int) __linecode(212);
__linespec void     A_Sector_SetColor(int, int, int, int, int) __linecode(212);
__linespec void     A_Sector_SetFade(int, int, int, int) __linecode(213);
__linespec void     A_Sector_SetDamage(int, int, int) __linecode(214);
//linespec void     A_Teleport_Line(int, int, int) __linecode(215);
__linespec void     A_Sector_SetGravity(int, int, int) __linecode(216);
__linespec void     A_Stairs_BuildUpDoom(int, int, int, int, int) __linecode(217);
__linespec void     A_Sector_SetWind(int, int, int, int) __linecode(218);
__linespec void     A_Sector_SetFriction(int, int) __linecode(219);
__linespec void     A_Sector_SetCurrent(int, int, int, int) __linecode(220);
__linespec void     A_Scroll_Texture_Both(int, int, int, int, int) __linecode(221);
//linespec void     A_Scroll_Texture_Model(int, int) __linecode(222);
__linespec void     A_Scroll_Floor(int, int, int, int) __linecode(223);
__linespec void     A_Scroll_Ceiling(int, int, int, int) __linecode(224);
//linespec void     A_Scroll_Texture_Offsets(int) __linecode(225);
__linespec void     A_ACS_ExecuteAlways(int, int) __linecode(226);
__linespec void     A_ACS_ExecuteAlways(int, int, int) __linecode(226);
__linespec void     A_ACS_ExecuteAlways(int, int, int, int) __linecode(226);
__linespec void     A_ACS_ExecuteAlways(int, int, int, int, int) __linecode(226);
//linespec void     A_PointPush_SetForce(int, int, int, int) __linecode(227);
__linespec void     A_Plat_RaiseAndStarTx0(int, int) __linecode(228);
__linespec void     A_Thing_SetGoal(int, int, int) __linecode(229);
__linespec void     A_Thing_SetGoal(int, int, int, int) __linecode(229);
__linespec void     A_Plat_UpByValueStayTx(int, int, int) __linecode(230);
__linespec void     A_Plat_ToggleCeiling(int) __linecode(231);
__linespec void     A_Light_StrobeDoom(int, int, int) __linecode(232);
__linespec void     A_Light_MinNeighbor(int) __linecode(233);
__linespec void     A_Light_MaxNeighbor(int) __linecode(234);
__linespec void     A_Floor_TransferTrigger(int) __linecode(235);
__linespec void     A_Floor_TransferNumeric(int) __linecode(236);
__linespec void     A_ChangeCamera(int, int, int) __linecode(237);
__linespec void     A_Floor_RaiseToLowestCeiling(int, int) __linecode(238);
__linespec void     A_Floor_RaiseByValueTxTy(int, int, int) __linecode(239);
__linespec void     A_Floor_RaiseByTexture(int, int) __linecode(240);
__linespec void     A_Floor_LowerToLowestTxTy(int, int) __linecode(241);
__linespec void     A_Floor_LowerToHighest(int, int, int) __linecode(242);
__linespec void     A_Floor_LowerToHighest(int, int, int, int) __linecode(242);
__linespec void     A_Exit_Normal(int) __linecode(243);
__linespec void     A_Exit_Secret(int) __linecode(244);
__linespec void     A_Elevator_RaiseToNearest(int, int) __linecode(245);
__linespec void     A_Elevator_MoveToFloor(int, int) __linecode(246);
__linespec void     A_Elevator_LowerToNearest(int, int) __linecode(247);
__linespec void     A_HealThing(int) __linecode(248);
__linespec void     A_HealThing(int, int) __linecode(248);
__linespec void     A_Door_CloseWaitOpen(int, int, int) __linecode(249);
__linespec void     A_Door_CloseWaitOpen(int, int, int, int) __linecode(249);
__linespec void     A_Floor_Donut(int, int, int) __linecode(250);
__linespec void     A_FloorAndCeiling_LowerRaise(int, int, int)__linecode(251);
__linespec void     A_Ceiling_RaiseToNearest(int, int) __linecode(252);
__linespec void     A_Ceiling_LowerToLowest(int, int) __linecode(253);
__linespec void     A_Ceiling_LowerToFloor(int, int) __linecode(254);
__linespec void     A_Ceiling_CrushRaiseAndStaySilA(int, int, int, int) __linecode(255);
__linespec void     A_Ceiling_CrushRaiseAndStaySilA(int, int, int, int, int) __linecode(255);

//
// Natives
//

__native int      A_GetLineUDMFInt(int, __string) __nacode(1);
__native _Accum   A_GetLineUDMFFixed(int, __string) __nacode(2);
__native int      A_GetThingUDMFInt(int, __string) __nacode(3);
__native _Accum   A_GetThingUDMFFixed(int, __string) __nacode(4);
__native int      A_GetSectorUDMFInt(int, __string) __nacode(5);
__native _Accum   A_GetSectorUDMFFixed(int, __string) __nacode(6);
__native int      A_GetSideUDMFInt(int, _Bool, __string) __nacode(7);
__native _Accum   A_GetSideUDMFFixed(int, _Bool, __string) __nacode(8);
__native _Accum   A_GetActorVelX(int) __nacode(9);
__native _Accum   A_GetActorVelY(int) __nacode(10);
__native _Accum   A_GetActorVelZ(int) __nacode(11);
__native _Bool    A_SetActivator(int) __nacode(12);
__native _Bool    A_SetActivator(int, int) __nacode(12);
__native _Bool    A_SetActivatorToTarget(int) __nacode(13);
__native _Accum   A_GetActorViewHeight(int) __nacode(14);
__native char     A_GetChar(__string, int) __nacode(15);
__native int      A_GetAirSupply(int) __nacode(16);
__native _Bool    A_SetAirSupply(int, int) __nacode(17);
__native void     A_SetSkyScrollSpeed(int, _Accum) __nacode(18);
__native int      A_GetArmorType(__string, int) __nacode(19);
__native int      A_SpawnSpotForced(__string, int) __nacode(20);
__native int      A_SpawnSpotForced(__string, int, int) __nacode(20);
__native int      A_SpawnSpotForced(__string, int, int, int) __nacode(20);
__native int      A_SpawnSpotFacingForced(__string, int) __nacode(21);
__native int      A_SpawnSpotFacingForced(__string, int, int) __nacode(21);
__native _Bool    A_CheckActorProperty(int, int, int) __nacode(22);
__native _Bool    A_CheckActorPropertyFixed(int, int, _Accum) __nacode(22);
__native _Bool    A_CheckActorPropertyString(int, int, __string) __nacode(22);
__native void     A_SetActorVelocity(int, _Accum, _Accum, _Accum) __nacode(23);
__native void     A_SetActorVelocity(int, _Accum, _Accum, _Accum, _Bool) __nacode(23);
__native void     A_SetActorVelocity(int, _Accum, _Accum, _Accum, _Bool, _Bool) __nacode(23);
__native void     A_SetUserVariable(int, __string, int) __nacode(24);
__native void     A_SetUserVariableFixed(int, __string, _Accum) __nacode(24);
__native int      A_GetUserVariable(int, __string) __nacode(25);
__native _Accum   A_GetUserVariableFixed(int, __string) __nacode(25);
__native void     A_Radius_Quake2(int, int, int, int, int, __string) __nacode(26);
__native _Bool    A_CheckActorClass(int, __string) __nacode(27);
__native void     A_SetUserArray(int, __string, int, int) __nacode(28);
__native void     A_SetUserArrayFixed(int, __string, int, _Accum) __nacode(28);
__native int      A_GetUserArray(int, __string, int) __nacode(29);
__native _Accum   A_GetUserArrayFixed(int, __string, int) __nacode(29);
__native void     A_SoundSequenceOnActor(int, __string) __nacode(30);
__native void     A_SoundSequenceOnSector(int, __string, int) __nacode(31);
__native void     A_SoundSequenceOnPolyobj(int, __string) __nacode(32);
__native _Accum   A_GetPolyobjX(int) __nacode(33);
__native _Accum   A_GetPolyobjY(int) __nacode(34);
__native _Bool    A_CheckSight(int, int, int) __nacode(35);
__native int      A_SpawnForced(__string, _Accum, _Accum, _Accum) __nacode(36);
__native int      A_SpawnForced(__string, _Accum, _Accum, _Accum, int) __nacode(36);
__native int      A_SpawnForced(__string, _Accum, _Accum, _Accum, int, int) __nacode(36);
__native void     A_AnnouncerSound(__string, int) __nacode(37);
__native _Bool    A_SetPointer(int, int) __nacode(38);
__native _Bool    A_SetPointer(int, int, int) __nacode(38);
__native _Bool    A_SetPointer(int, int, int, int) __nacode(38);
__native _Bool    ACS_NamedExecute(__string, int) __nacode(39);
__native _Bool    ACS_NamedExecute(__string, int, int) __nacode(39);
__native _Bool    ACS_NamedExecute(__string, int, int, int) __nacode(39);
__native _Bool    ACS_NamedExecute(__string, int, int, int, int) __nacode(39);
__native _Bool    ACS_NamedSuspend(__string, int) __nacode(40);
__native _Bool    ACS_NamedTerminate(__string, int) __nacode(41);
__native _Bool    ACS_NamedLockedExecute(__string, int, int, int, int) __nacode(42);
__native _Bool    ACS_NamedLockedExecuteDoor(__string, int, int, int, int) __nacode(43);
__native int      ACS_NamedExecuteWithResult(__string) __nacode(44);
__native int      ACS_NamedExecuteWithResult(__string, int) __nacode(44);
__native int      ACS_NamedExecuteWithResult(__string, int, int) __nacode(44);
__native int      ACS_NamedExecuteWithResult(__string, int, int, int) __nacode(44);
__native int      ACS_NamedExecuteWithResult(__string, int, int, int, int) __nacode(44);
__native _Accum   ACS_NamedExecuteWithResultFixed(__string) __nacode(44);
__native _Accum   ACS_NamedExecuteWithResultFixed(__string, int) __nacode(44);
__native _Accum   ACS_NamedExecuteWithResultFixed(__string, int, int) __nacode(44);
__native _Accum   ACS_NamedExecuteWithResultFixed(__string, int, int, int) __nacode(44);
__native _Accum   ACS_NamedExecuteWithResultFixed(__string, int, int, int, int) __nacode(44);
__native _Bool    ACS_NamedExecuteAlways(__string, int) __nacode(45);
__native _Bool    ACS_NamedExecuteAlways(__string, int, int) __nacode(45);
__native _Bool    ACS_NamedExecuteAlways(__string, int, int, int) __nacode(45);
__native _Bool    ACS_NamedExecuteAlways(__string, int, int, int, int) __nacode(45);
__native int      A_UniqueTID() __nacode(46);
__native int      A_UniqueTID(int) __nacode(46);
__native int      A_UniqueTID(int, int) __nacode(46);
__native _Bool    A_IsTIDUsed(int) __nacode(47);
__native int      A_Sqrt(int) __nacode(48);
__native _Accum   A_FixedSqrt(_Accum) __nacode(49);
__native _Accum   A_VectorLength(_Accum, _Accum) __nacode(50);
__native void     A_SetHudClipRect(int x, int y, int width, int height) __nacode(51);
__native void     A_SetHudClipRect(int x, int y, int width, int height, int wrapwidth) __nacode(51);
__native void     A_SetHudWrapWidth(int wrapwidth) __nacode(52);

__native int      A_ResetMap() __nacode(100);
__native int      A_PlayerIsSpectator(int player) __nacode(101);
__native int      A_ConsolePlayerNumber() __nacode(102);
__native int      A_GetTeamProperty(int team, int prop) __nacode(103);
__native _Accum   A_GetTeamPropertyFixed(int team, int prop) __nacode(103);
__native __string A_GetTeamPropertyString(int team, int prop) __nacode(103);
__native int      A_GetPlayerLivesLeft(int player) __nacode(104);
__native int      A_SetPlayerLivesLeft(int player, int amount) __nacode(105);
__native int      A_KickFromGame(int player, __string reason) __nacode(106);

__native int      A_GetTeamScore(int team) __nacode(19620);
__native int      A_SetTeamScore(int team, int value) __nacode(19621);


//----------------------------------------------------------------------------|
// Cleanup                                                                    |
//

#undef _A

#undef __asmfunc
#undef __asmcode
#undef __asmcode_imm

#undef __linespec
#undef __linecode

#undef __native
#undef __nacode

#endif//__HEADER__A_ZDOOM_H__

