#include <iostream>
using namespace std;

bool checkPalindrome(int number) {

    if(number < 0)
        return false;
        
    int originalNumber = number;
    int reversedNumber = 0;
    while(number != 0) {
        int digit = number % 10;
        reversedNumber = reversedNumber * 10 + digit;
        number /= 10;
    }
    return originalNumber == reversedNumber;
}

int main() {
    int number;
    cout << "Enter a number: ";
    cin >> number;

    bool isPalindrome = checkPalindrome(number);

    if(isPalindrome) {
        cout << number << " is a palindrome." << endl;
    } else {
        cout << number << " is not a palindrome." << endl;
    }
}