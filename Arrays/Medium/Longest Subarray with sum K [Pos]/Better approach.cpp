#include <bits/stdc++.h>
using namespace std;

int longestSubarray(vector<int>& nums, int k) {
    int n = nums.size();

    map<int, int> mpp;

    int prefixSum = 0;
    int maxLen = 0;
    for(int i=0 ;i<n; i++) {
        prefixSum += nums[i];
        
        if(prefixSum == k)
            maxLen = max(maxLen, i+1);

        if(mpp.find(prefixSum-k) != mpp.end()) {
            maxLen = max(maxLen, i - mpp[prefixSum-k]);
        }
        mpp[prefixSum] = i;
    } 

    return maxLen;    
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
