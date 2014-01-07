@echo off
color F

set PATH=C:\Games\Doom\ACC
set SRC=.\scripts\acs
set OBJ=.\acs

_timestamp

acc -i %SRC% %SRC%\Augs %OBJ%\Augs
acc -i %SRC% %SRC%\Arena %OBJ%\Arena
acc -i %SRC% %SRC%\Menu %OBJ%\Menu
acc -i %SRC% %SRC%\RPG %OBJ%\RPG
acc -i %SRC% %SRC%\Shield %OBJ%\Shield
acc -i %SRC% %SRC%\Shop %OBJ%\Shop
acc -i %SRC% %SRC%\Skills %OBJ%\Skills
acc -i %SRC% %SRC%\Stats %OBJ%\Stats
acc -i %SRC% %SRC%\Utils %OBJ%\Utils

pause >nul
