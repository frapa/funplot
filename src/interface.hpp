#ifndef INTERFACE
#define INTERFACE

#include "vars.hpp"
#include "opengl.hpp"
#include "drawing_functions.hpp"

void mainView() {
	displayInit();
	
	renderGrid();
	renderFunction();
	
	displayEnd();
}

#endif