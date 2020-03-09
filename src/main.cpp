#include"../include/main.h"
#include<iostream>
#include<fstream>
#include<vector>
#include<unordered_set>
using namespace std;

vector<line>lineArray;
vector<circle>circleArray;
unordered_set<dot, myHashFuc> crossDot;
ifstream inputFile;
ofstream outputFile;

void input(int num) {
	for (int i = 0; i < num; i++) {
		char type;
		inputFile >> type;
		if (type == 'L') {
			int x1, y1, x2, y2;
			inputFile >> x1 >> y1 >> x2 >> y2;
			line newline = line(x1, y1, x2, y2);
			for (line i : lineArray) {
				calculate(i, newline);
			}
			for (circle i : circleArray) {
				if (newline.b == 0) {
					yParelLine(newline, i);
				}
				else {
					getLCcrossDot(newline, i);
				}
			}
			lineArray.push_back(newline);
		}
		else if (type == 'C') {
			int x, y, r;
			inputFile >> x >> y >> r;
			circle newcircle = circle(x, y, r);
			for (line i : lineArray) {
				if (i.b == 0) {
					yParelLine(i, newcircle);
				}
				else {
					getLCcrossDot(i, newcircle);
				}
			}
			for (circle i : circleArray) {
				line* temp = get2CircleLine(i, newcircle);
				if (temp != NULL) {
					if (temp->b == 0) {
						yParelLine(*temp, newcircle);
					}
					else {
						getLCcrossDot(*temp, newcircle);
					}
				}
			}
			circleArray.push_back(newcircle);
		}
	}
}

struct dot calculate(line A, line B) {
	struct dot result;
	if (A.a * B.b == A.b * B.a) {
		return result;
	}
	result.x = (A.b * B.c - A.c * B.b) / (A.a * B.b - B.a * A.b);
	result.y = (B.a * A.c - B.c * A.a) / (A.a * B.b - A.b * B.a);
	crossDot.insert(result);
	return result;
}

vector<double> level2Equation(vector<double> simple) {
	double a = simple[0];
	double b = simple[1];
	double c = simple[2];
	vector<double> solution;
	double delta = b * b - 4 * a * c;
	if (delta == 0) {
		solution.push_back(-b / 2 * a);
	}
	else if(delta > 0){
		solution.push_back((-b + sqrt(delta)) / 2 * a);
		solution.push_back((-b - sqrt(delta)) / 2 * a);
	}
	return solution;
}

vector<double> getEquationForLC(line x, circle y) {
	double a = y.x;
	double b = y.y;
	double r = y.r;
	double m = x.a;
	double n = x.b;
	double p = x.c;
	vector<double> simple(3);
	simple[0] = m * m + n * n;
	simple[1] = 2 * (m * p - a * n * n + b * m * n);
	simple[2] = (a * a + b * b - r * r) * n * n + p * p + 2 * b * p * n;
	return simple;
}

void getLCcrossDot(line A, circle B) {
	vector<double> simple = getEquationForLC(A, B);
	vector<double> solution = level2Equation(simple);
	double k = -A.a / A.b;
	double b = -A.c / A.b;
	if (solution.size() == 1) {
		crossDot.insert(struct dot(solution[0], k * solution[0] + b));
	}
	else if (solution.size() == 2) {
		crossDot.insert(struct dot(solution[0], k * solution[0] + b));
		crossDot.insert(struct dot(solution[1], k * solution[1] + b));
	}
}

line* get2CircleLine(circle a, circle b) {
	double distance = pow(a.x - b.x, 2) + pow(a.y - b.y, 2);
	/* ÏàÀë */
	if (distance > pow(a.r + b.r, 2)) {
		return NULL;
	}
	/* ÄÚº¬ */
	else if (distance < pow(a.r - b.r, 2)) {
		return NULL;
	}
	double _a = 2 * (b.x - a.x);
	double _b = 2 * (b.y - a.y);
	double _c = a.x * a.x - b.x * b.x + a.y * a.y - b.y * b.y - a.r * a.r + b.r * b.r;
	return new line(_a, _b, _c);
}

void yParelLine(line A, circle B) {
	double x = -A.c / A.a;
	vector<double> simple(3);
	simple[0] = 1;
	simple[1] = -2 * B.y;
	simple[2] = B.y * B.y + x * x - 2 * B.x * x + B.x * B.x - B.r * B.r;
	vector<double> solution = level2Equation(simple);
	if (solution.size() == 1) {
		crossDot.insert(struct dot(x, solution[0]));
	}
	else if (solution.size() == 2) {
		crossDot.insert(struct dot(x, solution[0]));
		crossDot.insert(struct dot(x, solution[1]));
	}
}

int main(int argc, char* argv[]) {
	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "-i") == 0) {
			inputFile = ifstream(argv[i + 1]);
		}
		else if (strcmp(argv[i], "-o") == 0) {
			outputFile = ofstream(argv[i + 1]);
		}
	}
	int num = 0;
	inputFile >> num;
	input(num);
	cout << crossDot.size() << endl;
	outputFile << crossDot.size() << endl;
	return 0;
}