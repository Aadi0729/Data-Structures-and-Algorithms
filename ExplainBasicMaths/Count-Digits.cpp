#include <iostream>
using namespace std;

int countDigits(int number) {
    int cnt = 0;

    if(number == 0) {
        return 1;
    }

    while(number != 0) {
        number /= 10;
        cnt++;
    }

    return cnt;
}

int main() {
    int num;
    cout << "Enter an integer: ";
    cin >> num;

    int count = countDigits(num);
    cout << "There are " << count << " digits in the number " << num << endl;

    return 0;
}