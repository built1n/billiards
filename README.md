Billiards
=========

A simple, 2D, extremely portable billiards game. Portability is it's main goal, followed by accuracy in the physics simulation.

Portability is achieved by means of a abstraction layer.

Compilation
===========

For SDL: just run `make`. The executable is `billiards-sdl`.

For Rockbox: run the `setup.sh` script in `platforms/rockbox/` and build Rockbox.

Good Coding Practices
=====================

&bull; Don't use globals (for KnightOS support)

&bull; Use a generic main() function (for Rockbox support)

&bull; Avoid floating-point math, used fixed-point instead (for performance reasons)

Current Status
==============

Wall-to-ball collision/handling works.

Ball-to-ball collision detection works, resolution is a WIP.
