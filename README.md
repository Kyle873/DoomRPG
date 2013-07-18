ZDoom Forum Thread: http://forum.zdoom.org/viewtopic.php?f=19&t=33292

For Players
===========

PLEASE READ THIS!
-----------------
- When starting the game for the first time, you will need to go into Options -> Doom RPG Options and restore the options to defaults. If you don't do this, you will have many issues including not being able to move and other oddities.
- DoomRPG-Brutal.pk3 and DoomRPG-Extras.pk3 CAN NOT BE USED TOGETHER, you must use either one or the other, or else loading will fail.
- When using DoomRPG-Brutal.pk3 (Brutal Doom Doom RPG Patch), make sure you have Brutal Doom Compatibility enabled in the Doom RPG Options menu. If you don't do this, there will be errors and/or strange issues.
- If you need help, have questions, or find bugs, please post them in the Doom RPG Thread on the ZDoom forum.

TIPS
----
- There are 2 different pages in the Stats menu, use the run key to switch between them.
- You can Overdrive a skill by holding the run button. Doing this will always use the skill, regardless of it's Energy cost. However, this will bring your current Energy into the negatives. When negative, you will suffer stat penalties and not be able to use any skills until your Energy is restored past 0.
- Overdriving an unlearnt skill will automatically use an available Skill Token to learn it.
- You can Respec (reset your stats, skills, inventory and levels) from the Doom RPG Options menu. Respecs will cost you half of your total Credits.
- You can change the current skill level by using the computer beside the entry teleporter at the UAC Outpost.

PLEASE NOTE
-----------
This README contains information which will eventually be moved to the wiki. It is currently here as a quick reference point for those who need it.

For Modders - Editor IDs
========================

Credits
-------
- 10001 - Credits1
- 10002 - Credits5
- 10003 - Credits10
- 10004 - Credits20
- 10005 - Credits50
- 10006 - Credits100
- 10007 - Credits1000

Health
------
- 10010 - SmallMedikit
- 10011 - LargeMedikit
- 10012 - XLMedikit
- 10013 - MedPack
- 10014 - SuperMedPack
- 10015 - SurgeryKit
- 10016 - AtomicHealth
- 10017 - Continue
- 10018 - EPCapsule
- 10019 - BigEPCapsule
	
Armor
-----
- 10020 - UsedGreenArmor
- 10021 - UsedBlueArmor
- 10022 - YellowArmor
- 10023 - UsedYellowArmor
- 10024 - RedArmor
- 10025 - UsedRedArmor
- 10026 - WhiteArmor
- 10027 - UsedWhiteArmor

Powerups
--------
- 10030 - InvulnerabilityCharge
- 10031 - InvisibilityCharge
- 10032 - TimeSphere
- 10033 - BigBackpack
- 10034 - StrengthRune
- 10036 - DrainRune
- 10037 - EndlessRune
- 10038 - ResistanceRune
- 10039 - RegenerationRune
- 10040 - FrightRune
- 10041 - GhostRune
- 10042 - HighJumpRune
- 10043 - HasteRune

Tokens
------
- 10050 - StatToken
- 10051 - StatCapToken
- 10052 - SkillToken
- 10053 - BigStatToken
- 10054 - BigStatCapToken
- 10055 - BigSkillToken
- 10056 - MegaToken
- 10057 - BigMegaToken

Accessories
-----------
- 10070 - StrengthBadge
- 10071 - DefenseBadge
- 10072 - VitalityBadge
- 10073 - EnergyBadge
- 10074 - RegenerationBadge
- 10075 - AgilityBadge
- 10076 - CapacityBadge
- 10077 - LuckBadge
- 10078 - RainbowBadge

Monsters
--------
- 10100 - ZombieMan
- 10110 - ShotGunGuy
- 10120 - ChainGunGuy

FUNCTION REFERENCE
==================

Some of these are a little out of date because I'm lazy, but if you really need to see them you can look in the \scripts folder of the respective package, the plaintext ACS scripts are stored in there.

RPG.acs
-------
- Init - This script is ran at the start of every level and handles setting up all the initial vars as well as rechecking and reinitializing the Accessories and tables to prevent any issues, also closes all the menus due to a bug where you could exit a level while in a menu
- Loop - This script runs every frame and handles running all the Check* functions for keeping everything up to date in the system
- Death - This script is run when the player dies, it will troll you, clear your inventory (to prevent abusing the resurrect command to revive yourself, fully intact) and nuke a bunch of vars to make the death look clean and to prevent any bugs that may occur with auras being active when dying or trying to use skills when dead
- QuickHeal - Uses the highest tier healing item in your inventory
- QuickArmor - Uses the highest tier armor item in your inventory
- QuickAmmo - Buys a clips worth of the current weapon's ammo

Stats.acs
---------
- CheckCombo() - Handles the combo count system and giving the player XP/Rank when the combo is over
- CheckLevel() - Checks for if you have levelled up, if so, give you stat and skill tokens depending on your difficulty as well as random factors, also has some edge cases for possible display issues or trying to surpass the level cap
- CheckRank() - Checks for if you have ranked up, also handles the Payout system
- CheckSecrets() - Checks if you have found a secret, if so, gives you a rank bonus
- CheckHealth() - Handles screen fades/sound effects for if your health is lower than 10% max, will also cut your current speed and jump height in half.
- CheckStats() - Very important. This function handles the formulas used in the stat system as well as hard capping the stats, keeping HUD/menu counts updated, handling survival bonus, and applying tokens automagically if you have that option turned on
- CheckStatCap() - Keeps your current stat cap updated
- DoRegen() - Handles HP/EP regeneration depending on stats and skills
- SetupTables() - Iterates the XP and rank tables and inserts the requirements for levelling up each
- CapStats(int cap) - This will cap all stats to the specified value
- RecalculateStats() - Handles recalculating your current HP/EP if your Vitality/Energy are increased/decreased by tokens or accessories
- RandomStatUp() - Increases a random stat
- CheckLuck() - Determines the LuckDropper's drop rates
- CheckBurnout() - Applies Burnout penalties if EP < 0

