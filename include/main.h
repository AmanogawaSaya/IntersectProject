#pragma once

struct dot {
	double x;
	double y;

	bool operator<(const dot& rhs) const {
		return x + y < rhs.x + rhs.y;
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
private:
	double k;
	double b;

public:
	line(double x1, double y1, double x2, double y2) {
		line::k = (y2 - y1) / (x2 - x1);
		line::b = y1 - line::k * x1;
	}

	double getK() {
		return k;
	}

	double getB() {
		return b;
	}
};

class circle {
private:
	int x;
	int y;
	int r;

public:
	circle(int x, int y, int r) {
		circle::x = x;
		circle::y = y;
		circle::r = r;
	}

};

void input(int num);
struct dot calculate(double k1, double b1, double k2, double b2);