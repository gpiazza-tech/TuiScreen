# TuiScreen

TuiScreen is a tiny and efficient C library for turning the console window into a 2D canvas thats simple to use. 
Great for making small UI console applications or games without all the boilerplate.

## How to build

Windows
	- Install git and Visual Studio 2026
	- Clone the repository: `git clone https://github.com/gpiazza-tech/TuiScreen`
	- Run scripts/Setup-Windows.bat to build as a static library or scripts/Setup-Examples-Windows.bat to build an example application.
	- Open the generated .sln file in Visual Studio and build
	
Linux
	- Install git, gcc, and make: `sudo apt install build-essential git`
	- Clone the repository: `git clone https://github.com/gpiazza-tech/TuiScreen`
	- Run `scripts/Setup-Linux.sh` to build as a static library or `scripts/Setup-Examples-Linux.sh` to build the included example application.
	(You may need to enable execution permissions first with `sudo chmod +x scripts/Setup-Linux.sh`)
	- Run `make` to build the project