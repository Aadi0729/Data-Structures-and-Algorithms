#include <bits/stdc++.h>
using namespace std;

int sum(int N) {
    if(N == 0)
        return 0;

    return N + sum(N-1);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    int n;
    cin >> n;
    
    cout << "The sum of first " << n << " number is " << sum(n);

    return 0;
}
