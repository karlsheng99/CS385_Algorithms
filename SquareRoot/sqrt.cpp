/*******************************************************************************
 * Name    : sqrt.cpp
 * Author  : Zikang Sheng
 * Version : 1.0
 * Date    : September 2, 2020
 * Description : Compute the square root of a double using Newton's method.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <limits>
#include <iomanip>
#include <cmath>
using namespace std;

double sqrt(double num, double epsilon) {
	if (num < 0) {
		return numeric_limits<double>::quiet_NaN();
	}
	else if (num == 0 || num == 1) {
		return num;
	}

	double last = num;
	double next = (last + num / last) / 2;

	while (abs(last - next) > epsilon) {
		last = next;
		next = (last + num / last) / 2;
	}

	return next;
}

int main(int argc, char *argv[]) {
	double m, n;
	istringstream iss;
	double result;
	double epsilon = 1e-7;

	if (argc != 2 && argc != 3) {
		cerr << "Usage: " << argv[0] << " <value> [epsilon]" << endl;
		return 1;
	}

	iss.str(argv[1]);
	if (!(iss >> m)) {
		cerr << "Error: Value argument must be a double." << endl;
		return 1;
	}

	if (argc == 3){
		iss.clear();
		iss.str(argv[2]);
		if (!(iss >> n) || n <= 0) {
			cerr << "Error: Epsilon argument must be a positive double." << endl;
			return 1;
		}
		result = sqrt(m, n);
	}
	else {
		result = sqrt(m, epsilon);
	}

	cout << fixed << setprecision(8) << result << endl;
	return 0;
}


