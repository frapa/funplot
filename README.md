# Funplot

Funplot is a small program written in C++ that plots functions.
It uses opengl for rendering and make use of the hardware accelleration
capabilities of the graphic card.

## Dependencies

You need to have opengl and freeglut installed to run the program.
If you want to compile funplot, you also need the development versione
(i.e. header files) of these two libraries. The packages of the development
versions usually have -dev at the end (for instance freeglut3-dev)

## Compile and run

In order to compile funplot you need to install scons, a building software,
and to have g++ installed. Then just run:

	scons

This will compile the program. To run it, just type:

	./funplot

Here I assumed you are on a Unix machine. Anyway it should also work, with few
changes, on other operating systems.