Skills.acs
----------
- UseSkill - This script is activated whenever the player uses a skill, determines which skill to use
- DrawSkillHUD - Draws the catagory, name, level and description of the current skill on the HUD
- SkillCatagoryUp - Goes back a skill catagory
- SkillCatagoryDown - Goes forward a skill catagory
- SkillUp - Goes back a skill in the current catagory
- SkillDown - Goes forward a skill in the current catagory
- SkillLevelUp - Increases your current skill's usage level
- SkillLevelDown - Decreases your current skill's usage level
- CheckEP(int amount) - Used to check and decrease EP for using skills, includes error handling and checks to make sure you know the skill first before activating it, amount is the EP amount to check against
- Heal(int type) - Handles the Healing catagory of skills, type being either 0 for handling the Heal skill or 1 for handling the Repair Armor skill
- Projectile(str type) - Handles shooting projectiles, type being the actor class of the projectile to shoot
- Summon(str type) - Handles the Summoning skills, type being which actor class to summon
- BreakdownArmor() - Handles the Breakdown Armor skill
- BulletTime() - Activates the Bullet Time effect
- CheckSkills() - Handles the Aura system and other skill-related timers
- Transport - Handles transportation between your current level and the Outpost

Accessories.acs
---------------
- SetAccessorySlots() - Handles determing the max amount of accessories you can equip depending on your difficulty level
- CheckAccessories() - Checks Accessories and adds/removes bonuses depending on which are equipped
- EquipAccessory(int acc) - Handles equipping/unequipping accessories and making sure you can only equip up to the max amount determined by your difficulty level, acc is the index in the Accessories array that you are trying to equip/unequip

Shop.acs
--------
- OpenShop - This script handles opening/closing the shop when activated
- SellAll(int Page) - This script sells all items in your posession contained within the given page
- ShopLoop() - Handles all the input and drawing in the shop menu

Menu.acs
--------
- OpenMenu - This script handles opening/closing the menu
- MenuLoop() - This function handles the drawing and input of whichever menu you are currently in
- DrawMainMenu() - Draws the main menu
- DrawStatsMenu() - Draws the Stats menu
- DrawAccessoriesMenu() - Draws the Accessories menu
- DrawSkillMenu() - Draws the Skills menu
- DrawShieldMenu() - Draws the Shield menu
- MenuInput() - This function handles all the menu input in all of the menus
- IncreaseStat() - This function will increase whichever stat is highlighted in the level up menu by 1 and make sure you don't exceed the current stat cap
- IncreaseSkill() - This function will increase whichever skill's level is highlighted in the skills menu and make sure you don't increase the level past the maximum defined in the SkillLevelMax array

Utils.acs
---------
- GiveAccs - Gives you all the currently implemented accessories
- AddXP(int Amount) - Used by DECORATE to give the player experience and increase the current combo
- AddEP(int Amount) - Used by DECORATE to give the player EP
- Cheat(int StatBoost) - This does a whole crapton of stuff to make you rediculously overpowered and to help me test specific things, such as what the HUD looks like with all runes/powerups active. This script will max your level/rank, increase all your stats by the given amount, give you all accessories, max out all skills, max out your tokens, give you all health/armor/powerup inventory items, every rune, all weapons with full ammo, give you a rediculous amount of Credits, and FINALLY restore your HP and EP to maximum
- ModStat(int Stat, int Value) - This function will set a specific stat to a specific value
- Payout - This will cause the PayTimer to reset and immediately pay you
- AllRunes - Gives you every rune
- PrintSprite(str sprite, int id, int x, int y, int d) - Used to easily print sprites on the HUD
- Round(int fixednumber) - Rounds a floating-point number to the nearest whole number
- Pow(int x, int n) - Computes n-th power of x

TODO
====

In order

- Configurable base X/Y offset for redone menu system
- Add some sort of teleporter beacon you can buy at the store that lets you call in marine reinforcements?
- Option to auto buy ammo for current weapon when it's about to run out.
- Finish unique monster system

Bugs
====

Ideas
=====

Accessories
-----------
- Elemental Amplifiers for each element
- 25% discount at shop
- Halve EP Costs

Elemental System
----------------
- Possibly fire, ice, earth, lightning, acid, light, dark? (Obviously not all of them I'd imagine, but those were ones that immediately came to my head)
- Give monsters elements
- Projectile, nova, aura, hitscan? skills for each element as well as enemy attacks
- Resistance/amplification accessories


Credits
=======

Testers
-------
Ryan Cordell
LordMisfit
Serious Cacodemon
yoshi314
karmakazi
valherran
-Ghost-
Ribo Zurai
Frozenwolf150
dijosef

Resources
---------
- SBrightmaps by z86 (http://forum.zdoom.org/viewtopic.php?f=19&t=29792)-
- Cosmetic Doom by DecemberMan (http://forum.zdoom.org/viewtopic.php?f=19&t=32622)
- Brutal Doom by Sergeant_Mark_IV (http://forum.zdoom.org/viewtopic.php?t=28920)
- Doom Center by Katamori (http://www.doomworld.com/vb/wads-mods/54022-doom-center-do-you-know-that)

If I forgot or missed anyone, be sure to come and yell at me about it, I'm kind of forgetful sometimes...
