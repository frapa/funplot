#ifndef VARS
#define VARS

#include <vector>
#include "view.hpp"

/* This files defines global variables which affects the behavior of all
 * the program. Hence the name state
 */

// forward declare not to have dependecy problems
class Function;
void mainView();

namespace state {
	bool fullscreen = false;

	int width = 800;
	int height = 600;
	
	// view rect
	View view(-6.0, -(6.0*height/width), 12, 12.0*height/width, width, height);
	
	// set how many lines of the cartesian grid to be drawed
	double depth = 2;

	bool* keyStates = new bool[256];
	bool* specialKeyStates = new bool[256];
	
	int mouse_x, mouse_y;
	bool* mouseStates = new bool[10];
	
	std::vector<Function*> functions;
	
	// set every how many pixels the program should plot the functions
	int step = 2;
}

#endif