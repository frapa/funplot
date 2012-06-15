#ifndef MATH_LIB
#define MATH_LIB

#include <string>
#include <cmath>
#include <exception>

#include "pre_macro.hpp"

class Function {
private:
	FunctionParser f;
	
public:
	Function(std::string text) {
		f.Parse(text.c_str(), "x, e, pi");
	}
	
	double eval (double x) {
		double vars[] = {x, 2.718281828459, 3.14159265358979};
		
		double y = f.Eval(vars);
		
		if (f.EvalError() != 0) {
			throw OUT_OF_DOMAIN_ERROR;
		}
		
		return y;
	}
	
	double operator() (double x) {
		eval(x);
	}
	
	// find the zero of the function between a and b
	double zero(double _a, double _b, double precision=1e-10) {
		double a(_a), b(_b);
		
		if (eval(a)*eval(b) > 0) {
			// then there are no zeros, return absurd value
			return a - 1;
		} else if (eval(a) == 0) {
			return a;
		} else if (eval(b) == 0) {
			return b;
		} else {
			double c;
			while (fabs(b - a) > precision) {
				c = a + (b - a) / 2;
				
				if (eval(c) == 0) {
					return c;
				} else	if (eval(a)*eval(c) < 0) {
					// solution is in (a, c)
					b = c;
				} else if (eval(b)*eval(c) < 0) {
					// solution is in (c, b)
					a = c;
				}
			}
			
			return round(a * 0.1/precision) * precision;
		}
	}
};

#endif