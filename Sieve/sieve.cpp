/*******************************************************************************
 * Name    : sieve.cpp
 * Author  : Zikang Sheng
 * Version : 1.0
 * Date    : Sep 16, 2020
 * Description : Sieve of Eratosthenes
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.
	const int max_prime_width = num_digits(max_prime_),
			primes_per_row = 80 / (max_prime_width + 1);

	if (num_primes_ <= primes_per_row) {
		cout << 2;
		for (int i = 3; i <= limit_; i++) {
			if (is_prime_[i]) {
				cout << " " << i;
			}
		}
	}
	else {
		int count = 0;
		for (int i = 0; i <= limit_; i++) {
			if (is_prime_[i]) {
				if (count != 0)
					cout << " ";
				cout << setw(max_prime_width) << i;
				count++;
				if (count >= primes_per_row) {
					cout << endl;
					count = 0;
				}
			}
		}
	}
	cout << endl;
}

int PrimesSieve::count_num_primes() const {
    // TODO: write code to count the number of primes found
	int count = 0;
	for (int i = 0; i <= limit_; i++) {
		if (is_prime_[i])
			count++;
	}
    return count;
}

void PrimesSieve::sieve() {
    // TODO: write sieve algorithm
	num_primes_ = 0;

	is_prime_[0] = false;
	is_prime_[1] = false;
	for (int i = 2; i <= limit_ ; i++) {
		is_prime_[i] = true;
	}

	for (int i = 2; i <= sqrt(limit_); i++) {
		if (is_prime_[i]) {
			for (int j = i*i; j <= limit_ ; j += i) {
				is_prime_[j] = false;
			}
		}
	}

	num_primes_ = count_num_primes();

	int index = limit_;
	while (!is_prime_[index]){
		index--;
	}
	max_prime_ = index;
}

int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
	if (num > 0)
		return 1+ num_digits(num/10);
    return 0;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.

    PrimesSieve prime (limit);
    cout << "\n" << "Number of primes found: " << prime.num_primes() << endl;
    cout << "Primes up to " << limit << ":" << endl;
    prime.display_primes();
    return 0;
}



