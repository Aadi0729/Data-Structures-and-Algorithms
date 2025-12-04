#include <bits/stdc++.h>
using namespace std;

void print(int N) {
    if(N == 0)
        return;

    cout << N << " ";
    print(N-1);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    int n;
    cin >> n;

    print(n);

    return 0;
}