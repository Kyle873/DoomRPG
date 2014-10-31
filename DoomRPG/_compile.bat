@echo off
color F

set PATH=..\Utilities\DH-ACC\bin\64
set SRC=.\scripts
set OBJ=.\acs
set ACC=DH-acc --named-scripts --near-pointers --use-chunk-ATAG --debug-error-pos -D__LIBDS_ZONESIZE=128 --debug-static-list=DebugStaticList.log --debug-mapregister-list=MapVars.log --debug-maparray-list=MapArrays.log --script-regargs=4 -Z -i %SRC%\inc -i %SRC%\lib

rem Standard Libraries
echo Compiling Standard Libraries
echo    - stdlib
%ACC% -c %PATH%\..\..\lib\stdlib.ds -o %OBJ%\stdlib.o
echo    - stdio
%ACC% -c %PATH%\..\..\lib\stdio.ds -o %OBJ%\stdio.o
echo    - string
%ACC% -c %PATH%\..\..\lib\string.ds -o %OBJ%\string.o
echo    - z_zone
%ACC% -c %PATH%\..\..\lib\z_zone.c -o %OBJ%\z_zone.o

echo Linking LibDS.lib
%ACC% %OBJ%\stdlib.o %OBJ%\stdio.o %OBJ%\string.o %OBJ%\z_zone.o -o %OBJ%\LibDS.lib

rem Change the stack offset so we don't overlap with the standard library
set ACC=%ACC% --static-offset=152000000

rem Doom RPG Libraries
echo Compiling Doom RPG Libraries
echo    - BitIO
%ACC% -c %SRC%/lib/BitIO.c -o %OBJ%\BitIO.o

rem Doom RPG Modules
echo Compiling Doom RPG
echo    - Arena
%ACC% -c %SRC%\Arena.ds -o %OBJ%\Arena.o
echo    - Augs
%ACC% -c %SRC%\Augs.ds -o %OBJ%\Augs.o
rem echo    - GUI
rem %ACC% -c %SRC%\GUI.ds -o %OBJ%\GUI.o
rem echo    - GUIMenu
rem %ACC% -c %SRC%\GUIMenu.ds -o %OBJ%\GUIMenu.o
echo    - HealthBars
%ACC% -c %SRC%\HealthBars.ds -o %OBJ%\HealthBars.o
echo    - HUD
%ACC% -c %SRC%\HUD.ds -o %OBJ%\HUD.o
echo    - ItemData
%ACC% -c %SRC%\ItemData.ds -o %OBJ%\ItemData.o
echo    - Map
%ACC% -c %SRC%\Map.ds -o %OBJ%\Map.o
echo    - Menu
%ACC% -c %SRC%\Menu.ds -o %OBJ%\Menu.o
echo    - Minigame
%ACC% -c %SRC%\Minigame.ds -o %OBJ%\Minigame.o
echo    - Mission
%ACC% -c %SRC%\Mission.ds -o %OBJ%\Mission.o
echo    - Monsters
%ACC% -c %SRC%\Monsters.ds -o %OBJ%\Monsters.o
echo    - Namegen
%ACC% -c %SRC%\Namegen.ds -o %OBJ%\Namegen.o
echo    - Outpost
%ACC% -c %SRC%\Outpost.ds -o %OBJ%\Outpost.o
echo    - Password
%ACC% -c %SRC%\Password.ds -o %OBJ%\Password.o
echo    - Popoffs
%ACC% -c %SRC%\Popoffs.ds -o %OBJ%\Popoffs.o
echo    - RPG
%ACC% -c %SRC%\RPG.ds -o %OBJ%\RPG.o
echo    - Shield
%ACC% -c %SRC%\Shield.ds -o %OBJ%\Shield.o
echo    - Shop
%ACC% -c %SRC%\Shop.ds -o %OBJ%\Shop.o
echo    - Skills
%ACC% -c %SRC%\Skills.ds -o %OBJ%\Skills.o
echo    - Stats
%ACC% -c %SRC%\Stats.ds -o %OBJ%\Stats.o
echo    - Stims
%ACC% -c %SRC%\Stims.ds -o %OBJ%\Stims.o
echo    - Turret
%ACC% -c %SRC%\Turret.ds -o %OBJ%\Turret.o
echo    - Utils
%ACC% -c %SRC%\Utils.ds -o %OBJ%\Utils.o

echo Linking RPG.lib
%ACC% %OBJ%\BitIO.o %OBJ%\Arena.o %OBJ%\Augs.o %OBJ%\HealthBars.o %OBJ%\HUD.o %OBJ%\ItemData.o %OBJ%\Map.o %OBJ%\Menu.o %OBJ%\Minigame.o %OBJ%\Mission.o %OBJ%\Monsters.o %OBJ%\Namegen.o %OBJ%\Outpost.o %OBJ%\Password.o %OBJ%\Popoffs.o %OBJ%\RPG.o %OBJ%\Shield.o %OBJ%\Shop.o %OBJ%\Skills.o %OBJ%\Stats.o %OBJ%\Stims.o %OBJ%\Turret.o %OBJ%\Utils.o -o %OBJ%\RPG.lib

echo Cleaning up Object Files
del %OBJ%\*.o

echo Done!

pause >nul
