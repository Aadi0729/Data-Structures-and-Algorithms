#include <iostream>
#include <cmath>
using namespace std;

// int reverseNumber(int number) {
//     int originalNumber = number;
//     int cnt = 0;

//     while(number != 0) {
//         number /= 10;
//         cnt++;
//     }

//     int reversed = 0;
    

//     while(cnt > 0) {
//         int digit = originalNumber % 10;
//         reversed = reversed + pow(10, cnt-1) * digit;

//         originalNumber /= 10;
//         cnt--;
//     }

//     return reversed;
// }

int reverseNumber(int number) {
    int reversed = 0;

    while(number != 0) {
        int digit = number % 10;
        reversed = reversed * 10 + digit;
        number /= 10;
    }
    return reversed;
}
int main() {
    int num;
    cout << "Enter an integer: ";
    cin >> num;

    cout << "The reverse of the number is: " << reverseNumber(num) << endl;

    return 0;
}