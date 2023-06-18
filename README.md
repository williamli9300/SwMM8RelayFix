# Swim Meet Manager 8.0 Relay Fix Script
#### by William Li | [https://github.com/williamli9300/SwMM8RelayFix](https://github.com/williamli9300/SwMM8RelayFix) | v1.1 release

A simple executable script to fix the Relay Team Names bug introduced in Hy-Tek Swim Meet Manager 8.0. 

Meant for use with SwissTiming Quantum timing system start lists.

This is the successor of the Relay Removal workaround (now deprecated; found [here](https://github.com/williamli9300/quantum-removerelays)).

## Table of Contents
1. [Use Case](#usecase)
2. [Instructions](#installation)
3. [Changes from Relay Removal Tool](#changes)

Disclaimer: As per the included License, the author of this script offers no warranty and disclaims all responsibility and/or liability for incidents relating to the use of this script. This script has been tested with real Quantum start lists before being published; however, you use this software at your own risk. Please ensure that qualified, technologically literate Quantum operators are present to supervise the process. 

Feedback is welcome! Please feel free to report any bugs, issues, and/or communicate feature requests or other forms of feedback to the author of the script.

Script written in Python, compiled using PyInstaller.

## Use Case <a name="usecase"></a>
On some video boards, a bug in the way that the Quantum-AQ Software reads start lists created by Hy-Tek Swim Meet Manager 8.0 can causes the Team Name/Nationality field to show up incorrectly during individual events, i.e. as a Relay Name (e.g. `RELAY-A`, `TEAM-A`, etc.) This bug is not present when using start list files generated by Meet Manager 7.0.

This tool reverts the Club/Nationality field for relay swimmers in the Quantum Start List back to MM7.0 format.

Recommended Relay Team Name format is `Team Abbr - A` or `Relay - A`, as `Short Team Name` can cause issues with team name appearances depending on definitions in the `Teams` menu. This can be changed under can be changed under `Run > Interfaces > Scoreboard > Customize`.

## Instructions <a name="installation"></a>
- Download and unzip the release package.
- Place `MM8RelayFix.exe` into the Quantum Data Set directory (i.e. into the folder containing `quantum.slx`)
  - The script is designed to work **in the same directory as the start list file**. For example, if your QAQF Data Set is in `C:\Quantum\Race\` (or, in other words, if your start list file is at `C:\Quantum\Race\quantum.slx`, the application should be found at `C:\Quantum\Race\removerelays.exe`. 
- Simply double click the script to run. You may need to give the app permission to "Run Anyway".

## Changes from Relay Removal Tool <a name="changes"></a>
- The application is now standalone! This means only one `*.exe` file is needed — no more big folders full of strange files!
- The application is now fully automatic! This means that you no longer need to select options like meet format, or to follow lengthy instructions, in order to get it to work!
- The application is now a **proper fix**! This means it is no longer a workaround, and no longer requires you to rename files or move them around!
