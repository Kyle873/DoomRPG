@echo off
color F

set PATH=C:\Games\Doom\DH-ACC
set SRC=.\scripts
set OBJ=.\acs

dh-acc -Z -i %SRC% Menu.ds %OBJ%\Menu.o
dh-acc -Z -i %SRC% Stats.ds %OBJ%\Stats.o
dh-acc -Z -i %SRC% RPG.ds %OBJ%\RPG.o

pause >nul
