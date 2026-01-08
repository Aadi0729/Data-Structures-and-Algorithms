**Key Idea**

- Sort the array once.
- Fix one element.
- Use two pointers (```left```, ```right```) to find pairs that complete the triplet.

**Why Sorting Is Essential**

- Groups duplicate values together.
- Enables deterministic pointer movement.
- Makes duplicate elimination possible without extra data structures.

**Duplicate Handling Strategy**

Duplicates are avoided intrinsically, not post-processed.

**1. Skip duplicate fixed elements**

Fixing the same value again leads to the same target and a reduced search space, so no new unique triplets can be formed.

**2. Skip duplicate ```left``` values after finding a valid triplet**

Prevents repeating the same pair with the fixed element.

**3. Skip duplicate ```right``` values after finding a valid triplet**

Completes duplicate elimination at the pair level.

This ensures that *each unique value-based triplet is generated exactly once.*

```
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> threeSum(vector<int>& nums, int target) {
    int n = nums.size();

    vector<vector<int>> res;

    sort(nums.begin(), nums.end());

    for(int i=0; i<n-2; i++) {

        // Skip duplicate fixed elements
        if(i > 0 && nums[i] == nums[i - 1]) continue;

        int left = i+1;
        int right = n-1;;

        while(left < right) {
            int sum = nums[i] + nums[left] + nums[right];

            if(sum > target)
                right--;

            else if(sum < target)
                left++;

            else {
                res.push_back({nums[i], nums[left], nums[right]});

                int lVal = nums[left];
                int rVal = nums[right];

                // Skip duplicates
                while(left < right && nums[left] == lVal) left++;
                while(left < right && nums[right] == rVal) right--;
            }
        }
    }
    return res;
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
    
    int target;
    cin >> target;

    vector<vector<int>> res = threeSum(nums, target);

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

**Complexity**

**Time Complexity:** ```O(n²)```

**Space Complexity:** ```O(1)``` (excluding output storage)

```
3-Sum is an extension of 2-Sum using the same two-pointer idea.

The real challenge is duplicate control, not pair finding.

Hashing solutions work but require extra space and post-processing.

Sorting + two pointers provides the cleanest, most efficient solution.

The same pattern generalizes naturally to 4-Sum and K-Sum problems.
```

**IMPORTANT**
```
3-Sum is solved optimally by sorting the array, fixing one element, applying the two-pointer technique, and skipping duplicates at every level to ensure unique triplets.
```
