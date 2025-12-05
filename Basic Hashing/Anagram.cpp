#include <bits/stdc++.h>
using namespace std;

bool checkAnagram(string s, int n1, string t, int n2) {
    if(n1 != n2)
        return false;

    int freq[256] = {0};

    for(int i=0; i<n1; i++) {
        freq[s[i]]++;
    }

    for(int i=0; i<n2; i++) {
        freq[t[i]]--;
    }

    for(int i=0; i<256; i++) {
        if(freq[i] != 0)
            return false;
    }

    return true;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    string s = "sileno";
    int n1 = s.size();

    string t = "listen";
    int n2 = t.size();

    bool isAnagram = checkAnagram(s, n1, t, n2);

    if(isAnagram)
        cout << "s and t are anagrams.";
    else
        cout << "s and t are not anagrams.";

    return 0;
}
