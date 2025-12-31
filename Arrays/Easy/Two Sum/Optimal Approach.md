### Sorting + Two Pointers (Index-Safe Version)

Problem: Sorting destroys original indices
Fix: Store (value, index) pairs

```
#include <bits/stdc++.h>
using namespace std;

pair<int, int> twoSum(vector<int>& nums, int target) {
    int n = nums.size();

    // Creating a {Value, Index} array
    vector<pair<int, int>> temp;

    for(int i=0; i<n; i++) {
        temp.push_back({nums[i], i});
    }

    // Sort the created array based on Values, Indices stay the same
    // Sorting happens on .first (value) & .second (original index) stays correct
    sort(temp.begin(), temp.end());

    int i=0;
    int j=n-1;
    while(i < j) {
        int sum = temp[i].first + temp[j].first;
        if(sum > target)
            j--;
        else if(sum < target)
            i++;
        else
            return {temp[i].second, temp[j].second};
    }

    return {-1,-1};
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

    pair<int, int> res = twoSum(nums, target);

    if(res.first == 0 && res.second == 0)
        cout << "Doesn't exist...";
    else
        cout << "The indices of the two numbers which add up to " << target << " are [" << res.first << ", " << res.second << "]";

    return 0;
}
```

**Steps:**

- Create (value, index) array
- Sort by value
- Use two pointers on values
- Return stored original indices

**TC**: ```O(n log n)```

**SC**: ```O(n)```
