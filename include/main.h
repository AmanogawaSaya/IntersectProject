#pragma once
#include<vector>
using namespace std;

struct dot {
	double x;
	double y;

	bool operator < (const struct dot & b) const {
		if (x == b.x && y == b.y) {
			return false;
		}
		else if (x < b.x || x == b.x && y < b.y) {
			return true;
		}
		return false;
	}

	dot() {
		x = 0.0;
		y = 0.0;
	}

	dot(double x, double y) {
		dot::x = x;
		dot::y = y;
	}
};

/* line is y = kx + b -> Ax + By + C = 0*/
class line {
public:
	double k;
	double b;

	line(double x1, double y1, double x2, double y2) {
		line::k = (y2 - y1) / (x2 - x1);
		line::b = y1 - line::k * x1;
	}

	line(double k, double d) {
		line::k = k;
		line::b = d;
	}
};

class circle {
public:
	double x;
	double y;
	double r;

	circle(int x, int y, int r) {
		circle::x = x;
		circle::y = y;
		circle::r = r;
	}
};

void input(int num);
struct dot* calculate(line A, line B);
vector<double> level2Equation(vector<double> simple);
vector<double> getEquationForLC(line x, circle y);
void getLCcrossDot(line A, circle B);
line* get2CircleLine(circle a, circle b);