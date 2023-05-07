# OpenPF2 for Unreal Engine

<img src="./Logo.png#gh-light-mode-only" title="OpenPF2 Logo" alt="Tabletop made of four arrows pointing toward the center of the table, with the tagline 'Just add story.'" width="512">

A plug-in for Unreal Engine that provides logic and content for building an RPG
with mechanics similar to Pathfinder&trade; 2nd Edition by Paizo Publishing.

All abilities and stats are implemented using the Gameplay Ability System (GAS)
plug-in that ships with Unreal Engine.

## Why OpenPF2?

OpenPF2 is a labor of love from experienced developers who believe in the power
of UE and want to bring that power to role-playing game development. We’re here
to give independent game developers the structure, starting content, and support
to experiment and implement Action RPGs or turn-based RPGs quickly, with as
little or as much C++ code as they feel comfortable with.

Unlike other RPG frameworks on the Unreal Marketplace, OpenPF2 is:
- **Open-source (here on GitHub),** so you can always look under the hood and
  suggest or contribute changes.
- **Free to use in any UE project.** We believe that the best kind of
  prototyping shouldn’t cost you anything.
- **Available for commercial licensing.** As a proof-of-concept blossoms into a
  closed-source venture, we’re open to licensing our code privately for a fee,
  so you don’t need to deal with the complexity of sharing parts of your
  codebase if you require full control of your IP.
- **More than just a framework.** OpenPF2 is preloaded with **content** based on
  the Pathfinder® Second Edition Core Rulebook, making it easy to create new
  characters and enemies by filling out character sheets rather than having to
  implement and balance your own stats.
- **Modular and pluggable.** Use as little or as much of our existing classes
  and content as you like in your project. 
    - Each system in the framework communicates with other systems through
      standard interfaces (in the `UINTERFACE` sense), so every major component
      can be replaced with a custom component if you don't like the default
      implementation. 
    - All PF2 sample content from the core rulebook is in a separate section
      from content required for the framework to function, so you can pick
      whichever parts you want to include or completely roll your own without
      breaking the essential framework parts.      
- **Blueprint-friendly.** Most of the framework is exposed to Blueprint so you
  can dive in and build prototypes or assemble production-grade abilities right
  from the start with a minimum of C++ knowledge.
- **Built on the Gameplay Ability System (GAS)**–a standard component of
  Unreal Engine supported by Epic Games, rather than a custom,
  in-house framework. GAS plays nicely with other plug-ins and frameworks and
  receives updates and improvements from Epic themselves.

## Compatibility

This plug-in is only maintained and compatible with Unreal Engine 5.1 and later.

## Current Status

**This plug-in is in pre-alpha status. It is not yet expected to be useful for
production-grade projects, but it may be a useful reference for you even in
its current state.**

