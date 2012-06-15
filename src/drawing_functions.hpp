#ifndef DRAWING
#define DRAWING

#include <sstream>
#include "vars.hpp"
#include "math.hpp"

void renderGrid() {
	std::stringstream converter;
	
	double magnitude = 1;
	if (state::view.width >= 1) {
		while (true){
			if (state::view.width / magnitude > 10) {
				magnitude *= 10;
			} else {
				break;
			}
		}
	} else {
		while (true){
			if (state::view.width / magnitude < 0.1) {
				magnitude *= 0.1;
			} else {
				break;
			}
		}
	}
	
	if (state::depth > 1) {
		glColor4f(0.9, 0.9, 0.9, 1.0);
		
		double step_x, start_x;
		if (state::view.width / magnitude < 4) {
			step_x = magnitude / 10;
			start_x = int(state::view.left / (magnitude / 10)) *
				(magnitude / 10);
		} else {
			step_x = magnitude;
			start_x = int(state::view.left / (magnitude)) *
				(magnitude);
		}
		
		double step_y, start_y;
		if (state::view.height / magnitude < 4) {
			step_y = magnitude / 10;
			start_y = int(state::view.bottom / (magnitude / 10)) *
				(magnitude / 10);
		} else {
			step_y = magnitude;
			start_y = int(state::view.bottom / (magnitude)) *
				(magnitude);
		}
			
		// start drawing
		glBegin(GL_LINES);
			for (double x = start_x; x <= state::view.right; x += step_x) {
				glVertex2f(state::view.toScreenX(x), 0);
				glVertex2f(state::view.toScreenX(x), state::height);
			}
			
			for (double y = start_y; y <= state::view.top; y += step_y) {
				glVertex2f(0, state::view.toScreenY(y));
				glVertex2f(state::width, state::view.toScreenY(y));
			}
		glEnd();
	}
	
	// render major lines if depth > 1
	/*if (state::depth > 1) {
		glColor4f(0.9, 0.9, 0.9, 1.0);
		
		// Compute number of needed majot lines
		// There should be a major line every 60 pixels.
		double nx = state::width / 80.0;
		double ny = state::height / 80.0;
		
		
		
		std::cout << magnitude << std::endl;
		
		int step_x = state::view.width / nx;
		int start_x = state::view.left - step_x *
			((state::view.left / step_x) - int(state::view.left / step_x));
		
		int step_y = state::view.height / ny;
		int start_y = state::view.bottom - step_y *
			((state::view.bottom / step_y) - int(state::view.bottom / step_y));
		
		// start drawing
		glBegin(GL_LINES);
		if (state::view.width / nx > 1) {
				for (int x = start_x; x <= state::view.right; x += step_x) {
					glVertex2f(state::view.toScreenX(x), 0);
					glVertex2f(state::view.toScreenX(x), state::height);
				}
		}
		
		if (state::view.height / ny > 1) {
			for (int y = start_y; y <= state::view.top; y += step_y) {
				glVertex2f(0, state::view.toScreenY(y));
				glVertex2f(state::width, state::view.toScreenY(y));
			}
		}
		glEnd();
		
		// print numbers	
		glColor4f(0.3, 0.3, 0.3, 1.0);
		if (state::view.width / nx > 1) {
			for (int x = start_x; x <= state::view.right; x += step_x) {
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
		}
		
		if (state::view.height / ny > 1) {
			for (int y = start_y; y <= int(state::view.top); y += step_y) {
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
	}*/
	
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
			try {
				y = (*state::functions[0])(state::view.toPlaneX(x));
				glVertex2f(x, state::view.toScreenY(y));
			} catch (int e) {
				if (e == OUT_OF_DOMAIN_ERROR) {
					;
				}
			}
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