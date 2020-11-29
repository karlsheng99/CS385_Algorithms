/*******************************************************************************
 * Name    : fastmult.cpp
 * Author  : Zikang Sheng
 * Version : 1.0
 * Date    : November 28, 2020
 * Description : Multiply two large (base-10) integers supplied on the command-line.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
using namespace std;

string add(const string& a, const string& b, const string& carry) {
    if (a.length() == 0 && b.length() == 0) {
        if (carry == "1") {
            return carry;
        }
        return "";
    }
    else {
        if (a.length() == 0) {
            int temp = b.at(b.length() - 1) - '0' + carry.at(0) - '0';
            if (temp >= 10) {
                return add(a, b.substr(0, b.length() - 1), "1") + to_string(temp - 10);
            }
            return add(a, b.substr(0, b.length() - 1), "0") + to_string(temp);
        }
        else if (b.length() == 0) {
            int temp = a.at(a.length() - 1) - '0' + carry.at(0) - '0';
            if (temp >= 10) {
                return add(a.substr(0, a.length() - 1), b, "1") + to_string(temp - 10);
            }
            return add(a.substr(0, a.length() - 1), b, "0") + to_string(temp);
        }
        else {
            int temp = a.at(a.length() - 1) - '0' + b.at(b.length() - 1) - '0' + carry.at(0) - '0';
            if (temp >= 10) {
                return add(a.substr(0, a.length() - 1), b.substr(0, b.length() - 1), "1") + to_string(temp - 10);
            }
            return add(a.substr(0, a.length() - 1), b.substr(0, b.length() - 1), "0") + to_string(temp);
        }
    }
}

string add(const string& a, const string& b) {
    string new_a = a;
    string new_b = b;
    while (new_a.length() > 1 && new_a.at(0) == '0') {
        new_a = new_a.substr(1);
    }
    while (new_b.length() > 1 && new_b.at(0) == '0') {
        new_b = new_b.substr(1);
    }
    return add(new_a, new_b, "0");
}

string subtract(const string& a, const string& b, const string& carry) {
    if (a.length() == 0) {
        return "";
    }
    if (a.compare("1") == 0 && carry.compare("1") == 0) {
        return "";
    }
    else {
        if (b.length() == 0) {
            int temp = a.at(a.length() - 1) - '0' - (carry.at(0) - '0');
            if (temp < 0) {
                return subtract(a.substr(0, a.length() - 1), b, "1") + to_string(temp + 10);
            }
            return subtract(a.substr(0, a.length() - 1), b, "0") + to_string(temp);
        }
        else {
            int temp = a.at(a.length() - 1) - '0' - (carry.at(0) - '0') - (b.at(b.length() - 1) - '0');
            if (temp < 0) {
                return subtract(a.substr(0, a.length() - 1), b.substr(0, b.length() - 1), "1") + to_string(temp + 10);
            }
            return subtract(a.substr(0, a.length() - 1), b.substr(0, b.length() - 1), "0") + to_string(temp);
        }
    }
}

string subtract(const string& a, const string& b) {
    string new_a = a;
    string new_b = b;
    while (new_a.length() > 1 && new_a.at(0) == '0') {
        new_a = new_a.substr(1);
    }
    while (new_b.length() > 1 && new_b.at(0) == '0') {
        new_b = new_b.substr(1);
    }
    return subtract(new_a, new_b, "0");
}

void pad_zeros(string& a, string& b) {
    int newlen = pow(2, ceil(log2(max(a.length(), b.length()))));
    string temp1(newlen - a.length(), '0');
    string temp2(newlen - b.length(), '0');
    a = temp1 + a;
    b = temp2 + b;
}

string multiply(const string& a, const string& b) {
    string new_a = a;
    string new_b = b;
    pad_zeros(new_a, new_b);
    if (new_a.length() == 1 && new_b.length() == 1){
        int temp = (new_a.at(0) - '0') * (new_b.at(0) - '0');
        return to_string(temp);
    }
    else {
        string a1 = new_a.substr(0, new_a.length() / 2);
        string a0 = new_a.substr(new_a.length() / 2);
        string b1 = new_b.substr(0, new_b.length() / 2);
        string b0 = new_b.substr(new_b.length() / 2);
        string c2 = multiply(a1, b1);
        string c0 = multiply(a0, b0);
        string c1 = subtract(multiply(add(a1, a0), add(b1, b0)), add(c2, c0));
        if (c2 != "0") {
            string temp1(new_a.length(), '0');
            c2 += temp1;
        }
        if (c1 != "0") {
            string temp2(new_a.length() / 2, '0');
            c1 += temp2;
        }
        return add(add(c2, c1), c0);
    }
}

int main(int argc, char * const argv[]) {
    istringstream iss;
    string a, b;

    iss.str(argv[1]);
    iss >> a;
    iss.clear();

    iss.str(argv[2]);
    iss >> b;
    iss.clear();

    string result = multiply(a, b);
    cout << result << endl;
}