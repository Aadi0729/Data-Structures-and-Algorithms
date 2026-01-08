## 4-Sum using Fix Two Elements + Hashing (Intermediate)

Two elements are fixed using nested loops, and the remaining problem is reduced to detecting a complement using hashing.

A global set is used to store sorted quadruplets to ensure uniqueness.

Although correct, this approach requires extra space and explicit duplicate handling, which motivates the optimal sorting + two-pointer solution.

```
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> fourSum(vector<int>& nums, int target) {
    int n = nums.size();

    set<vector<int>> set1; // O(M) → stored unique quadruplets (output-dependent)

    // O(n³ · log M) → M = number of unique quadruplets
    for(int i=0; i<n; i++) {
        for(int j=i+1; j<n; j++) {

            set<int> set2; // O(n) → hashing for the third loop

            for(int k=j+1; k<n; k++) {
                int val = target - nums[i] - nums[j] - nums[k];

                if(set2.find(val) != set2.end()) {
                    vector<int> quadruplet = {nums[i], nums[j], nums[k], val};
                    sort(quadruplet.begin(), quadruplet.end());
                    set1.insert(quadruplet);
                }

                set2.insert(nums[k]);
            }
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

**Time Complexity:** ```O(n³ · log M)```, where ```M``` is the number of unique quadruplets.

**Space Complexity:** ```O(n + M)``` — ```O(n)``` for the hash set used during iteration and ```O(M)``` for storing unique quadruplets.
