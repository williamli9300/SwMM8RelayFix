# Swim Meet Manager 8.0 Relay Fix Script

#### by William Li | [https://github.com/williamli9300/SwMM8RelayFix](https://github.com/williamli9300/SwMM8RelayFix) | v2.0 release

A simple executable script to fix the Relay Team Names bug introduced in Hy-Tek Swim Meet Manager 8.0. 

Meant for use with SwissTiming Quantum timing system start lists.

This is the successor of the Relay Removal workaround (now deprecated; found [here](https://github.com/williamli9300/quantum-removerelays)).

## Table of Contents

1. [Use Case](#usecase)
2. [Instructions](#installation)
3. [Changelog](#changelog)
4. [Changes from Relay Removal Tool](#changes)

Disclaimer: As per the included License, the author of this script offers no warranty and disclaims all responsibility and/or liability for incidents relating to the use of this script. This script has been tested with real Quantum start lists before being published; however, you use this software at your own risk. Please ensure that qualified, technologically literate Quantum operators are present to supervise the process. 

Feedback is welcome! Please feel free to report any bugs, issues, and/or communicate feature requests or other forms of feedback to the author of the script.

Script originally written in Python 3.10. Newest version is written C++, compiled using Visual Studio 2022 per ISO C++20 Standard.

## Use Case <a name="usecase"></a>

On some name- and team-name displaying scoreboards, a bug in the way that the Quantum-AQ Software reads start lists created by Hy-Tek Swim Meet Manager 8.0 can causes the Team Name/Nationality field to show up incorrectly during individual events, i.e. as a Relay Name (e.g. `RELAY-A`, `TEAM-A`, etc.) This bug is not present when using start list files generated by Meet Manager 7.0.

This tool reverts the Club/Nationality field for relay swimmers in the Quantum Start List back to MM7.0 format.

Recommended Relay Team Name format is `Team Abbr - A` or `Relay - A`, as the `Short Team Name` field may be configured improperly by teams in some regions. This can be changed under `Run > Interfaces > Scoreboard > Customize`.

## Instructions <a name="installation"></a>

- Download and unzip the release package.
- Place `MM8RelayFix2.exe` into the Quantum Data Set directory (i.e., the folder containing `quantum.slx`)
  - The script is designed to work **in the same directory as the start list file**. For example, if your Quantum Data Set Working Directory is `C:\Quantum\Race\` (or, in other words, if your start list file is at `C:\Quantum\Race\quantum.slx`), the application should be found at `C:\Quantum\Race\MM8RelayFix2.exe`. 
- Simply double click the script to run. You may need to give the app permission to "Run Anyway".

## Changelog <a name="changelog"></a>

- v2.0
  - Python script translated to C++ for native deployment.
  - (This means a 99% smaller filesize and more efficient software!)
  - Fixed minor issue in Python script that would add a new line to end of start list.
  - Python script kept in release for systems with Python preinstalled.
  - New C++ script updated to catch more exceptions.
  - `*.exe` executable now signed with trusted certificate.
  - Changes to license file.
  - Renamed executable `MM8RelayFix2.exe`
  - Minor updates, including addition of a changelog, to `README.md`.
- v1.1
  - Fixed filename errors from release v1.0.
  - Fixed minor formatting issues.
- v1.0
  - Initial release of `pyinstaller` compiled Python application!
  - Contained major issue: filenames not yet changed from debugging, resolved in next release.

## Changes from Relay Removal Tool <a name="changes"></a>

- The application is now standalone! This means only one `*.exe` file is needed — no more big folders full of strange files!
- The application is now fully automatic! This means that you no longer need to select options like meet format, or to follow lengthy instructions, in order to get it to work!
- The application is now a **proper fix**! This means it is no longer a workaround, and no longer requires you to rename files or move them around!
