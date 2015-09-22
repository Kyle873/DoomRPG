#ifndef DOOMRPG__SCRIPTS__DEFS_H
#define DOOMRPG__SCRIPTS__DEFS_H

#include <ACS_ZDoom.h>
#include <stdbool.h>
#include <stdio.h>

#pragma GDCC STRENT_LITERAL ON
#pragma GDCC FIXED_LITERAL  ON

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

#define string  __str
#define fixed   __fixed

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
#define keybind         [[extern("ACS")]] [[script("Net")]]

#define number_script(N)    [[call("ScriptI"), address(N)]]
#define named_script        [[call("ScriptS")]]
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

#endif // DOOMRPG__SCRIPTS__DEFS_H

