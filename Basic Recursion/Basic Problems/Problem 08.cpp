#include <bits/stdc++.h>
using namespace std;

int fib(int N) {
    if(N <= 1)
        return N;

    return fib(N-1) + fib(N-2);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    int n;
    cin >> n;

    cout << "Result: " << fib(n);

    return 0;
}
