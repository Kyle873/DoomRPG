@echo off
color F

set PATH=..\..\DH-ACC
set SRC=.\scripts
set OBJ=.\acs
set ACC=DH-acc --named-scripts --auto-stack-size=0 --debug-mapregister-list=MapVars.log --debug-maparray-list=MapArrays.log -Z -i %SRC%\inc

_timestamp

%ACC% %SRC%\Arena.ds -o %OBJ%\Arena.o
%ACC% %SRC%\Augs.ds -o %OBJ%\Augs.o
%ACC% %SRC%\Menu.ds -o %OBJ%\Menu.o
%ACC% %SRC%\Minigame.ds -o %OBJ%\Minigame.o
%ACC% %SRC%\RPG.ds -o %OBJ%\RPG.o
%ACC% %SRC%\Shield.ds -o %OBJ%\Shield.o
%ACC% %SRC%\Shop.ds -o %OBJ%\Shop.o
%ACC% %SRC%\Skills.ds -o %OBJ%\Skills.o
%ACC% %SRC%\Stats.ds -o %OBJ%\Stats.o
%ACC% %SRC%\Stims.ds -o %OBJ%\Stims.o
%ACC% %SRC%\Utils.ds -o %OBJ%\Utils.o

echo Done!

pause >nul
