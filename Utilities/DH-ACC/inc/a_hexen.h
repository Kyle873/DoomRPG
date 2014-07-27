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
// Hexen scripting functions and definitions.
//
// Identifiers beginning with A_ or ACS_ followed by a capital letter are
// reserved for use by this header.
//
//-----------------------------------------------------------------------------

#ifndef __HEADER__A_HEXEN_H__
#define __HEADER__A_HEXEN_H__


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


//----------------------------------------------------------------------------|
// Global Functions                                                           |
//

//
// Builtins
//

__asmfunc void   A_AmbientSound(__string, int _A(127)) __asmcode(ACS_SOUND_AMBIENT);
__asmfunc void   A_ChangeCeiling(int, __string) __asmcode_imm(ACS_STAG_SET_TEXTURE_CEILING);
__asmfunc void   A_ChangeFloor(int, __string) __asmcode_imm(ACS_STAG_SET_TEXTURE_FLOOR);
__asmfunc void   A_ClearLineSpecial(void) __asmcode(ACS_LINE_CLR_SPECIAL);
__asmfunc void   A_Delay(int) __asmcode_imm(ACS_WAIT_TICS);
__asmfunc int    A_GameSkill(void) __asmcode(ACS_GAME_GET_SKILL);
__asmfunc int    A_GameType(void) __asmcode(ACS_GAME_GET_TYPE);
__asmfunc int    A_LineSide(void) __asmcode(ACS_LINE_GET_SIDE);
__asmfunc int    A_PlayerCount(void) __asmcode(ACS_GAME_GET_PLAYERCOUNT);
__asmfunc void   A_PolyWait(int) __asmcode_imm(ACS_WAIT_POLYOBJECT);
__asmfunc int    A_Random(int, int) __asmcode_imm(ACS_MISC_RANDOM);
__asmfunc _Accum A_RandomFixed(_Accum, _Accum) __asmcode_imm(ACS_MISC_RANDOM);
__asmfunc void   A_ScriptWait(int) __asmcode_imm(ACS_WAIT_SCRIPT);
__asmfunc void   A_SectorSound(__string, int _A(127)) __asmcode(ACS_SOUND_SECTOR);
__asmfunc void   A_SetLineBlocking(int, int _A(0)) __asmcode(ACS_LTAG_SET_BLOCK);
__asmfunc void   A_SetLineSpecial(int, int _A(0), int _A(0), int _A(0), int _A(0), int _A(0), int _A(0)) __asmcode(ACS_LTAG_SET_SPECIAL);
__asmfunc void   A_SetLineTexture(int, int, int, __string) __asmcode(ACS_LTAG_SET_TEXTURE);
__asmfunc void   A_SoundSequence(__string) __asmcode(ACS_SOUND_SEQUENCE);
__asmfunc void   A_Suspend(void) __asmcode(JMP_HLT);
__asmfunc void   A_TagWait(int) __asmcode_imm(ACS_WAIT_STAG);
__asmfunc int    A_ThingCount(int _A(0), int _A(0)) __asmcode_imm(ACS_GAME_GET_THINGCOUNT_SID);
__asmfunc void   A_ThingSound(int, __string, int _A(127)) __asmcode(ACS_SOUND_MTAG);
__asmfunc int    A_Timer(void) __asmcode(ACS_GAME_GET_TIME);

//
// Line Specials
//

//linespec void A_Polyobj_StartLine(int, int, int, int) __linecode(1);
__linespec void A_Polyobj_RotateLeft(int, int, int) __linecode(2);
__linespec void A_Polyobj_RotateRight(int, int, int) __linecode(3);
__linespec void A_Polyobj_Move(int, int, int, int) __linecode(4);
//linespec void A_PolyObj_ExplicitLine(int, int, int, int, int) __linecode(5);
__linespec void A_PolyObj_MoveTimes8(int, int, int, int) __linecode(6);
__linespec void A_PolyObj_DoorSwing(int, int, int, int) __linecode(7);
__linespec void A_PolyObj_DoorSlide(int, int, int, int, int) __linecode(8);

__linespec void A_Door_Close(int, int) __linecode(10);
__linespec void A_Door_Open(int, int) __linecode(11);
__linespec void A_Door_Open(int, int, int) __linecode(11);
__linespec void A_Door_Raise(int, int, int) __linecode(12);
__linespec void A_Door_Raise(int, int, int, int) __linecode(12);
__linespec void A_Door_LockedRaise(int, int, int, int) __linecode(13);
__linespec void A_Door_LockedRaise(int, int, int, int, int) __linecode(13);

