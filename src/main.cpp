#include"../include/main.h"
#include<iostream>
#include<vector>
#include<set>
using namespace std;

vector<line>lineArray;
vector<circle>circleArray;
set<struct dot> crossDot;

void input(int num) {
	for (int i = 0; i < num; i++) {
		char type;
		cin >> type;
		if (type == 'L') {
			int x1, y1, x2, y2;
			cin >> x1 >> y1 >> x2 >> y2;
			lineArray.push_back(line(x1, y1, x2, y2));
		}
		else if (type == 'C') {
			int x, y, r;
			cin >> x >> y >> r;
			circleArray.push_back(circle(x, y, r));
		}
	}
}

struct dot* calculate(double k1, double b1, double k2, double b2) {
	if (k1 == k2) {
		return NULL;
	}
	struct dot* result = new struct dot();
	result->x = (b2 - b1) / (k1 - k2);
	result->y = k1 * result->x + b1;
	return result;
}

vector<double> level2Equation(vector<double> simple) {
	double a = simple[0];
	double b = simple[1];
	double c = simple[2];
	vector<double> solution;
	double delta = pow(b, 2) - 4 * a * c;
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
	double a = y.getX();
	double b = y.getY();
	double r = y.getZ();
	double k = x.getK();
	double d = x.getB();
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
		crossDot.insert(struct dot(solution[0], A.getK() * solution[0] + A.getB()));
	}
	else if (solution.size() == 2) {
		crossDot.insert(struct dot(solution[0], A.getK() * solution[0] + A.getB()));
		crossDot.insert(struct dot(solution[1], A.getK() * solution[1] + A.getB()));
	}
}
line* get2CircleLine(circle a, circle b) {
	double distance = pow(a.getX() - b.getX(), 2) + pow(a.getY() - b.getY(), 2);
	/* ÏàÀë */
	if (distance > pow(a.getZ() + b.getZ(), 2)) {
		return NULL;
	}
	/* ÄÚº¬ */
	else if (distance < pow(a.getZ() - b.getZ(), 2)) {
		return NULL;
	}
	/*k = -(a2-a1) / (b2 - b1)*/
	double k = (a.getX() - b.getX()) / (b.getY() - a.getY());
	/*b = (c1^2 - c2^2 - b1^2 + b2^2 - a1^2 + a2^2) / 2(b2-b1)*/
	double d = (pow(a.getZ(), 2) - pow(b.getZ(), 2)
		- pow(a.getY(), 2) + pow(b.getY(), 2) - pow(a.getX(), 2) + pow(b.getX(), 2)) / 2 * (b.getY() - a.getY());
	return new line(k, d);
}

int main() {
	int num = 0;
	cin >> num;
	input(num);
	for (unsigned int i = 0; i < lineArray.size(); i++) {
		for (unsigned int j = i + 1; j < lineArray.size(); j++) {
			struct dot* temp = calculate(lineArray[i].getK(), lineArray[i].getB(), lineArray[j].getK(), lineArray[j].getB());
			if (temp != NULL) {
				crossDot.insert(*temp);
			}
		}
	}
	for (unsigned int i = 0; i < lineArray.size(); i++) {
		for (unsigned int j = 0; j < circleArray.size(); j++) {
			getLCcrossDot(lineArray[i], circleArray[j]);
		}
	}
	for (unsigned int i = 0; i < circleArray.size(); i++) {
		for (unsigned int j = i + 1; j < circleArray.size(); j++) {
			line* temp = get2CircleLine(circleArray[i], circleArray[j]);
			if(temp != NULL)
				getLCcrossDot(*temp, circleArray[i]);
		}
	}
	cout << crossDot.size() << endl;
	return 0;
}