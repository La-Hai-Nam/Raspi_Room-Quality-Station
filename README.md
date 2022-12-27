# Project Room-Quality-Station / 2022WS_team4

## Purpose
This project shall fullfill the [planning phase](https://gitlab.rz.htw-berlin.de/c71_cse/2022ws_team4/-/wikis/Planning), the [concept phase](https://gitlab.rz.htw-berlin.de/c71_cse/2022ws_team4/-/wikis/Concept), the [design phase](https://gitlab.rz.htw-berlin.de/c71_cse/2022ws_team4/-/wikis/Design), the [implementation phase](https://gitlab.rz.htw-berlin.de/c71_cse/2022ws_team4/-/wikis/Implementation), the [testing phase](https://gitlab.rz.htw-berlin.de/c71_cse/2022ws_team4/-/wikis/Test) and the [finalization phase](https://gitlab.rz.htw-berlin.de/c71_cse/2022ws_team4/-/wikis/Finalization) of developing and building a device called Room-Quality-Station. 

The station gives an overview about room climate values and signals the user, if the room quality should be improved.
To have an overview about the whole project it is recommended to read the [planning page](https://gitlab.rz.htw-berlin.de/c71_cse/2022ws_team4/-/wikis/Planning).

## General structure

### General
- [Requirements](https://gitlab.rz.htw-berlin.de/c71_cse/2022ws_team4/-/requirements_management/requirements): The requirements show what the device shall fullfill in this project
- [Use-cases:](https://gitlab.rz.htw-berlin.de/c71_cse/2022ws_team4/-/wikis/Concept#use-cases): The use-cases shows all possible use scenarios
- [Operating concept](https://gitlab.rz.htw-berlin.de/c71_cse/2022ws_team4/-/wikis/Design#operating-concept): This concept shows how the standard process of using the device should happen, that means it shows the following scenarios of the [use-cases](https://gitlab.rz.htw-berlin.de/c71_cse/2022ws_team4/-/wikis/Concept#use-cases) in the following order: 
    1) Startup, main scenario 
    2) Room-Quality-Report, main and all alternate scenarios 
    3) Shutdown, main scenario

### Technical documentation
- [Operating Manual](https://gitlab.rz.htw-berlin.de/c71_cse/2022ws_team4/-/wikis/Design#operating-mode-diagram): Shows a function diagram about different situations and what will happen after different actions 
- [Hardware Concept](https://gitlab.rz.htw-berlin.de/c71_cse/2022ws_team4/-/wikis/Concept#hardware-concept): Shows what main hardware components the device has and how the connections between them are implemented
- [Hardware/Software mapping](https://gitlab.rz.htw-berlin.de/c71_cse/2022ws_team4/-/wikis/Concept#hardwaresoftware-mapping): Shows what main software components the device has and how the connections between them and some of the main hardware components are implemented
- [Traceability table](https://gitlab.rz.htw-berlin.de/c71_cse/2022ws_team4/-/wikis/Concept#traceability-table): Shows which use-case contains which requirement(s)

### Technical artifacts
- [Source code](https://gitlab.rz.htw-berlin.de/c71_cse/2022ws_team4/-/tree/main/source_code/sensor): The source code contains the C-Codes that makes software of the device working

### Milestones
- [Milestone 1 (Planning and concept phase)](https://gitlab.rz.htw-berlin.de/c71_cse/2022ws_team4/-/wikis/Planning#milestone-1) 
- [Milestone 2 (Design, implementation and testing phase)](https://gitlab.rz.htw-berlin.de/c71_cse/2022ws_team4/-/wikis/Planning#milestone-2)
- [Milestone 3 (Finalization Phase)](https://gitlab.rz.htw-berlin.de/c71_cse/2022ws_team4/-/wikis/Planning#milestone-3)

### Milestone presentations
- [M1 presentation](https://gitlab.rz.htw-berlin.de/c71_cse/2022ws_team4/-/blob/main/Documentation/PCSE_M1-Vortrag_TeamD.pdf)

### Changes after milestone presentations
- Name change from "Weather station" to "Room quality station" after M1 presentation; The cause was to find a more suitable name
- Measurement values added after M1 presentation: Humidity, air quality; The cause was that we have chosen a better sensor
- Measurement values removed after M1 presentation: CO2-level; The cause was that CO2-sensors are too expensive and not needed (because of air quality is added)
- Improved the tracibility table after M1 presentation
- Changes in the hardware concept after M1 presentation based on the adding and removing measurement values changes


## Roadmap
... in work ... 

