**Problem**

Given an integer array ```nums```, return all unique triplets
```[nums[i], nums[j], nums[k]]``` such that:

- ```i ≠ j```, ```i ≠ k```, and ```j ≠ k```
- ```nums[i] + nums[j] + nums[k] = 0```
- The solution set *must not contain duplicate triplets*

**Important Notes**

- The order of numbers inside a triplet does not matter.
- The order of triplets in the output does not matter.
- Duplicate triplets are not allowed, even if they come from different indices.

**Input Format**

- An integer array ```nums``` of length ```n```
- ```3 ≤ n ≤ 3000```
- ```-10⁵ ≤ nums[i] ≤ 10⁵```

**Output Format**

- Return a list of unique triplets where the sum of elements is ```0```.

**Example 1**
**Input**
```
nums = [-1, 0, 1, 2, -1, -4]
```

**Output**
```
[[-1, -1, 2], [-1, 0, 1]]
```

**Explanation**

Possible triplets whose sum is zero:

- ```(-1, -1, 2)```
- ```(-1, 0, 1)```

Triplet ```(-1, 0, 1)``` appears multiple times via different indices but is included only once.

**Example 2**
**Input**
```
nums = [0, 0, 0, 0]
```

**Output**
```
[[0, 0, 0]]
```

**Explanation**

Although there are multiple index combinations, only one unique triplet is allowed.

**Example 3**
**Input**
```
nums = [1, 2, -2, -1]
```

**Output**
```
[]
```

**Explanation**

No three numbers sum to zero.

```
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> threeSum(vector<int>& nums, int target) {
    int n = nums.size();

    set<vector<int>> st;

    for(int i=0; i<n; i++) {
        for(int j=i+1; j<n; j++) {
            for(int k=j+1; k<n; k++) {
                int sum = nums[i] + nums[j] + nums[k];

                if(sum == target) {
                    vector<int> triplet = {nums[i], nums[j], nums[k]};
                    sort(triplet.begin(), triplet.end());
                    st.insert(triplet);
                }
            }
        }
    }
    return vector<vector<int>>(st.begin(), st.end());
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

**Follow-Up Questions (Interview Context)**

1. Can you solve this in less than O(n³) time?
2. How do you avoid duplicate triplets?
3. Why is sorting helpful here?
4. Can this pattern be extended to 4-Sum?
