@echo off
color F

set PATH=..\..\DH-ACC
set SRC=.\scripts
set OBJ=.\acs
set ACC=DH-acc --named-scripts --use-chunk-ATAG --debug-error-pos --debug-mapregister-list=MapVars.log --debug-maparray-list=MapArrays.log -Z -i %SRC%\inc

_timestamp

echo ----------------------------------------

rem Standard Libraries
echo Compiling Standard Libraries
%ACC% -c %PATH%/lib/stdlib.ds -o %OBJ%\stdlib.o
%ACC% -c %PATH%/lib/stdio.ds -o %OBJ%\stdio.o
%ACC% -c %PATH%/lib/string.ds -o %OBJ%\string.o

rem Doom RPG Modules
echo Compiling Arena
%ACC% -c %SRC%\Arena.ds -o %OBJ%\Arena.o
echo Compiling Augs
%ACC% -c %SRC%\Augs.ds -o %OBJ%\Augs.o
echo Compiling GUI
%ACC% -c %SRC%\GUI.ds -o %OBJ%\GUI.o
echo Compiling Menu
%ACC% -c %SRC%\Menu.ds -o %OBJ%\Menu.o
echo Compiling MenuGUI
%ACC% -c %SRC%\MenuGUI.ds -o %OBJ%\MenuGUI.o
echo Compiling Minigame
%ACC% -c %SRC%\Minigame.ds -o %OBJ%\Minigame.o
echo Compiling Outpost
%ACC% -c %SRC%\Outpost.ds -o %OBJ%\Outpost.o
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
%ACC% %OBJ%\stdlib.o %OBJ%\stdio.o %OBJ%\string.o %OBJ%\Arena.o %OBJ%\Augs.o %OBJ%\GUI.o %OBJ%\Menu.o %OBJ%\MenuGUI.o %OBJ%\Minigame.o %OBJ%\Outpost.o %OBJ%\RPG.o %OBJ%\Shield.o %OBJ%\Shop.o %OBJ%\Skills.o %OBJ%\Stats.o %OBJ%\Stims.o %OBJ%\Utils.o -o %OBJ%\RPG.lib

echo ----------------------------------------

echo Cleaning up object files
del %OBJ%\*.o

echo ----------------------------------------
echo Done!

pause >nul
