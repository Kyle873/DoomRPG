#include <ACS_ZDoom.h>
#include <stdbool.h>
#include <stdio.h>

#define ACS_EndHudMessage2      ACS_EndHudMessageX
#define ACS_EndHudMessage3      ACS_EndHudMessageXX
#define ACS_EndHudMessage4      ACS_EndHudMessageXXX
#define ACS_EndHudMessageBold2  ACS_EndHudMessageBoldX
#define ACS_EndHudMessageBold3  ACS_EndHudMessageBoldXX
#define ACS_EndHudMessageBold4  ACS_EndHudMessageBoldXXX

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
