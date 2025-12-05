#include <bits/stdc++.h>
using namespace std;

void checkOccurrence(vector<int>& nums, int n) {
    int max = INT_MIN;
    for(int i=0; i<n; i++) {
        if(nums[i] > max)
            max = nums[i];
    }

    int freq[max+1] = {0};

    for(int i=0; i<n; i++) {
        freq[nums[i]]++;
    }

    for(int i=0; i<max+1; i++) {
        if(freq[i] > 0)
            cout << i << " -> " << freq[i] << endl;
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    int n;
    cin >> n;

    vector<int> nums(n);
    for(int i=0; i<n; i++) {
        cin >> nums[i];
    }

    checkOccurrence(nums, n);

    return 0;
}
