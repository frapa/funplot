#ifndef OPENGL_FUN
#define OPENGL_FUN

#include "vars.hpp"

void displayInit () {
	glClearColor(1.0, 1.0, 1.0, 1.0); // Clear the background
	
	glClear (GL_COLOR_BUFFER_BIT); //Clear the colour buffer (more buffers later on)
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glEnable(GL_MULTISAMPLE_ARB);
	
	glLoadIdentity();  // Load the Identity Matrix to reset our drawing locations
}
	
void displayEnd () {
	glutSwapBuffers(); // Swap the OpenGL buffers to the window
}

void reshape (int new_width, int new_height) {
	state::width = new_width;
	state::height = new_height;
	
	state::view.setScreen(new_width, new_height);
	
	// Set our viewport to the size of our window
	glViewport(0, 0, (GLsizei)state::width, (GLsizei)state::height); 
	
	// Switch to the projection matrix so that we can manipulate how our scene is viewed
	glMatrixMode(GL_PROJECTION);
	
	// Start our projection modifications
	glPushMatrix();
	
	// Reset the projection matrix to the identity matrix so that we don't get any artifacts
	// (cleaning up)
	glLoadIdentity(); 
	
	// Set 2D perspective
	gluOrtho2D(0, state::width, 0, state::height);
	
	// Switch back to the model view matrix, so that we can start drawing shapes correctly
	glMatrixMode(GL_MODELVIEW);
}

void keyDown(unsigned char key, int x, int y) {
	int mod = glutGetModifiers();
	
	if (key == 'z') {
		state::points.clear();
		state::command = 10; // stands for find a zero
		state::get_points = 2;
	}
	
	state::keyStates[key] = true;
}

void keyUp(unsigned char key, int x, int y) {
	state::keyStates[key] = false;
}

void specialKeyDown(int key, int x, int y) {
	state::specialKeyStates[key] = true;
}

void specialKeyUp(int key, int x, int y) {
	state::specialKeyStates[key] = false;
}

void mouseClick(int button, int action, int x, int y) {
	state::mouseStates[button] = !action;
	
	if (button == 0 and action == GLUT_UP) {
		// if points have to be taken for the current command
		// save this point
		if (state::get_points != 0) {
			state::points.push_back(state::view.toPlaneX(x));
			state::get_points -= 1;
		}
	} else if (button == 4) {
		state::view.zoom(1.25);
	} else if (button == 3) {
		state::view.zoom(0.8);
	}
	
	state::mouse_x = x;
	state::mouse_y = state::height - y;
	
	// find out whether an action should be taken
	if (state::get_points == 0) {
		// if the user want to calculare the zero of the function
		if (state::command == 10) {
			if (state::functions[0]->zero(state::points[0], state::points[1]) < state::points[0]) {
				std::cout << "No solution between " << state::points[0] << " and "
					<< state::points[1] << std::endl;
			} else {
				std::cout.precision(10);
				std::cout <<
					"The solution between " << state::points[0] << " and " << state::points[1] <<
					" is: " << state::functions[0]->zero(state::points[0], state::points[1])
					<< std::endl;
			}
			state::command = 0;
		}
	}
	
	glutPostRedisplay();
}

void mouseMotion(int x, int y) {
	state::mouse_x = x;
	state::mouse_y = state::height - y;
}

void mouseClickedMotion(int x, int y) {
	int dx = x - state::mouse_x;
	int dy = (state::height - y) - state::mouse_y;
	
	if (state::mouseStates[GLUT_LEFT_BUTTON]) {
		state::view.move(-state::view.toXScale(dx), -state::view.toYScale(dy));
	}
	
	state::mouse_x = x;
	state::mouse_y = state::height - y;
	
	glutPostRedisplay();
}

#endif