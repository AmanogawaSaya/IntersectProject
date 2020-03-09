#pragma once
#include<vector>
using namespace std;

struct dot {
	double x;
	double y;

	bool operator == (const struct dot& b) const {
		return x == b.x && y == b.y;
	}

	bool operator < (const struct dot& b) const {
		if (x < b.x) {
			return true;
		}
		else if(x == b.x){
			if (y < b.y) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
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

struct myHashFuc
{
	std::size_t operator()(const struct dot & key) const
	{
		return std::hash<double>()(key.x + key.y);
	}
};

/* line is y = kx + b -> Ax + By + C = 0*/
class line {
public:
	double a;
	double b;
	double c;

	line() {
		a = 0.0;
		b = 0.0;
		c = 0.0;
	}

	line(double x1, double y1, double x2, double y2) {
		line::a = y2 - y1;
		line::b = x1 - x2;
		line::c = x2 * y1 - x1 * y2;
	}

	line(double a, double b, double c) {
		line::a = a;
		line::b = b;
		line::c = c;
	}
	double distance(struct dot X) {
		return fabs((a * X.x + b * X.y + c) / sqrt(a * a + b * b));
	}
};

class circle {
public:
	double x;
	double y;
	double r;

	circle() {
		x = 0.0;
		y = 0.0;
		r = 0.0;
	}

	circle(int x, int y, int r) {
		circle::x = x;
		circle::y = y;
		circle::r = r;
	}
};

void input(int num);
struct dot calculate(line A, line B);
vector<double> level2Equation(vector<double> simple);
vector<double> getEquationForLC(line x, circle y);
void getLCcrossDot(line A, circle B);
line* get2CircleLine(circle a, circle b);
void yParelLine(line A, circle B);