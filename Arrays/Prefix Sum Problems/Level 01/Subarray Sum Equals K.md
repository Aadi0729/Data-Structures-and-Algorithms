## Problem Statement

You are given an integer array nums and an integer k.

A subarray is a contiguous part of the array.

Your task is to return the total number of subarrays whose sum is exactly equal to k.

**Example 1**
*Input:*
nums = [1, 1, 1]
k = 2

*Output:*
2

*Explanation:*
The subarrays with sum = 2 are:

[1, 1] (indices 0 to 1)
[1, 1] (indices 1 to 2)

**Example 2**
*Input:*
nums = [1, 2, 3]
k = 3

*Output:*
2

*Explanation:*
The subarrays with sum = 3 are:

[1, 2]
[3]

## SOLUTION

```
#include <bits/stdc++.h>
using namespace std;

int subarrayWithSumK(vector<int>& nums, int k) {
    int n = nums.size();

    unordered_map<int, int> freq;

    freq[0] = 1;

    int currentPrefixSum = 0;
    int count = 0;

    for(int i=0; i<n; i++) {
        currentPrefixSum += nums[i];

        if(freq.find(currentPrefixSum-k) != freq.end()) {
            count += freq[currentPrefixSum-k];
        }
        freq[currentPrefixSum]++;
    }

    return count;
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

    cout << "The number of subarrays with sum k: " << subarrayWithSumK(nums, k);

    return 0;
}
```

**Time & Space Complexity**

*Time:* O(n) average
*Space:* O(n)
