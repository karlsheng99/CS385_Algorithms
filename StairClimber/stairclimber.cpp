/*******************************************************************************
 * Name    : stairclimber.cpp
 * Author  : Zikang Sheng
 * Version : 1.0
 * Date    : Oct 2, 2020
 * Description : Lists the number of ways to climb n stairs.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.

	vector< vector<int> > ways;
	if (num_stairs == 0) {
		ways.push_back({});
	}
	else {
		for (int i = 1; i < 4; i++) {
			if (num_stairs >= i) {
				vector< vector<int> > result = get_ways(num_stairs - i);
				for (unsigned int j = 0; j < result.size(); j++) {
					result[j].insert(result[j].begin(), i);
					ways.push_back(result[j]);
				}
			}
		}
	}
	return ways;
}

void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
	int size = ways.size();
	int digits = 0;
	while (size > 0){
		size /= 10;
		digits++;
	}

	for (unsigned int i = 0; i < ways.size(); i++) {
		cout << setw(digits) << i+1 << ". [" << ways[i][0];
		for (unsigned int j = 1; j < ways[i].size(); j++) {
			cout << ", " << ways[i][j];
		}
		cout << "]" << endl;
	}
}

int main(int argc, char * const argv[]) {
	int stair;
	istringstream iss;

	//Case 1: No input arguments
	if (argc == 1) {
		cerr << "Usage: " << argv[0] << " <number of stairs>" << endl;
		return 1;
	}

	//Case 2: Too many input arguments
	if (argc > 2) {
		cerr << "Usage: " << argv[0] << " <number of stairs>" << endl;
		return 1;
	}

	iss.str(argv[1]);
	//Case 3: Bad input
	if (!(iss >> stair)) {
		cerr << "Error: Number of stairs must be a positive integer." << endl;
		return 1;
	}
	else {
		//Case 4: Bad input
		if (stair <= 0 ) {
			cerr << "Error: Number of stairs must be a positive integer." << endl;
			return 1;
		}
		else {
			vector< vector<int> > ways = get_ways(stair);
			int num = ways.size();

			//Case 5: Valid (One stair)
			if (num == 1)
				cout << "1 way to climb 1 stair." << endl;

			//Case 6: Valid (Multiple stairs)
			else
				cout << num << " ways to climb " << stair << " stairs." << endl;
			display_ways(ways);
		}
	}
}
