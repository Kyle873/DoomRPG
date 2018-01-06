Quick Stuff
===
- Animate the invulnerability sphere icon in the stats screen

General
===
- Re-check all default settings, see how they feel, etc
- Add combo stuff to rank payout level section
- Clean up the crate hacking interface a bit (use IDs, prevent overlaps, etc)
- Rework the way auras drop items; in particular, use the Inventory Transfer flag to make enemies drop backpacks
- Add more CVARs to customize the loot generator (how it calculates max items in particular, player level, player luck, map number, combinations, etc)
- Add a ticker/notice display for different events (shop special item changes, rolling events, reinforcement spawns, etc)

DRLA
===
- DRLA HUD needs it's drawing order reviewed to make sure nothing is overlapping with each other
- Double-check all DRLA icons, sprites, info and etc in the ItemData
- DRLA ammo counters for synthfire weapons are reversed on the HUD
- Double-check that all DRLA assembly tokens are actually saved with the charsave system
- Investigate the Death's Gazes artifact stunning power pissing off marines and other Outpost appliances when it's already got a check not to
- Add immunity to megabosses from the Death's Gaze death stunlock
- Add a DRLA only corrupted player event, fuck you die
- Add Utility skills similar to DRLA's skulls
  - Ditto for recall phase device (mark/recall system)

Events
===
- Sinstorm's demon spawn cubes spawn monsters inside of walls and each other, which frankly looks silly as hell
- Event object spawning (Power column, Radiation Neutralizer) needs to be randomized so that it doesn't consistently spawn in awkward places

Turret
===
- Change turret maintenance timers to percentages instead of times since timers lose accuracy with upgrades
- Revamp overheat system's numbers for the addition of upgrades for it
- Add a beam/team skill to slowly clean Toxicity from the player
- Empty crates should be omitted from the crate sensor beam iteration
  - Add a FindCrate() function which takes a TID and returns the found crate with that TID to help with this

Brightmaps
===
- Low Power Generator
- Turret parts crate
- UAC supply crate

Sounds
===
- Many skill usage sounds are placeholders and need replacing
- Status effect hit and avoid sounds are also placeholders
- Extra Life pickup and use sounds
- Add ambient stingers for when the music is off, just to fuck with you :D

QoL
===
- Add a way to take everything out of a crate similar to bulk withdrawal from the Locker

Bugs
===
- Modpack save/load is broken
- Infinite ammo related buffs are broken
- Furious Fusion stops working every time you sell a weapon?
- Look into summons always attacking the Force Wall object
- Whenever allied Arch-viles resurrect enemies they becomes allied too, but their auras act versus you
- Unequpping a shield eccessory that isn't equipped tries to run script 0
- Nuclear bomb event HUD not removed on next map if you escape rather than defuse
- Co-op PIP is still not working properly

New Augmentation System
===
- Remove shield accessories, they will simply become a 4th part to shield building
- Completely rewrite the Augmentation system to support categories, multiple enabled effects, and easier to handle/read battery usage
- Remove the current HUD widget and move its info up into the Credits/Module/Medkit widget, since they will play a much more active part in-game, the battery should be visible at all times with effects active
- Revamp and recategorize all the accessory effects into their own categories (Yholl offered to do this)
- Make the effects more generic and not just tailored to shields (Yholl offered to do this)
- Upgrading effects will have different benefits depending on the effect type
  - Static effects offer a few levels and change fairly drastically between upgrades
  - Scaled effects have a max level of 100 and scale their bonus slowly
  - Optimized effects have 10? levels which decrease the battery usage, but don't modify the effect at all
- Slot upgrades can only be used on a single category, which will increase the maximum effects you can have active in the specified category by 1
- The initial unlock of an augmentation will require a normal canister, further upgrades to it will require an upgrade canister
- Some effects will only discharge battery when used or triggered, while others discharge passively while active

New Shield System
===
To be rewritten into a more randomized parts system which is easier to handle and maintain, details later

Sprinting/Dodging System
===
- This can utilize DRLA's existing stamina system, don't really see any point in having such a system in vanilla where the enemies are much less varied and agile

Rewrites/Reorganization
===
- GUI System, Finish the GUI library and move all menu and related things to using it
- Arena System to support separate arena maps and their own self-contained scripting
