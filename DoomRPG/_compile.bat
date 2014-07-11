@echo off
color F

set PATH=..\..\DH-ACC
set SRC=.\scripts
set OBJ=.\acs
set ACC=DH-acc --named-scripts --near-pointers --use-chunk-ATAG --debug-error-pos -D__LIBDS_NOLIB --debug-mapregister-list=MapVars.log --debug-maparray-list=MapArrays.log --script-regargs=4 -Z -i %SRC%\inc -i %SRC%\lib

_timestamp

echo ----------------------------------------

rem Standard Libraries
echo Compiling Standard Libraries
%ACC% -c %PATH%/lib/stdlib.ds -o %OBJ%\stdlib.o
%ACC% -c %PATH%/lib/stdio.ds -o %OBJ%\stdio.o
%ACC% -c %PATH%/lib/string.ds -o %OBJ%\string.o

rem Doom RPG Libraries
echo Compiling BitIO
%ACC% -c %SRC%/lib/BitIO.c -o %OBJ%\BitIO.o

rem Doom RPG Modules
echo Compiling Arena
%ACC% -c %SRC%\Arena.ds -o %OBJ%\Arena.o
echo Compiling Augs
%ACC% -c %SRC%\Augs.ds -o %OBJ%\Augs.o
rem echo Compiling GUI
rem %ACC% -c %SRC%\GUI.ds -o %OBJ%\GUI.o
rem echo Compiling GUIMenu
rem %ACC% -c %SRC%\GUIMenu.ds -o %OBJ%\GUIMenu.o
echo Compiling HealthBars
%ACC% -c %SRC%\HealthBars.ds -o %OBJ%\HealthBars.o
echo Compiling HUD
%ACC% -c %SRC%\HUD.ds -o %OBJ%\HUD.o
echo Compiling ItemData
%ACC% -c %SRC%\ItemData.ds -o %OBJ%\ItemData.o
echo Compiling Map
%ACC% -c %SRC%\Map.ds -o %OBJ%\Map.o
echo Compiling Menu
%ACC% -c %SRC%\Menu.ds -o %OBJ%\Menu.o
rem echo Compiling Minigame
rem %ACC% -c %SRC%\Minigame.ds -o %OBJ%\Minigame.o
echo Compiling Mission
%ACC% -c %SRC%\Mission.ds -o %OBJ%\Mission.o
echo Compiling Monsters
%ACC% -c %SRC%\Monsters.ds -o %OBJ%\Monsters.o
echo Compiling Namegen
%ACC% -c %SRC%\Namegen.ds -o %OBJ%\Namegen.o
echo Compiling Outpost
%ACC% -c %SRC%\Outpost.ds -o %OBJ%\Outpost.o
echo Compiling Password
%ACC% -c %SRC%\Password.ds -o %OBJ%\Password.o
echo Compiling Popoffs
%ACC% -c %SRC%\Popoffs.ds -o %OBJ%\Popoffs.o
echo Compiling RPG
%ACC% -c %SRC%\RPG.ds -o %OBJ%\RPG.o
echo Compiling Shield
%ACC% -c %SRC%\Shield.ds -o %OBJ%\Shield.o
echo Compiling Shop
%ACC% -c %SRC%\Shop.ds -o %OBJ%\Shop.o
echo Compiling Skills
%ACC% -c %SRC%\Skills.ds -o %OBJ%\Skills.o
echo Compiling Stats
%ACC% -c %SRC%\Stats.ds -o %OBJ%\Stats.o
echo Compiling Stims
%ACC% -c %SRC%\Stims.ds -o %OBJ%\Stims.o
echo Compiling Utils
%ACC% -c %SRC%\Utils.ds -o %OBJ%\Utils.o
echo Linking RPG.lib
%ACC% %OBJ%\stdlib.o %OBJ%\stdio.o %OBJ%\string.o %OBJ%\BitIO.o %OBJ%\Arena.o %OBJ%\Augs.o %OBJ%\HealthBars.o %OBJ%\HUD.o %OBJ%\ItemData.o %OBJ%\Map.o %OBJ%\Menu.o %OBJ%\Mission.o %OBJ%\Monsters.o %OBJ%\Namegen.o %OBJ%\Outpost.o %OBJ%\Password.o %OBJ%\Popoffs.o %OBJ%\RPG.o %OBJ%\Shield.o %OBJ%\Shop.o %OBJ%\Skills.o %OBJ%\Stats.o %OBJ%\Stims.o %OBJ%\Utils.o -o %OBJ%\RPG.lib

echo ----------------------------------------

echo Cleaning up object files
del %OBJ%\*.o

echo ----------------------------------------
echo Done!

pause >nul
