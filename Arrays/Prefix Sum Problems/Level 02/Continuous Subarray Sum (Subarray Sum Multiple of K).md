## Problem Statement

You are given an integer array nums and an integer k.

A subarray is a contiguous part of the array.

Your task is to determine whether there exists a subarray of length at least 2 whose sum is a multiple of k.

Return: 
true if such a subarray exists
false otherwise
```
Example 1
Input:
nums = [23, 2, 4, 6, 7]
k = 6

Output:
true
```
**Explanation:**

The subarray [2, 4] has sum 6, which is divisible by 6.
```
Example 2
Input:
nums = [23, 2, 6, 4, 7]
k = 6

Output:
true
```

**Explanation:**
The subarray [23, 2, 6, 4, 7] has sum 42, which is divisible by 6.
```
Example 3
Input:
nums = [1, 2, 3]
k = 5

Output:
false
```

## SOLUTION
```
#include <bits/stdc++.h>
using namespace std;

bool checkSubarray(vector<int>& nums, int k) {
    int n = nums.size();

    if(k == 0) {
        for(int i=1; i<n; i++) {
            if(nums[i] == 0 && nums[i-1] == 0)
                return true;
        }

        return false;
    }

    unordered_map<int, int> mpp;
    mpp[0] = -1; // virtual prefix remainder

    int prefixSum = 0;
    for(int i=0; i<n; i++) {
        prefixSum += nums[i];
        int rem = prefixSum % k;

        if(rem < 0)
            rem += k;

        if(mpp.find(rem) != mpp.end()) {
            if(i-mpp[rem] >= 2)
                return true;
        }
        else
            mpp[rem] = i; // store first occurrence
    }
    return false;
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

    bool res = checkSubarray(nums, k);

    if(res)
        cout << "There exists subarray of length atleast 2 with sum multiple of " << k;
    else
        cout << "Doesn't exist.";

    return 0;
}
```

**Complexity**

**Time Complexity: ```O(n)```**

**Space Complexity: ```O(n)```**