__linespec void A_Floor_LowerByValue(int, int, int) __linecode(20);
__linespec void A_Floor_LowerToLowest(int, int) __linecode(21);
__linespec void A_Floor_LowerToNearest(int, int) __linecode(22);
__linespec void A_Floor_RaiseByValue(int, int, int) __linecode(23);
__linespec void A_Floor_RaiseToHighest(int, int) __linecode(24);
__linespec void A_Floor_RaiseToNearest(int, int) __linecode(25);
__linespec void A_Stairs_BuildDown(int, int, int, int, int) __linecode(26);
__linespec void A_Stairs_BuildUp(int, int, int, int, int) __linecode(27);
__linespec void A_Floor_RaiseAndCrush(int, int, int) __linecode(28);
__linespec void A_Floor_RaiseAndCrush(int, int, int, int) __linecode(28);
__linespec void A_Pillar_Build(int, int, int) __linecode(29);
__linespec void A_Pillar_Open(int, int, int, int) __linecode(30);
__linespec void A_Stairs_BuildDownSync(int, int, int, int) __linecode(31);
__linespec void A_Stairs_BuildUpSync(int, int, int, int) __linecode(32);

__linespec void A_Floor_RaiseByValueTimes8(int, int, int) __linecode(35);
__linespec void A_Floor_LowerByValueTimes8(int, int, int) __linecode(36);

__linespec void A_Ceiling_LowerByValue(int, int, int) __linecode(40);
__linespec void A_Ceiling_RaiseByValue(int, int, int) __linecode(41);
__linespec void A_Ceiling_CrushAndRaise(int, int, int) __linecode(42);
__linespec void A_Ceiling_CrushAndRaise(int, int, int, int) __linecode(42);
__linespec void A_Ceiling_LowerAndCrush(int, int, int) __linecode(43);
__linespec void A_Ceiling_LowerAndCrush(int, int, int, int) __linecode(43);
__linespec void A_Ceiling_CrushStop(int) __linecode(44);
__linespec void A_Ceiling_CrushRaiseAndStay(int, int, int) __linecode(45);
__linespec void A_Ceiling_CrushRaiseAndStay(int, int, int, int) __linecode(45);
__linespec void A_Floor_CrushStop(int) __linecode(46);

__linespec void A_Plat_PerpetualRaise(int, int, int) __linecode(60);
__linespec void A_Plat_Stop(int) __linecode(61);
__linespec void A_Plat_DownWaitUpStay(int, int, int) __linecode(62);
__linespec void A_Plat_DownByValue(int, int, int, int) __linecode(63);
__linespec void A_Plat_UpWaitDownStay(int, int, int) __linecode(64);
__linespec void A_PlatUpByValue(int, int, int, int) __linecode(65);
__linespec void A_Floor_LowerInsant(int, int, int) __linecode(66);
__linespec void A_Floor_RaiseInsant(int, int, int) __linecode(67);
__linespec void A_Floor_MoveToValueTimes8(int, int, int, int) __linecode(68);
__linespec void A_Ceiling_MoveToValueTimes8(int, int, int, int) __linecode(69);
__linespec void A_Teleport(int) __linecode(70);
__linespec void A_Teleport(int, int) __linecode(70);
__linespec void A_Teleport(int, int, int) __linecode(70);
__linespec void A_Teleport_NoFog(int) __linecode(71);
__linespec void A_Teleport_NoFog(int, int) __linecode(71);
__linespec void A_Teleport_NoFog(int, int, int) __linecode(71);
__linespec void A_ThrustThing(int, int) __linecode(72);
__linespec void A_ThrustThing(int, int, int) __linecode(72);
__linespec void A_ThrustThing(int, int, int, int) __linecode(72);
__linespec void A_DamageThing(int) __linecode(73);
__linespec void A_DamageThing(int, int) __linecode(73);
__linespec void A_Teleport_NewMap(int, int) __linecode(74);
__linespec void A_Teleport_NewMap(int, int, int) __linecode(74);
__linespec void A_Teleport_EndGame(void) __linecode(75);

