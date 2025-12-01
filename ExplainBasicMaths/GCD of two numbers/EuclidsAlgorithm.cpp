#include <iostream>
using namespace std;

int gcd(int a, int b) {
    // a = 18, b = 12
    while(b != 0) {
        int rem = a % b;
        a = b;
        b = rem;
    }

    return a;
}
int main()
{
    int num1, num2;
    cout << "Enter the two numbers: ";
    cin >> num1 >> num2;

    int res = gcd(num1, num2);

    cout << res << " is the GDC of num1 and num2.";

    return 0;
}