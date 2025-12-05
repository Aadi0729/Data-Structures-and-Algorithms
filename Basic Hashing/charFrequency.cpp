#include <bits/stdc++.h>
using namespace std;

void checkOccurrence(string s, int n) {
    int freq[256] = {0};

    for(int i=0; i<n; i++) {
        freq[(int)s[i]]++;
    }

    for(int i=0; i<256; i++) {
        if(freq[i] > 0)
            cout << char(i) << " -> " << freq[i] << " [ASCII Value] = " << i << endl;
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    string s = "aA3$aa";
    int n = s.size();

    checkOccurrence(s, n);

    return 0;
}
