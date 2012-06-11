#ifndef DRAWING
#define DRAWING

#include <sstream>
#include "vars.hpp"
#include "math.hpp"

void renderGrid() {
	std::stringstream converter;
	
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
		
		// print numbers	
		glColor4f(0.3, 0.3, 0.3, 1.0);
		for (int x = state::view.left; x <= int(state::view.right); ++x) {
			if (x != 0) {
				converter.clear();
				converter << x;
				std::string num_text;
				converter >> num_text;
				
				// get box of the text
				FTBBox box = state::normal_font->BBox(num_text.c_str());
				// adjust positioning
				FTPoint point(state::view.toScreenX(x) - box.Upper().X()/2.0,
					state::view.toScreenY(0) - box.Upper().Y() - 3);
				// display the number
				state::normal_font->Render(num_text.c_str(), -1, point);
			}
		}
		
		for (int y = state::view.bottom; y <= int(state::view.top); ++y) {
			if (y != 0) {
				converter.clear();
				converter << y;
				std::string num_text;
				converter >> num_text;
				
				// get box of the text
				FTBBox box = state::normal_font->BBox(num_text.c_str());
				// adjust positioning
				FTPoint point(state::view.toScreenX(0) - box.Upper().X() - 5,
					state::view.toScreenY(y) - box.Upper().Y()/2);
				// display the number
				state::normal_font->Render(num_text.c_str(), -1, point);
			}
		}
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
	
	// print 0
	glColor4f(0.3, 0.3, 0.3, 1.0);
	FTBBox box = state::normal_font->BBox("0");
	FTPoint point(state::view.toScreenX(0) - box.Upper().X() - 5,
		state::view.toScreenY(0) - box.Upper().Y() - 3);
	state::normal_font->Render("0", -1, point);
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