We are attempting to model as much of the PF2 Core Rulebook as possible. But,
before we can do that, the base framework and a proof-of-concept set of MVP 
scope needs to be completed. You can can track our progress so far using the
[issue tracker](https://github.com/OpenPF2/PF2Core/issues?q=is%3Aissue+is%3Aclosed).
At a high level, the MVP scope includes:
- 1 **character ancestry** (Human), with **4 heritages**.
- 1 **character class** (Barbarian).
- 1 **archetype** (Barbarian).
- **35 character backgrounds**.
- **17 skills** _(already modeled as of November 2021)_, and **skill actions**.
- **Dice/rolling** math library _(already implemented as of December 2021)_.
- Various **Kismet/Blueprint function libraries** for all math sourced from the 
  Core Rulebook _(development on-going)_.
- **Network-ready** game logic _(development on-going; all parts of PF2 are
  being developed and tested with networking ability from the start)_.
- **Character stats** as Gameplay Attribute Sets _(already implemented as of 
  November 2021)_.
- **Character metadata** including **languages known**, **alignment**, and 
  **deity**.
- **Character creation UI:** A basic one, included as a starter template to be
  customized by game designers.
- Items and equipment:
  - **Character inventory**, **equipment management**, and associated UI.
  - Ability to **equip/un-equip pieces of equipment**.
  - **Handedness** of equipment.
  - **Bulk** tracking.
  - **Currency and equipment cost** tracking.
  - **Item level**.
  - **Armor** types and armor class.
  - **Damage to items and equipment:** Items can take damage and become 
    destroyed from use.
- **Encounter/exploration/down-time mode** system with rules-switching for each 
  _(development already in progress)_.
- **Automatic transitions** from **exploration into encounter** mode upon enemy
  sighting _(development already in progress)_.
- **Encounter** rules _(development already in progress)_.
  - **Encounter participant tracking** (i.e., which characters of the party and
    which "enemy" NPCs are in the encounter, with ability for characters to be
    added after encounter has already started).
  - Automatic **rolling of initiative** when characters join encounters.
  - **Combat following initiative order**, with either **turn-based or real-time
    player controls and interactions** _(development already in progress)_.
  - Actions:
    - **Binding actions to controls**, including associated UI for bindings.
    - **Action queuing** (i.e., allowing player to queue actions in real time to
      be executed when it is their turn, per initiative order) _(Completed as of
      November 2022)_.
    - **Action selection**, including associated UI for selecting actions.
    - **Actions with triggers**.
    - **Action points** enforcement (e.g., one-point actions, two-point actions,
      reactions, free actions).
    - **Reactions** with triggers.
- Special **attack-damage-stacking** rules (e.g., take highest of a given type
  of damage rather than stacking).
- Constrained movement and range of movement.
- **End-of-encounter rewards:**
  - **Hero Points**.
  - **Experience points (XP)**.
  - **Loot drops**
  - **Character level-up** based on experience (XP).
  - **Ability boosts** and associated UI
- **Feats:**
  - All **general feats**.
  - **Ancestry feats** (Humans only, for now, since only Human ancestry is being
    implemented for MVP).
  - **Class feats** (Barbarians only, for now, since only the Barbarian class is
    being implemented for MVP).
  - **Feat selection** and associated UI.
- **Conditions and afflictions** (poisoned, stunned, unconscious, etc.)
- **Hit points and health tracking**.
- **Damage types** as GAS Gameplay Effects and **damage type resistances** as
  GAS Gameplay Attributes _(development already in progress)_.
- **Difficulty class (DC)** and other types of **checks**, including related
  math and rolls:
  - Attack rolls
  - Perception
  - Saving throws
  - Skill checks
  - Flat checks
  - Secret checks
  - Damage checks
- **Down-time mode**:
  - Long-term rest.
  - Skill re-training.
- **Metric units** for all measurements (e.g., reach, height, stride, etc.).
- **All weapons** outlined in Chapter 6, "Equipment" of Core Rulebook.

## Note on Units

Pathfinder 2E materials—including the Core Rulebook—use imperial units
(feet), but Unreal Engine uses metric units, so OpenPF2 does as well. In the
real world, 1 foot is equal to 0.3048 meters; but, to avoid having to deal with
decimal values, OpenPF2 uses a simple conversion of `1.5 meters per 5 feet`
that slightly rounds values (1.5 meters equals ~4.92 feet in the real world).

To convert units provided by Pathfinder 2E materials into those used in
OpenPF2, simply multiply the provided value (in feet) by a ratio of `1.5/5`.
For example, if a weapon has a range of 60 feet, then its range in OpenPF2 is
`60 feet * 1.5 meters/5 feet = 18 meters`.

## Installation

1. Check-out the project into the `Plugins/` folder of your larger UE5 project.
   Ensure that the folder into which you check-out the project is named 
   `OpenPF2Core`.
2. Modify the `*.uproject` file of your larger UE5 project to ensure that both
   the `OpenPF2Core` and `GameplayAbilities` plug-ins are enabled, like so:
   ```json
   "Plugins": [
     {
       "Name": "GameplayAbilities",
       "Enabled": true
     },
     {
       "Name": "OpenPF2Core",
       "Enabled": true
     }
   ]
   ```
3. Re-generate Visual Studio/Rider project files.
4. Edit the `*.Build.cs` file and add `"OpenPF2Core"` to the `PrivateDependencyModuleNames` section:
   ```C#
   PrivateDependencyModuleNames.AddRange(new string[]
   {
       "OpenPF2Core",
   });
   ```
5. Compile your project.
6. Copy the `Config/Tags/` folder from the plug-in into your project's `Config` folder.
   _Even in UE 5.1, this is still required. The engine
   [does not automatically scan or package config files provided by plugins](https://docs.unrealengine.com/5.1/en-US/plugins-in-unreal-engine/#pluginsinprojects)._

## Licensing

### Open-source Licenses

Since this plug-in incorporates content and elements that were originally
created by Paizo Publishing, the code in this repository is licensed under a
mix of the Open Game License (OGL) version 1.0a and the Mozilla Public License
version 2.0. See [LICENSE.txt](LICENSE.txt) for details on what portions of the
code base are covered by each license.

All code in this project is licensed in a way that is compatible with the
[Unreal Engine End User License Agreement For Publishing](https://www.unrealengine.com/en-US/eula/publishing).
However, if you are attempting to use this code with other game engines
(e.g., Unity) or projects that are not based on Unreal Engine, be aware that
rare, select portions of the code are licensed from Epic Games only for use
with Unreal Engine and will need to be removed from your copy of the project.

For information about precisely which license applies to a source file, consult
its file header. If you encounter a file that lacks a license in its header,
please [file an issue](https://github.com/OpenPF2/PF2Core/issues/new). 

### Alternate, Commercial Licensing (for Proprietary Projects)

If you are developing a commercial, proprietary, or closed-source game or
project that is otherwise incompatible with the open-source OGL and MPL 
licensing of this plug-in, the author is willing to discuss alternate, custom 
licensing. 

The license will be among the following parties:
* The licensee (you).
* The author of this plug-in project (Guy Elsmore-Paddock).
* Paizo Publishing (for Pathfinder 2E Core Mechanics).

If you are interested in a custom license, please reach out to us (see 
"Reach Out" below). 


## Reach Out

Interested in joining the project? Having trouble getting started with the code?
Want to explore a custom license? Here are a few ways to get in touch with us:

- [Join our Discord server](https://discord.gg/8HtYdvNNWd)
- [DM the project lead (Guy) on Reddit](https://www.reddit.com/message/compose/?to=GuyPaddock).

---
<small>
Paizo and Pathfinder are trademarks of Paizo Inc. Nothing in this project is
officially sanctioned or endorsed by Paizo Publishing.
</small>
