#include<iostream>
#include<vector>
#include<set>
#include"../include/main.h"
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
	cout << crossDot.size() << endl;
	return 0;
}