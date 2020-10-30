/*******************************************************************************
 * Name    : inversioncounter.cpp
 * Author  : Zikang Sheng & Keye Li
 * Version : 1.0
 * Date    : Oct 26, 2020
 * Description : Counts the number of inversions in an array.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    long count = 0;
    for (int i = 0; i < length-1; i++) {
        for (int j = i+1; j < length; j++) {
            if (array[i] > array[j]) {
                count++;
            }
        }
    }
    return count;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    int *scratch = new int[length];
	int low = 0;
	int high = length - 1;

	long result = mergesort(array, &scratch[0], low, high);

    delete [] scratch;
	return result;
}

static long mergesort(int array[], int scratch[], int low, int high) {
    long result = 0;
    if(low < high){

		int mid = low + (high - low)/2;
		result += mergesort(array, scratch, low, mid);
		result += mergesort(array, scratch, mid+1, high);


		int L = low;
		int H = mid + 1;
		for (int k = low; k <= high;k++){
			
            if(L <= mid && (H > high || array[L] <= array[H])){
				scratch[k] = array[L];
				L++;
			}
			else{
				scratch[k] = array[H];
				H++;
				result += mid-L+1;
			}
		}

		for(int k = low; k <= high; k++){
			array[k] = scratch[k];
		}
	}
    return result;
}

int main(int argc, char *argv[]) {
    istringstream iss;
    string input;

    if (argc > 2){
    	cerr << "Usage: " << argv[0] << " [slow]" << endl;
    	return 1;
    }
    if (argc == 2){
        iss.str(argv[1]);
        if(!(iss >> input)){
            cerr << "Error: Unrecognized option " << "'" << input << "'." << endl;
            return 1;
        }
        if(input != "slow"){
            cerr << "Error: Unrecognized option " << "'" << input << "'." << endl;
            return 1;
        }
    }
    iss.clear();

    cout << "Enter sequence of integers, each followed by a space: " << flush;
    

    int value, index = 0;
    vector<int> values;
    string str = "";
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    if (values.size() == 0) {
        cerr << "Error: Sequence of integers not received." << endl;
        return 1;
    }

    if (input == "slow"){
    	long result = count_inversions_slow(&values[0], values.size());
    	cout << "Number of inversions: " << result << endl;
        return 0;
    }

    if (argc == 1){
    	long result = count_inversions_fast (&values[0], values.size());
    	cout << "Number of inversions: " << result << endl;
        return 0;
    }

    return 0;
}
