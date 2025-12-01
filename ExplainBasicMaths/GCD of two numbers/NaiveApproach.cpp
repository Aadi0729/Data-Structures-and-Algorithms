#include <iostream>
using namespace std;

int gcd(int a, int b) {
    // a=18, b=12
    int mini = min(a,b);
    int largestDivisor = 1;
    for(int i=1; i<=mini; i++) {
        if(a%i == 0 & b%i == 0) {
            largestDivisor = i;
        }
    }
    return largestDivisor;
}
int main()
{
    int num1, num2;
    cout << "Enter the two numbers: ";
    cin >> num1 >> num2;

    int res = gcd(num1, num2);

    cout << res << " is the GCD of " << num1 << " and " << num2;

    return 0;
}