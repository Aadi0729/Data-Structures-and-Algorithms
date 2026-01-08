**Approach:**

Fix one element and reduce the remaining problem to 2-Sum using a hash set.
To avoid duplicate triplets, sort each valid triplet and store it in a global set.

**Limitations:**
This approach requires extra space and relies on a set to remove duplicates after generation.

**Conclusion:**
Although correct, sorting + two pointers is preferred because it avoids duplicates intrinsically and uses constant extra space.

```
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> threeSum(vector<int>& nums, int target) {
    int n = nums.size();

    set<vector<int>> set1; // to avoid duplicate triplets globally

    for(int i=0; i<n; i++) {

        set<int> set2; // to detect complements for current i

        for(int j=i+1; j<n; j++) {
            int val = target-nums[i]-nums[j];

            if(set2.find(val) != set2.end()) {
                vector<int> triplet = {nums[i], nums[j], val};
                sort(triplet.begin(), triplet.end());
                set1.insert(triplet);
            }

            set2.insert(nums[j]);
        }
    }

    return vector<vector<int>>(set1.begin(), set1.end());
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

## Why this approach is still NOT preferred ?

**Reason 1: Duplicate handling is indirect**

- You generate duplicates
- Then rely on set to clean them

Optimal solutions avoid generating duplicates in the first place.

**Reason 2: Extra space is unavoidable**

- Hash set for each i
- Global set for results

Sorting + two pointers:

- No hashing
- No global set
- O(1) extra space (excluding output)

**Reason 3: Hard to extend cleanly**

For 4-Sum:

- Hashing becomes extremely messy
- Sorting + pointers extends naturally

```
Time: O(n² · log M)
Space: O(n + M)
```
