#ifndef VARS
#define VARS

#include <vector>
#include <FTGL/ftgl.h>
#include "view.hpp"
#include "math.hpp"

/* This files defines global variables which affects the behavior of all
 * the program. Hence the name state
 */

// forward declare not to have dependecy problems
void mainView();

namespace state {
	bool fullscreen = false;

	int width = 800;
	int height = 600;
	
	// view rect
	View view(-6.0, -(6.0*height/width), 12, 12.0*height/width, width, height);
	
	// set how many lines of the cartesian grid to be drawed
	double depth = 2;
	
	// this deretmines which command is active (find a zero, integral, etc)
	// 0 for nothing
	int command = 0;
	// if the command needs some points, this int specifies how many still
	// have to be collected
	int get_points = 0;

	bool* keyStates = new bool[256];
	bool* specialKeyStates = new bool[256];
	
	int mouse_x, mouse_y;
	bool* mouseStates = new bool[10];
	
	std::vector<Function*> functions;
	
	// points used for varous tasks
	std::vector<double> points;
	
	// set every how many pixels the program should plot the functions
	int step = 2;
	
	FTFont* normal_font;
}

#endif