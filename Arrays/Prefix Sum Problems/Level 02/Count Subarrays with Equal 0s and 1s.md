## Problem Statement

You are given a binary array nums consisting only of 0s and 1s.

A subarray is a contiguous part of the array.

Your task is to count the total number of subarrays that contain an equal number of 0s and 1s.

Return the count.
```
**Example 1**
*Input:*
nums = [0, 1]

*Output:*
1
```
*Explanation:*

The subarray [0, 1] contains one 0 and one 1.
```
**Example 2**
*Input:*
nums = [0, 1, 0]

*Output:*
2
```
*Explanation:*

The subarrays with equal 0s and 1s are:

[0, 1]
[1, 0]
```
**Example 3**
*Input:*
nums = [0, 0, 1, 0, 1, 1]

*Output:*
6
```
## SOLUTION
```
#include <bits/stdc++.h>
using namespace std;

int countSubarraysEqualZeroOne(vector<int>& nums) {
    int n = nums.size();

    unordered_map<int, int> freq;
    freq[0] = 1;

    int prefixSum = 0;
    int count = 0;

    for(int i=0; i<n; i++) {

        prefixSum += (nums[i] == 0 ? -1 : 1);

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

    cout << countSubarraysEqualZeroOne(nums) << " subarrays with equal 0's and equal 1's.";

    return 0;
}
```

**Time Complexity (TC): O(n)**
One pass through the array; each hash operation is O(1) on average.

**Space Complexity (SC): O(n)**
In the worst case, we store up to n distinct prefix sums in the hash map.
