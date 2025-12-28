## Problem Statement

You are given an integer array nums and an integer p.

You are allowed to remove exactly one contiguous subarray (possibly empty) from the array.

After removing this subarray, the sum of the remaining elements must be divisible by p.

Your task is to return the length of the shortest subarray that can be removed so that the remaining sum is divisible by p.

If it is not possible, return -1.
```
Example 1
Input:
nums = [3,1,4,2]
p = 6

Output:
1
```
**Explanation:**

Total sum = 10

10 % 6 = 4

Removing subarray [4] makes remaining sum 6, which is divisible by 6
```
Example 2
Input:
nums = [6,3,5,2]
p = 9

Output:
2
```
```
Example 3
Input:
nums = [1,2,3]
p = 3

Output:
0
```
**Explanation:**

Total sum is already divisible by 3

No need to remove anything

## SOLUTION
```
#include <bits/stdc++.h>
using namespace std;

int shortestSubarray(vector<int>& nums, int p) {
    int n = nums.size();

    int totalSum = 0;
    for(auto val : nums)
        totalSum += val;

    int rem = totalSum % p;
    if(rem == 0)
        return 0;

    unordered_map<int, int> mpp;
    mpp[0] = -1;

    int prefixSum = 0;
    int minLen = n;

    for(int i=0; i<n; i++) {
        prefixSum += nums[i];
        int currRem = prefixSum % p;
        if(mpp.find((currRem - rem + p)%p) != mpp.end()) {
            minLen = min(minLen, i-mpp[(currRem - rem + p)%p]);
        }
        mpp[currRem] = i;
    }

    return minLen == n ? -1 : minLen;
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

    int p;
    cin >> p;

    cout << "The shortest subarray length is " << shortestSubarray(nums, p) << " that can be removed so that the remaining sum is divisible by " << p;

    return 0;
}
```

## Time & Space Complexity

**Time Complexity:** ```O(n)```

**Space Complexity:** ```O(n)```

### Core Idea

- If ```totalSum % p = r```, then the array has an offset ```r``` from divisibility.
- To fix this, remove a subarray whose sum has remainder ```r``` modulo ```p```.
- We do not remove exact sum ```r```; we remove any sum in remainder class ```r```.

### Why Prefix Sum + Modulo

- Subarray sum = ```prefixSum[j] - prefixSum[i]```
- We want:
```
(prefixSum[j] - prefixSum[i]) % p = r
```
- Rearranged:
```
prefixSum[i] % p = (prefixSum[j] % p - r + p) % p
```

### What We Track

- ```currRem = prefixSum % p```
- ```need = (currRem - r + p) % p```
- A hashmap storing:
```
remainder -> latest index
```

### Algorithm Steps

1. Compute ```totalSum % p = r```

2. If ```r == 0```, return ```0```

3. Initialize map with ```{0 : -1}```

4. Traverse array:

- Update ```prefixSum```
- Compute ```currRem```
- Compute ```need```
- If ```need``` exists → update shortest length
- Store ```currRem``` with current index

5. If no valid subarray found → return ```-1```

### Important Insights

- ```currRem == r``` only finds subarrays starting at index ```0``` (insufficient).
- Checking ```need``` finds subarrays starting anywhere.
- Store the latest index to get the shortest subarray.
- Always normalize modulo to avoid negatives.

### One-Line Mental Lock

We remove a remainder offset, not an exact value.
