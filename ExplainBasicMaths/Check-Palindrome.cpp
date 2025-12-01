#include <iostream>
using namespace std;

bool checkPalindrome(int number) {

    if(number < 0) {
        return false;
    }
    int originalNum = number;
    int reversedNum = 0;

    while(number != 0) {
        int digit = number % 10;
        reversedNum = reversedNum * 10 + digit;
        number /= 10;
    }

    return originalNum == reversedNum;
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