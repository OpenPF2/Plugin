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
Since this plug-in incorporates content and elements that were originally
created by Paizo Publishing, the code in this repository is licensed under a mix
of the Open Game License (OGL) version 1.0a. and the Mozilla Public License 
version 2.0. See [LICENSE.txt](LICENSE.txt) for details on what portions of the
code base are covered by each license.

---
<small>
Paizo and Pathfinder are trademarks of Paizo Inc. Nothing in this project is
officially sanctioned or endorsed by Paizo Publishing.
</small>
