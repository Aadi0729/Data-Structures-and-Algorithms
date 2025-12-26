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

If two numbers have the same remainder r when divided by k, then they can be written as:
```
Number1 = a*k + r
Number2 = b*k + r
```

Subtracting them:
```
Number2 − Number1
= (b*k + r) − (a*k + r)
= (b − a) * k
```

Which is clearly divisible by k.

```
It’s a mathematical property: if two numbers have the same remainder modulo k, their difference must be a multiple of k. That’s why matching prefix sum remainders guarantees a subarray divisible by k.
```
## When rem < 0:
**Why adding k is sufficient (general proof)**

Suppose:

𝑟 = 𝑎 % 𝑘 

From C++ rules:

−𝑘 < 𝑟 < 𝑘

So the only invalid case is:

r < 0 ⇒ −k < r < 0

Now add k:

r + k ∈ (0,k)

So:

0 ≤ r + k < k

Which is exactly the mathematical remainder range.

Therefore:

If r<0, then r+k is the unique mathematical remainder

### NOTE: Adding k works because negative remainders already lie in (-k, 0), and shifting by one full modulo cycle places them into the unique canonical range [0, k-1] without changing their equivalence class.
