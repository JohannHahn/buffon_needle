# buffon_needle
Simulation of the Buffon's needle problem, used to approximate Pi.

Usually people use Pi to create the randomly rotated sticks, but I think using Pi to approximate Pi is cheating :).

My method doesn't use Pi in any way for the approximation.
The randomly rotated sticks are created by first creating two random points 
and scaling the line they make to be of the predetermined length < the gap between the lines.

Full explanation of the problem:
https://en.wikipedia.org/wiki/Buffon%27s_needle_problem

This repo uses raylib as a submodule, do:

`git clone https://github.com/JohannHahn/buffon_needle.git --recurse-submodules`
to get all the files.

Raylib:
https://github.com/raysan5/raylib

Build:
CMakeLists is provided, run something like:

`cmake -S . -G "Your build system"`

Running:
You can just run it as is, or provide exactly 4 arguments in the terminal: 
1. window width
2. window height
3. number of lines
4. target fps

Some combination of arguments seem to give better approximations.
The standart configuration is good to at least get pi ~ 3.1
