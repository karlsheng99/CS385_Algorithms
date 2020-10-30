/*******************************************************************************
 * Name    : pointers.cpp
 * Author  : Zikang Sheng
 * Version : 1.0
 * Date    : September 4, 2020
 * Description : *
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
using namespace std;

void display_array(int array[], const int length) {
	cout << "[";
	if (length >= 1){
		cout << array[0];
	}
	for (int i = 1; i < length; i++) {
		cout << ", " << array[i];
	}
	cout << "]" << endl;
}

void display_array_ptr(int array[], const int length) {
    cout << "[";
    if (length >= 1) {
        cout << *array;
    }
    for (int *ptr = array + 1, *end = array + length; ptr < end; ptr++) {
        cout << ", " << *ptr;
    }
    cout << "]" << endl;
}

void pass_by_value(int x) {
	x = 10;
}

void pass_by_pointer(int *x) {
	*x = 10;
}

void pass_by_reference(int &x) {
	x = 10;
}

int main() {
	int x = 5, *z = &x;
	cout << &x << " " << z << endl;
	cout << x << " " << *z << endl;
	int y = 6;
	cout << x << " " << y << endl;

	*z = 7;
	cout << x << " " << y << endl;
	z = &y;
	*z = 7;
	cout << x << " " << y << endl;
	cout << &x << " " << &y << " " << z << endl;
	z--;
	cout << &x << " " << &y << " " << z << endl;
	z++;
	z++;
	cout << *z << endl;
	cout << z << endl;

	int *values = new int[y];
	for (int i = 0; i < y; i++) {
		*(values + i) = i;
	}
	cout << y <<endl;
	display_array(values, y);
	display_array_ptr(values, y);
	delete [] values;

	x = 5;
	pass_by_value(x);
	cout << x << endl;

	x = 5;
	pass_by_pointer(&x);
	cout << x << endl;

	x = 5;
	pass_by_reference(x);
	cout << x << endl;
	return 0;
}