__linespec void ACS_Execute(int, int) __linecode(80);
__linespec void ACS_Execute(int, int, int) __linecode(80);
__linespec void ACS_Execute(int, int, int, int) __linecode(80);
__linespec void ACS_Execute(int, int, int, int, int) __linecode(80);
__linespec void ACS_Suspend(int, int) __linecode(81);
__linespec void ACS_Terminate(int, int) __linecode(82);
__linespec void ACS_LockedExecute(int, int, int, int, int) __linecode(83);

__linespec void A_Polyobj_OR_RotateLeft(int, int, int) __linecode(90);
__linespec void A_Polyobj_OR_RotateRight(int, int, int) __linecode(91);
__linespec void A_Polyobj_OR_Move(int, int, int, int) __linecode(92);
__linespec void A_Polyobj_OR_MoveTimes8(int, int, int, int) __linecode(93);
__linespec void A_Pillar_BuildAndCrush(int, int, int, int) __linecode(94);
__linespec void A_Pillar_BuildAndCrush(int, int, int, int, int) __linecode(94);
__linespec void A_FloorAndCeiling_LowerByValue(int, int, int) __linecode(95);
__linespec void A_FloorAndCeiling_RaiseByValue(int, int, int) __linecode(96);
__linespec void A_Ceiling_LowerAndCrushDist(int, int, int) __linecode(97);
__linespec void A_Ceiling_LowerAndCrushDist(int, int, int, int) __linecode(97);
__linespec void A_Ceiling_LowerAndCrushDist(int, int, int, int, int) __linecode(97);
__linespec void A_Sector_SetTranslucent(int, int, int) __linecode(98);
__linespec void A_Sector_SetTranslucent(int, int, int, int) __linecode(98);

//linespec void A_Scroll_Texture_Left(int, int) __linecode(100);
//linespec void A_Scroll_Texture_Right(int, int) __linecode(101);
//linespec void A_Scroll_Texture_Up(int, int) __linecode(102);
//linespec void A_Scroll_Texture_Down(int, int) __linecode(103);

__linespec void A_Light_ForceLightning(int) __linecode(109);
__linespec void A_Light_RaiseByValue(int, int) __linecode(110);
__linespec void A_Light_LowerByValue(int, int) __linecode(111);
__linespec void A_Light_ChangeToValue(int, int) __linecode(112);
__linespec void A_Light_Fade(int, int, int) __linecode(113);
__linespec void A_Light_Glow(int, int, int, int) __linecode(114);
__linespec void A_Light_Flicker(int, int, int) __linecode(115);
__linespec void A_Light_Strobe(int, int, int, int, int) __linecode(116);

__linespec void A_Radius_Quake(int, int, int, int, int) __linecode(120);
//linespec void A_Line_SetIdentification(int) __linecode(121);

//linespec void A_UsePuzzleItem(int, int) __linecode(129);
//linespec void A_UsePuzzleItem(int, int, int) __linecode(129);
//linespec void A_UsePuzzleItem(int, int, int, int) __linecode(129);
//linespec void A_UsePuzzleItem(int, int, int, int, int) __linecode(129);
__linespec void A_Thing_Activate(int) __linecode(130);
__linespec void A_Thing_Deactivate(int) __linecode(131);
__linespec void A_Thing_Remove(int) __linecode(132);
__linespec void A_Thing_Destroy(int) __linecode(133);
__linespec void A_Thing_Destroy(int, int) __linecode(133);
__linespec void A_Thing_Destroy(int, int, int) __linecode(133);
__linespec void A_Thing_Projectile(int, int, int, int, int) __linecode(134);
__linespec void A_Thing_Spawn(int, int, int) __linecode(135);
__linespec void A_Thing_Spawn(int, int, int, int) __linecode(135);
__linespec void A_Thing_ProjectileGravity(int, int, int, int, int) __linecode(136);
__linespec void A_Thing_SpawnNoFog(int, int, int) __linecode(137);
__linespec void A_Thing_SpawnNoFog(int, int, int, int) __linecode(137);
__linespec void A_Floor_Waggle(int, int, int, int, int) __linecode(138);

__linespec void A_Sector_ChangeSound(int, int) __linecode(140);


//----------------------------------------------------------------------------|
// Cleanup                                                                    |
//

#undef _A

#undef __asmfunc
#undef __asmcode
#undef __asmcode_imm

#undef __linespec
#undef __linecode

#endif//__HEADER__A_HEXEN_H__

