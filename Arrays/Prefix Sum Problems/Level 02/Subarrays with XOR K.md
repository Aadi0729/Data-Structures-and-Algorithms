## Problem Statement

You are given an integer array nums of size n and an integer k.

A subarray is a contiguous part of the array.

Your task is to count the total number of subarrays whose XOR is exactly equal to k.

Return the count.
```
Example 1
Input:
nums = [4, 2, 2, 6, 4]
k = 6

Output:
4
```
**Explanation:**

The subarrays with XOR = 6 are:

[4,2]
[2,2,6]
[6]
[6,4]
```
Example 2
Input:
nums = [5, 6, 7, 8, 9]
k = 5

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

    int count = 0;
    int prefixXor = 0;

    for(auto val : nums) {
        prefixXor ^= val;

        if(freq.find(prefixXor ^ k) != freq.end())
            count += freq[prefixXor ^ k];

        freq[prefixXor]++;
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

    cout << "There are " << countSubarrays(nums, k) << " subarrays with XOR " << k;

    return 0;
}
```

### Complexity

**Time Complexity:** ```O(n)```

**Space Complexity:** ```O(n)```
