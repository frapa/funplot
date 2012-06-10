#ifndef MATH_LIB
#define MATH_LIB

#include <string>

class Function {
private:
	FunctionParser f;
	
public:
	Function(std::string text) {
		f.Parse(text.c_str(), "x, e, pi");
	}
	
	double eval (double x) {
		double vars[] = {x, 2.718281828459, 3.14159265358979};
		return f.Eval(vars);
	}
	
	double operator() (double x) {
		eval(x);
	}
};

#endif