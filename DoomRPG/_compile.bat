@echo off
color F

set PATH=..\..\\DH-ACC
set SRC=.\scripts
set OBJ=.\acs

rem _timestamp

DH-acc -Z -i %SRC%\inc %SRC%\Arena.ds -o %OBJ%\Arena.o
DH-acc -Z -i %SRC%\inc %SRC%\Augs.ds -o %OBJ%\Augs.o
DH-acc -Z -i %SRC%\inc %SRC%\Menu.ds -o %OBJ%\Menu.o
DH-acc -Z -i %SRC%\inc %SRC%\Minigame.ds -o %OBJ%\Minigame.o
DH-acc -Z -i %SRC%\inc %SRC%\RPG.ds -o %OBJ%\RPG.o
DH-acc -Z -i %SRC%\inc %SRC%\Shop.ds -o %OBJ%\Shop.o
DH-acc -Z -i %SRC%\inc %SRC%\Skills.ds -o %OBJ%\Skills.o
DH-acc -Z -i %SRC%\inc %SRC%\Stats.ds -o %OBJ%\Stats.o
DH-acc -Z -i %SRC%\inc %SRC%\Stims.ds -o %OBJ%\Stims.o
DH-acc -Z -i %SRC%\inc %SRC%\Utils.ds -o %OBJ%\Utils.o

echo Done!

pause >nul
