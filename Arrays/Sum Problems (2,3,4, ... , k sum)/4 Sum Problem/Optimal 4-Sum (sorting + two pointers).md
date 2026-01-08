4-Sum is solved optimally by sorting the array, fixing two elements, applying the two-pointer technique on the remaining part, 
and skipping duplicates at every level to ensure unique quadruplets.

```
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> fourSum(vector<int>& nums, int target) {
    int n = nums.size();

    vector<vector<int>> res;
    sort(nums.begin(), nums.end());

    for(int i=0; i<n-3; i++) {

        if(i > 0 && nums[i] == nums[i-1]) continue;
        for(int j=i+1; j<n-2; j++) {

            if(j > i+1 && nums[j] == nums[j-1]) continue;

            int left = j+1;
            int right = n-1;

            while(left < right) {
                long long sum = (long long)nums[i] + nums[j] + nums[left] + nums[right];

                if(sum > target)
                    right--;
                else if(sum < target)
                    left++;
                else {
                    res.push_back({nums[i], nums[j], nums[left], nums[right]});

                    int lVal = nums[left];
                    int rVal = nums[right];

                    while(left < right && nums[left] == lVal) left++;
                    while(left < right && nums[right] == rVal) right--; 
                }
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

**Time Complexity:** ```O(n³)```

Two nested loops fix the first two elements, and a two-pointer scan runs in linear time for each fixed pair, resulting in ```O(n³)``` overall time complexity.

**Space Complexity:** ```O(1)``` (excluding output)

No extra data structures are used besides the result container.
