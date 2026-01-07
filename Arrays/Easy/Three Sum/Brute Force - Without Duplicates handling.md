This brute-force solution **does NOT handle duplicates**, which is a **core requirement of 3-Sum**.

```
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> threeSum(vector<int>& nums, int target) {
    int n = nums.size();

    vector<vector<int>> temp;

    for(int i=0; i<n; i++) {
        for(int j=i+1; j<n; j++) {
            for(int k=j+1; k<n; k++) {
                int sum = nums[i] + nums[j] + nums[k];

                if(sum == target)
                    temp.push_back({nums[i], nums[j], nums[k]});       
            }
        }
    }
    return temp;
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

**Time:** ```O(n³)```
**Space:** ```O(1)``` auxiliary (ignoring output)
