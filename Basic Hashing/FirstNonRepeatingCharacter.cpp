#include <bits/stdc++.h>
using namespace std;

char firstNonRepeating(string s, int n) {
    int freq[256] = {0};

    for(int i=0; i<n; i++) {
        freq[s[i]]++;
    }

    for(int i=0; i<n; i++) {
        if(freq[s[i]] == 1)
            return s[i];
    }

    return 'a';
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    string s = "zxcabx";
    int n = s.size();

    char res = firstNonRepeating(s, n);

    cout << "The first non-repeating character is " << res;

    return 0;
}
