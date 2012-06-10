#ifndef DRAWING
#define DRAWING

#include "vars.hpp"
#include "math.hpp"

void renderGrid() {
	// render major lines if depth > 1
	if (state::depth > 1) {
		glColor4f(0.9, 0.9, 0.9, 1.0);
		
		glBegin(GL_LINES);
			for (int x = state::view.left; x <= int(state::view.right); ++x) {
				glVertex2f(state::view.toScreenX(x), 0);
				glVertex2f(state::view.toScreenX(x), state::height);
			}
			
			for (int y = state::view.bottom; y <= int(state::view.top); ++y) {
				glVertex2f(0, state::view.toScreenY(y));
				glVertex2f(state::width, state::view.toScreenY(y));
			}
		glEnd();
	}
	
	// render axes (light gray)
	glColor4f(0.7, 0.7, 0.7, 1.0);
	glLineWidth(1.f);
	
	glBegin(GL_LINES);
		// x axis
		glVertex2f(0, state::view.toScreenY(0));
		glVertex2f(state::width, state::view.toScreenY(0));
		// y axis
		glVertex2f(state::view.toScreenX(0), 0);
		glVertex2f(state::view.toScreenX(0), state::height);
	glEnd();
}

void renderFunction() {
	// plot function (black line)
	glColor4f(0.0, 0.0, 0.0, 1.0);
	glLineWidth(1.f);
	
	double y;
	
	glBegin(GL_LINE_STRIP);
		// loop for each point on x axis
		for (int x = 0; x < state::width + state::step; x += state::step) {
			y = (*state::functions[0])(state::view.toPlaneX(x));
			glVertex2f(x, state::view.toScreenY(y));
		}
	glEnd();
}

/*
void renderDerivative() {
	// plot derivate
	glColor4f(0.0, 0.5, 0.0, 1.0);
	glLineWidth(1.f);
	
	glBegin(GL_LINE_STRIP);
		// almost same as before
		double d = 0;
		for (int x = 0; x < width; ++x) {
			d = grid.f1(x);
			glVertex2f(x, 300.f-d*80.f);
		}
	glEnd();
}


void renderSidebar() {
	// render sidebar background
	glColor4f(0.3, 0.3, 0.3, 0.9);
	
	glBegin(GL_QUADS);
		glVertex2f(width-sidebar_width, 0);
		glVertex2f(width, 0);
		glVertex2f(width, height);
		glVertex2f(width-sidebar_width, height);
	glEnd();
}
*/

#endif