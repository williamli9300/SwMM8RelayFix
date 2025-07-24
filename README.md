# Swim Meet Manager 8.0 Relay Fix Script

#### by William Li | [https://github.com/williamli9300/SwMM8RelayFix](https://github.com/williamli9300/SwMM8RelayFix) | v3.0 release

A simple executable script to fix the Relay Team Names issue introduced in Hy-Tek Swim Meet Manager 8.0. 

**New in Version 3:** An version is included to simultaneously remove special characters (e.g. accents) to ensure compatibility with scoreboards that cannot display special characters.

Intended for use with SwissTiming Quantum-AQ Network File Sharing Start Lists (`quantum.slx`). A sample start list (mock-up names) is provided for testing.

This is the successor of the Relay Removal workaround (now deprecated; found [here](https://github.com/williamli9300/quantum-removerelays)).

## Table of Contents

1. [Use Case](#usecase)
2. [Compatibility](#compatibility)
3. [Instructions](#installation)
4. [Changelog](#changelog)
5. [Changes from Relay Removal Tool](#changes)

**Disclaimer:** The author of this script offers no warranty and disclaims all responsibility and/or liability for incidents relating to the use of this script. This script has been tested with real Quantum start lists before being published; however, you use this software at your own risk. Please ensure that qualified, technologically literate Quantum operators are present to supervise the process. 

Feedback is welcome! Please feel free to report any bugs, issues, and/or communicate feature requests or other forms of feedback to the author of the script.

Newest version is written C++, compiled using Visual Studio 2022 per ISO C++20 Standard.

## Compatibility <a name="compatibility"></a>

- Use with Hy-Tek Meet Manager 8.0 (tested with versions `Ca`, `Fd`, and `Fe`) and SwissTiming Quantum AQ.

- Built for use with Windows 11; compatible with Windows 10.

## Use Case <a name="usecase"></a>

### TLDR:

**The way that Hy-Tek Swim Meet Manager 8.0 creates Start List files has changed compared to Meet Manager 7.0. As a result, if you have relays in a session, athletes' teams may show up on the scoreboard as below. This script transforms the format used by MM7.0 so that the Team field shows up properly (without the relay indicator) for each athlete's individual events.** 

(Jump to [Instructions](#installation))

```
Event 1  Girls 200M Individual Medley   0.0
-------------------------------------------
Ln  Name                Team           Time
-------------------------------------------
1 - Rosario, Amani      CLUB
2 - Pace, Christina     CLUB-A
3 - Hester, Brinley     CLUB-A
4 - Atkins, Phoebe      CLUB
5 - Mora, Felicity      RELAY-B
6 - Robles, Rene        RELAY-C
7 - McIntosh, Carolyn   CLUB
8 - Greer, Aya          RELAY-A
```



### Extended Explanation

Hy-Tek Swim Meet Manager writes a semicolon-delimited Start List file to share names with Quantum. Each line contains information such as an ID number (Swimmer ID, Relay ID, Event ID, etc.). Quantum then indexes each line to build a list of all swimmers and relays swimming in the session, allowing you to search for and add a swimmer into a lane using the Quantum software.

Meet Manager 7 wrote the Relay entries in Start Lists with the following syntax: 

```
;relID;4;0;CLUB - A;;CLUB;Demonstration Team Swim Club;
;swID;5;1;LASTNAME,;Firstname;CLUB;Demonstration Team Swim Club;
;swID;5;2;LASTNAME,;Firstname;CLUB;Demonstration Team Swim Club;
;swID;5;3;LASTNAME,;Firstname;CLUB;Demonstration Team Swim Club;
;swID;5;4;LASTNAME,;Firstname;CLUB;Demonstration Team Swim Club;
```

with the first line columns corresponding to `Relay ID,` `Lane`, `Swimmer #` (0 for Relay Header), `Relay Name`, `Team Name`, and`Long Team Name`, and each subsequent line containing columns for `Swimmer ID` `Lane`, `Swimmer #`, `Last Name`, `First Name`, `Team Name`, and `Long Team Name`.

In Meet Manager 8, the syntax was changed, replacing `Team Name` with `RelayName`:

```
;relayID;4;0;CLUB - A;;CLUB;Demonstration Team Swim Club;
;swID;5;1;LASTNAME,;Firstname;CLUB-B;Demonstration Team Swim Club;
;swID;5;2;LASTNAME,;Firstname;CLUB-B;Demonstration Team Swim Club;
;swID;5;3;LASTNAME,;Firstname;CLUB-B;Demonstration Team Swim Club;
;swID;5;4;LASTNAME,;Firstname;CLUB-B;Demonstration Team Swim Club;
```

As a result, when Quantum indexes all athletes, their `Team Name` indicator is overwritten with a `Relay Name` indicator, even for their individual events, causing Quantum to display their Relay Name instead of their Team Name. (Whether it shows up as "RELAY-X" or "CLUB-X" depends on the Start List customization settings in Meet Manager.)

This tool reverts the Club/Nationality field for relay swimmers in the Quantum Start List back to MM7.0 format, by replacing the contents of the `Relay Name` field in each relay member's line to the `Team Name` field found in the Relay header.

Additionally, a version of the tool is provided that simultaneously removes all characters not compatible with the ASCII Printable Characters character set, by replacing common accented characters with their unaccented counterparts, and discarding other non-ASCII characters as a failsafe. This functionality is optional (choose your version) and intended to simultaneously fix start list compatibility with scoreboards that are unable to display non-ASCII characters.

## Instructions <a name="installation"></a>

**The recommended Relay Team Name format is `Team Abbr - A` or `Relay - A`, as the `Short Team Name` field may be configured improperly by teams in some regions. This can be changed under `Run > Interfaces > Scoreboard > Customize`.**

- Download and unzip the release package.
- Place `SwMM8RelayFixV3.exe` or `SwMM8RelayFixV3_RemoveSpecialChars.exe` into the Quantum Data Set directory (i.e., the folder containing `quantum.slx`)
- Simply double click the script to run. You may need to give the app permission to "Run Anyway".

Notes:

* The script is designed to work **in the same directory as the start list file**. For example, if your Quantum Data Set Working Directory is `C:\Quantum\Race\` (or, in other words, if your start list file is at `C:\Quantum\Race\quantum.slx`), the application should be found at `C:\Quantum\Race\SwMM8RelayFixV3.exe`.
* This script can be run in a network directory, e.g. in `\\CLERK-LAPTOP\Quantum\Race\`. If you are running the script in a network directory, you may see a notice that says `CMD.EXE was started with the above path as the current directory. UNC paths are not supported. Defaulting to Windows directory`. This is normal and occurs because the Command Prompt tries to open the network directory after the script has finished running. As long as you see `Done. File cleanup completed successfully.` or `Done. File cleanup and special character scrubbing completed successfully.`, the script was completed successfully.

## Changelog <a name="changelog"></a>

- v3.0
  
  - Modified debug output to be more verbose and easier to follow.
  - Includes a version that enables detection and removal of non ASCII characters.
  - Renamed executables `SwMM8RelayFixV3.exe` and `SwMM8RelayFixV3_RemoveSpecialChars.exe`.
  - Compiled as standalone executable (self-contained binary) by linking run-time libraries using `\MT` compiler option.
  - Signed with trusted certificate.
  - `README.md` updated with TLDRs and lengthier explanations.

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
