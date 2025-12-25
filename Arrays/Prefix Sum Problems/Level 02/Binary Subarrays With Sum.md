## Problem Statement

You are given a binary array nums (containing only 0s and 1s) and an integer goal.

A subarray is a contiguous part of the array.

Your task is to return the total number of subarrays whose sum is exactly equal to goal.
```
Example 1
Input:
nums = [1, 0, 1, 0, 1]
goal = 2

Output:
4
```
*Explanation:*

The subarrays with sum 2 are:

[1,0,1]
[1,0,1]   (starting at index 2)
[0,1,0,1]
[1,0,1,0]
```
Example 2
Input:
nums = [0, 0, 0, 0, 0]
goal = 0

Output:
15
```
*Explanation:*

All possible subarrays have sum 0.
```
Example 3
Input:
nums = [1, 1, 1, 1]
goal = 2

Output:
3
```

## SOLUTION
```
#include <bits/stdc++.h>
using namespace std;

int countSubarrays(vector<int>& nums, int k) {

    unordered_map<int, int> freq;
    freq[0] = 1;

    int count = 0;
    int prefixSum = 0;

    for(auto val : nums) {
        prefixSum += val;

        if(freq.find(prefixSum-k) != freq.end())
            count += freq[prefixSum-k];

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

    int goal;
    cin >> goal;

    cout << "There are " << countSubarrays(nums, goal) << " subarrays with sum exactly equal to " << goal;

    return 0;
}
```
```
Time Complexity: O(n)

Space Complexity: O(n)
```
```
Binary Subarrays With Sum = K is just Subarray Sum Equals K on a binary array.
Same prefix sum, same hashing, same logic.
```
