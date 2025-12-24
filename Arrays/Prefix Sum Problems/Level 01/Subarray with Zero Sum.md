## Problem Statement

You are given an integer array nums of size n.

Your task is to determine whether there exists at least one subarray whose sum is equal to 0.

Return:

true if such a subarray exists

false otherwise

**Example 1**
*Input:*
nums = [4, 2, -3, 1, 6]

*Output:*
true

*Explanation:*

The subarray:

[2, -3, 1]

has sum = 0.

**Example 2**
*Input:*
nums = [1, 2, 3, 4]

*Output:*
false

*Explanation:*

No subarray has sum 0.

**Example 3**
*Input:*
nums = [0, 1, 2]

*Output:*
true

*Explanation:*

[0]

itself is a zero-sum subarray.

## SOLUTION
```
#include <bits/stdc++.h>
using namespace std;

bool subarraySumZero(vector<int>& nums) {
    int n = nums.size();

    unordered_set<int> set;
    set.insert(0);

    int prefixSum = 0;

    for(auto val : nums) {
        prefixSum += val;

        if(set.find(prefixSum) != set.end())
            return true;
        set.insert(prefixSum);
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

    bool res = subarraySumZero(nums);

    if(res)
        cout << "true";
    else
        cout << "false";

    return 0;
}
```

**Time Complexity (TC): O(n)**

Single traversal of the array

Each insert / lookup in unordered_map or unordered_set is O(1) on average

**Space Complexity (SC): O(n)**

In the worst case, we store up to n distinct prefix sums in the map/set

```
Why do we insert 0 initially in Prefix Sum problems?

0 represents a virtual prefix sum before the array starts.

It models the sum of no elements (sum before index 0).

This allows us to correctly detect subarrays that start at index 0.

Without inserting 0, valid subarrays like [0…j] would be missed.

In maps, freq[0] = 1 enables correct counting.

In sets, inserting 0 enables existence checks.

It does not create fake subarrays — it completes the logic.

One-line takeaway

Initializing prefix sum 0 ensures subarrays starting from index 0 are handled correctly.
```
