## Problem

Given an integer array ```nums```, find all unique combinations of ```k``` elements whose sum equals ```target```.
Uniqueness is defined by **values**, not indices.

**Core Idea**

**K-Sum = Fix one element + (K-1)-Sum**

Instead of writing multiple nested loops, use **recursion** to fix elements until the problem reduces to **2-Sum**, which is solved using **two pointers**.

**Why Sorting Is Mandatory**

- Enables two-pointer technique
- Groups duplicates together
- Makes duplicate skipping deterministic
- Allows optimal time complexity

```
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> kSumHelper(vector<int>& nums, long long target, int k, int start) {
            vector<vector<int>> res;
            int n = nums.size();

            // Base case: 2-Sum using two pointers
            if (k == 2) {
                int left = start, right = n - 1;

                while (left < right) {
                    long long sum = (long long)nums[left] + nums[right];

                    if (sum < target) {
                        left++;
                    }
                    else if (sum > target) {
                        right--;
                    }
                    else {
                        res.push_back({nums[left], nums[right]});

                        int lVal = nums[left];
                        int rVal = nums[right];

                        while (left < right && nums[left] == lVal) left++;
                        while (left < right && nums[right] == rVal) right--;
                    }
                }
                return res;
            }

            // Recursive case: reduce K-Sum → (K-1)-Sum
            for (int i = start; i <= n - k; i++) {

                // Skip duplicate fixed values
                if (i > start && nums[i] == nums[i - 1]) continue;

                vector<vector<int>> subResults =
                    kSumHelper(nums, target - nums[i], k - 1, i + 1);
                    
                for (auto& subset : subResults) {
                    subset.insert(subset.begin(), nums[i]);
                    res.push_back(subset);
                }
            }

    return res;
}

vector<vector<int>> kSum(vector<int>& nums, int target, int k) {
    sort(nums.begin(), nums.end());
    return kSumHelper(nums, target, k, 0);
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
    
    int target;
    cin >> target;

    vector<vector<int>> res = kSum(nums, target, k);

    for(int i=0; i<res.size(); i++) {
        cout << "[";
        for(int j=0; j<res[0].size(); j++) {
            cout << res[i][j] << " ";
        }
        cout << "]" << endl;
    }

    return 0;
}
```

**Time & Space Complexity**

**Time:** ```O(n^(k−1))```

**Space:** ```O(k)``` recursion stack (excluding output)

Examples:

- 2-Sum → ```O(n)```
- 3-Sum → ```O(n²)```
- 4-Sum → ```O(n³)```

*Fix one element at each step and reduce K-Sum to 2-Sum, handling duplicates by skipping repeated values.*
