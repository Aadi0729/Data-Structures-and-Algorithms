#include <iostream>
using namespace std;

// void printAllDivisors(int n) {

//     for(int i=1; i<=n; i++) {
//         if(n % i == 0) {
//             cout << i << " ";
//         }
//     }
// }

void printAllDivisors(int n) {

    for(int i=1; i*i<=n; i++) {
        if(n % i == 0) {
            cout << i << " ";
            if(i != n/i) {
                cout << n/i << " ";
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter a positive integer: ";
    cin >> n;

    cout << "The divisors of " << n << " are: ";
    
    printAllDivisors(n);

    return 0;
}