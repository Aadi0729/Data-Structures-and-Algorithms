## Problem

Given an integer array ```nums``` and an integer ```target```, find **all unique quadruplets**
```[nums[i], nums[j], nums[k], nums[l]]``` such that:

- ```i ≠ j ≠ k ≠ l```
- ```nums[i] + nums[j] + nums[k] + nums[l] = target```

The solution set must **not contain duplicate quadruplets**

Uniqueness is defined by **values**, not indices.

```
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> fourSum(vector<int>& nums, int target) {
    int n = nums.size();

    set<vector<int>> res;

    for(int i=0; i<n; i++) {
        for(int j=i+1; j<n; j++) {
            for(int k=j+1; k<n; k++) {
                for(int l=k+1; l<n; l++) {
                    int sum = nums[i] + nums[j] + nums[k] + nums[l];

                    if(sum == target) {
                        vector<int> quadruplet = {nums[i], nums[j], nums[k], nums[l]};
                        sort(quadruplet.begin(), quadruplet.end());

                        res.insert(quadruplet);
                    }
                }
            }
        }
    }
    return vector<vector<int>>(res.begin(), res.end());
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

    vector<vector<int>> res = fourSum(nums, target);

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

Four nested loops are used to generate all possible index quadruplets, resulting in a time complexity of ```O(n⁴)```.

To handle duplicates, each valid quadruplet is sorted and inserted into a set, which guarantees uniqueness.

Set insertion takes ```O(log M)``` time, where ```M``` is the number of unique quadruplets, making the overall time complexity ```O(n⁴ · log M)```.

The space complexity is ```O(M)``` since all unique quadruplets are stored in the set.

**Time Complexity:**	```O(n⁴ · log M)```
**Space Complexity:**	```O(M)```
