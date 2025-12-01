#include <iostream>
using namespace std;

int countDigits(int number) {

    if(number == 0)
        return 1;
    
    if(number < 0)
        number = abs(number);

    int count = 0;
    while(number != 0) {
        number /= 10;
        count++;
    }
    return count;
}

int main() {
    int num;
    cout << "Enter an integer: ";
    cin >> num;

    int count = countDigits(num);
    cout << "There are " << count << " digits in the number " << num << endl;

    return 0;
}