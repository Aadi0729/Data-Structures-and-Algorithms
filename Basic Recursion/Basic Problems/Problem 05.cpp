#include <bits/stdc++.h>
using namespace std;

int fact(int N) {
    // if(N == 0)
    //     return 1;

    if(N == 1)
        return 1;

    return N * fact(N-1);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    int n;
    cin >> n;

    cout << "The factorial of 5 is " << fact(n);

    return 0;
}
