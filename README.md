## PSXJun

PSXJun is an amateur experimental low level emulator to learn more about computer architecture, using the PlayStation 1 as a case study. For an actual playable emulator, please check out the emulators listed below.

## Motivation

One aim of this project is to gain familiarity with writing a 3D engine as previous emulators I made used 2D pixel engines where I treated OpenGL merely as a way to blitz pixel quads.

I am also a fan of making things one enjoy, and as I enjoyed making 2D emulators, this seems to be a natural progression.

## Scope 

For now, I aim to get BIOS and games to boot before being playable. I do not expect to be able to make an emulator compatible with the entire PSX games library and I do not intend to support sound. 

## Build Instructions

TBD

## Resources

Below lists the resources I used in order to build my emulator. I will be adding to this list in the future.

* PlayStation Architecture: A practical analysis by Rodrigo Copetti
	* A useful overview of the PS1 architecture
		
* IDT R30xx Family Software Reference Manual
	* Details behavioral functionality of the R30xx family of MIPS microprocessors. The PSX uses a R3000A microprocessor.

## Other PSX Emulators

Please checkout the following emulators, which inspired me to make my own. I guarantee they run much better than PSXJun:

* https://github.com/stenzek/duckstation
* https://github.com/VelocityRa/pctation
* https://github.com/dkoluris/pseudo
* https://github.com/JaCzekanski/Avocado
