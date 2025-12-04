#include <bits/stdc++.h>
using namespace std;

void print(int N) {
    if(N == 0)
        return;

    print(N-1);
    cout << "Aditya" << endl;
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
