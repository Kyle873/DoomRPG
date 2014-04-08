@echo off
color F

set PATH=..\..\DH-ACC
set SRC=.\scripts
set OBJ=.\acs
set ACC=DH-acc --named-scripts --auto-stack-size=0 --use-chunk-ATAG --debug-error-pos --debug-mapregister-list=MapVars.log --debug-maparray-list=MapArrays.log -Z -i %SRC%\inc

_timestamp

rem Standard Libraries
%ACC% -c %PATH%/lib/stdlib.ds -o %PATH%\lib\stdlib.o
%ACC% -c %PATH%/lib/stdio.ds -o %PATH%\lib\stdio.o
%ACC% %PATH%\lib\stdlib.o %PATH%\lib\stdio.o -o %OBJ%\libDS.o

rem Doom RPG Modules
%ACC% %SRC%\Arena.ds -o %OBJ%\Arena.o
%ACC% %SRC%\Augs.ds -o %OBJ%\Augs.o
%ACC% %SRC%\GUI.ds -o %OBJ%\GUI.o
%ACC% %SRC%\Menu.ds -o %OBJ%\Menu.o
%ACC% %SRC%\Minigame.ds -o %OBJ%\Minigame.o
%ACC% %SRC%\Outpost.ds -o %OBJ%\Outpost.o
%ACC% %SRC%\RPG.ds -o %OBJ%\RPG.o
%ACC% %SRC%\Shield.ds -o %OBJ%\Shield.o
%ACC% %SRC%\Shop.ds -o %OBJ%\Shop.o
%ACC% %SRC%\Skills.ds -o %OBJ%\Skills.o
%ACC% %SRC%\Stats.ds -o %OBJ%\Stats.o
%ACC% %SRC%\Stims.ds -o %OBJ%\Stims.o
%ACC% %SRC%\Utils.ds -o %OBJ%\Utils.o

echo Done!

pause >nul
