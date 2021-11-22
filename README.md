# OpenPF2 for Unreal Engine
A plug-in for Unreal Engine that provides logic and content for building an RPG
with mechanics similar to Pathfinder&trade; 2nd Edition by Paizo Publishing.

All abilities and stats are implemented using the Gameplay Ability System (GAS)
plug-in that ships with Unreal Engine.

## Status
This plug-in is still in an early stage of development. We are attempting to
model as much of the PF2 Core Rulebook as possible. You can track our progress
and see which parts of the PF2 Core Rulebook match which parts of the codebase
here:

https://1drv.ms/x/s!AigXEMxuXyh0gpRnYs8NlW-gC2oMnA?e=K8dHvP

## Installation
1. Check-out the project into the `Plugins/` folder of your larger UE4 project.
   Ensure that the folder into which you check-out the project is named 
   `OpenPF2Core`.
2. Modify the `*.uproject` file of your larger UE4 project to ensure that both
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
4. Compile your project.
5. Copy the `Config/Tags/` folder from the plug-in into your project's `Config` folder.
   _Even in UE 4.27, this is still required. The engine
   [does not automatically scan or package config files provided by plugins](https://docs.unrealengine.com/4.27/en-US/ProductionPipelines/Plugins/#pluginsinprojects)._

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

### Alternate Licensing (for Proprietary Projects)
If you are developing a commercial, proprietary, or closed-source game or
project that is otherwise incompatible with the open-source licensing of this
plug-in an alternate, custom license is an option. 

The license will be among the following parties:
* The licensee (you).
* The author of this plug-in project (Guy Elsmore-Paddock).
* Paizo Publishing (for Pathfinder 2E Core Mechanics).

If you are interested in a custom license, please [DM me on 
Twitter](https://twitter.com/guypaddock).

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

---
<small>
Paizo and Pathfinder are trademarks of Paizo Inc. Nothing in this project is
officially sanctioned or endorsed by Paizo Publishing.
</small>
