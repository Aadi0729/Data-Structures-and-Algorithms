#include <bits/stdc++.h>
using namespace std;

bool checkPalindrome(string s, int start, int end) {
    if(start >= end)
        return true;

    if(s[start] != s[end])
        return false;

    return checkPalindrome(s, start+1, end-1);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    string s = "ababa";
    int n = s.size();

    bool isPalindrome = checkPalindrome(s, 0, n-1);

    if(isPalindrome)
        cout << "s is a palindrome.";
    else
        cout << "s is not a palindrome.";

    return 0;
}
