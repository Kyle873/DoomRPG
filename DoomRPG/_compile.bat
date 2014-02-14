@echo off
color F

set PATH=..\..\\DH-ACC
set SRC=.\scripts
set OBJ=.\acs

rem _timestamp

DH-acc -Z -i %SRC%\inc %SRC%\Arena.ds -o %OBJ%\Arena.o
DH-acc -Z -i %SRC%\inc %SRC%\Augs.ds -o %OBJ%\Augs.o
DH-acc -Z -i %SRC%\inc %SRC%\Main.ds -o %OBJ%\Main.o
DH-acc -Z -i %SRC%\inc %SRC%\Stats.ds -o %OBJ%\Stats.o
DH-acc -Z -i %SRC%\inc %SRC%\Stims.ds -o %OBJ%\Stims.o
DH-acc -Z -i %SRC%\inc %SRC%\Utils.ds -o %OBJ%\Utils.o

echo Done!

pause >nul
