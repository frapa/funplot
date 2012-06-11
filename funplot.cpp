#include <iostream>

// opengl headers
#include <GL/glew.h>
#include <GL/glut.h>

#include <FTGL/ftgl.h>

// fparser header for math functions evaluation
#include "fparser/fparser.hh"

// internal headers
#include "src/vars.hpp"
#include "src/opengl.hpp"
#include "src/drawing_functions.hpp"
#include "src/interface.hpp"
#include "src/math.hpp"

int main (int argc, char **argv) {
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE); 

	glutInitWindowSize(state::width, state::height); // Set the width and height of the window
	glutInitWindowPosition(100, 100); // Set the position of the window

	glutCreateWindow("Funplot"); // Set the title for the window
	
	glutDisplayFunc(mainView);
	glutReshapeFunc(reshape);
	
	glutMouseFunc(mouseClick);
	glutPassiveMotionFunc(mouseMotion);
	glutMotionFunc(mouseClickedMotion);
	
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	glutSpecialFunc(specialKeyDown);
	glutSpecialUpFunc(specialKeyUp);
	
	// init fonts
	state::normal_font = new FTGLTextureFont("./fonts/Inconsolata.otf");
	state::normal_font->FaceSize(16);
	
	// init functions
	state::functions.push_back(new Function(argv[1]));
	
	glutMainLoop(); // start mainloop
}