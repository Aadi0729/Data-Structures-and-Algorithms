## Problem Statement

You are given a binary array nums consisting only of 0s and 1s.

A subarray is a contiguous part of the array.

Your task is to find the length of the longest subarray that contains an equal number of 0s and 1s.

If no such subarray exists, return 0.

**Example 1**
*Input:*
nums = [0, 1]

*Output:* 2

*Explanation:*

The subarray [0, 1] contains one 0 and one 1.

**Example 2**
*Input:*
nums = [0, 1, 0]

*Output:* 2

*Explanation:*

The longest subarray with equal 0s and 1s is:

[0, 1]  or  [1, 0]

**Example 3**
*Input:*
nums = [0, 0, 1, 0, 0, 0, 1, 1]

*Output:* 6

## SOLUTION
```
#include <bits/stdc++.h>
using namespace std;

int longestSubarray(vector<int>& nums) {
    int n = nums.size();

    unordered_map<int, int> mpp;
    mpp[0] = -1;

    int prefixSum = 0;
    int maxLen = 0;

    for(int i=0; i<n; i++) {

        prefixSum += (nums[i] == 0 ? -1 : 1);

        if(mpp.find(prefixSum) != mpp.end())
            maxLen = max(maxLen, i-mpp[prefixSum]);

        if(mpp.find(prefixSum) == mpp.end())
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

    cout << longestSubarray(nums) << " is the length of the longest subarray with equal 0's and equal 1's.";

    return 0;
}
```

**Time Complexity: O(n)**

**Space Complexity: O(n)**
