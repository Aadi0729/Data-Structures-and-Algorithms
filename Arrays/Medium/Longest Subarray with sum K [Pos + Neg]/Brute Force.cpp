#include <bits/stdc++.h>
using namespace std;

int longestSubarray(vector<int>& nums, int k) {
    int n = nums.size();

    int maxLength = 0;
    for(int i=0; i<n; i++) {
        int sum = 0;
        for(int j=i; j<n; j++) {
            sum += nums[j];
            if(sum == k) {
                maxLength = max(maxLength, j-i+1);
            }
        }
    }

    return maxLength ? maxLength : -1;
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

    int k;
    cin >> k;

    cout << "The longest subarray is of length " << longestSubarray(nums, k);

    return 0;
}
