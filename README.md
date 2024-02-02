# buffon_needle
Simulation of the Buffon's needle problem, used to approximate Pi.

Full explanation:
https://en.wikipedia.org/wiki/Buffon%27s_needle_problem

This repo uses raylib as a submodule, do:

`git clone https://github.com/JohannHahn/buffon_needle.git --recurse-submodules`
to get all the files.

Raylib:
https://github.com/raysan5/raylib

Build:
CMakeLists is provided, run something like:

`cmake -S . -G "Your generator of choice"`

Running:
You can just run it as is, or provide exactly 3 arguments in the terminal: 
1. window width
2. window height
3. number of lines

Some combination of arguments seem to give better approximations.
The standart configuration is good to at least get pi ~ 3.1
