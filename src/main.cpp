#include"../include/main.h"
#include<iostream>
#include<fstream>
#include<vector>
#include<set>
using namespace std;

vector<line>lineArray;
vector<circle>circleArray;
set<struct dot> crossDot;
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
				getLCcrossDot(newline, i);
			}
			lineArray.push_back(newline);
		}
		else if (type == 'C') {
			int x, y, r;
			inputFile >> x >> y >> r;
			circle newcircle = circle(x, y, r);
			for (line i : lineArray) {
				getLCcrossDot(i, newcircle);
			}
			for (circle i : circleArray) {
				line* temp = get2CircleLine(i, newcircle);
				if (temp != NULL)
					getLCcrossDot(*temp, newcircle);
			}
			circleArray.push_back(newcircle);
		}
	}
}

struct dot calculate(line A, line B) {
	struct dot result;
	if (A.k == B.k) {
		return result;
	}
	result.x = (B.b - A.b) / (A.k - B.k);
	result.y = A.k * result.x + A.b;
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
	double k = x.k;
	double d = x.b;
	vector<double> simple;
	simple.push_back(pow(k, 2) + 1);
	simple.push_back(2 * (d * k - b * k - a));
	simple.push_back(pow((d - b), 2) - pow(r, 2));
	return simple;
}

void getLCcrossDot(line A, circle B) {
	vector<double> simple = getEquationForLC(A, B);
	vector<double> solution = level2Equation(simple);
	if (solution.size() == 1) {
		crossDot.insert(struct dot(solution[0], A.k * solution[0] + A.b));
	}
	else if (solution.size() == 2) {
		crossDot.insert(struct dot(solution[0], A.k * solution[0] + A.b));
		crossDot.insert(struct dot(solution[1], A.k * solution[1] + A.b));
	}
}

line* get2CircleLine(circle a, circle b) {
	double distance = pow(a.x - b.x, 2) + pow(a.y - b.y, 2);
	/* ���� */
	if (distance > pow(a.r + b.r, 2)) {
		return NULL;
	}
	/* �ں� */
	else if (distance < pow(a.r - b.r, 2)) {
		return NULL;
	}
	/*k = -(a2-a1) / (b2 - b1)*/
	double k = (a.x - b.x) / (b.y - a.y);
	/*b = (c1^2 - c2^2 - b1^2 + b2^2 - a1^2 + a2^2) / 2(b2-b1)*/
	double d = (pow(a.r, 2) - pow(b.r, 2)
		- pow(a.y, 2) + pow(b.y, 2) - pow(a.x, 2) + pow(b.x, 2)) / 2 * (b.y - a.y);
	return new line(k, d);
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