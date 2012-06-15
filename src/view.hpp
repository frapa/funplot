#ifndef VIEW
#define VIEW

class View {
public:
	double bottom, left, top, right;
	double width, height;
	int screen_width, screen_height;
	
	View(double l, double b, double w, double h, int sw, int sh):
		left(l), bottom(b), width(w), height(h),
		right(l + w), top(b + h),
		screen_width(sw), screen_height(sh)
	{}
	
	
	void setScreen(int sw, int sh) {
		screen_width = sw;
		screen_height = sh;
	}
	
	void move(double x, double y) {
		left += x;
		right += x;
		
		bottom += y;
		top += y;
	}
	
	void zoom(double z) {
		double new_width = width / z;
		double new_height = height / z;
		double mx = (width - new_width) / 2;
		double my = (height - new_height) / 2;
		
		left += mx;
		right -= mx;
		bottom += my;
		top -= my;
		
		width = new_width;
		height = new_height;
	}
	
	
	double toScreenX(double x) {
		double rx = x - left;
		double scale_x = screen_width / width;
		
		return rx * scale_x;
	}
	
	double toScreenY(double y) {
		double ry = y - bottom;
		double scale_y = screen_height / height;
		
		return ry * scale_y;
	}
	
	double toXScale(double x) {
		double scale_x = width / screen_width;
		
		return (x * scale_x);
	}
	
	double toPlaneX(double x) {
		return toXScale(x) + left;
	}
	
	double toYScale(double y) {
		double scale_y = height / screen_height;
		
		return (y * scale_y);
	}
	
	double toPlaneY(double y) {
		return toYScale(y) + bottom;
	}
	
	double getScaleX() {
		return screen_width / width;
	}
	
	double getScaleY() {
		return screen_height / height;
	}
};

#endif