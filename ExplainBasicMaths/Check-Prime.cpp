#include <iostream>
using namespace std;

bool checkPrime(int num) {
    if(num <= 1) {
        return false;
    }

    for(int i=2; i*i<=num; i++) {
        if(num % i == 0) {
            return false;
        }
    }

    return true;
}

int main() {
    int number;
    cout << "Enter an integer: ";
    cin >> number;

    bool isPrime = checkPrime(number);

    if(isPrime) {
        cout << number << " is a prime number." << endl;
    } else {
        cout << number << " is not a prime number." << endl;
    }
}