# Project Room-Quality-Station / 2022WS_team4

For a detailed description of how this project has been made refer to the [wiki](https://github.com/La-Hai-Nam/Raspi_Room-Quality-Station/wiki).

## Purpose
This project shall fullfill the [planning phase](https://github.com/La-Hai-Nam/Raspi_Room-Quality-Station/wiki/Concept), the [concept phase](https://github.com/La-Hai-Nam/Raspi_Room-Quality-Station/wiki/Concept), the [design phase](https://github.com/La-Hai-Nam/Raspi_Room-Quality-Station/wiki/Design), the [implementation phase](https://github.com/La-Hai-Nam/Raspi_Room-Quality-Station/wiki/Implementation), the [testing phase](https://github.com/La-Hai-Nam/Raspi_Room-Quality-Station/wiki/Test) and the [finalization phase](https://github.com/La-Hai-Nam/Raspi_Room-Quality-Station/wiki/Finalization) of developing and building a device called Room-Quality-Station. 

The station gives an overview about room climate values and signals the user, if the room quality should be improved.
To have an overview about the whole project it is recommended to read starting with the [planning phase](https://gitlab.rz.htw-berlin.de/c71_cse/2022ws_team4/-/wikis/Planning).

## General structure

### General
- [Requirements](https://gitlab.rz.htw-berlin.de/c71_cse/2022ws_team4/-/requirements_management/requirements)(requirment list does not exist on github only on gitlab): The requirements show what the device shall fullfill in this project
- [Use-cases:](https://github.com/La-Hai-Nam/Raspi_Room-Quality-Station/wiki/Concept#use-cases): The use-cases shows all possible use scenarios
- [Operating concept](https://github.com/La-Hai-Nam/Raspi_Room-Quality-Station/wiki/Design#operating-concept): This concept shows how the standard process of using the device should happen, that means it shows the following scenarios of the [use-cases](https://github.com/La-Hai-Nam/Raspi_Room-Quality-Station/wiki/Concept#use-cases) in the following order: 
    1) Startup, main scenario 
    2) Room-Quality-Report, main and all alternate scenarios 
    3) Shutdown, main scenario

### Technical documentation
- [Operating Manual](https://github.com/La-Hai-Nam/Raspi_Room-Quality-Station/blob/main/Documentation/Operating_Manual.pdf): Shows a function diagram about different situations and what will happen after different actions 
- [Hardware Concept](https://github.com/La-Hai-Nam/Raspi_Room-Quality-Station/wiki/Concept#hardware-concept): Shows what main hardware components the device has and how the connections between them are implemented
- [Hardware/Software mapping](https://github.com/La-Hai-Nam/Raspi_Room-Quality-Station/wiki/Concept#hardwaresoftware-mapping): Shows what main software components the device has and how the connections between them and some of the main hardware components are implemented
- [Traceability table](https://github.com/La-Hai-Nam/Raspi_Room-Quality-Station/wiki/Concept#traceability-table): Shows which use-case contains which requirement(s)

### Technical artifacts
- [Source code](https://github.com/La-Hai-Nam/Raspi_Room-Quality-Station/tree/main/room-quality-station): The source code contains the C-Codes that makes software of the device working

### Milestones
- [Milestone 1 (Planning and concept phase)](https://github.com/La-Hai-Nam/Raspi_Room-Quality-Station/wiki/Planning#milestone-1) 
- [Milestone 2 (Design, implementation and testing phase)](https://github.com/La-Hai-Nam/Raspi_Room-Quality-Station/wiki/Planning#milestone-2)
- [Milestone 3 (Finalization Phase)](https://github.com/La-Hai-Nam/Raspi_Room-Quality-Station/wiki/Planning#milestone-3)

### Milestone presentations
- [M1 presentation](https://github.com/La-Hai-Nam/Raspi_Room-Quality-Station/blob/main/Documentation/PCSE_M1-Vortrag_TeamD.pdf)
- [M2 presentation](https://github.com/La-Hai-Nam/Raspi_Room-Quality-Station/blob/main/Documentation/PCSE_M2-Vortrag_TeamD.pdf)

### Changes after milestone presentations
- Name change from "Weather station" to "Room quality station" after M1 presentation; The cause was to find a more suitable name
- Improved the tracibility table after M1 presentation
- Measurement values added after M1 presentation: Humidity, air quality; The cause was that we have chosen a better sensor
- Measurement values removed after M1 presentation: CO2-level; The cause was that CO2-sensors are too expensive and not needed (because of air quality is added)
- Changed the connection between the Raspberry Pi and the display from I²C to SPI after M1 presentation; The cause was that the display needs some hardware changes to run over I²C, that changes are very impractical
- Added a buzzer to the project after M1 presentation; The cause was that we wanted to add an alarm function in the case of a threshold exceeding
- Changes in the hardware concept after M1 presentation based on the last four mentioned points



## Roadmap
Click to see a roadmap of the whole project: [Link](https://github.com/La-Hai-Nam/Raspi_Room-Quality-Station/blob/main/Documentation/Roadmap.png)

