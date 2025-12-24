## Problem Statement

You are given an integer array nums of size n.

A subarray is a contiguous part of the array.

Your task is to count the total number of subarrays whose sum is exactly equal to 0.

Return the count.

**Example 1**
*Input:*
nums = [1, -1, 1, -1]

*Output:*
4

*Explanation:*

Zero-sum subarrays are:

[1, -1]
[-1, 1]
[1, -1]
[1, -1, 1, -1]

**Example 2**
*Input:*
nums = [0, 0, 0]

*Output:*
6

*Explanation:*

All possible subarrays have sum = 0:

[0], [0], [0],
[0,0], [0,0],
[0,0,0]

**Example 3**
*Input:*
nums = [1, 2, 3]

*Output:*
0

## SOLUTION
```
#include <bits/stdc++.h>
using namespace std;

int subarraySumZero(vector<int>& nums) {
    unordered_map<int, int> freq;
    freq[0] = 1;

    int count = 0;
    int prefixSum = 0;

    for(auto val : nums) {
        prefixSum += val;

        if(freq.find(prefixSum) != freq.end())
            count += freq[prefixSum];

        freq[prefixSum]++;
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

    cout << "The number of subarrays with 0 sum are " << subarraySumZero(nums);

    return 0;
}
```

**Time Complexity (TC): O(n)**

Single traversal of the array, with O(1) average hash operations.

**Space Complexity (SC): O(n)**

In the worst case, all prefix sums are distinct and stored in the hash map.

```
Same prefix sum repeating ⇒ zero-sum subarray

Frequency of prefix sum ⇒ number of subarrays

Initialize freq[0] = 1 to handle index-0 cases

Count grows as count += freq[prefixSum]
```
