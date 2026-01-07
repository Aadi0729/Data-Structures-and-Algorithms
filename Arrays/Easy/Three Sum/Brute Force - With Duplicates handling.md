## IDEA

1. Sort each valid triplet
2. Store it in a ```set```
3. Convert the set back to a vector

Why this is correct:

- Sorting normalizes order (```{-1,0,1}``` always looks the same)

- ```set``` guarantees uniqueness

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
**Time Complexity:** ```O(n³ log M)```
where ```M``` = number of unique triplets
(```log M``` comes from set insertion)

**Space Complexity:**
```O(M)``` for storing unique triplets

This is correct but inefficient, and that inefficiency is exactly why we optimize later.

```
In brute force, duplicates are unavoidable because the same values can come from different index combinations.
To fix this, I sort each triplet and store it in a set, but this increases space and time complexity.
That’s why we move to sorting + two pointers, where duplicates are handled implicitly.
```

**Follow-Up Questions (Interview Context)**

1. Can you solve this in less than O(n³) time?
2. How do you avoid duplicate triplets?
3. Why is sorting helpful here?
4. Can this pattern be extended to 4-Sum?
