#include <iostream>
#include <cmath>
using namespace std;

bool checkArmstrongNumber(int num) {

    if(num == 0) {
        return true;
    }
    
    int originalNum = num;
    int cnt = 0;
    while(num != 0) {
        num /= 10;
        cnt++;
    }

    num = originalNum;
    int sum = 0;
    while(num != 0) {
        int digit = num % 10;
        sum += pow(digit, cnt);
        num /= 10;
    }

    return sum == originalNum;
}

int main() {
    int number;
    cout << "Enter an integer: ";
    cin >> number;

    bool res = checkArmstrongNumber(number);

    if(res) {
        cout << number << " is an armstrong number.";
    }
    else {
        cout << number << " is not an armstrong number.";
    }

    return 0;
}