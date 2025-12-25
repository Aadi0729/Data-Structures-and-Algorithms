## Problem Statement

You are given an integer array nums of size n and an integer k.

A subarray is a contiguous part of the array.

Your task is to count the number of subarrays whose sum is divisible by k.

Return the count.
```
Example 1
Input:
nums = [4, 5, 0, -2, -3, 1]
k = 5

Output:
7
```
Explanation:

The subarrays whose sum is divisible by 5 are:

[4,5,0,-2,-3,1]
[5]
[5,0]
[5,0,-2,-3]
[0]
[0,-2,-3]
[-2,-3]
```
Example 2
Input:
nums = [5]
k = 9

Output:
0
```
```
Example 3
Input:
nums = [2, -2, 2, -4]
k = 6

Output:
2
```

## SOLUTION
```
#include <bits/stdc++.h>
using namespace std;

int countSubarrays(vector<int>& nums, int k) {

    unordered_map<int, int> freq;
    freq[0] = 1;

    int prefixSum = 0;
    int count = 0;

    for(auto val : nums) {
        prefixSum += val;
        int rem = prefixSum % k;

        if (rem < 0) rem += k;

        if(freq.find(rem) != freq.end())
            count += freq[rem];

        freq[rem]++;
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

    cout << "There are " << countSubarrays(nums, k) << " subarrays with sum divisible by " << k;

    return 0;
}
```
```
Time Complexity: O(n)
```
```
Space Complexity: O(n)
```
