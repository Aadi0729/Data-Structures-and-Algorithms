#include <iostream>
#include <cmath>
using namespace std;

// int reverseNumber(int number) {
//     int originalNum = number;

//     int cnt = 0;
//     while(number != 0) {
//         number /= 10;
//         cnt++;
//     }

//     int reversedNum = 0;
//     number = originalNum;
//     while(cnt > 0) {
//         int digit = number % 10;
//         reversedNum = reversedNum + digit * pow(10, cnt-1);
//         number /= 10;
//         cnt--;
//     }

//     return reversedNum;
    
// }


int reverseNumber(int number) {
    int reversedNum = 0;
    while(number != 0) {
        int digit = number % 10;
        reversedNum = reversedNum * 10 + digit;
        number /= 10;
    }

    return reversedNum;
}
int main() {
    int num;
    cout << "Enter an integer: ";
    cin >> num;

    cout << "The reverse of the number is: " << reverseNumber(num) << endl;

    return 0;
}