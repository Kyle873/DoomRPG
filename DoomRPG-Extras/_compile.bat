@echo off
color F

set PATH=C:\Games\Doom\ACC
set SRC=.\scripts
set OBJ=.\acs

_timestamp

acc -i %SRC% %SRC%\Gib %OBJ%\Gib

pause >nul
